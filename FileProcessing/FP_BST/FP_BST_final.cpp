#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;
struct Node
{
    int key;    //노드의 키값
    int height; //해당노드를 루트로 하는 서브트리의 높이
    Node *left;
    Node *right;
};
bool alreadyKeyExist = false;
bool deleteKeyNotExist = false;
//
void inOrderBST(Node *T)
{
    if (T == NULL)
        return;
    else
    {
        inOrderBST(T->left);
        printf("%d ", T->key);
        inOrderBST(T->right);
    }
}
int noNodes(Node *root) //노드의 개수
{
    int tmp = 0;
    if (root != NULL)
    {
        tmp = noNodes(root->left) + noNodes(root->right);
        tmp++; // root
    }
    return tmp;
}
Node *maxNode(Node *root)
{
    Node *p = NULL, *m = NULL;
    while (root != NULL)
    {
        p = root;
        root = root->right;
    }
    m = p;
    return m;
}
Node *minNode(Node *root)
{
    Node *p = NULL, *m = NULL;
    while (root != NULL)
    {
        p = root;
        root = root->left;
    }
    m = p;
    return m;
}
Node *getNode()
{
    Node *n = new Node();
    n->left = NULL;
    n->right = NULL;
    return n;
}
int height(Node *root)
{
    int leftH = 0, rightH = 0;
    if (root != NULL)
    {
        leftH = height(root->left) + 1;
        rightH = height(root->right) + 1;
    }
    return (leftH > rightH) ? leftH : rightH;
}
void heightUpdate(Node *root)
{
    if (root == NULL)
        return;
    else
    {
        heightUpdate(root->left);
        root->height = height(root);
        heightUpdate(root->right);
    }
}
Node *searchParent(Node *T, int searchKey)
{
    Node *p = T;
    Node *q = T;
    while (p != NULL && p->key != searchKey)
    {
        q = p;
        if (p->key > searchKey)
            p = p->left;
        else
            p = p->right;
    }
    return q;
}
Node *insertBST(Node *T, int newKey)
{
    Node *p = T;    // parent
    Node *q = NULL; // q는 p의 부모
    stack<Node *> st;
    while (p != NULL) //새노드 삽입할 위치 찾기, 그 부모 스택에 저장
    {
        if (newKey == p->key) // already key exist, 중복키
        {
            alreadyKeyExist = true;
            return T;
        }
        q = p;
        st.push(q); //현위치
        if (newKey < p->key)
            p = p->left;
        else
            p = p->right;
        //위치 찾음, p는 넣을 위치
    }
    //새노드
    Node *newNode = getNode();
    newNode->key = newKey;
    // q의 자식(p)으로 newkey 삽입
    if (T == NULL)
    {
        T = newNode;
    }
    else if (newKey < q->key)
        q->left = newNode;
    else
        q->right = newNode;
    //
    while (!st.empty())
    {
        // update height while popping parent node from stack
        st.pop();
        q->height = 1 + max(height(q->left), height(q->right));
    }
    return T;
}
Node *deleteBST(Node *T, int deleteKey)
{
    Node *p = T;                             // parent
    Node *q = NULL;                          // q는 p의 부모
    while (p != NULL && deleteKey != p->key) //삭제위치찾기, 부모 스택에 저장
    {
        q = p;
        if (deleteKey < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (p == NULL) // delete key not exist
    {
        deleteKeyNotExist = true;
        return T;
    }
    if (p->left != NULL && p->right != NULL) // degree 2개
    {
        Node *r = p;
        // Node *s = NULL;
        int leftHeight = height(p->left);
        int rightHeight = height(p->right);
        if (leftHeight < rightHeight) // right 더 깊음
        {
            p = minNode(p->right);
        }
        else if (leftHeight > rightHeight) // left 더 깊음
        {
            p = maxNode(p->left);
        }
        else
        {
            int numLeft = noNodes(p->left);
            int numRight = noNodes(p->right);
            if (numLeft >= numRight)
            {
                p = maxNode(p->left);
            }
            else
            {
                p = minNode(p->right);
            }
        }
        q = searchParent(r, p->key);
        r->key = p->key;
    }
    // p의 degree 0 or 1, delete p from T
    if (p->left == NULL && p->right == NULL) // degree 0
    {
        if (q == NULL)
            T = NULL; // case of root
        else if (q->left == p)
            q->left = NULL;
        else
            q->right = NULL;
    }
    else
    { // case of degree 1
        if (p->left != NULL)
        {
            if (q == NULL)
                T = T->left; // case of root
            else if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
        }
        else
        {
            if (q == NULL)
                T = T->right; // case of root
            else if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
        }
    }
    // update height
    heightUpdate(T);
    return T;
}
int main()
{
    string line;
    ifstream file("BST-input.txt"); // .txt 파일을 연다. 없으면 생성.
    Node *node = NULL;
    // Node *node = new Node();
    if (file.is_open()) // 정상적으로 열리나 확인
    {
        while (getline(file, line)) // 텍스트 파일 한 줄씩 읽기,string형태로 저장
        {
            // line = "i 25"
            string line_;
            if (line[0] == 'i')
            {
                line_ = line.substr(2);
                node = insertBST(node, stoi(line_));
                if (alreadyKeyExist)
                {
                    cout << line << " : The key already exists\n";
                    alreadyKeyExist = false;
                }
                inOrderBST(node);
                printf("\n");
            }
            else
            {
                line_ = line.substr(2);
                node = deleteBST(node, stoi(line_));
                if (deleteKeyNotExist)
                {
                    cout << line << " : The key does not exist\n";
                    deleteKeyNotExist = false;
                }
                inOrderBST(node);
                printf("\n");
            }
        }
        file.close(); // 열었던 파일은 반드시 닫아야함.
    }
    else
    {
        cout << "Unable to open file";
    }
    return 0;
}