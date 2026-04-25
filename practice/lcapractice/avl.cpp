#include <iostream>

#include <string>

using namespace std;


class node{

    string word;
    node* left; node * right;

    friend class avl;
};

class avl{

    private:
        node *root;

    public:

        avl(){
            root = NULL;
        }

        int height(node*temp){

            int h = 0;
            if (temp!=NULL){
                int l_h = height(temp->left);
                int r_h = height(temp->right);
                int max_h = max(l_h, r_h);

                h = max_h + 1;
            }

            return h;

        }

        node *ll(node*p){

            node *temp = p->left;
            node *x = temp->right;

            temp->right = p;
            p->left = x;

            return temp;

        }

        node *rr(node*p){

            node *temp = p->right;
            node *x = temp->left;

            temp->left = p;
            p->right = x;

            return temp;

        }

        node *lr(node* p){

            node *temp = p->left;

            p->left = rr(temp);
            return ll(p);

        }

        node *rl(node *p){

            node *temp = p->right;

            p->right = ll(temp);
            return rr(p);
            
        }


        int diff(node*temp){
            int l_h = height(temp->left);
            int r_h = height(temp->right);
            int bal_fac = l_h-r_h;
            return bal_fac;
        }

        node* balance(node *temp){

            int bal_fac = diff(temp);

            if(bal_fac>1){

                if (diff(temp->left)>0)
                    temp = ll(temp);

                else temp = lr(temp);
            }

            else if (bal_fac<-1){
                if(diff(temp->right)>0){
                    temp = rl(temp);

                }
                else temp = rr(temp);
            }

            return temp;

        }

        void insert(){

            

            char cont = 'y';

            while(cont=='y'){

                node *temp = new node();

                cout<<"Enter word: ";
                cin>>temp->word;

                temp->left = temp->right = NULL;

                root = bst_insert(root, temp);

                cout<<"Do you want to insert more?: ";
                cin>>cont;
            }
        }

        node *bst_insert(node *root, node *newnode){

            if (root==NULL){
                return newnode;
            }

            if(newnode->word<root->word){
                root->left = bst_insert(root->left, newnode);
            }

            else root->right = bst_insert(root->right, newnode);

            root = balance(root);
            return root;

        }

        void display_tree(node *ptr){

            if(ptr!=NULL){
                display_tree(ptr->left);

                if(ptr==root){
                    cout<<"Root-> "<<root->word;
                }
                else cout<<"\n"<<ptr->word;

                display_tree(ptr->right);
            }

        }

        void create(){

            insert();

            cout<<"\nAVL tree:\n";
            display_tree(root);

        }



};

int main(){

    avl tree;

    tree.create();


    return 0;
}