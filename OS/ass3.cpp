#include<bits/stdc++.h>
#include<unistd.h>
#include<string>
#include<cstring>
using namespace std;

int main(){
    int pipeParentToChild[2],pipeChildToParent[2];
    int pid;
    int return_status1, return_status2;
    char msg[200];
    
    return_status1 = pipe(pipeParentToChild);
    if(return_status1 == -1){
        cerr<<"Error : Unable to create pipe pipeParentToChild"<<endl;
    }
    
    return_status2 = pipe(pipeChildToParent);
    if(return_status2 == -1){
        cerr<<"Error : Unable to create pipe pipeChildToParent"<<endl;
    }
    
    pid = fork();
    
    if(pid>0){
        
    
        close(pipeParentToChild[0]);
        close(pipeChildToParent[1]);
        
        while(true){
        cout<<"Parent ==> Enter the message for child : ";
        cin.getline(msg,sizeof(msg));
        
        write(pipeParentToChild[1],msg,sizeof(msg));
        
        if(string(msg) == "exit")
        return 0;
        
        read(pipeChildToParent[0],msg,sizeof(msg));
        cout<<"Message from child : "<<msg<<endl;
        }
        
    }else{
        close(pipeParentToChild[1]);
        close(pipeChildToParent[0]);
        
        while(true){
            read(pipeParentToChild[0],msg,sizeof(msg));
        cout<<"Message from parent : "<<msg<<endl;
        
        if(string(msg) == "exit")
        return 0;
        
        cout<<"Child ==> Enter the Message for parent : ";
        cin.getline(msg,sizeof(msg));
        
        write(pipeChildToParent[1],msg,sizeof(msg));
        }
        
    }
    return 0;
}
