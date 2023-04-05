
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

// BST дерево
class BST {

    struct node1 {
        int data;
        node1* left;
        node1* right;
    };
    node1* root;

    node1* makeEmpty(node1* t) {
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node1* insert1(int x, node1* t)
    {
        if (t == NULL)
        {
            t = new node1;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
            t->left = insert1(x, t->left);
        else if (x > t->data)
            t->right = insert1(x, t->right);
        return t;
    }

    node1* findMin(node1* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node1* findMax(node1* t) {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node1* remove(int x, node1* t) {
        node1* temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder1(node1* t) {
        if (t == NULL)
            return;
        inorder1(t->left);
        cout << t->data << " ";
        inorder1(t->right);
    }

    node1* find1(node1* t, int x) {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find1(t->left, x);
        else if (x > t->data)
            return find1(t->right, x);
        else
            return t;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert1(int x) {
        root = insert1(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder1(root);
        cout << endl;
    }

    void search1(int x) {
        root = find1(root, x);
    }
};





 //  AVL дерево
struct Node {
    int data; // holds the key
    Node* parent; // pointer to the parent
    Node* left; // pointer to left child
    Node* right; // pointer to right child
    int bf; // balance factor of the node
};

typedef Node* NodePtr;

// class AVLTree implements the operations in AVL tree
class AVLTree {
private:
    NodePtr root;

    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer
    void initializeNode(NodePtr node, int key) {
        node->data = key;
        node->parent = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        node->bf = 0;
    }

    void preOrderHelper(NodePtr node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(NodePtr node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(NodePtr node) {
        if (node != nullptr) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }

        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    NodePtr deleteNodeHelper(NodePtr node, int key) {
        // search the key
        if (node == nullptr) return node;
        else if (key < node->data) node->left = deleteNodeHelper(node->left, key);
        else if (key > node->data) node->right = deleteNodeHelper(node->right, key);
        else {
            // the key has been found, now delete it

            // case 1: node is a leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            }

            // case 2: node has only one child
            else if (node->left == nullptr) {
                NodePtr temp = node;
                node = node->right;
                delete temp;
            }

            else if (node->right == nullptr) {
                NodePtr temp = node;
                node = node->left;
                delete temp;
            }

            // case 3: has both children
            else {
                NodePtr temp = minimum(node->right);
                node->data = temp->data;
                node->right = deleteNodeHelper(node->right, temp->data);
            }

        }

        // Write the update balance logic here 
        // YOUR CODE HERE

        return node;
    }




    // update the balance factor the node
    void updateBalance(NodePtr node) {
        if (node->bf < -1 || node->bf > 1) {
            rebalance(node);
            return;
        }

        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->bf -= 1;
            }

            if (node == node->parent->right) {
                node->parent->bf += 1;
            }

            if (node->parent->bf != 0) {
                updateBalance(node->parent);
            }
        }
    }

    // rebalance the tree
    void rebalance(NodePtr node) {
        if (node->bf > 0) {
            if (node->right->bf < 0) {
                rightRotate(node->right);
                leftRotate(node);
            }
            else {
                leftRotate(node);
            }
        }
        else if (node->bf < 0) {
            if (node->left->bf > 0) {
                leftRotate(node->left);
                rightRotate(node);
            }
            else {
                rightRotate(node);
            }
        }
    }

    void printHelper(NodePtr root, string indent, bool last) {
        // print the tree structure on the screen
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            }
            else {
                cout << "L----";
                indent += "|    ";
            }

            cout << root->data << "( BF = " << root->bf << ")" << endl;

            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }
    public:
        AVLTree() {
            root = nullptr;
        }

        // Pre-Order traversal
        // Node->Left Subtree->Right Subtree
        void preorder() {
            preOrderHelper(this->root);
        }

        // In-Order traversal
        // Left Subtree -> Node -> Right Subtree
        void Inorder() {
            inOrderHelper(this->root);
        }

        // Post-Order traversal
        // Left Subtree -> Right Subtree -> Node
        void postorder() {
            postOrderHelper(this->root);
        }

        // search the tree for the key k
        // and return the corresponding node
        NodePtr searchTree(int k) {
            return searchTreeHelper(this->root, k);
        }

        // find the node with the minimum key
        NodePtr minimum(NodePtr node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        // find the node with the maximum key
        NodePtr maximum(NodePtr node) {
            while (node->right != nullptr) {
                node = node->right;
            }
            return node;
        }

        // find the successor of a given node
        NodePtr successor(NodePtr x) {
            // if the right subtree is not null,
            // the successor is the leftmost node in the
            // right subtree
            if (x->right != nullptr) {
                return minimum(x->right);
            }

            // else it is the lowest ancestor of x whose
            // left child is also an ancestor of x.
            NodePtr y = x->parent;
            while (y != nullptr && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        // find the predecessor of a given node
        NodePtr predecessor(NodePtr x) {
            // if the left subtree is not null,
            // the predecessor is the rightmost node in the 
            // left subtree
            if (x->left != nullptr) {
                return maximum(x->left);
            }

            NodePtr y = x->parent;
            while (y != nullptr && x == y->left) {
                x = y;
                y = y->parent;
            }

            return y;
        }

        // rotate left at node x
        void leftRotate(NodePtr x) {
            NodePtr y = x->right;
            x->right = y->left;
            if (y->left != nullptr) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            }
            else if (x == x->parent->left) {
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;

            // update the balance factor
            x->bf = x->bf - 1 - max(0, y->bf);
            y->bf = y->bf - 1 + min(0, x->bf);
        }

        // rotate right at node x
        void rightRotate(NodePtr x) {
            NodePtr y = x->left;
            x->left = y->right;
            if (y->right != nullptr) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            }
            else if (x == x->parent->right) {
                x->parent->right = y;
            }
            else {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;

            // update the balance factor
            x->bf = x->bf + 1 - min(0, y->bf);
            y->bf = y->bf + 1 + max(0, x->bf);
        }

        // insert the key to the tree in its appropriate position
        void insert(int key) {
            // PART 1: Ordinary BST insert
            NodePtr node = new Node;
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            node->data = key;
            node->bf = 0;
            NodePtr y = nullptr;
            NodePtr x = this->root;

            while (x != nullptr) {
                y = x;
                if (node->data < x->data) {
                    x = x->left;
                }
                else {
                    x = x->right;
                }
            }

            // y is parent of x
            node->parent = y;
            if (y == nullptr) {
                root = node;
            }
            else if (node->data < y->data) {
                y->left = node;
            }
            else {
                y->right = node;
            }

            // PART 2: re-balance the node if necessary
            updateBalance(node);

        }

        NodePtr getRoot() {
            return this->root;
        }

        // delete the node from the tree
        NodePtr deleteNode(int data) {
            NodePtr deletedNode = deleteNodeHelper(this->root, data);
            return deletedNode;
        }

        // print the tree structure on the screen
        void prettyPrint() {
            printHelper(this->root, "", true);
        }

};


    // Структура для представления 
//каждого узла в красно-черном дереве
struct node {
    int d; // data
    int c; // 1-red, 0-black
    struct node* p; // parent
    struct node* r; // right-child
    struct node* l; // left child
};

// глобальный корень для всего дерева
struct node* root = NULL;

// функция для выполнения вставки узла в дерево бинарного поиска
struct node* bst(struct node* trav,
    struct node* temp)
{
    // Если дерево пустое, 
    //верните новый узел
    if (trav == NULL)
        return temp;

    // В противном случае повторите движение вниз по дереву
    if (temp->d < trav->d)
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d)
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }

    // Возвращает (неизмененный) указатель узла
    return trav;
}

// Функция, выполняющая поворот 
//переданного узла вправо
void rightrotate(struct node* temp)
{
    struct node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}

// Функция, выполняющая поворот 
//переданного узла влево
void leftrotate(struct node* temp)
{
    struct node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

// Эта функция исправляет нарушения,
//вызванные вставкой двоичного дерева поиска

void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0)
        && (pt->p->c == 1))
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;

        /*  Case : A
             Родительский элемент pt является 
             левым дочерним элементом
             от дедушки-родителя
pt */
        if (parent_pt == grand_parent_pt->l)
        {

            struct node* uncle_pt = grand_parent_pt->r;

            /* Case : 1
                The uncle of pt is also red
                требуется перекраска */
            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }

            else {

                /* Case : 2
                     pt является правым дочерним элементом своего родителя
                     Требуется поворот левым */
                if (pt == parent_pt->r) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                     pt является левым дочерним элементом своего родителя
                     Требуется поворот вправо */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }

        /* Case : B
             Родитель pt является 
             правым потомком 
             бабушки и дедушки
pt */
        else {
            struct node* uncle_pt = grand_parent_pt->l;

            /*  Case : 1
                Дядя пт тоже красный
                Требуется только перекраска */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                  pt является левым дочерним элементом своего родителя
                   Требуется поворот вправо */
                if (pt == parent_pt->l) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                     pt является правым дочерним элементом своего родителя
                   Требуется поворот влево */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }
    
    

}

// Функция для печати обхода фиксированного 
//дерева по порядку
void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}

// driver code
int main()
{
    BST t;
    clock_t start1 = clock();
    t.insert1(50);
    t.insert1(30);
    t.insert1(70);
    t.insert1(23);
    t.insert1(5);
    t.insert1(87);
    t.insert1(95);
    t.insert1(36);
    t.insert1(52);
    t.insert1(9);
    t.insert1(4);
    t.insert1(0);
    t.insert1(38);
    t.insert1(90);
    t.insert1(29);
    clock_t end1 = clock();
    cout << "Inorder Traversal of BST Tree\n";
    t.display();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("\nThe time: %f seconds\n", seconds1);
    //cout << endl;


    AVLTree BST;
    // bst.createSampleTree1();
    clock_t Start = clock();
    BST.insert(50);
    BST.insert(30);
    BST.insert(70);
    BST.insert(23);
    BST.insert(5);
    BST.insert(87);
    BST.insert(95);
    BST.insert(36);
    BST.insert(52);
    BST.insert(9);
    BST.insert(4);
    BST.insert(0);
    BST.insert(38);
    BST.insert(90);
    BST.insert(29);
    clock_t End = clock();
    //BST.prettyPrint();
    cout << "Inorder Traversal of AVL Tree\n";
    BST.Inorder();
    cout << endl;
    double Seconds = (double)(End - Start) / CLOCKS_PER_SEC;
    printf("\nThe time: %f seconds\n", Seconds);
    //return 0;

    int n = 15;
    int a[15] = { 50, 30, 70, 23, 5, 87, 95, 36, 52, 9, 4, 0, 38, 90, 29 };
    clock_t start = clock();
    for (int i = 0; i < n; i++) {

        // выделение памяти узлу и инициализация:
        // 1. цвет как красный
        // 2. родительский, левый и правый указатели равны нулю
        // 3. данные в виде i-го значения в массиве
        struct node* temp
            = (struct node*)malloc(sizeof(struct node));
        temp->r = NULL;
        temp->l = NULL;
        temp->p = NULL;
        temp->d = a[i];
        temp->c = 1;

        // вызывающая функция, которая 
        //выполняет вставку в двоичное дерево 
        //поиска этого вновь созданного узла
        root = bst(root, temp);
        
        // вызов функции для сохранения свойств rb
        // деревa
        fixup(root, temp);
        root->c = 0;
    }
    clock_t end = clock();
    
    printf("Inorder Traversal of RB Tree\n");
    inorder(root);
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time: %f seconds\n", seconds);

    return 0;
}