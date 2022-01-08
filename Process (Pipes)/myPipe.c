#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h>

  
int main()
{
  
  int p[2],p2[2];
  pipe(p);
  pipe(p2);
  
  pid_t pid = fork();
  
   if(pid > 0) {
      char array[50]="",reverseFromChild[50]="";
      
      int i=0,j=0;	
      gets(array);
      
      while(array[i]!='\0'){
      	 i++;
      }	
      write(p[1], array,50);
     
      printf("%s\n",array);
      
      read(p2[0], reverseFromChild, 50); //gets from child
      printf("%s",reverseFromChild);
      
  } 
  else if( pid == 0 ) {
      wait(NULL);	     //child process wait until parent process is done 
      char sequence[50]="",reverse[50]="";

      int i=0,j=0;
      
      read(p[0], sequence, 50);
      
      while(sequence[i]!='\0'){        
         i++;	
      }
	
      while(j<i){
          reverse[j]=sequence[(i-1)-j]; //reversing
	  j++;	
      }
	
     write(p2[1], reverse,50); //sending to parent process	

  }
  else {
      perror("error\n");
  } 
  
 
} 
