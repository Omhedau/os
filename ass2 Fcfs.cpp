/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include<bits/stdc++.h>
#include<iomanip>

using namespace std;

struct process {
    int pid;
    int arrival_time;
    int brust_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compareArrivalTime(process p1, process p2){
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2){
    return p1.pid < p2.pid;
}


int main(){
    int n;
    
    struct process p[100];
    float avg_turnarond_time;
    float avg_waiting_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    vector<int>order_Of_Execution;
    cout<<setprecision(2) <<fixed;
    
    cout<<"\n \n Enter the number of processes : ";
    cin>>n;
    
    cout<<endl;
    
    for(int i=0;i<n;i++){
        cout<<"enter the arrival time of process p"<<i+1<<" : ";
        cin>>p[i].arrival_time;
        cout<<"enter the brust time of the process p"<<i+1<<" : ";
        cin>>p[i].brust_time;
        p[i].pid = i+1;
    }
    
    sort(p,p+n,compareArrivalTime);
    
    for(int i=0;i<n;i++){
        
        if(i==0){
            p[i].start_time = p[i].arrival_time;
        }else{
            p[i].start_time = max(p[i-1].completion_time,p[i].arrival_time);
        }
        
        p[i].completion_time = p[i].start_time + p[i].brust_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time -p[i].brust_time;
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        
        
        order_Of_Execution.push_back(p[i].pid);
    }
    https://www.onlinegdb.com/online_c++_compiler#tab-stdin
    avg_waiting_time = (float)total_waiting_time / n;
    avg_turnarond_time = (float)total_turnaround_time / n;
    
    
    sort(p,p+n,compareID);
    
    int min_arrival_time = 1000000;
    int max_completion_time = -1;
    
    for(int i=0;i<n;i++){
        min_arrival_time = min(min_arrival_time,p[i].arrival_time);
        max_completion_time = max(max_completion_time,p[i].completion_time);
    }
    
    cout<<endl<<endl;
    
    cout<<"#P\t"<<"AT\t"<<"BT\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"\n"<<endl;
    
    for(int i=0;i<n;i++){
        cout<<p[i].pid<<"\t"<<p[i].arrival_time<<"\t"<<p[i].brust_time<<"\t"<<p[i].completion_time<<"\t"<<p[i].turnaround_time<<"\t"<<p[i].waiting_time<<"\t"<<"\n";
    }
    
    cout<<endl;      
    cout<<"Avg turnaround_time is "<<avg_turnarond_time<<endl;
    cout<<"Avg waiting_time is "<<avg_waiting_time<<endl;
    
    
    return 0;
}