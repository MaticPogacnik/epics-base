/* $Id$
 * assertUNIX.c
 *      Author:         Jeffrey Hill 
 *      Date:           02-27-95
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
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define epicsExportSharedSymbols
#include "dbDefs.h"
#include "epicsPrint.h"
#include "epicsVersion.h"
#include "epicsAssert.h"
#include "epicsThread.h"
#include "cantProceed.h"

/*
 * epicsAssert ()
 */
epicsShareFunc void epicsShareAPI 
	epicsAssert (const char *pFile, const unsigned line, 
    const char *pExp, const char *pAuthorName)
{
	errlogPrintf (
"\n\n\nA call to \"assert (%s)\" failed in %s line %d.\n", pExp, pFile, line);

	errlogPrintf (
"The file \"core\" will be created in the current working directory.\n");

	errlogPrintf (
"Please save this file and the text of this message in order to assist\n");

	errlogPrintf (
"in diagnosing this problem.\n");

	if (pAuthorName) {

		errlogPrintf (
"Please send the text of this message to \"%s\"\n", pAuthorName);

		errlogPrintf (
"(the author of this call to assert()) or to \"tech-talk@aps.anl.gov\"\n");

	}
	else {

		errlogPrintf (
"Please contact the author of this software or else send the text of\n");

		errlogPrintf (
"this message to \"tech-talk@aps.anl.gov\"\n");

	}
	errlogPrintf ("This problem occurred in \"%s\"\n", epicsReleaseVersion);
        errlogPrintf("calling epicsThreadSuspendSelf()\n");
        epicsThreadSuspendSelf();
}

