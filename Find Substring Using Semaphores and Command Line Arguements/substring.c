#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <semaphore.h> 
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
char *findstring;
sem_t mutex;
int count=0;

void *search_string(void *arg)
{
sem_wait(&mutex);
char *find;
find=(char*)malloc(sizeof(char)*strlen((char*)arg));
strcpy(find,(char*)arg);

char *temp=arg;
while((temp=strstr(temp,findstring))!=NULL)
{
//printf("DONE \n");
temp+=strlen(findstring);
count++;
}
sem_post(&mutex);
}

int main(int argc,char *argv[])
{
sem_init(&mutex, 0,1); 
int fd;
char *data; 
int substring=(strlen(argv[1]));
findstring=(argv[1]);
printf("\n ------------------------ Taking Subroutine --------------------- \n");
printf("Subroutine= %s",findstring);
printf("-------------------------------------------------------------------------------");
printf("\n");
printf("Length of Substring= %i",substring);
printf("\n");
fd=open("input.txt",O_RDONLY);
data=mmap(NULL,getpagesize(),PROT_READ,MAP_SHARED,fd,0);
printf("\n --------------------- Displaying Contents of the File -------------------- \n");
printf("Contents of File= %s",data);
printf("\n--------------------------------------------------------------------------------------\n");
int filelength=strlen(data);
printf("\n-------------------------- Getting Length of File ----------------------------\n");
printf("Length Of File= %i",filelength);
printf("\n--------------------------------------------------------------------------------------\n");
int half1=filelength/2;
int half2=filelength-half1;
char *half1s=(char*)malloc(half1);
char *half2s=(char*)malloc(half2);
printf("\n----------------------- Displaying First Half Of File ------------------------\n");
strncpy(half1s,data,half1);
printf("First Half of File= %s",half1s);
printf("\n");
printf("first half= %i",half1);
printf("\n--------------------------------------------------------------------------------------\n");
printf("\n----------------------- Displaying Second Half Of File ------------------------\n");
strncpy(half2s,data+(half1),half2);
printf("Second Half of File= %s",half2s);
printf("\n");
printf("second half= %i",half2);
printf("\n");
printf("\n--------------------------------------------------------------------------------------\n");
pthread_t Thread_1,Thread_2;
pthread_create(&Thread_1,NULL,search_string,(void*)half1s);
sleep(2);
pthread_create(&Thread_2,NULL,search_string,(void*)half2s);
pthread_join(Thread_1,NULL);
pthread_join(Thread_2,NULL);
sem_destroy(&mutex);
printf("\n Occurence= %i\n",count);
return 0;
}
