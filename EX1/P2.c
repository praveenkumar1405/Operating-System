#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
   pid_t P2,P3;

   printf("P1 (Root Process) \n");
   printf("PID: %d \n", getpid());
   printf("Parent PID: %d \n\n", getppid());


   P2 = fork();

   if(P2 < 0)
   {
      perror("Fork failed.");
      return 1;
   }

   else if(P2 == 0)
   {

      printf("P2 (Child of P1) \n");
      printf("PID: %d \n", getpid());
      printf("Parent PID: %d \n\n", getppid());


      P3 = fork();
      if(P3 < 0)
      {
         perror("Second fork failed");
         return 1;
      }
      else if(P3 == 0)
      {

         printf("P3 (Child of P2) \n");
         printf("PID: %d \n", getpid());
         printf("Parent PID: %d \n\n", getppid());
      }
      else
      {

         wait(NULL);
      }
   }
   else
   {

      wait(NULL);
   }
   return 0;
}
