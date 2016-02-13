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
	int shmid,i,j,k,sum;
	srand((unsigned int)getpid());
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
	while(running)
	{
		if((shared_stuff->flag2)==1&&(shared_stuff->flag1)==1)
		{
			printf("Calculating the result......\n\n");
			for(i=0;i<(shared_stuff->n);i++)
			{
				for(j=0;j<(shared_stuff->m);j++)
				{
					(shared_stuff->add[i][j])=(shared_stuff->array1[i][j])+(shared_stuff->array2[i][j]);
			               sum=0;
                                      for(k=0;k<(shared_stuff->m);k++)
                                      sum=sum+(shared_stuff->array1[i][k])*(shared_stuff->array2[k][j]);
                                      (shared_stuff->mul[i][j])=sum;
      				}
			}
			printf("Result calculated!!\n");
			shared_stuff->flag3=1;
			shared_stuff->flag1=0;
			shared_stuff->flag2=0;
			sleep(2);			
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



