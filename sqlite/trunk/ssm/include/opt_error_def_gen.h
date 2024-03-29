#ifndef OPT_ERROR_DEF_GEN_H
#define OPT_ERROR_DEF_GEN_H

/* DO NOT EDIT --- generated by ../../tools/errors.pl from opt_error.dat
                   on Fri Jul  8 11:47:55 2011 

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
#define OPT_IllegalDescLine       0x20000
#define OPT_IllegalClass          0x20001
#define OPT_ClassTooLong          0x20002
#define OPT_TooManyClasses        0x20003
#define OPT_Duplicate             0x20004
#define OPT_NoOptionMatch         0x20005
#define OPT_NoClassMatch          0x20006
#define OPT_Syntax                0x20007
#define OPT_BadValue              0x20008
#define OPT_NotSet                0x20009
#define OPT_OK                    0x0
#define OPT_ERRMIN                0x20000
#define OPT_ERRMAX                0x20009

#endif
