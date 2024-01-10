#include <iostream>
#include <fstream>
#include <string>
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
int rotationIdx = 0;
/*                                                                                                              header1  */
void inOrderBST(Node *T);
int height(Node *root);
Node *getAVLNode(int newKey);
bool searchNode(Node *T, int searchKey);
Node *searchParent(Node *T, int searchKey);
int noNodes(Node *root);
Node *maxNode(Node *root);
Node *minNode(Node *root);
/*                                                                                                                   2   */
void updateHBf(Node **T);
void checkBalance(Node **T, int key, rotationType *rt, Node **p, Node **q);
Node *rotateTree(Node *T, rotationType rt, Node *p, Node *q);
rotationType findRotationType(Node *p);
/*                                                                                                                   3   */
void insertAVL(Node **T, int newKey);
void insertBST(Node **T, int newKey);
void deleteBST(Node **T, int &key);
void deleteAVL(Node **T, int deleteKey);
/*
                                                                                                            implement1

                                                                                                                         */
void inOrderBST(Node *T) /*                                                                                    inOrderBST*/
{                        // inorder 출력
    if (T == NULL)
        return;
    else
    {
        inOrderBST(T->left);
        printf("(%d, %d) ", T->key, T->bf); //출력 수정, 괄호와 콤마, space, bf 추가
        inOrderBST(T->right);
    }
}
int height(Node *n) /*                                                                                            height*/
{                   // 노드의 height 리턴
    int h = 0;
    if (n != NULL)
        h = 1 + max(height(n->left), height(n->right));
    return h;
}
Node *getAVLNode(int newKey) /*                                                                               getAVLNode*/
{                            // 빈 노드 생성
    Node *n = new Node();
    n->key = newKey;
    n->bf = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}
