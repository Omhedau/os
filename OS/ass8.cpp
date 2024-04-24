#include<bits/stdc++.h>
using namespace std;


void fcfs(int arr[],int head,int size){
    int seekCount = 0;
    int curr_track;
   for(int i=0;i<size;i++){
      curr_track = arr[i];
      seekCount += abs(head - curr_track);
      head = curr_track;
   }
   cout<<"seek Count = "<<seekCount<<endl;
}

void sstf(int arr[],int head,int size){
     int seekCount = 0;
     int curr_track;

     vector<int>temp(arr,arr+size);

     while(!temp.empty()){
        auto it = min_element(temp.begin(),temp.end(),[head](int a,int b){
            return abs(a -head) < abs(b - head);
        });

        curr_track = *it;
        seekCount += abs(head - curr_track);
        head = curr_track;
     }
  
  cout<<"Total seek count in sstf is "<<seekCount<<endl;

}

int main(){
    int size;
    cout<<"Enter the number of requests ";
    cin>>size;

    int arr[size];
    string direction;

    int head;
    cout<<"Enter the initail position of disk head ";
    cin>>head;

    cout<<"Enter the request sequence ";
    for(int i=0;i<size;i++){
        cin>>arr[i];
    }

    char choice;
    cout << "Choose a disk scheduling algorithm:" << endl;
    cout << "a) First Come First Serve (FCFS)" << endl;
    cout << "b) Shortest Seek Time First (SSTF)" << endl;
    cout << "c) SCAN" << endl;
    cout << "d) Circular SCAN (C-SCAN)" << endl;
    cin >> choice;


    switch(choice){
        case 'a':
         fcfs(arr,head,size);
         break;
        case 'b':
         sstf(arr,head,size); 
         break;
        default:
         break;
    }



    return 0;
}