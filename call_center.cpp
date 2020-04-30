#include <bits/stdc++.h>

using namespace std;

// Class for queue
template <typename T>
class CallQueue {
    T* arr;        // array to store queue elements
    int capacity;  // maximum capacity of the queue
    int front;     // front points to front element in the queue (if any)
    int rear;      // rear points to last element in the queue
    int count;     // current size of the queue

    public:
    CallQueue();                     // constructor
    CallQueue(const CallQueue& cp);  // copy constructor
    ~CallQueue();                    // destructor
    void setSize(int size);

    void dequeue();
    void enqueue(T x);
    void deepCopy(const CallQueue& cp);
    T peek();
    int size();
    bool empty();
    bool isFull();
};

// Constructor to initialize queue
template <typename T>
CallQueue<T>::CallQueue() {
    front = 0;
    rear = -1;
    count = 0;
}

template <typename T>
void CallQueue<T>::setSize(int size) {
    arr = new T[size];
    capacity = size;
}

template <typename T>
CallQueue<T>::CallQueue(const CallQueue& cp) {
    arr = new T[cp.capacity];
    capacity = cp.capacity;
    for (int i = 0; i < cp.capacity; i++) {
        this->arr[i] = cp.arr[i];
    }
    // copy(begin(cp.arr),end(cp.arr),begin(arr));
    this->front = cp.front;
    this->rear = cp.rear;
    this->count = cp.count;
}

// Destructor to free memory allocated to the queue
template <typename T>
CallQueue<T>::~CallQueue() {
    delete arr;
}

template <typename T>
void CallQueue<T>::deepCopy(const CallQueue& cp) {
    capacity = cp.capacity;
    for (int i = 0; i < cp.capacity; i++) {
        this->arr[i] = cp.arr[i];
    }
    this->front = cp.front;
    this->rear = cp.rear;
    this->count = cp.count;
}

