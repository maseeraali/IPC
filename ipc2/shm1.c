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
	int shmid;
	int i,c;
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
	shared_stuff->flag1=0;
        shared_stuff->flag2=0;
        shared_stuff->flag=0;
        while(running)
	{
		while((shared_stuff->flag1)==1)
		{
                     	  sleep (1);
            		//Do something
		}
        	if(shared_stuff->flag==1)
       	        {
            		printf("%d found\n",(shared_stuff->to_search));

        	}
        	if((shared_stuff->flag)==-1)
        	{
            		printf("%d not found\n",(shared_stuff->to_search));
        	}	
        	printf("What do you want to do\n1.enter an array\n2.exit\n");
		fflush(stdin);		
		scanf("%d",&c);
		if(c==2)
		{
			shared_stuff->n=-1;			
			running=0;
		}
		else
		{
			printf("Enter the size of array :");
			scanf("%d",&(shared_stuff->n));
			for(i=0;i<shared_stuff->n;i++)
			{
				printf("Enter %d element",i+1);
				scanf("%d",&(shared_stuff->array[i]));
			}
			shared_stuff->flag1=1;	
		}
	}
	if(shmdt(shared_memory)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


