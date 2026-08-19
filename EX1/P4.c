#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
   pid_t pid2, pid3, pid4, pid5, pid6, pid7;

   printf("--- P1 Started ---\n");
   printf("P1 PID: %d, PPID: %d\n\n", getpid(), getppid());

   pid2 = fork();
   if (pid2 < 0) {
      perror("Fork failed for P2");
      return 1;
   }
   else if (pid2 == 0) {
      printf("P2 (Child of P1)\n");
      printf("PID: %d, PPID: %d\n\n", getpid(), getppid());
      exit(0);
   }
   wait(NULL);

   pid3 = fork();
   if (pid3 < 0) {
      perror("Fork failed for P3");
      return 1;
   }
   else if (pid3 == 0) {
      printf("P3 (Child of P1)\n");
      printf("PID: %d, PPID: %d\n\n", getpid(), getppid());

      pid6 = fork();
      if (pid6 < 0) {
         perror("Fork failed for P6");
         return 1;
      }
      else if (pid6 == 0) {
         printf("P6 (Child of P3)\n");
         printf("PID: %d, PPID: %d\n\n", getpid(), getppid());
         exit(0);
      }
      wait(NULL);

      pid7 = fork();
      if (pid7 < 0) {
         perror("Fork failed for P7");
         return 1;
      }
      else if (pid7 == 0) {
         printf("P7 (Child of P3)\n");
         printf("PID: %d, PPID: %d\n\n", getpid(), getppid());
         exit(0);
      }
      wait(NULL);

      exit(0);
   }
   wait(NULL);

   pid4 = fork();
   if (pid4 < 0) {
      perror("Fork failed for P4");
      return 1;
   }
   else if (pid4 == 0) {
      printf("P4 (Child of P1)\n");
      printf("PID: %d, PPID: %d\n\n", getpid(), getppid());
      exit(0);
   }
   wait(NULL);

   pid5 = fork();
   if (pid5 < 0) {
      perror("Fork failed for P5");
      return 1;
   }
   else if (pid5 == 0) {
      printf("P5 (Child of P1)\n");
      printf("PID: %d, PPID: %d\n\n", getpid(), getppid());
      exit(0);
   }
   wait(NULL);
   return 0;
}
