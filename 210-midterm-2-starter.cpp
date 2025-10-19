#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int MIN_NR = 10,
    MAX_NR = 99,
    MIN_LS = 5,
    MAX_LS = 20;

class DoublyLinkedList 
{
    private: struct Node 
    {
        int data;
        Node * prev;
        Node * next;
        Node(int val, Node * p = nullptr, Node * n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node * head;
    Node * tail;

    public: DoublyLinkedList() 
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert_after(int value, int position) 
    {
        if (position < 0) 
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node * newNode = new Node(value);
        if (!head) 
        {
            head = tail = newNode;
            return;
        }

        Node * temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp -> next;
        if (!temp) 
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode -> next = temp -> next;
        newNode -> prev = temp;
        if (temp -> next)
            temp -> next -> prev = newNode;
        else
            tail = newNode;
        temp -> next = newNode;
    }

    void delete_val(int value) 
    {
        if (!head) return;
        Node * temp = head;
        while (temp && temp -> data != value)
            temp = temp -> next;
        if (!temp) return;
        if (temp -> prev)
            temp -> prev -> next = temp -> next;
        else
            head = temp -> next;
        if (temp -> next)
            temp -> next -> prev = temp -> prev;
        else
            tail = temp -> prev;
        delete temp;
    }

    void delete_pos(int pos) 
    {
        if (!head) 
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) 
        {
            pop_front();
            return;
        }

        Node * temp = head;
        for (int i = 1; i < pos; i++) 
        {
            if (!temp) 
            {
                cout << "Position doesn't exist." << endl;
                return;
            } else
                temp = temp -> next;
        }
        
        if (!temp) 
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp -> next) 
        {
            pop_back();
            return;
        }

        Node * tempPrev = temp -> prev;
        tempPrev -> next = temp -> next;
        temp -> next -> prev = tempPrev;
        delete temp;
    }

    void push_back(int v) 
    {
        Node * newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else 
        {
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v) 
    {
        Node * newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }

    int get_front_value() 
    {
        return head -> data;
    }

    int get_back_value() 
    {
        return tail -> data;
    }

    int get_value_at_position(int pos) 
    {
        Node *node = head;
        int idx = 0;
        while (node != nullptr && idx != pos)
        {
            idx++;
            node = node -> next;
        }

        if (node != nullptr)
        {
            return node -> data;
        }

        return -1;
    }

    void pop_front() 
    {
        if (!head) 
        {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;
        if (head -> next) 
        {
            head = head -> next;
            head -> prev = nullptr;
        } 
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() 
    {
        if (!tail) 
        {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = tail;
        if (tail -> prev) 
        {
            tail = tail -> prev;
            tail -> next = nullptr;
        } 
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() 
    {
        while (head) 
        {
            Node * temp = head;
            head = head -> next;
            delete temp;
        }
    }

    void print(vector<string> names) 
    {
        Node * current = head;
        if (!current) 
        {
            cout << "List is empty." << endl;
            return;
        }

        while (current) 
        {
            cout << "\t\t" << names[current -> data] << endl;
            current = current -> next;
        }
    }

    void print_reverse() 
    {
        Node * current = tail;
        if (!current) 
        {
            cout << "List is empty." << endl;
            return;
        }

        while (current) 
        {
            cout << current -> data << " ";
            current = current -> prev;
        }

        cout << endl;
    }
};

int main() 
{
    srand(time(0)); // Comment #1: Seed the random number generator.

    vector<string> names; // Comment #2: Vector to store names from file.
    string name;

    ifstream inFile("names.txt"); // Comment #3: Open the file names.txt for reading.

    while (getline(inFile, name)) // Comment #4: Read each name from the file and add to the vector until the end of file is reached.
    {
        names.push_back(name); // Comment #5: Add the read name to the vector.
    }
    
    inFile.close(); // Comment #6: Close the file after reading all names.

    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning

    DoublyLinkedList list; // Comment #7: Create a DoublyLinkedList object.

    cout << endl << "Store opens:" << endl;
    // Comment #8: Read 5 names randomly from vector.
    for (int i = 0; i < 5; ++i)
    {
        int randNum = rand() % 100; // Comment #9: Generate random number from 0 to 99.
        cout << "\t" << names[randNum] << " joins the line" << endl;      
        list.push_back(randNum); // Comment #10: Storing random number in the linked list instead of names.
    }

    cout << "\tResulting Line:" << endl;

    list.print(names); // Comment #11: Print the names in the linked list.

    for (int i = 1; i < 20; ++i) // Comment #12: Simulate 19 time steps.
    {
        cout << "Tme step #" << i + 1 << ":" << endl;
        int prob = rand() % 100 + 1;  // Comment #13: Returns random number 1-100.

        if (prob <= 10)
        {
            // Comment #14: Add VIP to front of line with 10% chance.
            int randNum = rand() % 100;
            cout << "\t" << names[randNum] << " (VIP) joins the front of the line" << endl;      
            list.push_front(randNum);

            // Comment #15: Random person leaves line from random position for 10% chance.
            int randPosLeaveLine = rand() % 5;
            int nodeValue = list.get_value_at_position(randPosLeaveLine);
            if (nodeValue != -1)
            {
                string nameLeftLine = names[nodeValue];
                list.delete_pos(randPosLeaveLine);
                cout << "\t" << nameLeftLine << " (at the rear) left the line" << endl;
            }
        }

        if (prob <= 20) // Comment #16: 20% chance that person at back leaves line and removed from the back.
        {
            int backValue = list.get_back_value();
            string nameLeftLine = names[backValue];
            cout << "\t" << nameLeftLine << " left the line" << endl;
            list.pop_back();
        }

        if (prob <= 40) // Comment #17: 40% chance that person at front is served and remmoved from the front.
        {
            int frontValue = list.get_front_value();
            string nameIsServed = names[frontValue];
            cout << "\t" << nameIsServed << " is served" << endl;
            list.pop_front();
        }

        if (prob <= 60) // Comment #18: 60% chance that a new person joins the line and added to the back.
        {
            int randNum = rand() % 100;
            cout << "\t" << names[randNum] << " joined the line" << endl;      
            list.push_back(randNum);
        }

        cout << "\tResulting Line:" << endl;

        list.print(names);
    }

    return 0;
}