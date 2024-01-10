#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
using namespace std;
struct Node
{
    int key;    //키값
    int height; //해당노드를 루트로 하는 서브트리의 높이
    int bf;     // balace factor, 왼쪽서브트리높이-오른쪽서브트리높이
    Node *left;
    Node *right;
};
typedef enum rotationType
{
    NO,
    LL,
    RR,
    LR,
    RL
} rotationType;
string strRt[5] = {"NO", "LL", "RR", "LR", "RL"};
// header
void inOrderBST(Node *T);
int height(Node *root);
//
Node *getAVLNode(int newKey);
bool searchNode(Node *T, int searchKey);
Node *searchParent(Node *T, int searchKey);
void updateHBf(Node **T); // update height,bf
void checkBalance(Node **T, int newKey, Node **p, Node **q, rotationType *rt);
rotationType findRotationType(Node *p);
void insertAVL(Node **T, int newKey);
void insertBST(Node **T, int newKey);
Node *rotateTree(Node *T, rotationType rt, Node *p, Node *q);
void deleteBST(Node **T, int deleteKey);
void deleteAVL(Node **T, int deleteKey);
//
//
//
//
//구현
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
void inOrderBST(Node *T) // inOrder 출력
{
    if (T == NULL)
        return;
    else
    {
        inOrderBST(T->left);
        printf("(%d, %d) ", T->key, T->bf);
        inOrderBST(T->right);
    }
}
bool searchNode(Node *T, int searchKey)
{
    Node *tmp = T;
    while (tmp != NULL && tmp->key != searchKey)
    {
        if (tmp->key > searchKey)
            tmp = tmp->left;
        else
            tmp = tmp->right;
    }
    if (tmp == NULL)
        return false;
    return true;
}
int height(Node *n)
{
    int h = 0;
    if (n != NULL)
        h = 1 + max(height(n->left), height(n->right));
    return h;
}
// insert
Node *getAVLNode(int newKey)
{
    Node *n = new Node();
    n->key = newKey;
    n->bf = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
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
void updateHBf(Node **T)
{
    Node *t = *T;
    if (t == NULL)
        return;
    t->height = height(t);
    t->bf = height(t->left) - height(t->right);
    updateHBf(&t->left);
    updateHBf(&t->right);
}
void checkBalance(Node **T, int newKey, Node **p, Node **q, rotationType *rt)
{ // p는 불균형 발생 노드, q는 p의 부모
    updateHBf(T);
    Node *x = *T;
    Node *xp = x;
    while (x != NULL)
    {
        if (x->bf > 1 || x->bf < -1) //불균형 발생
        {
            *p = x;
            *q = xp;
        }
        xp = x;
        //
        if (x->key > newKey)
            x = x->left;
        else
            x = x->right;
    }
    *rt = findRotationType(*p);
    cout << strRt[*rt] << " ";
}
rotationType findRotationType(Node *p)
{
    if (p == NULL)
        return NO;
    if (p->bf > 1)
    {
        if (p->left->bf < 0)
            return LR;
        return LL;
    }
    else
    {
        if (p->right->bf > 0)
            return RL;
        return RR;
    }
    return NO;
}

void insertAVL(Node **T, int newKey) ///////////////////////////////////////////////////////////
{
    Node *p = NULL;
    Node *q = NULL;
    rotationType rt = NO;
    insertBST(T, newKey);
    checkBalance(T, newKey, &p, &q, &rt);
    p = rotateTree(*T, rt, p, q); //불균형트리 회전
    //교정된 트리와 기존트리 연결
    if (p == NULL)
        return;
    if (searchNode(p, (*T)->key)) // root가 불균형노드에 포함
    {
        *T = p;
        return;
    }
    if (p->key < q->key)
        q->left = p;
    else
        q->right = p;
    // bf update
    updateHBf(T);
    return;
}
void insertBST(Node **T, int newKey)
{
    Node *p = *T;
    Node *q = NULL;   // q는 p의 부모
    while (p != NULL) //새노드 삽입할 위치 찾기
    {
        q = p;
        if (newKey < p->key)
            p = p->left;
        else
            p = p->right;
        // p 위치에 새노드 넣기
    }
    //새노드 생성
    Node *y = getAVLNode(newKey); //새로 삽입되는 노드
    // q의 자식(p)으로 newkey 삽입
    if (*T == NULL)
        *T = y;
    else if (newKey < q->key)
        q->left = y;
    else
        q->right = y;
}
Node *rotateTree(Node *T, rotationType rt, Node *p, Node *q)
{ // // p는 불균형 발생 노드, q는 p의 부모
    Node *tmp;
    q = p;
    switch (rt)
    {
    case LR:
        tmp = p->left;
        p->left = rotateTree(T, RR, tmp, q);
        return rotateTree(T, LL, p, q);
    case LL:
        tmp = p->left;
        p->left = tmp->right;
        tmp->right = p;
        updateHBf(&tmp);
        return tmp;
    case RL:
        tmp = p->right;
        p->right = rotateTree(T, LL, tmp, q);
        return rotateTree(T, RR, p, q);
    case RR:
        tmp = p->right;
        p->right = tmp->left;
        tmp->left = p;
        updateHBf(&tmp);
        return tmp;
    case NO:
        return p;
    }
    return p;
}
// deleteAVL
void deleteAVL(Node **T, int deleteKey)
{
    Node *p = NULL;
    Node *q = NULL;
    rotationType rt = NO;
    deleteBST(T, deleteKey);
    checkBalance(T, deleteKey, &p, &q, &rt);
    p = rotateTree(*T, rt, p, q); //불균형트리 회전
    //교정된 트리와 기존트리 연결
    if (p == NULL)
        return;
    if (searchNode(p, (*T)->key)) // root가 불균형노드에 포함
    {
        *T = p;
        return;
    }
    if (p->key < q->key)
        q->left = p;
    else
        q->right = p;
    // bf update
    updateHBf(T);
    return;
}
void deleteBST(Node **T, int deleteKey)
{
    Node *p = *T;               // parent
    Node *q = NULL;             // q는 p의 부모
    while (deleteKey != p->key) //삭제 p 위치찾기
    {
        q = p;
        if (deleteKey < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (p->left != NULL && p->right != NULL) // degree 2개
    {
        Node *r = p;
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
            *T = NULL; // case of root
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
                *T = (*T)->left; // case of root
            else if (q->left == p)
                q->left = p->left;
            else
                q->right = p->left;
        }
        else
        {
            if (q == NULL)
                *T = (*T)->right; // case of root
            else if (q->left == p)
                q->left = p->right;
            else
                q->right = p->right;
        }
    }
}
int main()
{
    string line;
    ifstream file("testInput.txt"); // .txt 파일을 연다. 없으면 생성.
    Node *n = NULL;
    if (file.is_open()) // 정상적으로 열리나 확인
    {
        while (getline(file, line)) // 텍스트 파일 한 줄씩 읽기, string 형태로 저장
        {
            string line_;
            if (line[0] == 'i') // insert
            {
                line_ = line.substr(2); // key value type string
                bool boolSearch = searchNode(n, stoi(line_));
                if (boolSearch) //중복키존재
                    cout << line << " : The key already exists\n";
                else
                    insertAVL(&n, stoi(line_));
                cout << line_ << " ";
                inOrderBST(n);
                printf("\n");
            }
            else // delete
            {
                line_ = line.substr(2);
                bool boolSearch = searchNode(n, stoi(line_));
                if (!boolSearch) //존재하지 않는키
                    cout << line << " : The key does not exist\n";
                else
                    deleteAVL(&n, stoi(line_));
                cout << line_ << " ";
                inOrderBST(n);
                printf("\n");
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    return 0;
}
