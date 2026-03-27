#include<stdio.h>
struct process{
    int pid,at,bt,ct,tat,wt,rt;
};
int main(){
    struct process p[20];
    int visited[20]={0};
    int front=0,rear=0;
    int time=0;
    int completed=0;
    int queue[100];
    int n,tq;
    float avgwt=0.0,avgtat=0.0;
    printf("enter the number of process: \n");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("enter the Arrival Time for P%d ",i+1);
        scanf("%d",&p[i].at);
        printf("enter the Burst Time for P%d ",i+1);
        scanf("%d",&p[i].bt);
        p[i].rt=p[i].bt;
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                struct process temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    printf("\n enter the time quantum: ");
    scanf("%d",&tq);
    while(completed<n){
        for(int i=0;i<n;i++){
            if(p[i].at<=time && visited[i]==0){
                queue[rear++]=i;
                visited[i]=1;
            }
        }
        if(front==rear){
            time++;
            continue;
        }
        int idx=queue[front++];
        if(p[idx].rt>tq){
            p[idx].rt-=tq;
            time+=tq;
        }
        else{
            time+=p[idx].rt;
            p[idx].rt=0;
            p[idx].ct=time;
            p[idx].tat=p[idx].ct-p[idx].at;
            p[idx].wt=p[idx].tat-p[idx].bt;
            avgwt+=p[idx].wt;
            avgtat+=p[idx].tat;
            completed++;
        }
        for(int i=0;i<n;i++){
            if(p[i].at<=time && visited[i]==0){
                queue[rear++]=i;
                visited[i]=1;
            }
        }
        if(p[idx].rt>0){
            queue[rear++]=idx;
        }
    }
    printf("\n--- Round Robin Scheduling ---\n");
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
}

    printf("\nAverage TAT = %.2f",avgtat/n);
    printf("\nAverage WT = %.2f\n",avgwt/n);

    return 0;
}
