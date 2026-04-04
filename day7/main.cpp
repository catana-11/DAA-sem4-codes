// n queens problem

#include <iostream>
#include <cmath>
using namespace std;


class nqueens{

    private:

        // board[i] = column position of queen placed in row i
        int board[20];

    public:

        // is placing queen at (r, c) is safe?
        int place(int r, int c) {
            for (int i = 1; i < r; i++) {

                if (board[i] == c || abs(board[i] - c) == abs(i - r)) {
                    return 0;

                    // 1. same column --> board[i] == c
                    // 2. diagonal → abs(board[i] - c) == abs(i - r)
                }
            }
            return 1;
        } 

        void nqueen(int r, int n) {
            for (int i = 1; i <= n; i++) {
                // try placing queen in col i of row r
                if (place(r, i)==1) {

                    board[r] = i; 

                    // if all queens are placed
                    if (r == n) {
                        cout << "Solution: ";
                        for (int j = 1; j <= n; j++) {
                            cout << board[j] << " ";
                        }
                        cout << endl;
                    } 
                    else {
                        // next row
                        nqueen(r + 1, n);
                    }
                }
            }
        }

};


int main() {

    int n;
    nqueens nq;

    cout << "Enter no. of queens: "; cin >> n;

    nq.nqueen(1, n);

    return 0;
}