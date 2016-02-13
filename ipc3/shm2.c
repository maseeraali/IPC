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
	int i,j;
	shmid= shmget((key_t)1234, sizeof(struct shared_use_st),0666|IPC_CREAT);
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
    shared_stuff->flag3=0;
    while(running)
	{
		while((shared_stuff->flag2)==1&&(shared_stuff->flag1)==1)
		{
            sleep (1);
            //Do some job
		}
        if(shared_stuff->flag3==1)
        {
            printf("ADDITION\n");
            for(i=0;i<shared_stuff->n;i++)
            {
                for(j=0;j<(shared_stuff->m);j++)
                    
                {
                    printf("%d\t",(shared_stuff->add[i][j]));
                }
                printf("\n");
            }
            printf("\nMULTIPLICATION\n");
            for(i=0;i<shared_stuff->n;i++)
            {
                for(j=0;j<(shared_stuff->m);j++)
                    
                {
                    
                    printf("%d\t",(shared_stuff->mul[i][j]));
                }
                printf("\n");
            }
           running =0;
        }
      if((shared_stuff->flag1)==1)
        {for(i=0;i<(shared_stuff->n);i++)
        {
            for(j=0;j<(shared_stuff->m);j++)
                
            {
                printf("Enter element");
                scanf("%d",&(shared_stuff->array2[i][j]));
            }
        }
        shared_stuff->flag2=1;
       
	}	
	}
	if(shmdt(shared_memory)==-1)
	{
		fprintf(stderr,"shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
