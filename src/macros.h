// Central location for macro definitions that should be useful everywhere.

#define min(a, b) (b) < (a) ? (b) : (a)
#define max(a, b) (b) > (a) ? (b) : (a)
#define clamp(x, low, high) \
    (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

// Debug print.
#define dprint(val, type) char* val ## _d_s = type ## ToString(val);\
                          printf(#val ": %s\n", val ## _d_s);\
                          free(val ## _d_s)
