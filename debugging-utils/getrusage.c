#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <spawn.h>
#include <sys/resource.h>

#define PRETTY_PRINT(item) #item ": %li\n"

extern char **environ;

int main(int argc, char* argv[]) {
        if (argc == 1) {
                printf("no arguments\n");
                exit(1);
        }
        int pid;
        int status = posix_spawnp(&pid, argv[1], NULL, NULL, argv+1, environ);
        if (status == 0) {
                if (waitpid(pid, &status, 0) != -1) {
                        struct rusage ru;
                        getrusage(RUSAGE_CHILDREN, &ru);
                        printf("\n"
                               PRETTY_PRINT(maxrss)
                               PRETTY_PRINT(ixrss)
                               PRETTY_PRINT(idrss)
                               PRETTY_PRINT(isrss)
                               PRETTY_PRINT(minflt)
                               PRETTY_PRINT(majflt)
                               PRETTY_PRINT(swap)
                               PRETTY_PRINT(inblock)
                               PRETTY_PRINT(oublock)
                               PRETTY_PRINT(msgsnd)
                               PRETTY_PRINT(msgrcv)
                               PRETTY_PRINT(signals)
                               PRETTY_PRINT(nvcsw)
                               PRETTY_PRINT(nivcsw),
                               ru.ru_maxrss,
                               ru.ru_ixrss,
                               ru.ru_idrss,
                               ru.ru_isrss,
                               ru.ru_minflt,
                               ru.ru_majflt,
                               ru.ru_nswap,
                               ru.ru_inblock,
                               ru.ru_oublock,
                               ru.ru_msgsnd,
                               ru.ru_msgrcv,
                               ru.ru_nsignals,
                               ru.ru_nvcsw,
                               ru.ru_nivcsw
                               );
                       exit(status);
                } else {
                        perror("waitpid");
                }
        } else {
                printf("posix_spawn: %s\n", strerror(status));
                exit(status);
        }
}
