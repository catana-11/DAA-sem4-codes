//implement prims

#include <iostream>

using namespace std;


class prims {

    private:

        int cost_mat[10][10];
        int n; int edges; 
        // n is vertices

    public:

        prims() { // constructor to set paths infinity
            cout << "Enter number of vertices: "; cin >> n;

            // initialize cost_mat with some infinity type value 
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    cost_mat[i][j] = 999;
                }
            }
        }

        void create() {

            cout << "Enter number of edges: "; cin >> edges;

            cout << "Enter edge details:\n";

            for(int i = 0; i < edges; i++){
                int source, dest, cost;
                cout<<"\nEnter source: "; cin >> source;
                cout<<"\nEnter destination vertex: "; cin>> dest;
                cout<<"\nEnter the cost for this edge: "; cin>> cost;

                cost_mat[source][dest] = cost;
                cost_mat[dest][source] = cost; // same across diagonal folding
            }
        }

        void display() {
            cout << "\ncost matrix:\n";
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(cost_mat[i][j] == 999)
                        cout << "inf ";

                    else
                        cout<<" " << cost_mat[i][j] << "  ";
                }
                cout << endl;
            }
        }

        void prims_algorithm() {

            int start;
            cout << "\nEnter starting vertex: "; cin >> start;

            int nearest[20];

            for (int i = 0; i<20; i++) {nearest[i] = -1;}

            int mincost = 0;

            nearest[start] = -1;

            for(int i = 0; i < n; i++){
                if(i != start)
                    nearest[i] = start;
            }

            cout << "\nEdges in mst:\n";

            int count = 1;

            while(count < n){

                int min = 999;
                int j = -1;

                // find minimum edge
                for(int i = 0; i < n; i++){
                    if(nearest[i] != -1  &&  min>cost_mat[nearest[i]][i]){
                        min = cost_mat[nearest[i]][i];
                        j = i; // j --> newly visited vertex
                    }
                }

                int s = nearest[j]; int d = j; // sources and dest to print edgds

                cout << s << " to " << d << " = " << min << endl;

                mincost += min;
                nearest[j] = -1;

                // now reset closest distances
                for(int k = 0; k < n; k++){
                    if(nearest[k] != -1 && cost_mat[j][k] < cost_mat[nearest[k]][k]){
                        nearest[k] = j;
                    }
                }
                count++;
            }

            cout << "\nMinimum cost = " << mincost << endl;
        }
};

int main(){

    prims p;

    p.create();
    p.display();

    p.prims_algorithm();

    return 0;
}
