
/*
 *********************************************************
 *  This file is included only for special purpose :
 *  to test compilation on non BSD  platforms.
 * 
 *  Do not use it, use native
 *  /usr/include/sys/event.h
 *********************************************************
 *
 */

struct kevent 
{
     uintptr_t ident;        /* identifier for this event */
     short     filter;       /* filter for event */
     u_short   flags;        /* action flags for kqueue */
     u_int     fflags;       /* filter flag value */
     intptr_t  data;         /* filter data value */
     void      *udata;       /* opaque user data identifier */
};



#define EVFILT_READ     0
#define EVFILT_WRITE    1
#define EVFILT_AIO      2   /* attached to aio requests */
#define EVFILT_VNODE    3   /* attached to vnodes */
#define EVFILT_PROC     4   /* attached to struct proc */
#define EVFILT_SIGNAL   5   /* attached to struct proc */
#define EVFILT_TIMER    6   /* arbitrary timer (in ms) */
#define EVFILT_SYSCOUNT 7   /* number of filters */


#ifndef EV_SET
#define EV_SET(kevp, a, b, c, d, e, f) do {     \
        (kevp)->ident = (a);                    \
        (kevp)->filter = (b);                   \
        (kevp)->flags = (c);                    \
        (kevp)->fflags = (d);                   \
        (kevp)->data = (e);                     \
        (kevp)->udata = (f);                    \
} while(0)
#endif

/* actions */
#define EV_ADD      0x0001      /* add event to kq (implies ENABLE) */
#define EV_DELETE   0x0002      /* delete event from kq */
#define EV_ENABLE   0x0004      /* enable event */
#define EV_DISABLE  0x0008      /* disable event (not reported) */

/* flags */
#define EV_ONESHOT  0x0010      /* only report one occurrence */
#define EV_CLEAR    0x0020      /* clear event state after reporting */
#define EV_SYSFLAGS 0xF000      /* reserved by system */
#define EV_FLAG1    0x2000      /* filter-specific flag */

/* returned values */
#define EV_EOF      0x8000      /* EOF detected */
#define EV_ERROR    0x4000      /* error, data contains errno */



/* just to test */

inline
int  kqueue(void)
{
    return 1;
}

inline
int  kevent(int kq, 
            const struct kevent *changelist, 
            int nchanges,
            struct kevent *eventlist,
            int nevents,
            const struct timespec *timeout)
{
    return 0;
}

