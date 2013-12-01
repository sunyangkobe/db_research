#ifndef STHREAD_STATS_INC_GEN_CPP
#define STHREAD_STATS_INC_GEN_CPP

/* DO NOT EDIT --- GENERATED from sthread_stats.dat by stats.pl
           on Fri Jul  8 11:47:53 2011

<std-header orig-src='shore' genfile='true'>

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

#include "w_defines.h"
/*  -- do not edit anything above this line --   </std-header>*/


sthread_stats &
operator+=(sthread_stats &s,const sthread_stats &t)
{
	s.rwlock_r_wait += t.rwlock_r_wait;
	s.rwlock_w_wait += t.rwlock_w_wait;
	s.needs_latch_condl += t.needs_latch_condl;
	s.needs_latch_uncondl += t.needs_latch_uncondl;
	s.latch_condl_nowait += t.latch_condl_nowait;
	s.latch_uncondl_nowait += t.latch_uncondl_nowait;
	return s;
}

#endif /* STHREAD_STATS_INC_GEN_CPP */
