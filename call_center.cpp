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

        for (int i = 0; i < num_employee; i++) {
            cout << occupied[i] << " ";
        }
        cout << endl;

        getEmployeeInfo();
        cout << "Allah" << endl;
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
        string name;
        cout << "Enter name of caller : " << endl;
        cin >> name;
    }
    void endCall() {
        string name;
        cout << "Enter name of the caller to end call : " << endl;
        cin >> name;

        for (int i = 0; i < num_employee; i++) {
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
                cout << "In the waiting list: " << endl;
                while (temp.size() != 0) {
                    cout << temp.front() << endl;
                    temp.pop();
                }
            }
            cout << endl;
        }
    }
};

int main() {
    CallCenter center(4, 3);

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