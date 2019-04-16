# MLFQ-Scheduling-Algorithm
Design a scheduling program to implements a Queue with two levels:
Level 1 : Fixed priority preemptive Scheduling
Level 2 : Round Robin Scheduling
For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. If one process P1 is scheduled and running , another process P2 with higher priority comes. The New process (high priority) process P2 preempts currently running process P1 and process P1 will go to second level queue. Time for which process will strictly execute must be considered in the multiples of 2..
All the processes in second level queue will complete their execution according to round robin scheduling.
Consider: 
1. Queue 2 will be processed after Queue 1 becomes empty.
2. Priority of Queue 2 has lower priority than in Queue 1.
3. When level 1 is not empty but none process has arrival time equal to current time then it will proceed to level 2
4. When level 1 is not empty but none process has arrival time equal to current time and level 2 is also empty then just current time will    increase.
5. As soon as new process comes it will execute in level 1 that is priority with preemption

 This all points are implemented in file pro_final.c
 
 Time Quantum=4
 Process    Arrival    Burst    Priority    Completion    Turn Around    Waiting
  Id        Time      Time                     Time           Time        Time
   A         0         14          2            44              44         30
   B         7         8           1            21              14          6
   C         3         10          0            13              10          0
   D         5         7           2            28              23         16
   E         1         5           3            33              32         27
   F         50        5          25            55              5           0
   Average Waiting Time : 13.17
   Average Turn Around Time : 21.33
 
 