bool searchNode(Node *T, int searchKey) /*                                                                    getAVLNode*/
{                                       // 해당 키값이 노드에 존재하는지 확인
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
Node *searchParent(Node *T, int searchKey) /*                                                               searchParent*/
{                                          // 해당 키값의 부모노드 리턴
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
int noNodes(Node *root) /*                                                                                      noNodes*/
{                       //노드의 개수 리턴
    int tmp = 0;
    if (root != NULL)
    {
        tmp = noNodes(root->left) + noNodes(root->right);
        tmp++; // root
    }
    return tmp;
}
Node *maxNode(Node *root) /*                                                                                    maxNode*/
{                         // key값이 가장 큰 노드 리턴
    Node *p = NULL, *m = NULL;
    while (root != NULL)
    {
        p = root;
        root = root->right;
    }
    m = p;
    return m;
}
Node *minNode(Node *root) /*                                                                                    minNode*/
{                         // key값이 가장 작은 노드 리턴
    Node *p = NULL, *m = NULL;
    while (root != NULL)
    {
        p = root;
        root = root->left;
    }
    m = p;
    return m;
}
/*
                                                                                                                     2

                                                                                                                         */
void updateHBf(Node **T) /*                                                                                    updateHBf*/
{                        // 노드의 height와 bf update
    Node *t = *T;
    if (t == NULL)
        return;
    t->height = height(t);
    t->bf = height(t->left) - height(t->right);
    updateHBf(&t->left);
    updateHBf(&t->right);
}
void checkBalance(Node **T, int key, rotationType *rt, Node **p, Node **q) /*                                checkBalance*/
{                                                                          // p는 불균형 발생 노드, q는 p의 부모, 삽입이나 삭제로 불균형된 노드 중 가장 가까운 노드
    updateHBf(T);                                                          // 키와 bf 값 업데이트
    Node *x = *T;
    Node *xp = x;
    while (x != NULL)
    {
        if (x->bf > 1 || x->bf < -1) //불균형 발생
        {
            *p = x; // p는 불균형 노드, q는 그 부모노드
            *q = xp;
        }
        xp = x;
        if (x->key > key)
            x = x->left;
        else
            x = x->right;
    }
    *rt = findRotationType(*p); //불균형 발생 노드의 회전종류 찾기
    rotationIdx = *rt;
    // cout << strRt[*rt] << " ";
}
Node *rotateTree(Node *T, rotationType rt, Node *p, Node *q) /*                                                 rotateTree*/
{                                                            //  p는 불균형 발생 노드, q는 p의 부모
    Node *tmp;
    q = p;
    switch (rt) // rotationType에 따라 서브트리를 회전
    {
    case LR:
        tmp = p->left;
        p->left = rotateTree(T, RR, tmp, q); //부분 RR 회전
        return rotateTree(T, LL, p, q);      // LL 회전
    case LL:
        tmp = p->left;
        p->left = tmp->right;
        tmp->right = p;
        updateHBf(&tmp);
        return tmp;
    case RL:
        tmp = p->right;
        p->right = rotateTree(T, LL, tmp, q); //부분 LL 회전
        return rotateTree(T, RR, p, q);       // RR 회전
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
rotationType findRotationType(Node *p) /*                                                                findRotationType*/
{                                      // 불균형 발생 노드의 회전 종류 찾기
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
/*
                                                                                                                     3

                                                                                                                         */
void insertAVL(Node **T, int newKey) /*                                                                         insertAVL*/
{
    Node *p = NULL;
    Node *q = NULL;
    rotationType rt = NO; // NO로 초기값
    insertBST(T, newKey);
    checkBalance(T, newKey, &rt, &p, &q);
    p = rotateTree(*T, rt, p, q); //불균형트리 회전
    //교정된 트리와 기존트리 연결
    if (p == NULL)
        return;
    if (searchNode(p, (*T)->key)) // root가 불균형트리에 포함
    {
        *T = p;
        return;
    }
    if (p->key < q->key)
        q->left = p;
    else
        q->right = p;
    // height와 bf update
    updateHBf(T);
    return;
}
void insertBST(Node **T, int newKey) /*                                                                        insertBST*/
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
void deleteAVL(Node **T, int deleteKey) /*                                                                     deleteAVL*/
{
    Node *p = NULL;
    Node *q = NULL;
    rotationType rt = NO;
    int key = deleteKey;
    deleteBST(T, deleteKey);
    checkBalance(T, deleteKey, &rt, &p, &q);
    p = rotateTree(*T, rt, p, q); //불균형트리 회전
    //교정된 트리와 기존트리 연결
    if (p == NULL)
        return;
    if (searchNode(p, (*T)->key)) // root가 불균형트리에 포함
    {
        *T = p;
        return;
    }
    if (p->key < q->key)
        q->left = p;
    else
        q->right = p;
    // height, bf update
    updateHBf(T);
    return;
}
void deleteBST(Node **T, int &deleteKey) /*                                                                    deleteBST*/
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
        else // 깊이가 같을 때 노드수가 더 많은 subtree 선택
        {
            int numLeft = noNodes(p->left);
            int numRight = noNodes(p->right);
            if (numLeft > numRight) //노드 수도 같을 경우 right subtree선택
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
        // updatedeleteKey, deletekey를 바꾼 노드의 부모 키 값으로 변경
        deleteKey = q->key;
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
/*
                                                                                                                    main

                                                                                                                         */
int main()
{
    string line;
    ifstream file("AVL-input.txt"); // .txt 파일을 연다. 없으면 생성.
    Node *n = NULL;
    if (file.is_open()) // 정상적으로 열리나 확인
    {
        while (getline(file, line)) // 텍스트 파일 한 줄씩 읽기, string 형태로 저장
        {
            string line_;
            rotationIdx = 0;
            if (line[0] == 'i') /*                                                                                 insert*/
            {
                line_ = line.substr(2); // string key value
                bool boolSearch = searchNode(n, stoi(line_));
                if (boolSearch) //이미 있는 키인지 확인
                    cout << line << " : The key already exists\n";
                else
                {
                    insertAVL(&n, stoi(line_));
                    cout << strRt[rotationIdx] << " ";
                }
                inOrderBST(n);
                printf("\n");
            }
            else /*                                                                                                delete*/
            {
                line_ = line.substr(2);
                bool boolSearch = searchNode(n, stoi(line_));
                if (!boolSearch) //삭제할 키가 존재하는지 확인
                    cout << line << " : The key does not exist\n";
                else
                {
                    deleteAVL(&n, stoi(line_));
                    cout << strRt[rotationIdx] << " ";
                }
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