# Scheduling-Algorithm

The design I went with for this scheduling algorithm was to use linklist to implement queues. For the linklist I would make a dummy node for easy access to 
the linklist. I will make 4 linklist Head, Ready, Run, Final. In the Head linklist I will use it for putting the data I read from the input.txt file. In 
the Ready linklist it will replicate the ready state, while the Run linklist will replicate the Run state. The last linklist Final will be used to hold the 
process that have finished running. To start the RoundRobin scheduler I will have a for loop that counts time from 0 to 96. In the body of the loop I will 
have three major if statements if(curr->BT==0){}, if(Head->next!=NULL){}, and if(Ready->next!=NULL){}. In the if(curr->BT==0){} statement it is used to 
check if the process has finished running, if it is put it in the Final linklist and get the first process in Ready into the Run state, and update the Wait 
Time and EndTime of the new process. In the if(Head->next!=NULL){} statement it is used to check if the current time is equal to the next process in Head 
linklist, when the time is equal to the next process in Head linklist put it in to the ready state, if the current process priority is less than the 
process's priority in Ready state then I move the process in Ready state to Run state and move the current process in Run state to the end of the Ready 
state, and update the Wait Time and EndTime of the new process. In the if(Ready->next!=NULL){} statement it is used to check if the time is in the quantum 
of 10 by % the time by 10 if it is equal to 0 then it matches the quantum, and it checks if the current process priority is less than or equal to the 
process's priority in Ready state. If it is then it switches the process in the Run and Ready state, and update the Wait Time and EndTime of the new 
process. In the end it will call PrintTime to print all process in the Final Linklist in the order it was finished. Before it prints to the outFile it will 
increment the Turnaround Time by Wait Time + Burst Time. The difficulties that I faced was to figure out how to get the Wait Time and Turnaround Time.

