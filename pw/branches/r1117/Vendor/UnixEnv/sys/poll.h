#ifndef _POLL_H
#define _POLL_H
/*
**  Emulate poll() for those platforms (e.g., Ultrix) that don't have it.
**  Usually select() and poll() are the same functionally, differing only
**  in the calling interface, but in a few cases they behave differently,
**  possibly where the platform implements STREAMS devices and one or the
**  other has some compatibility bug.  Poll() has a cleaner programming
**  interface, anyway.
*/

/*
struct pollfd {
	int fd;
	short events;
	short revents;
};*/

/*
#define POLLIN 001
#define POLLPRI 002
#define POLLOUT 004
#define POLLNORM POLLIN
#define POLLERR 010
#define POLLHUP 020
#define POLLNVAL 040
*/
//int poll PROTO((struct pollfd *, int, int));

/* _POLL_H_H_ */
// ----------------------------------------
/*
 *  prt
 *
 *  Copyright 1994 University of Washington
 *
 *  Permission is hereby granted to copy this software, and to
 *  use and redistribute it, except that this notice may not be
 *  removed.  The University of Washington does not guarantee
 *  that this software is suitable for any purpose and will not
 *  be held liable for any damage it may cause.
 */

/*
**  emulate poll() for those platforms (Ultrix) that don't have it.
*/

// #include "osdefs.h"

#include <sys/types.h>
#include <sys/time.h>
#include "poll.h"

void bzero();

inline int
poll (struct pollfd *fds,
	unsigned long nfds,
	int timo)
{
    struct timeval timeout, *toptr;
    fd_set ifds, ofds, efds, *ip, *op, *ep;
    int i, rc, n;
    FD_ZERO(&ifds);
    FD_ZERO(&ofds);
    FD_ZERO(&efds);
    for (i = 0, n = -1, op = ip = 0; i < nfds; ++i) {
	fds[i].revents = 0;
	if (fds[i].fd < 0)
		continue;
	if (fds[i].fd > n)
		n = fds[i].fd;
	if (fds[i].events & (POLLIN|POLLPRI)) {
		ip = &ifds;
		FD_SET(fds[i].fd, ip);
	}
	if (fds[i].events & POLLOUT) {
		op = &ofds;
		FD_SET(fds[i].fd, op);
	}
	FD_SET(fds[i].fd, &efds);
    }
    if (timo < 0)
	toptr = 0;
    else {
	toptr = &timeout;
	timeout.tv_sec = timo / 1000;
	timeout.tv_usec = (timo - timeout.tv_sec * 1000) * 1000;
    }
    rc = select(++n, ip, op, &efds, toptr);
    if (rc <= 0)
	return rc;

    for (i = 0, n = 0; i < nfds; ++i) {
	if (fds[i].fd < 0) continue;
	if (fds[i].events & (POLLIN|POLLPRI) && FD_ISSET(fds[i].fd, &ifds))
		fds[i].revents |= POLLIN;
	if (fds[i].events & POLLOUT && FD_ISSET(fds[i].fd, &ofds))
		fds[i].revents |= POLLOUT;
	if (FD_ISSET(i, &efds))
		/* Some error was detected ... should be some way to know. */
		fds[i].revents |= POLLHUP;
    }
    return rc;
}

#endif