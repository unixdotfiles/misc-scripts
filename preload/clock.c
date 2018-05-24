#include <stdio.h>
#include <time.h>
__attribute__((visibility("default"))) int
clock_gettime(clockid_t clock_id, struct timespec *tp) {
        return 0;
}
