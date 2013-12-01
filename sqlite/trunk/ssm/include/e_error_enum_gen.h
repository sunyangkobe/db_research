#ifndef E_ERROR_ENUM_GEN_H
#define E_ERROR_ENUM_GEN_H

/* DO NOT EDIT --- generated by ../../tools/errors.pl from e_error.dat
                   on Fri Jul  8 11:47:59 2011 

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
enum {
    eUSERABORT                = 0x80000,
    eCRASH                    = 0x80001,
    eOUTOFSPACE               = 0x80002,
    eALIGNPARM                = 0x80003,
    eBADSTID                  = 0x80004,
    eFRAMENOTFOUND            = 0x80005,
    eSPACENOTFOUND            = 0x80006,
    eBADPID                   = 0x80007,
    eBADVOL                   = 0x80008,
    eVOLTOOLARGE              = 0x80009,
    eDEVTOOLARGE              = 0x8000a,
    eDEVICEVOLFULL            = 0x8000b,
    eDEVNOTMOUNTED            = 0x8000c,
    eALREADYMOUNTED           = 0x8000d,
    eVOLEXISTS                = 0x8000e,
    eBADFORMAT                = 0x8000f,
    eNVOL                     = 0x80010,
    eEOF                      = 0x80011,
    eDUPLICATE                = 0x80012,
    eBADSTORETYPE             = 0x80013,
    eBADSTOREFLAGS            = 0x80014,
    eBADNDXTYPE               = 0x80015,
    eBADSCAN                  = 0x80016,
    eWRONGKEYTYPE             = 0x80017,
    eNDXNOTEMPTY              = 0x80018,
    eBADKEYTYPESTR            = 0x80019,
    eBADKEY                   = 0x8001a,
    eBADCMPOP                 = 0x8001b,
    eOUTOFLOGSPACE            = 0x8001c,
    eRECWONTFIT               = 0x8001d,
    eBADSLOTNUMBER            = 0x8001e,
    eRECUPDATESIZE            = 0x8001f,
    eBADSTART                 = 0x80020,
    eBADAPPEND                = 0x80021,
    eBADLENGTH                = 0x80022,
    eBADSAVEPOINT             = 0x80023,
    ePAGECHANGED              = 0x80024,
    eINSUFFICIENTMEM          = 0x80025,
    eBADARGUMENT              = 0x80026,
    eTWOTRANS                 = 0x80027,
    eTWOTHREAD                = 0x80028,
    eTWOUTHREAD               = 0x80029,
    eNOTRANS                  = 0x8002a,
    eINTRANS                  = 0x8002b,
    eTWOQUARK                 = 0x8002c,
    eNOQUARK                  = 0x8002d,
    eINQUARK                  = 0x8002e,
    eNOABORT                  = 0x8002f,
    eNOTPREPARED              = 0x80030,
    eISPREPARED               = 0x80031,
    eEXTERN2PCTHREAD          = 0x80032,
    eNOTEXTERN2PC             = 0x80033,
    eNOSUCHPTRANS             = 0x80034,
    eTHREADMAPFULL            = 0x80035,
    eNOTPARENTLOCK            = 0x80036,
    eBADLOCKMODE              = 0x80037,
    eLOCKTIMEOUT              = 0x80038,
    eNOTBLOCKED               = 0x80039,
    eDEADLOCK                 = 0x8003a,
    eBADCCLEVEL               = 0x8003b,
    eRETRY                    = 0x8003c,
    eFOUNDEXTTOFREE           = 0x8003d,
    eCANTWHILEACTIVEXCTS      = 0x8003e,
    eLISTTOOLONG              = 0x8003f,
    eNOHANDLE                 = 0x80040,
    eLOGVERSIONTOONEW         = 0x80041,
    eLOGVERSIONTOOOLD         = 0x80042,
    eBADMASTERCHKPTFORMAT     = 0x80043,
    eABORTED                  = 0x80044,
    eLOGSPACEWARN             = 0x80045,
    eBADCOMPENSATION          = 0x80046,
    eAPPENDFILEINOSCAN        = 0x80047,
    eINVALIDHINT              = 0x80048,
    eDUAUDITFAILED            = 0x80049,
    ePINACTIVE                = 0x8004a,
    eHOTPAGE                  = 0x8004b,
    eBPFORCEFAILED            = 0x8004c,
    eBRKKEYCMPNOTIMPL         = 0x8004d,
    eOK                       = 0x0,
    eERRMIN                   = 0x80000,
    eERRMAX                   = 0x8004d
};

#endif
