#include<stdio.h>

struct processes
{
	int arrival,burst,left_burst,priority,completion,processed;
	char name;
};

//implementing preemption with priority
void run(struct processes process[],int no_p,int total_burst)
{
	int time=0,max=999,i;
	process[max].priority=999;
	for(time=process[0].arrival;time<=total_burst;time++)
	{
		for(i=0;i<no_p;i++)
		{
			if(process[i].arrival<=time && process[i].processed!=1 && process[i].priority<process[max].priority)
        		max=i;
		}
		process[max].left_burst-=1;
		if(process[max].left_burst==0)
		{
			process[max].completion=time+1;
			process[max].processed=1;
			max=999;
		}
	}
	printf("\nProcess Arrival Burst Priority Completion\n");
	for(i=0;i<no_p;i++)
   	printf("   %c      %d     %d     %d        %d\n",process[i].name,process[i].arrival,process[i].burst,process[i].burst,process[i].completion);
}

//sorting processes by their arrival time
void sort_by_arrival(struct processes process[],int no_p)
{
	int i,j;
	struct processes temp;
	for(i=0;i<no_p-1;i++)
	{
		for(j=0;j<no_p-i-1;j++)
		{
			if(process[j].arrival > process[j+1].arrival)
			{
				temp=process[j];
				process[j] = process[j+1];
				process[j+1] = temp;
			}
		}
	}
}

void main()
{
	printf("\n--------Multilevel Feedback Queue Scheduling Algorithm--------\n");
	int no_p,i,total_burst=0;
	char c;
	printf("\nEnter no. of processes : ");
	scanf("%d",&no_p);
	
	struct processes process[1000];
	struct processes level1[no_p];
	struct processes level2[no_p];
	
	for(i=0,c='A';i<no_p;i++,c++)
	{
		process[i].name=c;
		printf("\nProcess %c",process[i].name);
		printf("\nEnter arrival time : ");
		scanf("%d",&process[i].arrival);
		printf("Enter burst time : ");
		scanf("%d",&process[i].burst);
		process[i].left_burst=process[i].burst;
		total_burst+=process[i].burst;
		printf("Enter priority : ");
		scanf("%d",&process[i].priority);
		process[i].processed=0;
	}
	
	sort_by_arrival(process,no_p);
	run(process,no_p,total_burst);
}
