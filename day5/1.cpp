// implement dictionary using AVL

#include <iostream>
using namespace std;


class avl_node{

    private:

        string word, meaning;
        avl_node *left, *right;

    public:

        friend class avl_tree;
};

class avl_tree{

    private:
        avl_node *root;

    public:

        int height(avl_node* temp){

            int h = 0;
            if (temp != NULL)
            {
                int l_height = height (temp->left);
                int r_height = height (temp->right);
                int max_height = max (l_height, r_height);
                h = max_height + 1;
            }
            return h;
        }

        int diff(avl_node* temp){
            int l_height = height (temp->left);
            int r_height = height (temp->right);
            int b_factor= l_height - r_height;
            return b_factor;
        }

        avl_node *rr_rotation(avl_node* parent){
            avl_node* temp = parent->right;
            parent->right = temp->left;
            temp->left = parent;
            return temp;

        }

        avl_node *ll_rotation(avl_node* parent){

            avl_node * temp = parent->left;
            parent->left = temp->right;
            temp->right = parent;
            return temp;
        }
        
        avl_node *lr_rotation(avl_node* parent){

            avl_node *temp = parent->left;
            parent->left = rr_rotation (temp); //calling RR rotation
            return ll_rotation (parent);
            // return root after LL rotation

        }

        avl_node *rl_rotation(avl_node* parent){
            avl_node *temp = parent->right;
            parent->right = ll_rotation (temp); // calling LL rotation
            return rr_rotation (parent);
            // return root after RR rotation
        }

        avl_node *balance(avl_node* temp){
            int bal_factor = diff(temp);
            if (bal_factor > 1)
            {
                if (diff (temp->left) > 0)
                    temp = ll_rotation (temp);
                else
                    temp = lr_rotation (temp);
            }
            else if (bal_factor < -1){
                if (diff (temp->right) > 0)
                    temp = rl_rotation (temp);
                else
                    temp = rr_rotation (temp);
            }
            return temp;

        }

        void insert(){
            char ch;

            do{
                avl_node *temp = new avl_node();

                cout<<"Enter word: ";
                cin>>temp->word;

                cout<<"Enter meaning: ";
                cin>>temp->meaning;

                temp->left = temp->right = NULL;

                root = bst_insert(root, temp);

                cout<<"Do you want to insert more? (Y/N): ";
                cin>>ch;

            }while(ch=='Y' || ch=='y');
        }

        avl_node* bst_insert(avl_node* temp, avl_node* newnode){

            if(temp == NULL){
                return newnode;
            }

            if(newnode->word < temp->word){
                temp->left = bst_insert(temp->left, newnode);
            }
            else{
                temp->right = bst_insert(temp->right, newnode);
            }

            temp = balance(temp);
            return temp;
        }

        void display_tree(avl_node* ptr){

            // inorder display:
            if(ptr != NULL){
                display_tree(ptr->left);

                if(ptr == root)
                    cout<<"\nRoot -> "<<ptr->word;
                else
                    cout<<"\n"<<ptr->word;

                display_tree(ptr->right);
            }
        }
  

        avl_tree(){
            root = NULL;
        }

        void create_avl(){
            insert();

            cout<<"\nAVL Dictionary Tree:\n";
            display_tree(root);
        }
};


int main(){

    avl_tree tree;

    tree.create_avl();

    return 0;
}