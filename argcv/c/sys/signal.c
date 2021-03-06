/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Yu Jing <yu@argcv.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **/
#include "argcv/c/sys/signal.h"

#include <sys/types.h>  // pid_t

#include <stdio.h>  // printf

#include <signal.h>    // signal
#include <sys/wait.h>  // wait

sigfunc* _signal(int signo, sigfunc* func) {
  struct sigaction act;  // bits/sigaction.h
  struct sigaction oact;
  printf("signal called  ...\n");

  act.sa_handler = func;
  sigemptyset(&act.sa_mask);  // signal.h
  act.sa_flags = 0;

  if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;  // SunOS 4.x
#endif                             // SA_INTERRUPT
  } else {
#ifdef SA_RESTART
    act.sa_flags |= SA_RESTART;  // SVR4, 4.4BSD
#endif                           // SA_RESTART
  }
  if (sigaction(signo, &act, &oact) < 0) return SIG_ERR;
  return oact.sa_handler;
}

/**
 *
 */
void sig_chld(int signo) {
  pid_t pid;
  int stat;
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
    // #ifdef __DEBUG__
    //     if (daemon_proc) {
    //       syslog(LOG_DEBUG, "child %d terminated \n", pid);
    //     } else {
    //       fprintf(stdout, "child %d terminated \n", pid);
    //     }
    // #endif  // __DEBUG__
  }
  return;
}
