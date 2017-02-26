// Central location for macro definitions that should be useful everywhere.

#define min(a, b) b < a ? b : a

// Debug print.
#define dprint(val, type) char* val ## _d_s = type ## ToString(val);\
                          printf(#val ": %s\n", val ## _d_s);\
                          free(val ## _d_s)
