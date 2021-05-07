#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
     char reset[]="11111";
     int  fd = open("test.txt", O_WRONLY | O_TRUNC);
     write(fd,reset, 5);
     close(fd);
   system("gcc PLO_Assignment.c -o Philosopher1");
   system("gcc 1.c -o Philosopher2");
   system("gcc 2.c -o Philosopher3");
   system("gcc 3.c -o Philosopher4");
   system("gcc 4.c -o Philosopher5");
   system("xterm -e './Philosopher1' & xterm -e './Philosopher2' & xterm -e './Philosopher3' & xterm -e './Philosopher4' & xterm -e './Philosopher5'");
   
   
 }