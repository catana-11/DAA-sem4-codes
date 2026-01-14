// create mobile user database and perform:
// seq search done
// binary search done
// quick sort done
// merge done
// heap sort done 


#include <iostream>
using namespace std;
#include <string>

class mobileuser{
   string username;
   int mobno;
   string addr;

   public:
        void accept_data(){
           cout<<"Enter name: "; cin>> username;
           cout<<"Enter mobile number: "; cin>>mobno;
           cout<<"Enter city: "; cin>>addr;
        }


        void display_data(){
           cout<<"["<<username<<", "<<mobno<<", "<<addr<<"]";
        }


        int seq_search(int n, mobileuser A[], string name ){
           int i=0;
          
           for(int i=0; i<n; i++){
               if (A[i].username == name){
                   cout<<"Found";
                   return 1;
               }
           }
           return 0;
        }


        int partition(mobileuser A[], int low, int high) {

            mobileuser pivot = A[low];
            int i = low;
            int j = high;

            while (i < j) {
                while (A[i].username <= pivot.username && i < high)i++;

                while (A[j].username > pivot.username && j > low) j--;

                if (i<j) {
                    mobileuser temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
            }

            mobileuser temp = A[low];
            A[low] = A[j];
            A[j] = temp;

            return j;
        }


      
        void quick_sort(mobileuser A[], int low, int high){
      
           if (low<high){
               int j = partition(A,low,high);
      
               quick_sort(A,low,j-1);
               quick_sort(A,j+1, high);
               cout<<"Inside quick sort\n";
            
           }
      
        }

        void binary_search(mobileuser A[], int n){

            string key;
            cout<<"\nEnter key: "; cin>>key;

            int low=0; int high = n-1;

            while (low<=high){

                int mid = (low+high)/2;

                if (key==A[mid].username){
                    cout<<"\nKey found by binary search at index "<<mid<<".\n";
                    break;
                }

                else if (key<A[mid].username){
                    high = mid-1;
                }

                else if (key>A[mid].username){
                    low = mid+1;
                }
            }

            if(low>high){
                cout<<"\nKey not found in binary search\n";
            }
        }

    void heap_sort(mobileuser A[], int n){

        for(int i = n/2-1; i>=0; i--){
            adjust(A, n-1, i);

        }

        while (n>0){
            mobileuser temp = A[0];
            A[0] = A[n-1];
            A[n-1] = temp;
            n--;
            adjust(A, n-1, 0);
        }
    
    }

    void adjust(mobileuser A[], int n, int i){

        while(2*i+1<=n){

            int j = 2*i+1; // index of left child

            if ((j+1<=n) && A[j+1].username>A[j].username){j = j+1;}

            if (A[i].username>=A[j].username){break;}

            else{

                mobileuser temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                i = j;

            }

        }
    }

    void merge_sort(mobileuser A[], int low, int high){

        if (low<high){
            int mid = (low+high)/2;

            merge_sort(A, low, mid);
            merge_sort(A, mid+1, high);

            combine(A, low, mid, high);
            
        }
    }

    void combine(mobileuser A[], int low, int mid, int high){

        int i = low; int j = mid+1; int k = low;
        mobileuser temp[20];

        while((i<=mid) &&(j<=high)){

            if (A[i].username < A[j].username){
                temp[k] = A[i]; i++; k++;
            }

            else{
                temp[k] = A[j]; j++; k++;
            }
        }

        while(i<=mid){
            temp[k] = A[i]; k++; i++;
        }

        while(j<=high){
            temp[k] = A[j]; j++; k++;
        }

        for(int l=low; l<=high; l++){
            A[l] = temp[l];
        }
    }

};




int main(){
   mobileuser m[20];
   int n;
   int low = 0;


   cout<<"How many entries?: "; cin>>n;
   int high = n-1;
   //bool check = "arya"<="manjiri";
   //cout<<"\n"<<check<<"\n";


   for (int i=0; i<n; i++){
       cout<<i<<"th entry:\n";
       m[i].accept_data();
       cout<<"\n----\n";
   };


   cout<<"Printing data: \n";


   for (int i=0; i<n; i++){
       m[i].display_data();
       cout<<"\n------------------\n";
   }

   string search_name;
   cout<<"\nEnter the name you want to search: "; cin>>search_name;


   int x = m->seq_search(n, m, search_name);
   cout<<"\n"<<x;



   int switch_choice;
   cout<<"\nSorting menu:\n1. Quick sort\n2. Heap sort\n3. Merge sort";
   cout<<"\nEnter choice: "; cin>>switch_choice;

    switch(switch_choice){

        case 1:
            cout<<"\nNow quick sorting: \n";
            m->quick_sort(m, low, high);


            cout<<"Printing data after sorting: \n";

            for (int i=0; i<n; i++){
                m[i].display_data();
                cout<<"\n------------------\n";
            }

            break;

        case 2:
            cout<<"\nNow heap sorting: \n";

            m->heap_sort(m, n);

            cout<<"Printing data after sorting: \n";

            for (int i=0; i<n; i++){
                m[i].display_data();
                cout<<"\n------------------\n";
            }

            break;

        case 3:
            cout<<"\nNow performing merge sort: \n";
            m->merge_sort(m, low, high);

            cout<<"Printing data after sorting: \n";

            for (int i=0; i<n; i++){
                m[i].display_data();
                cout<<"\n------------------\n";
            }

            break;
   }

    cout<<"\nNow performing binary search: \n";

    m->binary_search(m, n);

   return 0;
}

