/* -*- mode:C++; c-basic-offset:4 -*-
     Shore-MT -- Multi-threaded port of the SHORE storage manager
   
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
/*<std-header orig-src='shore' incl-file-exclusion='MEMBLOCK_CPP'>

 $Id: memblock.cpp,v 1.5 2010/12/08 17:37:38 nhall Exp $

SHORE -- Scalable Heterogeneous Object REpository

Copyright (c) 1994-99 Computer Sciences Department, University of
                      Wisconsin -- Madison
All Rights Reserved.

Permission to use, copy, modify and distribute this software and its
documentation is hereby granted, provided that both the copyright
notice and this permission notice appear in all copies of the
software, derivative works or modified versions, and any portions
thereof, and that both notices appear in supporting documentation.

THE AUTHORS AND THE COMPUTER SCIENCES DEPARTMENT OF THE UNIVERSITY
OF WISCONSIN - MADISON ALLOW FREE USE OF THIS SOFTWARE IN ITS
"AS IS" CONDITION, AND THEY DISCLAIM ANY LIABILITY OF ANY KIND
FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.

This software was developed with support by the Advanced Research
Project Agency, ARPA order number 018 (formerly 8230), monitored by
the U.S. Army Research Laboratory under contract DAAB07-91-C-Q518.
Further funding for this work was provided by DARPA through
Rome Research Laboratory Contract No. F30602-97-2-0247.

*/

#include "mem_block.h"
#include "atomic_ops.h"
#include <cstdlib>
#include <algorithm>
#ifdef __linux
#include <malloc.h>
#endif
#include "test_me.h"
#include <vector>
#include <new>
#include <stdlib.h>

#define TEMPLATE_ARGS chip_size, chip_count, block_size
using namespace memory_block;

struct test_block_pool : public block_pool {
    NORET        test_block_pool(size_t chip_size, size_t chip_count,
                    size_t block_size, size_t block_count)
    : _data(block_size*(block_count+1)) // one extra for alignment
    , _acquire_count(0)
    , _release_count(0)
    , _data_size(block_size*block_count)
    {
        // align the blocks properly
        union { char* c; long n; } u = {&_data[block_size]};
        u.n &= -block_size;
        _data_start = u.c;

        // initialize all the blocks and mark them free
        for(size_t i=0; i < block_count; i++) {
            block* b = new (u.c) block(TEMPLATE_ARGS);
            _freelist.push_back(b);
            u.c += block_size;
        }
    }
    
    virtual block*     _acquire_block() {
        if(_freelist.empty())
            return 0;
        
        block* b = _freelist.back();
        _freelist.pop_back();
        _acquire_count++;
        return b;
    }
    
    // takes back b, then returns b->_next
    virtual void     _release_block(block* b) {
        _release_count++;
        _freelist.push_back(b);
    }

    // true if /ptr/ points to data inside some block managed by this pool
    virtual bool    validate_pointer(void* ptr) {
        union { void* v; char* c; } u = {ptr};
        return (u.c - _data_start) < _data_size;
    }

    std::vector<char>    _data;
    std::vector<block*>    _freelist;
    size_t        _acquire_count;
    size_t        _release_count;
    long        _data_size;
    char*        _data_start;
};


