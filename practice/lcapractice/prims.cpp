#include <iostream>

using namespace std;

class prims{

    private:
        int cost[10][10];
        int nearest[10];
        int n;


    public:

        prims(){

            cout<<"\nEnter the no of vertices: "; cin>>n;

            for(int i=0; i<n; i++){
                for (int j = 0; j<n; j++){
                    cost[i][j] = 999;
                }
            }


        }

        void create(){
            int edges;
            int source; int dest; int edgecost;

            cout<<"\nEnter the no of edges: "; cin>>edges;

            for(int i = 0; i<edges; i++){

                cout<<"\nEnter source vertex: "; cin>>source;
                cout<<"\nEnter dest vertex: "; cin>>dest;

                cout<<"\nEnter cost of the edge: "; cin>>edgecost;

                cost[source][dest] = edgecost;
                cost[dest][source] = edgecost;
                
            }
        }

        void primsalg(int start){

            for(int i = 0; i<n; i++){
                if(i != start)
                    nearest[i] = start;
                else
                    nearest[i] = -1;
            }

            nearest[start] = -1;
            int mincost =0; int count = 1;

            while(count<n){
                int min = 999; int j = -1;

                for(int i = 0; i<n; i++){
                    if (nearest[i]!=-1 && cost[nearest[i]][i]<min){
                        min = cost[nearest[i]][i];
                        j = i;
                    }
                }

                int source = nearest[j]; int destination = j;
                cout<<"["<<source<<" , "<<destination<<"]";

                mincost +=min; nearest[j] = -1;

                // updating distances

                for(int k=0; k<n; k++){
                    if (nearest[k]!=-1 && cost[j][k]<cost[nearest[k]][k]){
                        nearest[k] = j;
                    }
                }

                count+=1;
            }

            cout<<"MST cost: "<<mincost;

        }



};

int main(){

    prims p;

    p.create();

    int st;

    cout<<"\nEnter the start vertex: "; cin>>st;

    p.primsalg(st);


    return 0;
}