#include <bits/stdc++.h>

using namespace std;

class CallCenter {
    private:
    queue<string> waiting_list;
    queue<string>* desks;
    bool* occupied;
    vector<string> employees;
    int num_employee;
    int max_queue_size;

    public:
    CallCenter(int num_employee, int max_queue_size) {
        this->num_employee = num_employee;
        this->max_queue_size = max_queue_size;

        desks = new queue<string>[num_employee];
        occupied = new bool[num_employee];

        cout << endl;

        getEmployeeInfo();
        cout << endl;
    }

    void getEmployeeInfo() {
        cout << "Enter names of all the employees : " << endl;
        for (int i = 0; i < num_employee; i++) {
            string name;
            cin >> name;
            employees.push_back(name);
        }
    }

    void newCall() {
        vector<int> queue_sizes(num_employee);

        for (int i = 0; i < num_employee; i++) {
            queue_sizes[i] = desks[i].size();
        }

        auto min_ele = min_element(queue_sizes.begin(), queue_sizes.end());
        int min_ele_index = min_ele - queue_sizes.begin();
        int min_ele_value = *min_ele;

        if (min_ele_value == max_queue_size) {
            cout << "Call center operating at maximum capacity.\nPlease call again after some time." << endl;
        } else {
            string name;
            cout << "Enter name of caller : " << endl;
            cin >> name;
            desks[min_ele_index].push(name);
        }
    }
    void endCall() {
        string name;
        cout << "Enter name of the caller to end call : " << endl;
        cin >> name;
        bool nameFound = false;
        for (int i = 0; i < num_employee; i++) {
            queue<string> toCheck;
            toCheck = desks[i];
            queue<string> checked;
            int len = toCheck.size();
            while (!toCheck.empty()) {
                if (toCheck.front().compare(name) == 0) {
                    nameFound = true;
                } else {
                    checked.push(toCheck.front());
                }
                toCheck.pop();
            }
            desks[i] = checked;
        }
        if (nameFound) {
            cout << "Caller " << name << " removed from the queue." << endl;
        } else {
            cout << "No callers named '" << name << "' found." << endl;
        }
    }
    void currentStatus() {
        for (int i = 0; i < num_employee; i++) {
            cout << "\nDesk #" << i + 1 << " attended by " << employees[i] << endl;
            if (desks[i].size() == 0) {
                cout << "Status: Free" << endl;
            } else {
                cout << "Status: Busy" << endl;
                queue<string> temp;
                temp = desks[i];
                cout << "Currently Attending: ";
                cout << temp.front() << endl;
                temp.pop();
                if(!temp.empty()){
                    cout << "In the waiting list: " << endl;
                    while (!temp.empty()) {
                        cout << temp.front() << endl;
                        temp.pop();
                    }
                }else{
                    cout << "No one in the waiting list." << endl;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int num_employee, max_queue_size;
    cout << "Enter number of employees: ";
    cin >> num_employee;
    cout << endl;
    cout << "Enter maximum size of queue: ";
    cin >> max_queue_size;
    cout << endl;

    CallCenter center(num_employee, max_queue_size);
    ofstream logfile;
    logfile.open("log.txt");

    int choice = 0;
    while (choice != 4) {
        cout << "Call center running..." << endl;
        cout << "1. New Call" << endl;
        cout << "2. End Call" << endl;
        cout << "3. View Current Status" << endl;
        cout << "4. Shutdown Call center" << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                center.newCall();
                break;
            case 2:
                center.endCall();
                break;
            case 3:
                center.currentStatus();
                break;
            case 4:
                logfile << "Writing this to a file.\n";
                logfile.close();
                return 0;
                break;
            default:
                cout << "Invalid Choice. Try again." << endl;
                break;
        }
    }

    return 0;
}