void test_block_list() {
    static size_t const chip_size = sizeof(int);
    static size_t const chip_count = 4;
    static size_t const block_size = 512;
    static size_t const block_count = 4;
    
    test_block_pool tbp(TEMPLATE_ARGS, block_count);
    void* ptr;

    {
    // create and destroy without ever allocating
    block_list bl(&tbp, TEMPLATE_ARGS);
    }

    {
    // change blocks when the current one is empty
    block_list bl(&tbp, TEMPLATE_ARGS);
    bl._change_blocks(TEMPLATE_ARGS); // clear out the fake block
    w_assert0(tbp._freelist.size() == block_count-1);

    // pretend we acquired and released everything in the block
    bl._hit_count = chip_count;
    
    // ... and ask for a new block
    bl._change_blocks(TEMPLATE_ARGS);
    w_assert0(tbp._freelist.size() == block_count-1);
    w_assert0(bl._tail == bl._tail->_next);

    // repeat, but with a too-full block
    {
        void* ptrs[chip_count-1];
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
        ptrs[i] = bl.acquire(TEMPLATE_ARGS);
        while(bl._avg_hit_rate >= (chip_count+1)/2) // matches min_allocated in _change_blocks
        bl._change_blocks(TEMPLATE_ARGS);
    
        w_assert0(tbp._freelist.size() == block_count-2);
        w_assert0(bl._tail == bl._tail->_next->_next);
    
        // now free all those pointers to create a run
        bl._hit_count = chip_count;
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
            block::release_chip(ptrs[i], TEMPLATE_ARGS);
        bl._change_blocks(TEMPLATE_ARGS);
        w_assert0(tbp._freelist.size() == block_count-1);
        w_assert0(bl._tail == bl._tail->_next);
    }

    // run of three?
    {
        // acquire two full runs worth of objects
        void* ptrs[2*chip_count];
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
            ptrs[i] = bl.acquire(TEMPLATE_ARGS);
        
        // should loop over the full blocks until it realizes it needs more
        ptr = bl.acquire(TEMPLATE_ARGS);
        block::release_chip(ptr, TEMPLATE_ARGS);
        
        w_assert0(tbp._freelist.size() == block_count-3);
        w_assert0(bl._tail == bl._tail->_next->_next->_next);
    
        // now free all those pointers to create a run
        bl._hit_count = chip_count;
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
        block::release_chip(ptrs[i], TEMPLATE_ARGS);
        bl._change_blocks(TEMPLATE_ARGS);
        w_assert0(tbp._freelist.size() == block_count-1);
        w_assert0(bl._tail == bl._tail->_next);
    }

    // run of two in list of three?
    {
        // acquire two full runs worth of objects
        void* ptrs[2*chip_count];
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
        ptrs[i] = bl.acquire(TEMPLATE_ARGS);
        
        // sholud loop over the full blocks until it realizes it needs more
        ptr = bl.acquire(TEMPLATE_ARGS);
        
        w_assert0(tbp._freelist.size() == block_count-3);
        w_assert0(bl._tail == bl._tail->_next->_next->_next);
    
        // now free all those pointers to create a run
        bl._hit_count = chip_count;
        for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++)
        block::release_chip(ptrs[i], TEMPLATE_ARGS);
        bl._change_blocks(TEMPLATE_ARGS);
        w_assert0(tbp._freelist.size() == block_count-2);
        w_assert0(bl._tail == bl._tail->_next->_next);
        block::release_chip(ptr, TEMPLATE_ARGS);
    }
    }

    // allocate a single value
    {
        block_list bl(&tbp, TEMPLATE_ARGS);
        ptr = bl.acquire(TEMPLATE_ARGS);
        w_assert0(ptr);
        w_assert0(tbp._freelist.size() == block_count-1);
    }
    
    // release a value after its originating block_list dies
    w_assert0(tbp._freelist.size() == block_count);
    block::release_chip(ptr, TEMPLATE_ARGS);

    // spill over but with the first block having space
    {
    block_list bl(&tbp, TEMPLATE_ARGS);
    for(size_t i=0; i < chip_count+1; i++) {
        ptr = bl.acquire(TEMPLATE_ARGS);
        w_assert0(ptr);
        block::release_chip(ptr, TEMPLATE_ARGS);
    }
    w_assert0(tbp._freelist.size() == block_count-1);
    }
    w_assert0(tbp._freelist.size() == block_count);
    
    // request a second block
    {
    block_list bl(&tbp, TEMPLATE_ARGS);
    void* ptrs[chip_count+1];
    for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++) {
        ptrs[i] = bl.acquire(TEMPLATE_ARGS);
        w_assert0(ptrs[i]);
    }
    for(size_t i=0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++) {
        block::release_chip(ptrs[i], TEMPLATE_ARGS);
    }
    w_assert0(tbp._freelist.size() == block_count-2);
    }
    // destroy list having two blocks
    w_assert0(tbp._freelist.size() == block_count);

}

