//dynamic programming: 0/1 knapsack

#include <iostream>

using namespace std;

class knapsack{

    private: 
        int n; // no. of items
        int M; // max capacity
        int w[20];  // weights array
        int p[20];  // profits array
        int B[20][20];

    public:

    knapsack(){

        for(int w=0; w<=M; w++){ // init the first row to 0
            B[0][w] = 0;
        }

        for(int i=0; i<=n; i++){ // init the colmn to 0
            B[i][0] = 0;
        }

    }

    void accept_weight(){
        cout<<"Enter the weights: "<<endl;
        for (int i = 0; i<n; i++){
            cout<<"Enter weight of "<<i<<"th item: "; cin>>w[i];
        }
    }

    void accept_profit(){
        cout<<"Enter the profits: "<<endl;
        for (int i = 0; i<n; i++){
            cout<<"Enter profit of "<<i<<"th item: "; cin>>p[i];
        }
    }

    void show_weights(){
        cout<<"Weights: "<<endl<<"[";
        for (int i = 0; i<n; i++){
            if (i!=n-1) cout<<w[i]<<", ";
            else cout<<w[i];
        }
        cout<<"]"<<endl;

    }

    void show_profits(){
        cout<<"Profits: "<<endl<<"[";
        for (int i = 0; i<n; i++){
            if (i != n-1) cout<<p[i]<<", ";
            else cout<<p[i];
        }
        cout<<"]"<<endl;
    }

    void set_n(){
        cout<<"Enter the number of items provided: "; cin>>n;
    }

    void set_m(){
        cout<<"Enter the max capacity of knapsack: "; cin>>M;
    }

    void print_table(){

        for(int i=0; i<=n; i++){
            cout<<"| ";
            for(int j = 0; j<=M; j++){
                cout<<B[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void algo() {
    
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= M; j++) {
                if (i==0 || j==0) B[i][j] = 0;

                else if (w[i-1] <= j)
                        B[i][j] = max(p[i-1] + B[i-1][j - w[i-1]], B[i-1][j]);

                else B[i][j] = B[i-1][j];
            }
        }
    }

    void backtrack(){
        int x = M, ans= B[n][M]; // ans is the profit result
        cout <<"weights used: [";
        for (int i = n; i > 0; i--) {
       
            if (ans != B[i - 1][x] && ans > 0) {
                cout << w[i - 1] << " ,";
                ans -= p[i - 1];
                x -= w[i - 1];
            }
        }
        cout<<"]";
    }

    void result(){
        cout<<endl<<"Final result: "<<B[n][M];
    }
    
};

int main(){

    knapsack k;

    k.set_n();
    k.set_m();

    k.accept_profit();
    k.accept_weight();

    k.show_profits();
    k.show_weights();

    k.algo();

    k.print_table();

    //k.result();

    k.backtrack();

    return 0;
}


