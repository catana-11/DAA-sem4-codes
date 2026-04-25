#include <iostream>

#include <fstream>

using namespace std;

class employee {
public:
    int empid;
    string name;

};

class hashing {

public:

    // init file with empty records
    hashing() {
        
        ofstream file("emp.txt");

        for (int i = 0; i < 10; i++) {
            file << -1 << " " << "NULL" << endl;
        }

        file.close();
    }

    // read entire file into array
    void load(employee arr[]) {
        ifstream file("emp.txt");

        for (int i = 0; i < 10; i++) {
            file >> arr[i].empid >> arr[i].name;
        }

        file.close();
    }

    // write array back to file
    void save(employee arr[]) {
        ofstream file("emp.txt");

        for (int i = 0; i < 10; i++) {
            file << arr[i].empid << " "  << arr[i].name << " "      << endl;
        }

        file.close();
    }

    void display() {
        employee arr[10];
        load(arr);

        cout << "\n...hashtable...\n";
        for (int i = 0; i < 10; i++) {
            cout << i << ": "  << arr[i].empid << " " << arr[i].name << " " << endl;
        }
    }

    void insert_without_replacement() {

        employee arr[10];
        load(arr);

        employee e;
        cout << "Enter id: "; cin >> e.empid;
        cout << "Enter name: "; cin >> e.name;

        int loc = e.empid % 10;   // hash fn
        
        // Case 1: slot empty, insert directly
        if (arr[loc].empid == -1) {
            arr[loc] = e;
        }
        else {
            // Case 2: collision : search next empty slot
            int i;
            for (i = (loc + 1) % 10; i != loc; i = (i + 1) % 10) {

                if (arr[i].empid == -1) {
                    arr[i] = e;   // insert at next free position
                    break;
                }
            }

            if (i == loc) {
                cout << "Table is full!\n";
            }
        }

        save(arr);
    }


    void insert_with_replacement() {

        employee arr[10];
        load(arr);

        employee e;
        cout << "Enter id: "; cin >> e.empid;
        cout << "Enter name: "; cin >> e.name;

        int loc = e.empid % 10;

        // Case 1: empty slot
        if (arr[loc].empid == -1) {
            arr[loc] = e;
        }
        else {

            int existing_hash = arr[loc].empid % 10; // jo pehle se element tha

            // Case 2: agar vo home key nahi tha toh: 
            if (existing_hash != loc) {

                employee temp = arr[loc]; // store displaced element
                arr[loc] = e;             // place new element in correct position

                // reinsert displaced element
                for (int i = (loc + 1) % 10; i != loc; i = (i + 1) % 10) {

                    if (arr[i].empid == -1) {
                        arr[i] = temp;
                        break;
                    }
                }
            }

            // Case 3: dono keys home key hai
            else {
                int i;
                for (i = (loc + 1) % 10; i != loc; i = (i + 1) % 10) {

                    if (arr[i].empid == -1) {
                        arr[i] = e;
                        break;
                    }
                }

                if (i == loc) {
                    cout << "Table full!\n";
                }
            }
        }

        save(arr);
    }

    void search() {
        employee arr[10];
        load(arr);

        int key;
        cout << "Enter id to search: ";
        cin >> key;

        int loc = key % 10;

        for (int i = loc; ; i = (i + 1) % 10) {

            if (arr[i].empid == -1) {
                cout << "Not found\n";
                return;
            }

            if (arr[i].empid == key) {
                cout << "Found at index " << i << endl;
                cout << arr[i].empid << " "<< arr[i].name << " "<< endl;
                return;
            }

            if ((i + 1) % 10 == loc) {
                cout << "Not found\n";
                return;
            }
        }
    }
};

int main() {

    hashing h;
    int ch;

    do {
        cout << "\n1.Display\n2.Insert Without Replacement\n3.Insert With Replacement\n4.Search\n5.Exit\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: h.display(); break;
            case 2: h.insert_without_replacement(); break;
            case 3: h.insert_with_replacement(); break;
            case 4: h.search(); break;
        }

    } while (ch != 5);

    return 0;
}