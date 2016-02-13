#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/shm.h>
#include "shm_com.h"
int main()
{
	int running=1;
	void *shared_memory=(void *)0;
	struct shared_use_st *shared_stuff;
	//int temp;
	int shmid;
	int i,j;
	srand((unsigned int)getpid());
	shmid= shmget((key_t)1233, sizeof(struct shared_use_st),0666|IPC_CREAT);
	if(shmid==-1)
	{
		fprintf(stderr,"shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory=shmat(shmid,(void *)0,0);
	if(shared_memory==(void *)-1)
	{
		fprintf(stderr,"shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %x\n",(int)shared_memory);
	shared_stuff=(struct shared_use_st *)shared_memory;
	while(running)
	{
		if((shared_stuff->flag1==1)&&(shared_stuff->flag2==1))
		{
			printf("Enter the element to be searched\n");
        		scanf("%d",&(shared_stuff->to_search));
		        for(i=0;i<(shared_stuff->n);i++)
			{
				if((shared_stuff->array[i])==(shared_stuff->to_search))
				{
		                        shared_stuff->flag=1;
        		                sleep(1);
                	        }
				
			}
			if(shared_stuff->flag==0)
			shared_stuff->flag=-1;
        		shared_stuff->flag1=0; 
        		shared_stuff->flag2=0;			
		}	
		if(shared_stuff->n==-1)		
       		 {
            		running=0;
        	}
	}
	if(shmdt(shared_memory)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

