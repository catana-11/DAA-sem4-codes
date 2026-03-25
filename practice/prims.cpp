#include <iostream>
#include <iomanip> 

using namespace std;

class prims {

    private:
        int cost_mat[10][10];
        int n; int edges; 

    public:

        prims() { 
            cout << "Enter number of vertices: "; cin >> n;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    cost_mat[i][j] = 999;
                }
            }
        }

        void create() {
            cout << "Enter number of edges: "; cin >> edges;
            cout << "Enter edge details (source dest cost):\n";

            for(int i = 0; i < edges; i++){
                int source, dest, cost;
                cout<<"\nEnter source: "; cin >> source;
                cout<<"\nEnter destination vertex: "; cin>> dest;
                cout<<"\nEnter the cost for this edge: "; cin>> cost;

                cost_mat[source][dest] = cost;
                cost_mat[dest][source] = cost; 
            }
        }

        void display() {
            cout << "\n--- Cost Matrix ---\n";
            cout << "   ";
            for(int i=0; i<n; i++) cout << i << "   "; 
            cout << endl;
            
            for(int i = 0; i < n; i++){
                cout << i << ": ";
                for(int j = 0; j < n; j++){
                    if(cost_mat[i][j] == 999) cout << "INF ";
                    else cout << setw(3) << cost_mat[i][j] << " ";
                }
                cout << endl;
            }
        }

        void prims_algorithm() {
            int start;
            cout << "\nEnter starting vertex: "; cin >> start;

            int nearest[20];
            int mincost = 0;

            // initialization
            // nearest[i] stores the node in the mst that is closest to node i.
            nearest[start] = -1; // -1 means the node is in the mst already.
            for(int i = 0; i < n; i++){
                if(i != start)
                    nearest[i] = start;
            }

            cout << "\n--- Starting Prim's Algorithm ---" << endl;
            cout << "Initial nearest array (all point to start " << start << "): ";
            for(int k=0; k<n; k++) cout << nearest[k] << " ";
            cout << endl;

            int count = 1;
            while(count < n){
                cout << "\n==========================================" << endl;
                cout << "ITERATION " << count << endl;
                cout << "==========================================" << endl;

                int min = 999;
                int j = -1;

                // --- DEBUGGING STEP 1: finding minimum edge ---
                cout << "Step 1: finding minimum edge connecting MST to outside..." << endl;
                
                for(int i = 0; i < n; i++){
                    // nearest[i] != -1 means node 'i' is NOT in MST yet
                    if(nearest[i] != -1){
                        int connection_cost = cost_mat[nearest[i]][i];
                        
                        cout << "  Checking Node " << i << ": Connected to MST via Node " << nearest[i] 
                             << " (Cost: " << connection_cost << ")";

                        if(min > connection_cost){
                            cout << " -> New Min Candidate!" << endl;
                            min = connection_cost;
                            j = i; // j is the node we might pick
                        } else {
                            cout << " -> Too expensive." << endl;
                        }
                    }
                }

                if(j == -1) {
                     cout << "Graph is disconnected!" << endl; 
                     return; 
                }

                int s = nearest[j]; 
                int d = j; 

                cout << "\n>>> SELECTED EDGE: " << s << " to " << d << " with Cost " << min << " <<<" << endl;

                mincost += min;
                nearest[j] = -1; // Mark j as visited (added to MST)

                // --- DEBUGGING STEP 2: updating nearest array ---
                cout << "\nStep 2: Updating distances using new node " << j << "..." << endl;
                
                for(int k = 0; k < n; k++){
                    // Only update nodes that are NOT in MST yet
                    if(nearest[k] != -1){
                        int old_cost = cost_mat[nearest[k]][k];
                        int new_cost_via_j = cost_mat[j][k];

                        cout << "  Node " << k << ": Old Cost (via " << nearest[k] << ") = " << old_cost 
                             << " | New Cost (via " << j << ") = " << new_cost_via_j;

                        if(new_cost_via_j < old_cost){
                            cout << " -> UPDATING nearest[" << k << "] to " << j << endl;
                            nearest[k] = j;
                        } else {
                            cout << " -> No Change" << endl;
                        }
                    }
                }
                
                // Show state of nearest array after iteration
                cout << "\nEnd of Iteration " << count << ". Current 'nearest' array: [ ";
                for(int k=0; k<n; k++) cout << nearest[k] << " ";
                cout << "]" << endl;

                count++;
            }

            cout << "\n------------------------------------------" << endl;
            cout << "Minimum cost = " << mincost << endl;
            cout << "------------------------------------------" << endl;
        }
};

int main(){
    prims p;
    p.create();
    p.display();
    p.prims_algorithm();
    return 0;
}