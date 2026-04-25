#include <iostream>

using namespace std;

class nqueen{

    private:
        int board[20];
        int n;

    public: 
        
        nqueen(){


            for(int i=0; i<=19; i++){board[i] = 0;}
        }

        void algo(int r, int n){

            for(int i = 1; i<=n; i++){

                if(safeplace(r,i)==1){
                    board[r] = i;

                    if (r==n){
                        cout<<"\nSolution is: ";
                        for(int j = 1; j<=n; j++){
                            cout<<" "<<board[j];
                        }
                    }

                    else algo(r+1, n);
                }
            }

        }

        int safeplace(int r, int c){

            for(int i=1; i<r; i++){

                if(board[i] == c || abs(board[i]-c) == abs(i-r)) return 0;
                
            }

            return 1;

        }


};


int main(){

    nqueen nq;
    int n;

    cout<<"\nEnter the number of queens: "; cin>>n;

    nq.algo(1, n);


    return 0;
}