// implement graph traversals using stack and queue class and functions

#include <iostream>

using namespace std;
// node class--------------------------------------------------------------------------------
class node{
        int userid;
        string name;
        string city;
        node *next;
        friend class graph;
};

// stack class-------------------------------------------------------------------------
class stack{

    int stk[20];


    int top;

    public:
        stack(){
            top = -1;
        }//constructor to set top -1

        void push(int x){
            top+=1;
            stk[top] = x;

        }

        int pop(){
            int x = stk[top];
            top--;
            return x;
        }

        int isempty(){
            if (top==-1){ return 1;}
            else return 0;
        }

        void stk_init(){
            for (int i=0; i<20; i++){
                stk[i] = 0;
            }
        }

};

// queue class ------------------------------------------------------------------------------

class queue{

    int q[20];
    int front, rear;

    public:

        queue(){
            front = 0;
            rear = -1;
        }

        int is_empty(){

            if (front>rear){return 1;}
            else return 0;
        }

        int is_full(){
            if (rear==19){
                return 1;
            }
            else return 0;
        }

        void enqueue(int x){

            if (is_full()==1){return;}

            rear++;
            q[rear] = x;

        }

        int dequeue(){
            if (is_empty()==1){return -1;}

            int x = q[front];
            front++;

            return x;

        }

        void queue_init(){

            for(int i=0; i<20; i++){
                q[i]=0;
            }

        }

};


// graph class-------------------------------------------------------------------------------
class graph{

    int n; // vertices
    node *head[20];
    public:
    int visited[20] = {0};
    

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


    void DFT_rec(int s){
        // s is starting vertex

        visited[s] = 1;

        cout<<"\n["<<head[s]->userid<<"]";

        node *temp;
        temp = head[s]->next;

        while(temp!=NULL){

            int v = temp->userid;

            //cout<<"\n["<<head[s]->userid<<"]";

            if (visited[v]==0){
                DFT_rec(v);
                
            }
            temp = temp->next;
        }

    }

    void DFT_nonrec(int s){

        cout<<"\nDepth first traversal (non-rec):\n";

        for (int i=0; i<n; i++){
            visited[i]=0;
        }

        stack stack_object;
        stack_object.stk_init();

        stack_object.push(s);
        visited[s]= 1;
        // hence added the start vertex

        while(stack_object.isempty()!=1){
            int v = stack_object.pop();

            cout<<"\n["<<head[v]->userid<<"]";

            node *temp = head[v]->next;

            while(temp!=NULL){

                int w = temp->userid;

                if (visited[w]==0){

                    stack_object.push(w);
                    visited[w] = 1;

                }
                temp = temp->next;
            }

        }
    }

    void BFT(int s){

        queue queue_object;
        queue_object.queue_init();

        cout<<"\nBreadth first traversal:\n";

        for (int i=0; i<n; i++) visited[i]=0;


        queue_object.enqueue(s);
        visited[s] = 1;

        while (queue_object.is_empty()!=1){
      
            int v = queue_object.dequeue();
            cout<<"\n["<<head[v]->userid<<"]";

            node *temp = head[v]->next;

            while (temp!=NULL){

                int w = temp->userid;

                if (visited[w]==0){
                    queue_object.enqueue(w);
                    visited[w] = 1;
                }

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
    for (int i=0; i<20; i++){
        g.visited[i] = 0;
    }
    

    cout<<"\nDepth first recursive:";
    int s;
    cout<<"\nEnter start vertex userid: "; cin>>s;
    cout<<"Depth first traversal rec:\n";
    g.DFT_rec(s);

    g.DFT_nonrec(s);

    g.BFT(s);

    return 0;
}

