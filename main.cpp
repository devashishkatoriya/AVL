//Program to implement Dictionary using AVL Tree.

/*
 * Created by Devashish Katoriya on 26-02-2017
 */

#include <iostream>
#include <string.h>

using namespace std;

#define LIMIT 30

//Function Prototypes
int stringCompare(char [],char []);

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
    AVLNode *delete_node(AVLNode *);
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
    void del(char []);
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
    char word[LIMIT], meaning[LIMIT];
    cout << "\nEnter new Entries (# to Stop) :-";
    while (1)
    {
        cout << "\n\nEnter new Word \t: ";
        cin >> word;
        if(stringCompare(word,"#")==0) //Please Ignore this Warning :)
            break;
        cout << "Enter meaning \t: ";
        cin >> meaning;
        root = insert(retRoot(), word, meaning);
    }
}

AVLNode *AVLTree::insert(AVLNode *r, char word[], char meaning[])
{
    if(r==NULL)
    {
        AVLNode *curr;
        curr = create_node(word,meaning);
        r = curr;
        cout<<"Word Inserted Successfully!";
    }
    else
    {
        if(stringCompare(word,r->word)<0)
        {
            r->left = insert(r->left,word,meaning);
            if(balance_factor(r)>=2 || balance_factor(r)<=-2)
            {
                if (stringCompare(word,r->left->word) < 0)
                    r = LL(r);
                else
                    r = LR(r);
            }
        }
        else if(stringCompare(word,r->word)>0)
        {
            r->right = insert(r->right,word,meaning);
            if(balance_factor(r)>=2 || balance_factor(r)<=-2)
            {
                if (stringCompare(word, r->right->word) > 0)
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
    T->right = rotate_right(T->right);
    T = rotate_left(T);
    return T;
}

AVLNode *AVLTree::LR(AVLNode *T)
{
    T->left = rotate_left(T->left);
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
        return 1;
    hl = height(T->left);
    hr = height(T->right);
    if(hl>hr)
        return hl+1;
    else
        return hr+1;
}

int AVLTree::balance_factor(AVLNode *T)
{
    if(T==NULL)
    {
        return 0;
    }
    else
        return height(T->left)-height(T->right);
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
        return;
    }
    temp = root;
    while(temp!=NULL)
    {
        if(stringCompare(temp->word,key)>0)
        {
            temp  = temp->left;
        }
        else if(stringCompare(temp->word,key)<0)
        {
            temp = temp->right;
        }
        else
        {
            cout<<"\nWord   \t: "<<temp->word;
            cout<<"\nMeaning \t: "<<temp->meaning;
            return;
        }
    }
    cout<<"\nWord NOT found!";
}

void AVLTree::del(char key[])
{
    if(isEmpty())
    {
        cout<<"\nDictionary is Empty!";
        return;
    }
    AVLNode *temp,*parent;
    char flag;
    temp = root;
    parent = root;
    flag = 'S';
    while(temp!=NULL)
    {
        if(stringCompare(temp->word,key)>0)
        {
            parent = temp;
            flag = 'L';
            temp  = temp->left;
        }
        else if(stringCompare(temp->word,key)<0)
        {
            parent = temp;
            flag = 'R';
            temp = temp->right;
        }
        else
        {
            if(flag == 'L')
            {
                parent->left = delete_node(temp);
                parent->height = height(parent);
                if(balance_factor(parent)>=2)
                {
                    parent = LL(parent);
                }
                else if(balance_factor(parent)<=-2)
                {
                    parent = RR(parent);
                }
            }
            else if(flag == 'R')
            {
                parent->right = delete_node(temp);
                parent->height = height(parent);
                if(balance_factor(parent)>=2)
                {
                    parent = LL(parent);
                }
                else if(balance_factor(parent)<=-2)
                {
                    parent = RR(parent);
                }
            }
            else
            {
                root = delete_node(temp);
                if(root!=NULL)
                {
                    root->height = height(root);
                    if (balance_factor(root) >= 2)
                    {
                        root = LL(root);
                    }
                    else if (balance_factor(root) <= -2)
                    {
                        root = RR(root);
                    }
                }
            }
            cout<<"\nWord Deleted Successfully!";
            return;
        }
    }
    cout<<"\nWord NOT found!";
}

AVLNode *AVLTree::delete_node(AVLNode *r)
{
    //if root == NULL then
    if(r==NULL)
    {
        return NULL;
    }
    
    //leaf node
    else if(r->left==NULL && r->right==NULL)
    {
        delete r;
        return NULL;
    }
        
    //node with left child only
    else if(r->left!=NULL && r->right==NULL)
    {
        return r->left;
    }
    //node with right child only
    else if(r->left==NULL && r->right!=NULL)
    {
        return r->right;
    }
        
    //node with two children
    else
    {
        AVLNode *temp;
        //find the minimum valued node in right subtree
        temp = r->right;
        while(temp->left!=NULL)
        {
            temp = temp->left;
        }
        //copy that to current node
        strcpy(r->word,temp->word);
        strcpy(r->meaning,temp->meaning);
        
        //delete the in-order successor
        r->right = delete_node(temp);
        
        r->height = height(r);
        if(balance_factor(r)>=2)
        {
            r = LL(r);
        }
        else if(balance_factor(r)<=-2)
        {
            r = RR(r);
        }
        return r;
    }
}

//main()
int main()
{
    AVLTree obj;
    int ch;
    char choice,word[LIMIT];
    cout<<"\nProgram to implement Dictionary using AVL Tree.";
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
        cout<<"\n 8 for Deletion";
        cout<<"\n -1 to Clear whole Tree";
        cout<<"\n  0 to Quit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        switch(ch) {
            case 1 :
                obj.construct();
                break;
            case 2 :
                if (!obj.isEmpty()) {
                cout << "\nIn-Order Traversal is ";
                obj.inOrder(obj.retRoot());
                }
                else
                    cout<<"\nDictionary is Empty!";
                break;
            case 3 :
                cout<<"\nEnter Word : ";
                cin>>word;
                obj.search(word);
                break;
            case 4 :
                cout<<"\nHeight of Tree is "<<obj.height(obj.retRoot());
                break;
            case 5 :
                cout<<"\nDepth of Tree is "<<obj.height(obj.retRoot());
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
            case 8 : if(!obj.isEmpty()) {
                    cout<<"\nCaution! The tree nodes might lose their balance factors!";
                    cout<<"\nEnter Word to Delete : ";
                    cin>>word;
                    obj.del(word);
                }
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

//Various Functions
int stringCompare(char a[],char b[])                                        //Compares two strings
{
    int i,len=0,len2=0;
    for(i=0;a[i]!='\0';i++)
        len++;
    for(i=0;b[i]!='\0';i++)
        len2++;
    if(len>len2)
        return 1;               //a>b
    else if(len<len2)
        return -1;              //a<b
    for(i=0;i<len;i++)
    {
        if(a[i]<b[i])
        {
            return -1;          //a<b
        }
        else if(a[i]>b[i])
        {
            return 1;           //a>b
        }
    }
    return 0;                   //a==b
}

/* OUTPUT

 
*/