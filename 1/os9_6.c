#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>

char buf[10000];

void even()
{
  	int file = open("./os9.txt", O_RDONLY);
  	int n = read(file, buf, 10000);
  	int file_even = open("./2.txt", O_CREAT|O_WRONLY);
  	char * end = (char*)malloc(1024);
  	int countRow = 0, j =0;
  
  	for(int i = 0; i < n; i++)
  	{
   		if((countRow + 1) % 2 ==0)
   		{
     			end[j] = buf[i];
     			printf("%c", end[j]); 
     			j++;
   		} 
   		if(buf[i] == '\n')
			countRow++;
  	}
  	write(file_even, end, j);
}
  
void odd()
{
   	int file = open("./os9.txt", O_RDONLY);
   	int n = read(file, buf, 10000);
   	int file_odd = open("./1.txt", O_CREAT|O_WRONLY);
   	char * end = (char*)malloc(1024);
   	int countRow = 0, j =0;
   	for(int i = 0; i < n; i++)
   	{
   		if((countRow + 1) % 2 !=0)
   		{
    			end[j] = buf[i];
  			printf("%c", end[j]); 
			j++;
   		} 
   		if(buf[i] == '\n')
   			countRow++;
   	}
  	write(file_odd, end, j);  
}

int main()
{
  	int number;
  	printf("%s", "Input number: ");
  	scanf("%d", &number);
  	if(number%2 == 0) even();
  	else odd();
	exit(0);
}