template<class T>
static void print_info() {
    printf("ChipSize: %zd   Overhead: %zd   block: %d       chips: %d\n",
       T::CHIP_SIZE, T::OVERHEAD, T::BYTES, T::COUNT);
}

void test_helper_templates() {
    /*
      fail_unless, bounds_check
    */
    fail_unless<true>::valid();
    // compile error
    //fail_unless<false>::valid();

    /*
      log2...
     */
    w_assert0(meta_log2<1>::VALUE == 0);
    
    w_assert0(meta_log2<2>::VALUE == 1);
    w_assert0(meta_log2<3>::VALUE == 1);
    
    w_assert0(meta_log2<4>::VALUE == 2);
    w_assert0(meta_log2<5>::VALUE == 2);
    w_assert0(meta_log2<6>::VALUE == 2);
    w_assert0(meta_log2<7>::VALUE == 2);
    
    w_assert0(meta_log2<8>::VALUE == 3);

    // compile error
    //meta_log2<0>();

    // compile error
    //meta_log2<-1>();

    /*
      block_size

      running the following bash script produces a fairly exhaustive
      set of tests:
      
      for size in $(seq 1 40); do
          for overhead in $(seq 1 40); do
          echo "print_info< meta_block_size<$size, $overhead> >();"
      done
      done > block_size_test.cpp
     */
    //#include "block_size_test.cpp"

    // specific examples which have exposed bugs in the past
    meta_block_size<1,127>();
    meta_block_size<2,31>();
    meta_block_size<4, 32>();
    meta_block_size<4, 7>();
    meta_block_size<31, 3,64>();
}

void test_block() {
    static size_t const max_bits = block_bits::MAX_CHIPS;
    static size_t const chip_size = sizeof(int);
    static size_t const chip_count = max_bits-(sizeof(block)+chip_size-1)/chip_size;
    static size_t const block_size = chip_size*max_bits;
    
    // n-bit bitmap can't fit n+1 bits
    EXPECT_ASSERT(block(sizeof(int),max_bits+1,512));
    // n ints + overhead won't fit in 128 bytes
    EXPECT_ASSERT(block(sizeof(int),max_bits,block_size));
    // but n - sizeof(block)/sizeof(int) should work
    block* bptr = new (memalign(8*sizeof(block_bits::bitmap)*sizeof(int), block_size))
    block(chip_size, chip_count, block_size);
    block &b = *bptr;
    
    // try to acquire too many times
    for(size_t i=0; i < chip_count; i++) {
        void* ptr = b.acquire_chip(TEMPLATE_ARGS);
        w_assert0(0 != ptr);
        block::release_chip(ptr, TEMPLATE_ARGS);
    }
    w_assert0(0 == b.acquire_chip(TEMPLATE_ARGS));
    
    // double free
    EXPECT_ASSERT(block::release_chip(b._get(0, chip_size), TEMPLATE_ARGS));
    // release non-aligned ptr
    EXPECT_ASSERT(block::release_chip(b._get(1, chip_size/2), TEMPLATE_ARGS));    

    // test full recycling
    b.recycle();
    w_assert0(b._bits.usable_count() == chip_count);
    w_assert0(b._bits.zombie_count() == 0);

    // partial recycling
    size_t release_count = 8;
    for(size_t i=release_count; i < chip_count; i++) {
        void* ptr = b.acquire_chip(TEMPLATE_ARGS);
        if(! (i%2)) {
            release_count++;
            block::release_chip(ptr, TEMPLATE_ARGS);
        }
    }
    b.recycle();
    w_assert0(b._bits.usable_count() == release_count);
    w_assert0(b._bits.zombie_count() == 0);

    // release after recycling
    for(size_t i=0; i < chip_count-release_count; i++) {
        if(i % 2) {
            void* ptr = b._get(i, chip_size);
            block::release_chip(ptr, TEMPLATE_ARGS);
        }
    }
}


int main() {
    test_block();
    test_helper_templates();
    test_block_list();
    return 0;
}

