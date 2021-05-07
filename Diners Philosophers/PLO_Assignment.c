#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

void prompt_()
{
  system("clear");
  char done[4];
  printf("\n(You are eating right now)Type Done When You are finished eating=");
  scanf("%s", done);
}
void delay()
{
       int j,k,temp;
        for (j = 0; j < 20000; j++)
        for (k = 0; k < 20000; k++)
        temp=0;
}
void read_(int fd,char status[])
{
  fd = open("test.txt", O_RDONLY);
  read(fd, status, 5);
  close(fd);
}
void write_(int fd,char status[])
{
        fd = open("test.txt", O_WRONLY | O_TRUNC);
        write(fd, status, 5);
        close(fd);
}

int main ()
{
    int fd,_printcount=1,runcount=0;
    char done[4];
    char status[5];
    int i,count,left,right;
    printf("\n Press Any key to eat and Enter\n");
    scanf("%s", done);
    continue_checking:
      left = 0;
      right = 0;
      delay();
      read_(fd,status);
      if (status[0] == '1' && status[4] == '1')
      {
        status[0] = '0';
        status[4] = '0';
       write_(fd,status);
       prompt_();
       read_(fd,status);
       status[0] = '1';
       status[4] = '1';
       write_(fd,status);
       _printcount = 1;
       goto continue_checking;
}
else if (status[0]=='1' && status[4]=='0')
{
 // if (right==0)
{
  system("clear");
  printf("\n Philosopher 2 is idle.... \n Philosopher 5 is eating... \n");
  right ++;
  left=0;
}
goto continue_checking;
}
else if (status[0]=='0' && status[4]=='1')
{
  //if (left==0)
{
  system("clear");
  printf("\n Philosopher 2 is eating.... \n Philosopher 5 is idle.... \n");
  left++;
  right;
}
goto continue_checking;
}
else 
{
   if (_printcount==1)
   printf("\nPhilosopher 2 and 5 are eating...\n");
   _printcount++;
   left=0;
   right=0;
goto continue_checking;
}
printf("%s \n", status);
return 0;
}