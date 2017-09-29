#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

static void ignoreSignal(int value, siginfo_t *sigInfo, void *context) {
}


int main(int argc, char **argv) {
  int sendSignalFlag=1;
  int pushbackPos=0;
  int pushbackLength;
  int result;

  char* pushbackString=NULL;
  for(int argPos=1; argPos<argc; argPos++) {
    if(!strcmp(argv[argPos], "--NoSignal")) {
      sendSignalFlag=0;
      continue;
    }
    if(!strcmp(argv[argPos], "--")) {
      argPos++;
      if(argPos+1!=argc) {
        fprintf(stderr, "Exactly one pushback string argument needed\n");
        return(1);
      }
      pushbackString=argv[argPos];
      break;
    }

    fprintf(stderr, "Usage: %s [--NoSignal] -- [pushback command]\n", argv[0]);
    return(1);
  }

  if(!pushbackString) {
    fprintf(stderr, "Usage: %s [--NoSignal] -- [pushback command]\n", argv[0]);
    return(1);
  }


// Change signal handler to ignore stop to avoid being stopped by
// a parent relaying STOP signal to all children.
  struct sigaction sigAction;
  sigAction.sa_sigaction=ignoreSignal;
  sigfillset(&sigAction.sa_mask);
  sigAction.sa_flags=SA_SIGINFO;
  sigaction(SIGSTOP, &sigAction, NULL);

// Send sigstop to parent to avoid parent using the input
  if (sendSignalFlag) kill(getppid(), SIGSTOP);

  pushbackLength=strlen(pushbackString)+1;
  for(pushbackPos=0; pushbackPos<pushbackLength; pushbackPos++) {
    result=ioctl(0, TIOCSTI,
        pushbackPos+1!=pushbackLength?pushbackString+pushbackPos:"\n");
    if(result) {
      fprintf(stderr, "Pushback failed, result %d, error %d (%s)\n",
          result, errno, strerror(errno));
      return(1);
    }
  }
  return(0);
}
