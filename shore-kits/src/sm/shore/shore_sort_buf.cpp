/* -*- mode:C++; c-basic-offset:4 -*-
     Shore-kits -- Benchmark implementations for Shore-MT
   
                       Copyright (c) 2007-2009
      Data Intensive Applications and Systems Labaratory (DIAS)
               Ecole Polytechnique Federale de Lausanne
   
                         All Rights Reserved.
   
   Permission to use, copy, modify and distribute this software and
   its documentation is hereby granted, provided that both the
   copyright notice and this permission notice appear in all copies of
   the software, derivative works or modified versions, and any
   portions thereof, and that both notices appear in supporting
   documentation.
   
   This code is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. THE AUTHORS
   DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER
   RESULTING FROM THE USE OF THIS SOFTWARE.
*/

/** @file shore_sort_buf.cpp
 *
 *  @brief Implementation of comparison functions for sort_buffer_t 
 *
 *  @author: Ippokratis Pandis, Sept 2008
 *
 */

#include "sm/shore/shore_sort_buf.h"

using namespace shore;



const int MIN_TUPLES_FOR_SORT = 250;


/**********************************************************************
 * 
 * Implementation of Comparison functions
 *
 * @input:  obj1, obj2 of the same type, casted to (const void*)
 *
 * @return: 1 iff obj1>obj2, 0 iff obj1==obj2, -1 iff obj1<obj2
 * 
 * @note:   Currently only INT and SMALLINT types supported (both fixed 
 *          legnth)
 *
 **********************************************************************/


int compare_smallint(const void* d1, const void* d2)
{
    short data1 = *((short*)d1);
    short data2 = *((short*)d2);
    if (data1 > data2) return (1);
    if (data1 == data2) return (0);
    return (-1);
}


int compare_int(const void* d1, const void* d2)
{
    int data1 = *((int*)d1);
    int data2 = *((int*)d2);
    if (data1 > data2) return (1);
    if (data1 == data2) return (0);
    return (-1);
}


int compare_bit(const void* d1, const void* d2)
{
    int data1 = *((bool*)d1);
    int data2 = *((bool*)d2);
    if (data1 > data2) return (1);
    if (data1 == data2) return (0);
    return (-1);
}

int compare_char(const void* d1, const void* d2)
{
    char data1 = *((char*)d1);
    char data2 = *((char*)d2);
    if (data1 > data2) return (1);
    if (data1 == data2) return (0);
    return (-1);
}


template <typename T>
int compare(const void* d1, const void* d2)
{
    T data1 = *((T*)d1);
    T data2 = *((T*)d2);
    if (data1 > data2) return (1);
    if (data1 == data2) return (0);
    return (-1);
}

/**********************************************************************
 *
 * sort_buffer_t methods
 *
 **********************************************************************/


/********************************************************************* 
 *
 *  @fn:    init
 *  
 *  @brief: Calculate the tuple size and allocate the initial memory
 *          buffer for the tuples.
 *
 *********************************************************************/

void sort_man_impl::init()
{
    assert (_ptable);

    /* calculate tuple size */
    _tuple_size = 0;

    //for (int i=0; i<_tuple_count; i++)
    for (uint_t i=0; i<_ptable->field_count(); i++)
        _tuple_size += _ptable->desc(i)->fieldmaxsize();

    /* allocate size for MIN_TUPLES_FOR_SORT tuples */
    assert (!_sort_buf); // ensure that it will be init only once 
    assert (_tuple_count==0);
    assert (_buf_size==0);
    _sort_buf = new char[MIN_TUPLES_FOR_SORT*_tuple_size]; 
    _buf_size = MIN_TUPLES_FOR_SORT;

    _is_sorted = false;
}



/********************************************************************* 
 *
 *  @fn:    reset
 *  
 *  @brief: Clear the buffer and wait for new tuples
 *
 *********************************************************************/

void sort_man_impl::reset()
{
    assert (_ptable);
    // the soft_buf should be set
    assert (_sort_buf);
    // if buf_size>0 means that the manager has already been set
    assert (_buf_size); 
    // no need to calculate tuple size
    assert (_tuple_size);

    // memset the buffer
    memset(_sort_buf, 0, _buf_size);
    _is_sorted = false;
}


