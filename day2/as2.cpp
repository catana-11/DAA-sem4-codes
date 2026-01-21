// implement adjacency list of a graph

#include <iostream>

using namespace std;

class node{
        int userid;
        string name;
        string city;
        node *next;
        friend class graph;
};

class graph{

    int n; // vertices
    node *head[];

    public:

    void create_adj_list(){

        cout<<"\nEnter the number of vertices: "; cin>>n;

        for (int i=0; i<n; i++){
            head[i] = new node();
            head[i]->next = NULL;
            head[i]->userid = i;
            cout<<"\nEnter the name of user with ID "<<i<<": "; 
            cin>>head[i]->name;
            
            cout<<"\nEnter the city of user with ID "<<i<<": "; 
            cin>>head[i]->city;
        }

        // now array of heads is done
        // now establish friends of each user (vertex)
        node *temp = head[0];
        int x; int yn = 0;
        node *curr;

        for (int i=0; i<n; i++){

            int cont = 1;

            temp = head[i];
            cout<<"\n....................................";
            cout<<"\nDo you want to add friends of userid "<<i<<"?: "; cin>>yn;
            if (yn==1){

                while (cont==1){
                    cout<<"\nEnter ID of friend you want to add: "; cin>>x;

                    if (x!=i){
                        curr = new node();
                        curr->userid = x;
                        curr->name = head[x]->name;
                        curr->city = head[x]->city;
                        curr->next = NULL;
                        temp->next = curr;
                        temp = curr;
                        cout<<"\nDo you want to add more friends for userid "<<i<<"?: "; cin>>cont;
                    }
                }

            }   

        }

    }


    void display_list(){

        cout<<"\nThe heads array is as so: ";

        for(int i=0; i<n; i++){

            cout<<"\n["<<head[i]->userid<<", "<<head[i]->name<<", "<<head[i]->city<<"]";

        }

        for(int i=0; i<n; i++){
            cout<<"\n.............................";
            cout<<"\nFriends of userid"<<i<<" are: ";

            node *temp;
            temp = head[i]->next;

            while (temp!=NULL){

            cout<<"\n["<<temp->userid<<", "<<temp->name<<", "<<temp->city<<"]";
            temp = temp->next;
    
            }
        }
    }
};


int main(){

    cout<<"\nMain program:\n";

    graph g;

    g.create_adj_list();
    g.display_list();


    return 0;
}

