#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int main()
{
   pid_t p2;
   printf("P1(Parent)\n");
   printf("PID:%d\n",getpid());
   printf("PPID:%d\n",getppid());
   p2=fork();

   if(p2<0)
   {
      perror("Fork failed");
      return 1;

   }
   else if(p2==0)
   {
      printf("p2(child)\n");
      printf("PID:%d\n",getpid());
      printf("PPID:%d\n",getppid());
   }
   else
   {
      wait(NULL);
   }
   return 0;
}
