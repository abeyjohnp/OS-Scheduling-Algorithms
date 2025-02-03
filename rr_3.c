#include <stdio.h>
struct Process
{
    int id, wt, tat, bt, ct, rem_tym;
};
int Process_Queue[10];
int front=-1, rear=-1;
void enqueue(int x)
{
    if (rear==9)
    {
        printf("Process Limit Exceeded !! Error");
    }
    else if (rear == -1)
    {
        front=0,rear=0;
        Process_Queue[rear]=x;
    }
    else
    {
        rear++;
        Process_Queue[rear]=x;
    }
}

int dequeue()
{
    int item;
    if (front==-1)
    {
        printf("Error");
    }
    else if (front==rear)
    {
        item = Process_Queue[front];
        front=-1,rear=-1;
        return (item);
        
    }
    else
    {
        item = Process_Queue[front];
        front++;
        return (item);
    }
}
void rr(struct Process P[], int n, int tq)
{
    int avg_wt=0, avg_tat=0, completed=0, time=0;
    int time_array[100];
    int process_print_array[100];
    int j=0;
    int k=0;
    int p=0;

    for (int i = 0; i < n; i++) 
    {
        P[i].rem_tym= P[i].bt;
        enqueue(i); 
    }

    while (completed < n)
    {
        int i = dequeue();

        if (P[i].rem_tym > tq) 
        {
            process_print_array[p++] = P[i].id; 
            k++;
            time+=tq;
            time_array[j++]=time;
            P[i].rem_tym-=tq;
            enqueue(i);
        }

        else 
        {
            process_print_array[p++] = P[i].id; 
            k++;
            time += P[i].rem_tym;
            time_array[j++]=time;
            P[i].rem_tym = 0;
            P[i].ct = time;
            completed++;
        }
    }

    printf("Gantt Chart : \n");
    for (int i=0; i<8*k*2 ; i++)
    {
        printf("-");
    }
    printf("\n");

    for (int i=0 ; i<p ; i++)
    {
        if (i>1 && (process_print_array[i-1]==process_print_array[i]))
        {
            printf("\t  \t");
        }
        else
        {
            printf("|\tP%d\t",process_print_array[i]);
        }
    }

    printf("|\n");
    for (int i=0; i<8*k*2 ; i++)
    {
        printf("-");
    }
    printf("\n");

    printf("0");
    for (int i=0 ; i<j ; i++)
    {
        printf("\t\t%d",time_array[i]);
    }

    for (int i = 0; i < n; i++) 
    {
        P[i].tat = P[i].ct;
        P[i].wt = P[i].tat - P[i].bt;
        avg_wt += P[i].wt;
        avg_tat += P[i].tat;
    }

    printf("\nThe Average Waiting Time : %.2f ms\n", (float) avg_wt / n);
    printf("The Average Turn Around Time : %.2f ms\n", (float) avg_tat / n);

    printf("\nPROCESS\tBURST TIME\tCOMPLETION TIME\tTURNAROUND TIME\tWAITING TIME\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", P[i].id, P[i].bt, P[i].ct, P[i].tat, P[i].wt);
    }


    

}

void main()
{
    int n,tq;
    printf("\t ROUND ROBIN SCHDULING ALGORITHM \n");
    struct Process P[10];
    printf("Enter the number of processes : ");    
    scanf("%d", &n);    
    for (int i=0 ;i<n ;i++)
    {
        printf("Enter the Process ID : ");
        scanf("%d", &P[i].id);
        printf("Enter the Burst Time (#%d) : ",P[i].id);
        scanf("%d", &P[i].bt);
    }
    printf("Enter the Quantum Time Slice : ");
    scanf("%d", &tq);
    rr(P,n,tq);
}
