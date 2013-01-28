#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/signal.h>
#include <sys/types.h>

typedef void (*sighandler_t)(int);

typedef int sigset_t;
typedef int sigval_t;

typedef struct
{
    int      si_signo;    /* Signal number */
    int      si_errno;    /* An errno value */
    int      si_code;     /* Signal code */
    int      si_trapno;   /* Trap number that caused
                             hardware-generated signal
                             (unused on most architectures) */
    pid_t    si_pid;      /* Sending process ID */
    uid_t    si_uid;      /* Real user ID of sending process */
    int      si_status;   /* Exit value or signal */
    clock_t  si_utime;    /* User time consumed */
    clock_t  si_stime;    /* System time consumed */
    sigval_t si_value;    /* Signal value */
    int      si_int;      /* POSIX.1b signal */
    void    *si_ptr;      /* POSIX.1b signal */
    int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
    int      si_timerid;  /* Timer ID; POSIX.1b timers */
    void    *si_addr;     /* Memory location which caused fault */
    long     si_band;     /* Band event (was int in
                             glibc 2.3.2 and earlier) */
    int      si_fd;       /* File descriptor */
    short    si_addr_lsb; /* Least significant bit of address */
} siginfo_t;

enum
{
    SIG_BLOCK,
    SIG_UNBLOCK,
    SIG_SETMASK
};

#define SIG_IGN ((sighandler_t)0)
#define SIG_DFL ((sighandler_t)1)
#define SIG_ERR ((sighandler_t)2)

#define SA_SIGINFO (1 << 0)

struct sigaction
{
    union
    {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t *, void *);
    };

    sigset_t sa_mask;
    int sa_flags;
};

static inline int sigemptyset(sigset_t *set)
{
    *set = 0;
    return 0;
}

static inline int sigaddset(sigset_t *set, int signum)
{
    *set |= 1 << signum;
    return 0;
}

static inline int sigdelset(sigset_t *set, int signum)
{
    *set &= ~(1 << signum);
    return 0;
}

static inline int sigismember(const sigset_t *set, int signum)
{
    return (*set >> signum) & 1;
}

int kill(pid_t pid, int sig);
int raise(int sig);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

sighandler_t signal(int signum, sighandler_t handler);

#endif
