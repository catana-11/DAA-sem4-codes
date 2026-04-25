// adj list, dfs bfs

#include <iostream>
#include <string>
using namespace std;

class stack{

    int stk[20];
    int top;

    public:

    stack(){
        top = -1;
    
    }

    void push(int x){

        top++;
        stk[top] = x;
    }

    int pop(){

        int x = stk[top];
        top--;
        return x;

    }

    int isempty(){
        if(top==-1) return 1;
        else return 0;

    }

    
};


class queue{

    int q[20];
    int front, rear;

    public:

    queue(){
        front = 0; rear =-1;
    }

    void push(int x){

        rear++;
        q[rear] = x;
    }

    int pop(){

        int x = q[front];
        front++;
        return x;

    }

    int isempty(){
        if(front>rear) return 1;
        else return 0;

    }

    
};

class node{

    int userid;
    string name;
    node* next;

    friend class graph;
};



class graph{

    int n;
    node *head[20];

    int visited[20];

    public:



        graph(){

            cout<<"\nEnter the number of vertices: "; cin>>n;

            for(int i = 0; i<n; i++){
                visited[i] = 0;
            }
            cout<<"Visited array constructed";
        }

        void adj_list_creation(){
            cout<<"---------";
            

            for(int i = 0; i<n; i++){

                head[i] = new node();
                head[i]->next  = NULL;
                cout<<"\nEnter name: "; cin>>head[i]->name;
                head[i]->userid= i;
            
            }


            // now attachig friends

            for (int i = 0; i<n; i++){

                node *temp = head[i];
                char cont = 'y';

                cout<<"\nDo you want to enter friends for vertex id "<<head[i]->userid<<": "; cin>>cont;
                cout<<"\nEntering friends for vertex id "<<head[i]->userid; cout<<endl;

            
                while (cont=='y'){
                    int x;
                    cout<<"\nEnter id of friend: "; cin>>x;

                    if (x!=i){
                        node *curr = new node();
                        curr->name = head[x]->name;
                        curr->userid = x;
                        curr->next = NULL;
                        temp->next = curr;
                        temp = curr;

                        cout<<"Wanna continue adding friends: "; cin>>cont;
                    }
                }
            }
        }



        void dft_rec(int s){

            visited[s] = 1;
            cout<<"["<<head[s]->userid<<", "<<head[s]->name<<"]";

            node *temp = head[s]->next;

            while(temp!=NULL){
                int w = temp->userid;

                if(visited[w]==0){
                    dft_rec(w);
                }

                temp = temp->next;
            }

        }

        void dft_nonrec(int s){

            for(int i=0; i<n; i++){visited[i] = 0;}

            stack stk;

            stk.push(s);
            visited[s] = 1;

            while (!stk.isempty()){

                int v = stk.pop();
                cout<<"["<<head[v]->userid<<", "<<head[v]->name<<"]";

                node *temp = head[v]->next;

                while(temp!=NULL){
                    int w = temp->userid;

                    if(visited[w]==0){
                        stk.push(w);
                        visited[w]=1;
                    }

                    temp = temp->next;
                }

            }
        
        }

        void bft_nonrec(int s){

            for(int i=0; i<n; i++){visited[i] = 0;}

            queue q;

            q.push(s);
            visited[s] = 1;

            while (!q.isempty()){

                int v = q.pop();
                cout<<"["<<head[v]->userid<<", "<<head[v]->name<<"]";

                node *temp = head[v]->next;

                while(temp!=NULL){
                    int w = temp->userid;

                    if(visited[w]==0){
                        q.push(w);
                        visited[w]=1;
                    }

                    temp = temp->next;
                }

            }
        
        }         

        

};


int main(){

    cout<<"before graph";

    graph g;

    cout<<"after graph";

    g.adj_list_creation();

    int x;

    cout<<"Enter start vertex: "; cin>>x;

    g.dft_rec(x);
    cout<<"\n-------------\n";

    g.dft_nonrec(x);

    cout<<"\n-------------\n";

    g.bft_nonrec(x);



    return 0;
}