/********************************************************************* 
 *
 *  @fn:    add_tuple
 *  
 *  @brief: Inserts a new tuple in the buffer. If there is not enough
 *          space, it doubles the allocated space.
 *
 *********************************************************************/

void sort_man_impl::add_tuple(sorter_tuple& atuple)
{
    CRITICAL_SECTION(cs, _sorted_lock);

    /* setup the tuple size */
    if (!_tuple_size) init();

    /* check if more space is needed */
    if (_buf_size == _tuple_count) {
        /* double the buffer size if needed */
        char* tmp = new char[(2*_buf_size)*_tuple_size];
        memcpy(tmp, _sort_buf, _buf_size*_tuple_size);
        delete [] _sort_buf;

        _sort_buf = tmp;
        _buf_size *= 2;

        //fprintf(stderr,"+\n");
    }

    /* add the current tuple to the end of the buffer */
    format(&atuple, *_preprow);
    assert (_preprow->_dest);
    memcpy(_sort_buf+(_tuple_count*_tuple_size), _preprow->_dest, _tuple_size);
    _tuple_count++;
    _is_sorted = false;
}


/********************************************************************* 
 *
 *  @fn:   sort
 *  
 *  @note: Uses the old qsort // TODO: use sort() 
 *
 *********************************************************************/

void sort_man_impl::sort()
{
    CRITICAL_SECTION(cs, _sorted_lock);

    /* compute the number of bytes used in sorting */
#if 0
    // displays buffer before/after sorting
    cout << "Before sorting: " << endl;
    switch (_ptable->desc(0)->type()) {
    case SQL_BIT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((bool*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    case SQL_SMALLINT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((short*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    case SQL_INT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((int*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    }
    cout << endl;

#endif

    // does the sorting
    switch (_ptable->desc(0)->type()) {
    case SQL_BIT:
        qsort(_sort_buf, _tuple_count, _tuple_size, compare_bit); break;
    case SQL_SMALLINT:
        qsort(_sort_buf, _tuple_count, _tuple_size, compare_smallint); break;
    case SQL_CHAR:
        qsort(_sort_buf, _tuple_count, _tuple_size, compare_char); break;
    case SQL_INT:
        qsort(_sort_buf, _tuple_count, _tuple_size, compare_int); break;
    default: 
        /* not implemented yet */
        assert(0);
    }
    _is_sorted = true;

#if 0
    cout << "After sorting: " << endl;
    switch (_ptable->desc(0)->type()) {
    case SQL_BIT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((bool*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    case SQL_SMALLINT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((short*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    case SQL_INT:
        for (int i=0; i<_tuple_count; i++) {
            cout << ((int*)(_sort_buf+i*_tuple_size))[0] << " ";
        };
        break;
    }
    cout << endl;
#endif
}

    
/********************************************************************* 
 *
 *  @fn:    get_sort_iter
 *  
 *  @brief: Initializes a sort_scan_impl for the particular sorter buffer
 *
 *  @note:  It is responsibility of the caller to de-allocate
 *
 *********************************************************************/

w_rc_t sort_man_impl::get_sort_iter(ss_m* db,
                                    sort_iter_impl* &sort_iter)
{
    sort_iter = new sort_iter_impl(db, _pspecifictable, this);
    return (RCOK);
}
     


/********************************************************************* 
 *
 *  @fn:    get_sorted
 *  
 *  @brief: Returns the tuple in the buffer pointed by the index
 *
 *  @note:  It asserts if the buffer is not sorted
 *
 *********************************************************************/

bool sort_man_impl::get_sorted(const int index, sorter_tuple* ptuple)
{
    CRITICAL_SECTION(cs, _sorted_lock);

    if (_is_sorted) {
        if (index >=0 && index < _tuple_count) {
            return (load(ptuple, _sort_buf + (index*_tuple_size)));
        }
        //TRACE( TRACE_DEBUG, "out of bounds index...\n");
        return (false);
    }
    TRACE( TRACE_DEBUG, "buffer not sorted yet...\n");
    return (false);
}

