
/* * $Id$
 *
 *                    L O S  A L A M O S
 *              Los Alamos National Laboratory
 *               Los Alamos, New Mexico 87545
 *
 *  Copyright, 1986, The Regents of the University of California.
 *
 *  Author: Jeff Hill
 */

#define epicsAssertAuthor "Jeff Hill johill@lanl.gov"

#include "iocinf.h"
#include "cac.h"
#include "virtualCircuit.h"

tcpSendWatchdog::tcpSendWatchdog 
    ( cac & cacIn, tcpiiu & iiuIn, double periodIn, epicsTimerQueue & queueIn ) :
    period ( periodIn ), timer ( queueIn.createTimer () ),
    cacRef ( cacIn ), iiu ( iiuIn )
{
}

tcpSendWatchdog::~tcpSendWatchdog ()
{
    this->timer.destroy ();
}

epicsTimerNotify::expireStatus tcpSendWatchdog::expire ( 
                 const epicsTime & /* currentTime */ )
{
#   ifdef DEBUG
        char hostName[128];
        this->iiu.hostName ( hostName, sizeof ( hostName ) );
        debugPrintf ( ( "Request not accepted by CA server %s for %g sec. Disconnecting.\n", 
            hostName, this->period ) );
#   endif
    this->cacRef.initiateAbortShutdown ( this->iiu );
    return noRestart;
}

void tcpSendWatchdog::start ()
{
    this->timer.start ( *this, this->period );
}

void tcpSendWatchdog::cancel ()
{
    this->timer.cancel ();
}

