#pragma once


const int RLIMIT_NOFILE = 7;

typedef unsigned int rlim_t;

struct rlimit {
    rlim_t rlim_cur;  /* Soft limit */
    rlim_t rlim_max;  /* Hard limit (ceiling for rlim_cur) */
};

int setrlimit(int resource, const struct rlimit *rlim) { return 0; } 