// Utility function to remove front element from the queue
template <typename T>
void CallQueue<T>::dequeue() {
    // check for queue underflow
    if (empty()) {
        cout << "UnderFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    front = (front + 1) % capacity;
    count--;
}

// Utility function to add an item to the queue
template <typename T>
void CallQueue<T>::enqueue(T item) {
    // check for queue overflow
    if (isFull()) {
        cout << "OverFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

// Utility function to return front element in the queue
template <typename T>
T CallQueue<T>::peek() {
    if (empty()) {
        cout << "UnderFlow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}

// Utility function to return the size of the queue
template <typename T>
int CallQueue<T>::size() {
    return count;
}

// Utility function to check if the queue is empty or not
template <typename T>
bool CallQueue<T>::empty() {
    return (size() == 0);
}

// Utility function to check if the queue is full or not
template <typename T>
bool CallQueue<T>::isFull() {
    return (size() == capacity);
}

class CallCenter {
    private:
    CallQueue<string>* desks;
    vector<string> employees;
    int num_employee;
    int max_queue_size;

    public:
    CallCenter(int num_employee, int max_queue_size) {
        this->num_employee = num_employee;
        this->max_queue_size = max_queue_size;

        desks = new CallQueue<string>[num_employee];

        for (int i = 0; i < num_employee; i++) {
            desks[i].setSize(max_queue_size);
        }

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

    void displayEmployeeInfo() {
        cout << "The names of the employees along with their I'd number's are: " << endl;
        for (int i = 0; i < num_employee; i++) {
            cout << "#" << i + 1 << " " << employees[i] << endl;
        }
        cout << endl;
    }

    void newCall(ofstream& logfile) {
        vector<int> queue_sizes(num_employee);

        for (int i = 0; i < num_employee; i++) {
            queue_sizes[i] = desks[i].size();
        }

        auto min_ele = min_element(queue_sizes.begin(), queue_sizes.end());
        int min_ele_index = min_ele - queue_sizes.begin();
        int min_ele_value = *min_ele;

        if (min_ele_value == max_queue_size) {
            cout << "\nCall center operating at maximum capacity.\nPlease call again after some time.\n"
                 << endl;
            // Adding the max capacity reached status to the log file
            logfile << "Incoming call disconnected as maximum capacity reached\n"
                    << endl;
        } else {
            string name;
            cout << "Enter name of caller : " << endl;
            cin >> name;
            desks[min_ele_index].enqueue(name);
            // Adding the new call status to the log file
            // getting current time and appending to log.txt
            time_t t = time(0);
            char* st = ctime(&t);
            logfile << "Caller " << name << " entered " << employees[min_ele_index]
                    << "'s call queue at - " << st << endl;
        }
    }
    void endCall(ofstream& logfile) {
        string name;
        cout << "Enter name of the caller to end call : " << endl;
        cin >> name;
        bool nameFound = false;
        CallQueue<string>* toCheck;
        CallQueue<string>* checked;
        for (int i = 0; i < num_employee; i++) {
            toCheck = new CallQueue<string>(desks[i]);
            checked = new CallQueue<string>();
            checked->setSize(max_queue_size);
            while (!toCheck->empty()) {
                if (toCheck->peek().compare(name) == 0) {
                    nameFound = true;
                } else {
                    checked->enqueue(toCheck->peek());
                }
                toCheck->dequeue();
            }
            cout << "checked size - " << checked->size() << endl;
            desks[i].deepCopy(*checked);
        }
        if (nameFound) {
            cout << "\nCaller " << name << " removed from the queue." << endl;
            // Adding the end call status to the log file
            // getting current time and appending to log.txt
            time_t t = time(0);
            char* st = ctime(&t);
            logfile << "Caller " << name << " ended the call at - " << st << endl;
        } else {
            cout << "\nNo callers named '" << name << "' found." << endl;
        }
    }
    void currentStatus() {
        CallQueue<string>* temp;
        for (int i = 0; i < num_employee; i++) {
            cout << "\nDesk #" << i + 1 << " attended by " << employees[i] << endl;
            if (desks[i].size() == 0) {
                cout << "Status: Free" << endl;
            } else {
                cout << "Status: Busy" << endl;
                temp = new CallQueue<string>(desks[i]);
                cout << "Currently Attending: ";
                cout << temp->peek() << endl;
                temp->dequeue();
                if (!temp->empty()) {
                    cout << "In the waiting list: " << endl;
                    while (!temp->empty()) {
                        cout << temp->peek() << endl;
                        temp->dequeue();
                    }
                } else {
                    cout << "No one in the waiting list." << endl;
                }
            }
            cout << endl;
        }
    }
};

// Function to search for a particular word in file
void nameSearch() {
    ifstream stream;
    stream.open("log.txt");
    string line, name;
    // get name to be searched
    cout << "Enter name of the employee - ";
    cin >> name;
    cout << endl;
    // go through every line in file
    int count = 0;
    while (getline(stream, line)) {
        // if match found we print out the entire line
        if (line.find(name) != 18446744073709551615UL) {
            cout << line << endl;
            count++;
        }
    }
    cout << endl;
    // if no match is found we print the name not found
    if (count == 0) {
        cout << name << " not found." << endl;
    }
    stream.close();
}

// Function to print out the entire log file
void displayLog() {
    ifstream stream;
    stream.open("log.txt");
    string line;
    // print the file line by line
    while (getline(stream, line)) {
        cout << line << endl;
    }
    stream.close();
}

int main() {
    int num_employee, max_queue_size;
    cout << "Enter number of employees: ";
    cin >> num_employee;
    cout << endl;
    cout << "Enter maximum size of queue: ";
    cin >> max_queue_size;
    cout << endl;

    CallCenter center(num_employee, max_queue_size);

    // opening log.txt file for writing
    ofstream logfile;
    logfile.open("log.txt");

    // getting current time and appending to log.txt
    time_t t = time(0);
    char* st = ctime(&t);
    logfile << "Call center opened on - " << st << endl;

    center.displayEmployeeInfo();

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
                center.newCall(logfile);
                break;
            case 2:
                center.endCall(logfile);
                break;
            case 3:
                center.currentStatus();
                break;
            case 4:
                t = time(0);
                st = ctime(&t);
                logfile << "Call center shutdown on - " << st << endl;
                logfile.close();
                cout << "\nCall center shutdown successfully.\n"
                     << endl;
                break;
            default:
                cout << "Invalid Choice. Try again." << endl;
                break;
        }
    }

    cout << "Entering administration mode..." << endl;
    choice = 0;
    while (choice != 3) {
        cout << "Do you want to: " << endl;
        cout << "1. Display entire log file" << endl;
        cout << "2. Search for work done by particular employee" << endl;
        cout << "3. Exit Admin mode." << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                cout << endl;
                displayLog();
                cout << endl;
                break;
            case 2:
                nameSearch();
                break;
            case 3:
                cout << "Exiting program." << endl;
                return 0;
                break;
            default:
                cout << "Invalid Choice. Try again." << endl;
                break;
        }
    }
    return 0;
}

// 3 3 1 2 3 1 a 1 b 1 c 1 d 1 e 1 f 1 g
// 2 2 1 2 1 a 1 b 1 c 1 d 1