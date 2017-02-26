//Program for AVL Tree

/*
 * Created by Devashish Katoriya on 26-02-2017
 */

#include <iostream>
#include <string.h>

using namespace std;

#define LIMIT 30

//Function Prototypes

//Class Declarations
class AVLNode
{
public :
    char word[LIMIT],meaning[LIMIT];
    int height;
    AVLNode *left,*right;
};

class AVLTree
{
    AVLNode *root;
    AVLNode *create_node(char [],char []);
    AVLNode *insert(AVLNode *,char [],char []);
    AVLNode *rotate_left(AVLNode *);
    AVLNode *rotate_right(AVLNode *);
    AVLNode *RR(AVLNode *);
    AVLNode *RL(AVLNode *);
    AVLNode *LR(AVLNode *);
    AVLNode *LL(AVLNode *);
public :
    AVLTree()
    {
        root = NULL;
    }
    inline AVLNode *retRoot()
    {
        return root;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    void clr()
    {
        root = NULL;
    }
    void construct();
    int balance_factor(AVLNode *);
    int height(AVLNode *);
    void inOrder(AVLNode *);
    void search(char []);
};

AVLNode *AVLTree::create_node(char word[], char meaning[])
{
    AVLNode *temp;
    temp = new AVLNode;
    strcpy(temp->word,word);
    strcpy(temp->meaning,meaning);
    temp->height = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void AVLTree::construct()
{
    char word[LIMIT],meaning[LIMIT];
    cout<<"\nEnter new Word \t: ";
    cin>>word;
    cout<<"Enter meaning \t: ";
    cin>>meaning;
    root = insert(retRoot(),word,meaning);
}

AVLNode *AVLTree::insert(AVLNode *r, char word[], char meaning[])
{
    if(r==NULL)
    {
        AVLNode *curr;
        curr = create_node(word,meaning);
        r = curr;
        cout<<"\nWord Inserted Successfully!";
    }
    else
    {
        if(strcmp(r->word,word)<0)
        {
            r->left = insert(r->left,word,meaning);
            if(balance_factor(r)>=2)
            {
                if (strcmp(word, r->left->word) < 0)
                    r = LL(r);
                else
                    r = LR(r);
            }
        }
        else if(strcmp(r->word,word)>0)
        {
            r->right = insert(r->right,word,meaning);
            if(balance_factor(r)>=2)
            {
                if (strcmp(word, r->right->word) < 0)
                    r = RR(r);
                else
                    r = RL(r);
            }
        }
        else
        {
            cout<<"\nEntry already Exist!";
        }
    }
    r->height = height(r);
    return r;
}

AVLNode *AVLTree::rotate_right(AVLNode *x)
{
    AVLNode *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}


AVLNode *AVLTree::rotate_left(AVLNode *x)
{
    AVLNode *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = height(x);
    y->height = height(y);
    return y;
}

AVLNode *AVLTree::RR(AVLNode *T)
{
    T = rotate_left(T);
    return T;
}

AVLNode *AVLTree::RL(AVLNode *T)
{
    T->right = rotate_right(T);
    T = rotate_left(T);
    return T;
}

AVLNode *AVLTree::LR(AVLNode *T)
{
    T->left = rotate_left(T);
    T = rotate_right(T);
    return T;
}

AVLNode *AVLTree::LL(AVLNode *T)
{
    T = rotate_right(T);
    return T;
}

int AVLTree::height(AVLNode *T)
{
    int hl,hr;
    if(T==NULL)
        return 0;
    if(T->left==NULL && T->right==NULL)
        return 0;
    hl = height(T->left);
    hr = height(T->right);
    if(hl>hr)
        return hl+1;
    else
        return hr+1;
}

int AVLTree::balance_factor(AVLNode *T)
{
    int lh,rh;
    if(T==NULL)
    {
        return 0;
    }
    else
        lh = 1 + T->left->height;
    if(T->right==NULL)
        rh = 0;
    else
        rh = 1+T->right->height;
    return lh-rh;
}

void AVLTree::inOrder(AVLNode *s1)								//in order()
{
    if(s1!=NULL) {
        inOrder(s1->left);
        cout << s1->word << ",";
        inOrder(s1->right);
    }
}

void AVLTree::search(char key[])
{
    AVLNode *temp;
    if(isEmpty())
    {
        cout<<"\nDictionary is Empty!";
    }
    temp = root;
    while(temp!=NULL)
    {
        if(strcmp(temp->word,key)>0)
        {
            temp  = temp->left;
        }
        else if(strcmp(temp->word,key)<0)
        {
            temp = temp->right;
        }
        else
        {
            cout<<"\nWord   \t: "<<temp->word;
            cout<<"\nMeaning \t: "<<temp->meaning;
            break;
        }
    }
    if(temp == NULL)
        cout<<"\nWord NOT found!";
}

//main()
int main() {
    AVLTree obj;
    int ch;
    char choice,word[LIMIT];
    cout<<"\nProgram to create Expression Tree.";
    do
    {
        ch = 0;
        choice = 'n';
        cout<<"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        cout<<"\n 1 for Construction and Insertion";
        cout<<"\n 2 for In-Order Traversal";
        cout<<"\n 3 for Searching";
        cout<<"\n 4 for Height of Tree";
        cout<<"\n 5 for Depth of Tree";
        cout<<"\n 6 for Root Node";
        cout<<"\n 7 for Balance Factor of Root";
        cout<<"\n -1 to Clear whole Tree";
        cout<<"\n 0 to  Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch)
        {
            case 1 :
                obj.construct();
                break;
            case 2 : cout<<"\nIn-Order Traversal is ";
                obj.inOrder(obj.retRoot());
                break;
            case 3 :
                cout<<"\nEnter Word : ";
                cin>>word;
                obj.search(word);
                break;
            case 4 :
                cout<<"\nHeight of Tree is "<<obj.height(obj.retRoot())+1;
                break;
            case 5 :
                cout<<"\nDepth of Tree is "<<obj.height(obj.retRoot())+1;
                break;
            case 6 : if(!obj.isEmpty())
                    cout<<"\nRoot Node is "<<obj.retRoot()->word;
                else
                    cout<<"\nEmpty Tree!";
                break;
            case 7 : if(!obj.isEmpty())
                    cout<<"\nBalance Factor of Root Node is "<<obj.balance_factor(obj.retRoot());
                else
                    cout<<"\nEmpty Tree!";
                break;
            case -1 : cout<<"\nAre you sure you want to clear tree (y/n) ? ";
                cin>>choice;
                if(choice=='y'||choice=='Y')
                {
                    obj.clr();
                    cout<<"\nTree Cleared Successfully!";
                }
                else
                    cout<<"\nCancelled!";
            case 0 : break;
            default : cout<<"\nInvalid Option!";
        }
        
        /*
        if(ch!=0)
        {
            cout<<"\n\n\n\n\n\n\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }
        */
    }while(ch!=0);
    
    cout<<"\nThank you for using this program :) \n\n";
    return 0;
}

/* OUTPUT

 
*/