/* devAoSoftRaw.c */
/* share/src/dev $Id$ */

/* Device Support Routines for soft raw Analog Output Records*/
/*
 *      Author:         Janet Anderson
 *      Date:           09-25-91
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 * Modification Log:
 * -----------------
 * .01  11-11-91        jba     Moved set of alarm stat and sevr to macros
 *      ...
 */

#include	<vxWorks.h>
#include	<types.h>
#include	<stdioLib.h>

#include	<alarm.h>
#include	<dbDefs.h>
#include	<dbAccess.h>
#include        <recSup.h>
#include	<devSup.h>
#include	<link.h>
#include	<special.h>
#include	<aoRecord.h>

/* Create the dset for devAoSoftRaw */
long write_ao();
struct {
	long		number;
	DEVSUPFUN	report;
	DEVSUPFUN	init;
	DEVSUPFUN	init_record;
	DEVSUPFUN	get_ioint_info;
	DEVSUPFUN	write_ao;
	DEVSUPFUN	special_linconv;
}devAoSoftRaw={
	6,
	NULL,
	NULL,
	NULL,
	NULL,
	write_ao,
	NULL};


static long write_ao(pao)
    struct aoRecord	*pao;
{
    char message[100];
    long status;

    /* ao.out must be a CONSTANT or a DB_LINK or a CA_LINK*/
    switch (pao->out.type) {
    case (CONSTANT) :
	break;
    case (DB_LINK) :
	status = dbPutLink(&pao->out.value.db_link,pao,DBR_LONG,
		&pao->rval,1L);
        if(status!=0) {
                recGblSetSevr(pao,LINK_ALARM,VALID_ALARM);
        }
	break;
    case (CA_LINK) :
	break;
    default :
        if(recGblSetSevr(pao,SOFT_ALARM,VALID_ALARM)){
		if(pao->stat!=SOFT_ALARM) {
			strcpy(message,pao->name);
			strcat(message,": devAoSoftRaw (write_ao) Illegal OUT field");
			errMessage(S_db_badField,message);
		}
	}
    }
    return(0);
}
