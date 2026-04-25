#include <iostream>

using namespace std;

class knapsack{

    private:

        int w[20]; int p[20];
        int M; // max cap
        int n;
        int table[20][20];

    public:

        knapsack(){

            cout<<"\nEnter the number of items: "; cin>>n;
            cout<<"\nEnter the max capacity of knapsack: "; cin>>M;

            for(int i = 0; i<n; i++) w[i] = 0;
            for(int i = 0; i<n; i++) p[i] = 0;

            for(int i = 0; i<n; i++){
                cout<<"Enter weight of item "<<i<<" : ";
                cin>>w[i];
            }

            for(int i = 0; i<n; i++){
                cout<<"Enter profit of item "<<i<<" : ";
                cin>>p[i];
            }

        }

        void algo(){

            for(int i = 0; i<=n; i++){
                for(int j = 0; j<=M; j++){

                    if (i==0||j==0){
                        table[i][j] = 0;
                    }

                    else if( w[i-1]<=j){
                        table[i][j] = max(table[i-1][j],
                                         p[i-1]+table[i-1][j-w[i-1]]);
                    } // wt can be included

                    else table[i][j] =  table[i-1][j];

                }
            }

            cout<<"\nMax cap is: "<<table[n][M];
        }

        void backtracking(){
            int x= M;

            cout<<"\nIncluded weights are: ";

            for(int i = n; i>0 && x>0; i--){
                if (table[i][x]!=table[i-1][x]){
                    cout<<"\nItem "<<i-1<<" having weight "<<w[i-1]<<" , ";
                    x -= w[i-1];
                }
            }
        }


};

int main(){

    knapsack k;

    k.algo();
    k.backtracking();


    return 0;
}