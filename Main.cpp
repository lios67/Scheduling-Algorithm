//g++ Main.cpp -std=c++11
//./a.out input.txt output.txt
#include <iostream>
#include <fstream>
using namespace std;

class Linklist{
    public:
    class Node{ //Class for Node
        public:
        Node *next; //Next pointer
        string process; //String for the process ID
        int priority, BT, AT, ST, ET=0, WT, TT; //int for Priority, Burst Time, Arrival Time, End Time =0, Wait Time, Turnaround Time
    };
    Node* Head(){   //Function for a dummy node
        Node *node = new Node();    //Create a new node 
        node->AT=-9999; //Set the Arrival Time to -9999
        node->priority=9999;    //Set the Priority to 9999
        node->next=NULL;    //Set next pointer to NULL
        return node;    //Return the new dummy node
    }
    void constructLL(ifstream &inFile, Node *Head){     //Function for Constructing the LinkList
        string pro;     //String pro for process ID
        int done=0, p, burst, a;    //int done for while loop, p for Priority, burst for Burst Time, a for Arrival Time.
        while(done==0){ //While loop for infinite loop to get all of the data
            inFile >> pro >> p >> burst >> a;   //Read process ID, Priority, Burst Time, and Arrival Time.
            if(inFile.eof()){break;}    //A checker to see if it is at the last line
            Node *newnode = new Node(); //Create a new node for data
            newnode->process=pro;   //Set process to pro
            newnode->priority=p;    //Set priority to p
            newnode->BT=burst;      //Set BT to burst
            newnode->AT=a;          //Set AT to a
            newnode->ET=a;          //Set ET to a 
            newnode->WT=0;          //Set WT to 0
            newnode->TT=burst;      //Set TT to burst
            newnode->next=NULL;     //Set next to NULL
            Insert(Head, newnode);  //Get the new node in to a LinkList 
        }
    }
    void Insert(Node *Head,Node *newNode){  //Function for putting the Nodes into a LinkList
        Node *spot = new Node();    //Create a new node
        spot=findSpot(Head, spot, newNode); //Find the spot to put the node to
		newNode->next=spot->next;   //Set the new node's next to spot next
		spot->next=newNode; //Set spot next to new node
    }
    Node* findSpot(Node *Head,Node *spot,Node *newNode){    //Function to find the spot to put the node
        spot=Head;  //Set the spot to Head the dummy node of the list
		while((spot->next!=NULL) ){ spot=spot->next; }  //While loop for getting the spot
		return spot;    //Return the spot
    }
    void InsertEnd(Node *Ready,Node *node){ //Function for Inserting the node to the end of the list
        Node *spot = new Node();    //Create a new node
        spot=Ready; //set spot to Ready the dummy node of the list
        while(spot->next!=NULL && ((spot->next->priority) >= (node->priority))){    //While loop for getting the spot in decending priority order
            spot=spot->next;    //Incremet the spot
        }
        node->next=spot->next;  //Set the new node's next to spot next
		spot->next=node;    //Set spot next to new node
    }
    void RoundRobin(Node *Head, Node *Ready, Node *Run, Node *Final, ofstream &outFile){    //Function to do RoundRobin scheduler
        Node *next = new Node();    //Create a new node
        Node *done = new Node();    //Create a new node
        Node *curr = new Node();    //Create a new node
        curr=Head->next;       //Set Curr to Head next
        Head->next=curr->next;  //Set HEad next to curr next
        curr->next=NULL;    //Set curr next to null 
        Run->next=curr;     //Put curr to Run queue
        for(int t=0;t<96;t++){  //For loop for counting time from 0 to 95
            if(curr->BT==0){    //If statement for curr Burst Time to 0
                done=curr;  //Set done to curr
                Insert(Final, done);    //Insert done to the end of final
                if(Ready->next==NULL){break;}   //If statement for checking if the Ready queue is empty
                curr=Ready->next;   //Set Ready's next to curr
                Ready->next=curr->next; //Set curr next to Ready next 
                curr->next=NULL;    //Set curr to NULL
                Run->next=curr;     //Put curr to Run queue
                curr->WT=curr->WT+(t-curr->ET); //Algorithm to slove for Wait Time
                curr->ET=t;     //Update End Time
                outFile << "Time: " << t << " New Process " << curr->process << " Run Process " << done->process << endl;   //To output the data to an txt file
            }
            if(Head->next!=NULL){   //If loop to check if there are anymore process 
                if(t==Head->next->AT){  //If loop for when the tie is equal to the arrival Time of the process
                    Node *ready = new Node();   //Create a new node
                    ready=Head->next;       //Set Head next to Ready
                    Head->next=ready->next; //Set ready next to Head next
                    ready->next=NULL;   //Set ready next to NULL
                    next=Ready->next;   //Set Ready next to next 
                    Ready->next=ready;  //put the new arrived process in ready
                    ready->next=next;   //Set next to ready next
                    if(Run->next==NULL){    //If there is nothing in the run state put the new arrived process in run state
                        Ready->next=next;   //Set next to Ready next
                        ready->next=NULL;   //Set Ready next to NULL
                        Run->next=ready;    //Put ready to Run queue
                    }else if(curr->priority<ready->priority){    //Check for priority
                        next=curr;          //Set curr to next
                        Run->next=NULL;         //Clear Run queue
                        InsertEnd(Ready, next); //Insert done to the end of final
                        curr=Ready->next;   //Set Ready's next to curr
                        Ready->next=curr->next; //Set curr next to Ready next 
                        curr->next=NULL;    //Set curr to NULL
                        curr->ET=t;     //Update End Time
                        curr->WT=curr->WT+(t-curr->ET); //Algorithm to slove for Wait Time
                        Run->next=curr; //Put curr to Run queue
                        outFile << "Time: " << t << " New Process " << curr->process << " Run Process " << next->process << endl;   //To output the data to an txt file
                    }
                }
            }
            if(Ready->next!=NULL){  //If statement to check if the Ready queue is empty
                if(t%10==0 && curr->priority<=Ready->next->priority){  //Check for quantum=10 and priority
                    next=curr;          //Set curr to next
                    Run->next=NULL;         //Clear Run queue
                    InsertEnd(Ready, next); //Insert done to the end of final
                    curr=Ready->next;   //Set Ready's next to curr
                    Ready->next=curr->next; //Set curr next to Ready next 
                    curr->next=NULL;    //Set curr to NULL
                    curr->WT=curr->WT+(t-curr->ET); //Algorithm to slove for Wait Time
                    curr->ET=t;     //Update End Time
                    Run->next=curr; //Put curr to Run queue
                    outFile << "Time: " << t << " New Process " << curr->process << " Run Process " << next->process << endl;   //To output the data to an txt file
                }
            }
            curr->BT--;     //Decrement Burst Time
            curr->ET++;     //Increment End Time
        } 
       PrintTime(Final, outFile);   //Print the finished process in Final queue
    }
    void PrintTime(Node *Final, ofstream &outFile){ //Function for printing the Final queue
        Node *temp = new Node();    //Create a new node
        temp=Final->next;   //Set temp to Final next
        while(temp!=NULL){  //While loop for checking if it is at the end of the queue
            temp->TT+=temp->WT; //Algorithm to slove for Turnaround Time
            outFile << "Process " << temp->process << ": " << temp->process << ", " << temp->TT << ", " << temp->WT << endl;    //To output the data to an txt file
            temp=temp->next;    //Increment temp
        }
    }
};

int main(int argc,char* argv[]) {   //Main
    ifstream inFile(argv[1]);   //Create a stream for inFile from argv 1
    ofstream outFile(argv[2]);  //Create a stream for outFile from argv 2
    Linklist *Start = new Linklist;     //Create a new Linklist
    Linklist :: Node *Head = Start->Head(); //Create a new linklist with dummy node
    Start->constructLL(inFile, Head);   //Call construct Linklist
    Linklist :: Node *Ready = Start->Head();    //Create a new linklist with dummy node
    Linklist :: Node *Run = Start->Head();  //Create a new linklist with dummy node
    Linklist :: Node *Final = Start->Head();    //Create a new linklist with dummy node
    Start->RoundRobin(Head, Ready, Run, Final, outFile);    //Call RoundRobin
    inFile.close();     //Close inFile
	outFile.close();    //Close outFile
}