#include<bits/stdc++.h>

using namespace std;

class CallCenter{
    private:
        queue<pair<int,string>> waiting_list;
        queue<pair<int,string>>* desks;
        bool* occupied;
        vector<string> employees;
        int num_employee;
    public:

    CallCenter(int num_employee){
        this->num_employee = num_employee;
        desks = new queue<pair<int,string>>[num_employee];
        occupied = new bool[num_employee];

        for(int i=0;i<num_employee;i++){
            cout<<occupied[i]<<" ";
        }cout<<endl;
        
        getEmployeeInfo();
        cout<<"Allah"<<endl;
    }

    void getEmployeeInfo(){
        cout<<"Enter names of all the employees : "<<endl;
        for(int i=0;i<num_employee;i++){
            string name;
            cin>>name;
            employees.push_back(name);
        }
    }

};


int main(){

    CallCenter center(4);

    int choice = 0;
    while(choice != 4){
        
    }

    return 0;
}