#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
sem_t mutex;
sem_t s_prod2;
sem_t s_cons;
int global=0;
int p1t[7];
int p2t[7];
int consarr[7];
char *prod1mem;
char *prod2mem;


void* prod1()
{
   sem_wait(&mutex);
   int fd;
   fd = open("input1.txt", O_RDWR | O_CREAT);
   prod1mem = mmap(NULL, 256, PROT_READ, MAP_SHARED, fd, 0);
   close(fd);
   char temp[7] = "";

   printf("%s \n", temp);

   int i = 0;
   int j = 0;
   while (i < 23)
   {
     if (prod1mem[i] == ',')
     {
       int x = atoi(temp);
       p1t[j] = x;
       printf("%i \n", p1t[j]);
       strncpy(temp, "", 7);
       i++;
       j++;
     }
     else
     {
       strncat(temp, &prod1mem[i], 1);
       i++;
     }
   }
   sem_post(&s_prod2);
}
void* prod2()
{
   sem_wait(&s_prod2);
   int fd1;
   fd1 = open("input2.txt", O_RDWR | O_CREAT);
   prod2mem =mmap(NULL, 256, PROT_READ, MAP_SHARED, fd1, 0);
   close(fd1);
   char temp[7]="";
   printf("%s \n",temp);
   
  int i = 0;
  int j = 0;
  while (i<23)
  {
    if (prod2mem[i] == ',')
    {
       int x = atoi(temp);
       p2t[j]=x;
      printf("%i \n", p2t[j]);
      strncpy(temp,"",7);
      i++;
      j++;
    }
    else
    {
      strncat(temp,&prod2mem[i],1);     
    i++;
    }
  
  }
  sem_post(&s_cons);
}
void* cons()
{
   sem_wait(&s_cons);
   global=global+2;
    printf("\nEVALUATING FINAL STEP\n Consumer: \n");
    int i;
    for(i=0;i<7;i++)
    {
if (p1t[i]>p2t[i])
{
  consarr[i]=p1t[i];
}
else
{
  consarr[i]=p2t[i];
}
    }
    for(i=0;i<7;i++)
    printf("\n %i",consarr[i]);
    printf("\n DONE \n");
    FILE *fd;
    fd = fopen("output.txt", "a");
    for (i = 0; i < 7; i++)
      fprintf(fd, "%d\n", consarr[i]);
    fclose(fd);
    sem_post(&mutex);
}
int main ()
{
sem_init (&mutex,0,1);
sem_init (&s_prod2,0,0);
sem_init (&s_cons,0,0);

pthread_t _prod1;
pthread_t _prod2;
pthread_t _cons;


pthread_create(&_prod1,NULL,prod1,NULL);
pthread_create(&_prod2, NULL, prod2, NULL);
pthread_create(&_cons, NULL, cons, NULL);

pthread_join(_cons, NULL);
pthread_join (_prod1,NULL);
pthread_join(_prod2, NULL);

exit(0);
return 0;
}
