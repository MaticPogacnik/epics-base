
/*
 * $Id$
 *
 * Author: Jeff Hill
 */

#ifndef osdTimeh
#define osdTimeh

struct timespec {
	time_t tv_sec; /* seconds since some epoch */
	long tv_nsec; /* nanoseconds within the second */
};

#endif /* ifndef osdTimeh */