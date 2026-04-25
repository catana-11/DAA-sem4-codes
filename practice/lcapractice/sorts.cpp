// implement sequential, binary search, quick and merge sort


#include <iostream>
#include <string>

using namespace std;

class student{

    private: 
        string name;
        int id;

    public:

        void display(student A[], int n){
            cout<<"\nDisplaying student data: \n";

            for (int i=0; i<n; i++){
                cout<<"["<<A[i].name<<", "<<A[i].id<<"]"<<endl;
            }

        }

        void linearsearch(student A[], int n, int key){

            for(int i=0; i<n; i++){
                if (A[i].id == key){
                    cout<<"\nFound at index: "<<i;
                    return;

                }

            }

            cout<<"\nID does not exist in this database";
        }

        void quicksort(student A[], int low, int high){

            if(low<high){

                int j = partition(A, low, high);

                quicksort(A, low, j-1);
                quicksort(A, j+1, high);
            }

        }

        int partition(student A[], int low, int high){

            int i = low; int j = high; int pivot = A[low].id;

            while(i<j){

                while (A[i].id<=pivot && i<high) i++;
                while (A[j].id>pivot && j>low) j--;

                if(i<j){
                    student temp;
                    temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
            }

            student temp = A[low];
            A[low] = A[j];
            A[j] = temp;

            return j;
        }

        int binary_rec(student A[], int low, int high, int key){

            if(low<=high){

                int mid = (low+high)/2;

                if (A[mid].id==key) {
                    cout<<"Key found!";
                    return 1;
                }

                else if (key<A[mid].id) return binary_rec(A, low, mid-1, key);

                else return binary_rec(A, mid+1, high, key);

            }

            return -1;

        }

        void mergesort(student A[], int low, int high){

            if(low<high){
                int mid = (low+high)/2;

                mergesort(A, low, mid);
                mergesort(A, mid+1, high);

                combine(A, low, mid, high);
            }
        }

        void combine(student A[], int low, int mid, int high){

            int i = low; int k = low; 
            int j = mid+1;
            student temp[20];

            while(i<=mid && j<=high){

                if(A[i].id<A[j].id){ temp[k] = A[i]; i++; k++;}

                else {temp[k] = A[j]; j++; k++;}


            }

            while(i<=mid){temp[k] = A[i]; i++; k++;}
            while(j<=high){temp[k] = A[j]; j++; k++;}

            for(int l = low; l<=high; l++){
                A[l] = temp[l];
            }


        }

        void set_name(){

            cin>>name;

        }

        void set_id(){
            cin>>id;
        }

        


};


int main(){

    student Arr[20];
    int n; int key;

    cout<<"\nEnter number of entries: "; cin>>n;

    for(int i=0; i<n; i++){
        cout<<"\nEnter name of student "<<i<<" : "; Arr[i].set_name();
        cout<<"\nEnter student id: "; Arr[i].set_id();

    }

    cout<<"\nWhat key do you want to searchh for: "; cin>>key;

    cout<<"\nImplementing linear search: ";
    Arr->linearsearch(Arr, n, key);

    int choice;
    cout<<"\nMethod: 1 for Quick 2 for MErge: "; cin>>choice;

    if (choice==1){
    
        cout<<"\nBefore sorting: ";
        Arr->display(Arr, n);

        Arr->quicksort(Arr, 0, n-1);
        cout<<"After sorting: ";
        
        Arr->display(Arr, n);
    }

    else if (choice==2){
        cout<<"\nBefore sorting using mergesort: ";
        Arr->display(Arr, n);
        Arr->mergesort(Arr, 0, n-1);

        cout<<"After sorting: ";
        Arr->display(Arr, n);

    }

    cout<<"\nImplementing binary search: ";

    int temp = Arr->binary_rec(Arr, 0, n-1, key);

    if (temp==1) {cout<<"\nFound key in binary.";}
    else cout<<"Key doesnt exist";

    

    return 0;
}