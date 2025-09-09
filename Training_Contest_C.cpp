#include <iostream>
#include <fstream>

using namespace std;

struct node {
    int value;
    //bool lr;
    node* parent;
    node* left;
    node* right;
    node(): value(0), parent(nullptr), left(nullptr), right(nullptr){}
};

node* createTree(int N, node* parent, int v = 1) {
    node* cur = new node;
    cur->parent = parent;
    cur->value = v; 
    if (v*2 <= N)
        cur->left = createTree(N, cur, v*2);
    if (v*2+1 <= N)
        cur->right = createTree(N, cur, v * 2 + 1);
    return cur;
}

void deleteTree(node* root) {
    if (root->left)
        deleteTree(root->left);
    if (root->right)
        deleteTree(root->right);
    delete root;
    root = nullptr;
}

bool fixedNum;

node* findNode(int N, node* root) { 
    node* tmp = root;
    fixedNum = false;
    if (N == root->value) fixedNum = true;
    if ((root->left) && (!fixedNum))
        tmp = findNode(N, root->left);
    if ((root->right) && (!fixedNum))
        tmp = findNode(N, root->right);
    if (fixedNum)
        return tmp;
    else return nullptr;
}

void printTree(node* root) { 
    if (root->left)
        printTree(root->left);
    cout << root->value << ' ';
    if (root->right)
        printTree(root->right);
}

int main()
{
    ifstream file("input.txt");
    int N, Q; 
    file >> N >> Q;

    int* numOfNodes = new int[Q];
    for (size_t i = 0; i < Q; ++i)
    {
        file >> numOfNodes[i];
    }

    node* n = createTree(N, nullptr);

    node* v = nullptr;
    node* p = nullptr;
    node* pp = nullptr;
    node* root = n;
    for (size_t i = 0; i < Q; ++i)
    {
        v = findNode(numOfNodes[i], root);
        if (v) {
            p = v->parent;
            if (p) {                                      
                pp = p->parent;
                if (p->left == v) { 
                    if (v->left) {          //если существует vl... то соединяем p и vl
                        p->left = v->left;
                        p->left->parent = p;
                    }
                    else
                        p->left = nullptr;

                    v->left = p; 
                    p->parent = v;
                    
                    if (pp) { 
                        if (pp->left == p) {
                            pp->left = v;
                            v->parent = pp;
                        }
                        else if (pp->right == p) {
                            pp->right = v;
                            v->parent = pp;
                        }
                    }
                    else {
                        v->parent = nullptr;
                        root = v;
                    }
                }
                else if (p->right == v) { 
                    if (v->right) {              //если существует vr... то соединяем p и vr
                        p->right = v->right;
                        p->right->parent = p;
                    }
                    else
                        p->right = nullptr;

                    v->right = p; 
                    p->parent = v;

                    if (pp) {
                        if (pp->right == p) {
                            pp->right = v;
                            v->parent = pp;
                        }
                        else if (pp->left == p) {
                            pp->left = v;
                            v->parent = pp;
                        }
                    }
                    else {
                        v->parent = nullptr;
                        root = v;
                    }
                }
            }
        }
        v = nullptr;
        p = nullptr;
        pp = nullptr;
    }
    printTree(root);
    deleteTree(n);
}