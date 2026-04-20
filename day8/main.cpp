#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class employee{

    int empid;
    string name;
    string address;

    friend class hashing;

};

class hashing{
    employee E;

    public:

        hashing(){

            fstream file("emp.txt", ios::out | ios::binary);

            for(int i=0; i<10; i++){

                E.empid = -1; 
                E.name = "..."; 
                E.address = "...";

                file.write((char*)&E, sizeof(E)); // (char*)&E --> converts object to raw bytes
            }

            file.close();
        }



        void display(){
            employee s;

            cout<<".........hash table.........."<<endl;
            fstream file("emp.txt", ios::in | ios::binary);

            int i = 0;

            while(file.read((char*)&s, sizeof(s))){
                // reads one obj at a time
                cout<<i<<": "<<s.empid<<", "<< s.name<<", "<<s.address<<endl;
                i++;
            }

            file.close();
        }





        void linear_probing_without_replacement(){

            char cont = 'y';

            fstream file("emp.txt", ios::in | ios::out | ios::binary);

            do {

                employee e, e1, e2;

                cout<<"Enter id: "; cin>>e.empid;
                cout<<"Enter name: "; cin>>e.name;
                cout<<"Enter address: "; cin>>e.address;

                int loc = e.empid % 10;  // hash fn

                file.seekg(loc*sizeof(e), ios::beg);  // jump to exact pos in file

                file.read((char*)&e1, sizeof(e1));      // read record at that index into e1

                if (e1.empid == -1){

                    file.seekp(loc*sizeof(e), ios::beg);
                    file.write((char*)&e, sizeof(e));
                }

                else{

                    int i;
                    for(i = (loc+1)%10; i != loc; i = (i+1)%10){

                        file.seekg(i*sizeof(e), ios::beg);

                        file.read((char*)&e2, sizeof(e2));

                        if (e2.empid == -1){
                            file.seekp(i*sizeof(e), ios::beg);   
                            file.write((char*)&e, sizeof(e));
                            break;
                        }
                    }

                    if(i == loc){
                        cout<<"table is full!"<<endl;
                    }
                }

                cout<<"\nDo you want to continue: "; 
                cin>>cont;

            } while(cont=='y');

            file.close();
        }


        void linear_probing_with_replacement(){

            char cont = 'y';

            fstream file("emp.txt", ios::in | ios::out | ios::binary);

            do{

                employee e, e1, e2;
                cout<<"Enter id: "; cin>>e.empid;
                cout<<"Enter name: "; cin>>e.name;
                cout<<"Enter address: "; cin>>e.address;

                int loc = e.empid % 10;

                file.seekg(loc*sizeof(e), ios::beg);
                file.read((char*)&e1, sizeof(e1));

                // Case 1: Empty 
                if(e1.empid == -1){
                    file.seekp(loc*sizeof(e), ios::beg);
                    file.write((char*)&e, sizeof(e));
                }

                else{
                    int existing_hash = e1.empid % 10;

                    // Case 2: Replacement 

                    if(existing_hash != loc){  // if not home key

                        // place new element at loc (home key)
                        file.seekp(loc*sizeof(e), ios::beg);
                        file.write((char*)&e, sizeof(e));

                        // reinsert old element (e1) (the one which wasny home key)
                        for(int i = (loc+1)%10; i != loc; i = (i+1)%10){

                            file.seekg(i*sizeof(e), ios::beg);
                            file.read((char*)&e2, sizeof(e2));

                            if(e2.empid == -1){
                                file.seekp(i*sizeof(e), ios::beg);
                                file.write((char*)&e1, sizeof(e1));
                                break;
                            }
                        }
                    }

                    // Case 3: No replacement, normal probing
                    else{

                        int i;
                        for(i = (loc+1)%10; i != loc; i = (i+1)%10){

                            file.seekg(i*sizeof(e), ios::beg);
                            file.read((char*)&e2, sizeof(e2));

                            if(e2.empid == -1){
                                file.seekp(i*sizeof(e), ios::beg);
                                file.write((char*)&e, sizeof(e));
                                break;
                            }
                        }

                        if(i == loc){
                            cout<<"Hash table is full!"<<endl;
                        }
                    }
                }

                cout<<"\nDo you want to continue: ";
                cin>>cont;

            } while(cont=='y');

            file.close();
        }

        void search_record(){

            int key;
            cout<<"Enter employee id to search: ";
            cin>>key;

            fstream file("emp.txt", ios::in | ios::binary);

            employee e;
            int loc = key % 10;

            int i;
            for(i = loc; ; i = (i+1)%10){

                file.seekg(i*sizeof(e), ios::beg);
                file.read((char*)&e, sizeof(e));


                if(e.empid == -1){
                    cout<<"Record not found!"<<endl;
                    break;
                }


                if(e.empid == key){
                    cout<<"Record found at index "<<i<<endl;
                    cout<<"ID: "<<e.empid<<endl;
                    cout<<"Name: "<<e.name<<endl;
                    cout<<"Address: "<<e.address<<endl;
                    break;
                }

                // full loop
                if((i+1)%10 == loc){
                    cout<<"Record not found!"<<endl;
                    break;
                }
            }

            file.close();
        }

        void modify_record(){

            int key;
            cout<<"Enter employee id to modify: ";
            cin>>key;

            fstream file("emp.txt", ios::in | ios::out | ios::binary);

            employee e;
            int loc = key % 10;

            int i;
            for(i = loc; ; i = (i+1)%10){

                file.seekg(i*sizeof(e), ios::beg);
                file.read((char*)&e, sizeof(e));

                if(e.empid == -1){
                    cout<<"Record not found!"<<endl;
                    break;
                }

                if(e.empid == key){

                    cout<<"Record found. Enter new details:"<<endl;
                    cout<<"New name: ";
                    cin>>e.name;
                    cout<<"New address: ";
                    cin>>e.address;

                    // move write pointer to same position
                    file.seekp(i*sizeof(e), ios::beg);
                    file.write((char*)&e, sizeof(e));

                    cout<<"Record updated successfully!"<<endl;
                    break;
                }

                if((i+1)%10 == loc){
                    cout<<"Record not found!"<<endl;
                    break;
                }
            }

            file.close();
        }
};

int main(){

    hashing h;

    int choice;

    do{
        cout<<"\n1. Display";
        cout<<"\n2. Insert (without replacement)";
        cout<<"\n3. Insert (with replacement)";
        cout<<"\n4. Search";
        cout<<"\n5. Modify";
        cout<<"\n6. Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;

        switch(choice){

            case 1: 
                h.display(); 
                break;

            case 2: 
                h.linear_probing_without_replacement(); 
                break;

            case 3: 
                h.linear_probing_with_replacement(); 
                break;

            case 4: 
                h.search_record(); 
                break;

            case 5: 
                h.modify_record(); 
                break;

        }

    } while(choice != 6);

    return 0;
}