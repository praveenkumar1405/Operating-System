#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
   pid_t P2, P3;
   printf("P1 (Root Process)\n");
   printf("PID: %d\n", getpid());
   printf("Parent PID: %d\n\n", getppid());



   P2 = fork();

   if(P2 < 0)
   {
      perror("First fork failed");
      return 1;
   }
   else if(P2 == 0)
   {
      printf("\nP2 (Left child ) \n");
      printf("PID: %d \n", getpid());
      printf("Parent PID: %d \n", getppid());
   }
   else
   {
      wait(NULL);
      P3 = fork();
      if(P3 < 0)
      {
         perror("Second fork failed");
         return 1;
      }
      else if(P3 == 0)
      {
         printf("\nP3 (Right child ) \n");
         printf("PID: %d \n", getpid());
         printf("Parent PID: %d \n", getppid());
      }
      else
      {
         wait(NULL);
      }
   }
   return 0;
}
