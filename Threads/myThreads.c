#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


FILE *input3;
FILE *input2;	
FILE *input1;
		
float numbers1[200]={0},numbers2[200]={0},numbers3[200]={0};
char i3[100],i2[100],i1[100];
float sum1=0,sum2=0,sum3=0,element=0;
int count1=0,count2=0,count3=0,control3=0,control2=0,control1=0;


void* myThread(void* data)
{   

	
	int i=0;
	float element=0;
	int myData=(int)data;
	
    	if(myData==3){
    	
		while (fscanf(input3, "%s\n", i3) > 0) {
			element=atof(i3);
			numbers3[count3++]=element;
		    	sum3+=element;
		    	
		    	printf("Thread%d reads %d. The value is %f. The sum is : %f\n",myData,count3,element,sum3);
		  	  	
		       pthread_join(pthread_self(),NULL); //used for wait
	    	}     
	    	printf("Thread%d Sum is : %f\n",myData,sum3);
	}
	if(myData==2){
		
		while (fscanf(input2, "%s\n", i2) > 0) {
			element=atof(i2);
			numbers2[count2++]=element;
		    	sum2+=element;

		    	printf("Thread%d reads %d. The value is %f. The sum is : %f\n",myData,count2,element,sum2);
		  	pthread_join(pthread_self(),NULL);
		        
	    	}			
	    	printf("Thread%d Sum is : %f\n",myData,sum2); 	
	}
	if(myData==1){
		while (fscanf(input1, "%s\n", i1) > 0) {
			element=atof(i1);
			
			numbers1[count1++]=element;
		    	sum1+=element;
		    	
		    	printf("Thread%d reads %d. The value is %f. The sum is : %f\n",myData,count1,element,sum1);
	    		pthread_join(pthread_self(),NULL);
	    				  	  
		        
	    	} 
	    		printf("Thread%d Sum is : %f\n",myData,sum1); 
	}
	
}

//program's execution begins in main like every C program
int main(int argc, char* argv[])
{   
    input3 = fopen("input3.txt", "r");
    input2 = fopen("input2.txt", "r");
    input1 = fopen("input1.txt", "r");	
   
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    int        t         = 1;  /* data passed to the new thread          */

    while(t<=3){

	    rc = pthread_create(&thread_id, NULL, myThread, (void*)t);  
	    if(rc)			/* cannot not create thread */
	    {
		printf("\n ERROR: return code from pthread_create is %d \n", rc);
		exit(1);
	    }

	    t++;
    }
    
    pthread_exit(NULL);		/* terminate the thread */
}

