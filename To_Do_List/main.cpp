 #include<bits/stdc++.h>
 using namespace std;

 struct Task{
     string name;
     bool completed;
 };

 const int MAXIMUM_TASKS=1000;
 bool addTask(Task tasks[],int &nTasks,const string &name){
    if(nTasks+1==MAXIMUM_TASKS){
        cout<<"The TODO List is Full!!"<<endl;
        return false;
    }
    Task task;
    task.name=name;
    task.completed=false;
    tasks[nTasks++]=task;
    cout<<"Task added successfully!!"<<endl;
    return true;
 }

 bool isEmpty(int nTasks) {
    return nTasks == 0;
 }

 void viewTasks(const Task tasks[],int nTasks){
    cout<<"TODO List:"<<endl;
    for(int i=0;i<nTasks;i++){
        cout<<i+1<<".";
        if(tasks[i].completed){
            cout<<"[COMPLETED]";
        }
        else{
            cout<<"[PENDING]";
        }
        cout<<tasks[i].name<<endl;
    }
 }

 bool markTaskAsCompleted(Task tasks[],int nTasks,int idx){
    if(idx<0||idx>=nTasks){
        cout<<"Task number "<<(idx+1)<<"is not available.Please try again."<<endl;
        return false;
    }
    tasks[idx].completed=true;
    cout<<"Task marked as completed!!"<<endl;
    return true;
 }

 bool removeTask(Task tasks[],int &nTasks,int idx){
     if(idx<0||idx>=nTasks){
        cout<<"Task number"<<(idx+1)<<" is not available. Please try again."<<endl;
        return false;
     }

     for(int i=idx;i<nTasks-1;i++){
        tasks[i]=tasks[i+1];
     }
     nTasks--;
     cout<<"Task removed successfully!!"<<endl;
     return true;
 }

 int main(){
     Task tasks[MAXIMUM_TASKS];
     int nTasks=0;
     while(true){
        cout<<"\n======== TODO List Options ======"<<endl;
        cout<<"1.Add Task"<<endl;
        cout<<"2.View Tasks"<<endl;
        cout<<"3.Mark Task as Completed"<<endl;
        cout<<"4.Remove Task"<<endl;
        cout<<"5.Remove All Tasks"<<endl;
        cout<<"6.Exit"<<endl;
        int choice;
        cout<<"Enter your choice(1-6):";
        cin>>choice;
        cin.ignore();
        cout<<endl;
        switch(choice){
            case 1:{
                while(true){
                    cout<<"Enter the task name:";
                    string name;
                    getline(cin,name);
                    addTask(tasks,nTasks,name);
                    cout<<"Do you want to add another task?(yes/no):";
                    string anotherTask;
                    cin>>anotherTask;
                    if(anotherTask!="yes"){
                        break;
                    }
                    cin.ignore();
                }
                break;
            }
            case 2:
                if(isEmpty(nTasks)) {
                    cout<<"There are no tasks currently to view...\n";
                    break;
                }
                viewTasks(tasks,nTasks);
                break;
            case 3:{
                if(isEmpty(nTasks)) {
                    cout<<"There are no tasks to mark as completed...\n";
                    break;
                }
                viewTasks(tasks,nTasks);
                cout<<"Enter the task number to mark as completed: ";
                int mark;
                cin>>mark;
                markTaskAsCompleted(tasks,nTasks,mark-1);
                break;
            }
            case 4:{
                if(isEmpty(nTasks)){
                    cout<<"There are no tasks to remove...\n";
                    break;
                }
                viewTasks(tasks,nTasks);
                cout<<"Enter the task number to remove:";
                int remove;
                cin>>remove;
                removeTask(tasks,nTasks,remove-1);
                break;
            }
            case 5:{
                nTasks=0;
                cout << "Tasks removed successfully..\n";
            }
                break;
            case 6:
                cout<<"Exiting from the To_List "<<endl;
                return 0;
            default:
                cout<<"Invalid choice!! Please select a valid option from (1-5)."<<endl;
                break;
            cout<<endl;
        }
     }
     return 0;
 }

