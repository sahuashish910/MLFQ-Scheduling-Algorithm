//process[i].processed=0 - in level 1  implements preemption with priority
//process[i].processed=1 - in level 2  implements round robin
//process[i].processed=2 - in completed

#include<stdio.h>

int front=-1,rear=-1,queue[1000];

struct processes
{
	int arrival,burst,left_burst,priority,completion,processed,turn,waiting;
	char name;
};

//adding element to queue
void addToQueue(int i)
{
	if(rear==100)
 	printf("OVERFLOW");
	rear++;
	queue[rear]=i;
	if(front==-1)
	front=0;
}

//deleting element from queue
int deleteFromQueue()
{
	if(front==-1)
 	return 0;
	int tempo=queue[front];
 	if(front==rear)
 	front=rear=-1;
 	else
 	front++;
 	return tempo;
}

//checking whether element is already in queue or not
int isInQueue(int i)
{
	int m;
	for(m=front;m<=rear;m++)
	{
		if(queue[m]==i)
		return 1;
	}
	return 0;
 }
 
 //checking whether queue is empty or not
 int isEmpty()
 {
 	if(front==-1)
	return 0;
	else 
	return 1;
 }

//sorting processes on base of name for displaying result
void sortByName(struct processes process[],int no_p)
{
	int i,j;
	struct processes temp;
	for(i=0;i<no_p-1;i++)
	{
		for(j=0;j<no_p-i-1;j++)
		{
			if(process[j].name > process[j+1].name)
			{
				temp=process[j];
				process[j] = process[j+1];
				process[j+1] = temp;
			}
		}
	}
}

//function for displaying result
void display(struct processes process[],int no_p,float avgw,float avgt)
{
	int i;
	printf("\nProcess    Arrival    Burst    Priority    Completion    Turn Around    Waiting");
	printf("\n  Id        Time      Time                    Time           Time        Time");
	for(i=0;i<no_p;i++)	
	{ 
		printf("\n   %c         %d         %d          %d            %d              %d           %d",process[i].name,
		process[i].arrival,process[i].burst,process[i].priority,process[i].completion,process[i].turn,process[i].waiting);
	}
	printf("\n\nAverage Waiting Time : %.2f",avgw);
	printf("\nAverage Turn Around Time : %.2f",avgt);
}

//main part of program: executes preemption with priority and round robin
void run(struct processes process[],int no_p,int total_burst,int tq)
{
	int time=0,max=999,i,j,z,flag=5;
	process[max].priority=999,process[max].left_burst=999;
	for(time=process[0].arrival;time<total_burst;time++)
	{
		for(i=0;i<no_p;i++)
		{
			if(process[i].arrival<=time && process[i].processed==0 && process[i].priority<process[max].priority)
			{
				if(max!=999 && (process[max].left_burst!=process[max].burst))
				{
					process[max].processed=1;
					addToQueue(max);
				}
				max=i;
			}
		}
		
		process[max].left_burst-=1;
		if(process[max].left_burst==0)
		{
			process[max].completion=time+1;
			process[max].processed=2;
			max=999;
		}
		
		//finding if level1 is empty and if not empty the process arrival time is greater than time por not
		for(i=0;i<no_p;i++)
		{
			if(process[i].arrival<=time)
			{
				if(process[i].processed==0)
				flag=0;
			} 
			if(process[i].processed>=time)
			{
				if(process[i].processed==0)
				flag=3;
			} 
		}
		//if queue or level is empty then don't go to round robin code
		if(isEmpty()!=1)
		flag=0;
		if(flag!=0)
		flag=3;
		
		if(flag==3)
		{
			//deleting first element from queue
			z=deleteFromQueue();
			//if left_burst time of process is less than or equal to time quantum
   			if(process[z].left_burst<=tq)
 			{                          
                time+=(process[z].left_burst);
   				process[z].left_burst=0;
   				process[z].completion=time+1;
				process[z].processed=2; 
				//adding the processes to queue which have come while scheduling         
            	for(j=0;j<no_p;j++)                
            	{
             		if(process[j].arrival<=time && process[j].processed==1&& isInQueue(j)!=1)
             		addToQueue(j);
           		}
       		}
       		//if left_burst time of process is greater than time quantum
    		else               
     		{
      			time+=(tq-1);
      			process[z].left_burst-=tq;
      			//adding the processes to queue which have come while scheduling   
      			for(j=0;j<no_p;j++)             
            	{
            		 if(process[j].arrival<=time && process[j].processed==1 && z!=j && isInQueue(j)!=1)
             			addToQueue(j);
           		}
           		//adding the processes to queue which is not completed
          		addToQueue(z);   
          
    		}
  		}
  		flag=5;
	}
	//calculating waiting and turn around
	float avgw=0,avgt=0;
	for(i=0;i<no_p;i++)
	{
		process[i].turn=(process[i].completion-process[i].arrival);
		process[i].waiting=(process[i].turn-process[i].burst);
		avgw+=process[i].waiting;
		avgt+=process[i].turn;
	}
	avgw=avgw/no_p;
	avgt=avgt/no_p;
	sortByName(process,no_p);
	display(process,no_p,avgw,avgt);
}

//sorting on basis of arrival time
void sortByArrival(struct processes process[],int no_p)
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

int main()
{
	printf("\n--------Multilevel Feedback Queue Scheduling Algorithm--------\n");
	int no_p,i,total_burst=0,tq=0;
	char c;
	printf("\nEnter no. of processes : ");
	scanf("%d",&no_p);
	
	struct processes process[1000];
	
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
	printf("\nEnter time quantum : ");
	scanf("%d",&tq);
	
	if(process[no_p-1].arrival>=total_burst)
	total_burst=(process[no_p-1].arrival+process[no_p-1].burst);
	
	sortByArrival(process,no_p);
	run(process,no_p,total_burst,tq);
}
