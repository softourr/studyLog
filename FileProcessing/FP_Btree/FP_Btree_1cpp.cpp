/*
 * 2022 File Processing
 * FP_Btree.cpp
 * 'BT-input.txt'
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;
bool found = false;
struct Node
{
    int n;    // 해당 노드가 가지고 있는 키의 개수
    int *k;   //해당 노드가 가지고 있는 키들을 담고있는 배열
    Node **p; //해당 노드가 가지고 있는 포인터들(자식 노드)
};
typedef pair<int, Node *> BTpair;
typedef stack<BTpair> PathStack;
/**
 * @brief btree inorder 순회 출력
 * @param T: tree
 */
void inorderBT(Node *T)
{
    int i;
    if (T == NULL)
        return;
    for (i = 0; i < T->n; i++)
    {
        if (T->p[0] != NULL)
            inorderBT(T->p[i]);
        printf("%d ", T->k[i]);
    }
    if (T->p[0] != NULL)
        inorderBT(T->p[i]);
}
/**
 * @brief m원 사이즈에 맞는 새로운 노드 생성
 * @param m: size
 * @return 초기화된 m 노드 리턴
 */
Node *getNode(int m)
{
    Node *T = new Node();
    T->n = 0;
    T->k = new int[m - 1]{};
    T->p = new Node *[m];
    for (int i = 0; i < m; i++)
        T->p[i] = NULL;
    return T;
}
/**
 * @brief key에 대한 검색, key 발견여부와 방문한 경로 담은 스택 리턴
 * @param T: Tree
 * @param m: m way search
 * @param key: target key
 * @param ps: pathStack
 * @return key 발견여부와 경로담은 스택 리턴, pair(i,x)는 x노드의 p[i]를 방문했다
 */
bool searchPath(Node **T, int m, int key, PathStack &ps)
{

    Node *x = *T;
    int i = 0;
    do
    {
        i = 0;                            // node의 idx
        while (i < x->n && key > x->k[i]) // n은 최대m-1개
            i++;
        BTpair a = make_pair(i, x); // x노드의 p[i] 따라가라
        ps.push(a);                 //경로저장
        //삽입할 키를 발견함, 삽입 불가
        if (i < x->n && key == x->k[i])
            return true;
    } while ((x = x->p[i]) != NULL);
    return false;
}
/**
 * @brief newKey를 노드 x의 적당한 위치에 삽입
 * @param T: Tree
 * @param m: m way search
 * @param x: **x
 * @param y: **y, x에서 newKey 위치 다음 포인터가 가리킬 노드
            (자식 노드에서 split되어 새로 만들어진 노드)
 * @param newKey
 * @return newkey가 삽입된 노드 x
 */
void insertKey(Node **T, int m, Node **x, Node **y, int newKey)
{
    // newKey보다 큰 키들을 오른쪽으로 한 칸씩 이동
    int i = (*x)->n - 1; // idx
    while (i >= 0 && newKey < (*x)->k[i])
    {
        (*x)->k[i + 1] = (*x)->k[i];
        (*x)->p[i + 2] = (*x)->p[i + 1];
        i--;
    } // i+1 자리가 key자리, p는 거기에 +1
    // newKey를 삽입
    (*x)->k[i + 1] = newKey;
    if (y == NULL)
        (*x)->p[i + 2] = NULL;
    else
        (*x)->p[i + 2] = *y;
    (*x)->n++;
}
/**
 * @brief t노드의 n,k,p 초기화
 * @param t: **t
 * @return: 초기화된 t노드
 */
void initKP(Node **t)
{
    Node *x = *t;
    x->n = 0;
    int i;
    for (i = 0; i < x->n; i++)
    {
        x->k[i] = 0;
        x->p[i] = NULL;
    }
    x->p[++i] = NULL;
    *t = x;
}
/**
 * @brief newKey를 x에 삽입 후 split
 * @param T: Tree
 * @param m: m way search
 * @param x: 분할할 노드, 이후 centerkey 이전 값들만 남아 리턴
 * @param y : x에서 newKey 위치 다음 포인터가 가리킬 노드
            (자식 노드에서 split되어 새로 만들어진 노드)
 * @param newKey
 * @return split 후 부모 노드에 삽입되어야 할 키값과 분리된 새로운 노드, 새로운 부모 반환
 */
BTpair splitNode(Node **T, int m, Node *x, Node *y, int newKey)
{
    //오버플로우를 위한 임시 노드, x와 newkey를 저장
    Node *tmp = getNode(m + 1);
    // copy x to tmp
    for (int a = 0; a < x->n; a++)
        tmp->k[a] = x->k[a];
    for (int a = 0; a <= x->n; a++)
        tmp->p[a] = x->p[a];
    tmp->n = x->n;
    // copyend

    insertKey(T, m, &tmp, &y, newKey); // tmp에 newkey 삽입

    int centerKey = tmp->k[tmp->n / 2]; // center key of tmpNode, 분할 기준인 중앙값

    int i = 0;
    initKP(&x);
    while (tmp->k[i] < centerKey) // centerkey보다 작은 key들 x에 업데이트
    {
        x->k[i] = tmp->k[i];
        x->p[i] = tmp->p[i];
        i++;
        x->n++;
    }
    x->p[i] = tmp->p[i];
    // centerkey보다 작은 경우 x에 update fin

    // centerkey보다 큰 경우들 새로운 노드로 복사
    Node *newNode = getNode(m); // centerKey 이후 값을 노드 newNode로 복사
    i++;                        // centerkey넘김
    while (i < tmp->n)
    {
        newNode->k[newNode->n] = tmp->k[i];
        newNode->p[newNode->n] = tmp->p[i];
        i++;
        newNode->n++;
    }
    newNode->p[newNode->n] = tmp->p[i];
    // centerkey보다 큰 경우들 fin
    delete tmp;
    BTpair pr = make_pair(centerKey, newNode);
    return pr;
}
/**
 * @brief btree 삽입, contain 'searchPath, insertKey, splitNode'
 * @param T: Tree
 * @param m: m way search
 * @param newKey: 삽입할 키값
 */
void insertBT(Node **T, int m, int newKey)
{
    Node *N = *T;
    found = false; // init
    //루트 노드 생성
    if (*T == NULL)
    {
        N = getNode(m);
        N->k[0] = newKey;
        N->n = 1;
        *T = N;
        return;
    }
    // newKey를 삽입할 노드의 경로를 탐색하며, 스택에 경로 저장
    PathStack ps;
    found = searchPath(T, m, newKey, ps);
    if (found)
        return; // newKey 발견함, 삽입불가

    bool finished = false;
    Node *x = ps.top().second;
    ps.pop();
    Node *y = NULL;
    do // 삽입은 단말노드에서 시작
    {
        if (x->n < m - 1) // overflow 발생 여부 검사
        {
            // overflow 발생 안함, newkey를 노드 x의 올바른 위치에 삽입
            insertKey(T, m, &x, &y, newKey);
            finished = true;
        }
        else // overflow 발생
        {
            // x를 newkey를 기준으로 분할, 분할된 노드 반환
            BTpair yp = splitNode(T, m, x, y, newKey);
            newKey = yp.first;
            y = yp.second;
            if (!ps.empty())
            {
                x = ps.top().second;
                ps.pop();
            }
            else //트리의 레벨이 하나 증가
            {
                *T = getNode(m);
                (*T)->k[0] = newKey;
                (*T)->n++;
                (*T)->p[0] = x;
                (*T)->p[1] = y;
                finished = true;
            }
        }
    } while (!finished);
}
/**
 * @brief x에서 oldkey 제거
 * @param T: Tree
 * @param m: m way search
 * @param x: **x, node
 * @param oldKey
 * @return x
 */
void deleteKey(Node **T, int m, Node **x, int oldKey)
{
    int i = 0;
    Node *d = *x;
    while (oldKey > d->k[i])
        i++;
    while (i < d->n)
    {
        d->k[i] = d->k[i + 1];
        d->p[i + 1] = d->p[i + 2];
        i++;
    }
    d->n--;
    x = &d;
}
/**
 * @brief x의 best 형제노드 index 반환
 * @param T: Tree
 * @param m: m way search
 * @param x: node
 * @param y: x의 부모노드
 * @return x의 best 형제노드의 idx, y->p[idx]가 best sibling
 */
int bestSibling(Node **T, int m, Node *x, Node *y)
{
    int i = 0;
    while (y->p[i] != x)
        i++;

    if (i == 0)
        return i + 1;
    else if (i == y->n)
        return i - 1;
    return i + 1;
}
/**
 * @brief x와 best sibling 노드간의 키 재분배
 * @param T: Tree
 * @param m: m way search
 * @param x: node
 * @param y: x의 부모노드
 * @param bestSib : y->p[bestSib]가 best sibling
 * @return 키 재분배
 */
void redistributeKeys(Node **T, int m, Node *x, Node *y, int bestSib)
{
    int i = 0;
    while (y->p[i] != x)
        i++;
    Node *bestNode = y->p[bestSib];
    if (bestSib < i)
    {
        int lastKey = bestNode->k[bestNode->n - 1];
        insertKey(T, m, &x, NULL, y->k[i - 1]);
        x->p[1] = x->p[0];
        x->p[0] = bestNode->p[bestNode->n];
        bestNode->p[bestNode->n] = NULL;
        deleteKey(T, m, &bestNode, lastKey);
        y->k[i - 1] = lastKey;
    }
    else
    {
        int firstKey = bestNode->k[0];
        insertKey(T, m, &x, NULL, y->k[i]);
        x->p[x->n] = bestNode->p[0];
        bestNode->p[0] = bestNode->p[1];
        deleteKey(T, m, &bestNode, firstKey);
        y->k[i] = firstKey;
    }
}
/**
 * mergeNode : x와 best sibling 노드간의 합병 수행
 * @param T: Tree
 * @param m: m way search
 * @param x: node
 * @param y: x의 부모노드
 * @param bestSib : y->p[bestSib]가 best sibling
 * @return x
 */
void mergeNode(Node **T, int m, Node *x, Node *y, int bestSib)
{
    int i = 0;
    while (y->p[i] != x)
        i++;

    Node *bestNode = y->p[bestSib];
    if (bestSib > i)
    {
        int tmp = i;
        i = bestSib;
        bestSib = tmp;

        Node *tmpNode = x;
        x = bestNode;
        bestNode = tmpNode;
    }
    bestNode->k[bestNode->n] = y->k[i - 1]; //형제노드와 부모키합병
    bestNode->n++;
    int j = 0;
    while (j < x->n)
    {
        bestNode->k[bestNode->n] = x->k[j];
        bestNode->p[bestNode->n] = x->p[j];
        bestNode->n++;
        j++;
    }
    bestNode->p[bestNode->n] = x->p[x->n];
    deleteKey(T, m, &y, y->k[i - 1]);
    delete x;
}
/**
 * @brief 내부노드인지 단말노드인지 리턴
 * @param x
 * @return true 단말노드
 * @return false 내부노드
 */
bool isLeaf(Node *x)
{
    for (int i = 0; i <= x->n; i++)
    {
        if (x->p[i] != NULL)
            return false;
    }
    return true;
}
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
/**
 * @brief 후행키 찾기
 * @param p : oldkey있는 노드와 그 p[idx]
 * @return BTpair, {후행키:후행키있는노드}
 */
BTpair successor(BTpair p) // 25
{
    //후행키 : 특정키의 오른쪽 자식노드를 root로 하는 서브트리의 가장 왼쪽값
    int s = 0;
    Node *rightSub = p.second->p[p.first + 1]; //ㅇㅇ, 오른쪽 자식노드
    //가장왼쪽, 작은값찾기, 후행키 찾기
    s = rightSub->k[0];
    while (rightSub->p[0] != NULL)
    {
        rightSub = rightSub->p[0];
        s = rightSub->k[0];
    }
    BTpair spair = make_pair(s, rightSub);
    return spair;
}
/**
 * @brief B-tree 삭제 알고리즘
 * @param T
 * @param m
 * @param oldKey
 */
void deleteBT(Node **T, int m, int oldKey)
{
    PathStack ps;
    found = true;                         // init
    found = searchPath(T, m, oldKey, ps); // oldekey가 있는 노드의 경로 탐색, 스택에 저장
    if (!found)
        return; // oldKey 발견못함, 삭제불가
    Node *x = ps.top().second;
    BTpair p = ps.top(); // oldkey있는 노드와 그 p[idx]
    ps.pop();
    if (!isLeaf(x)) // oldKey를 내부노드에서 발견
    {
        while (!ps.empty())
            ps.pop();
        //후행키(s)와 oldKey 바꾸기
        BTpair skey_sNode = successor(p);
        int skey = skey_sNode.first;
        Node *sNode = skey_sNode.second;
        bool found2 = searchPath(T, m, skey, ps); // 후행키 경로 저장
        swap(sNode->k[0], x->k[p.first]);         // 후행키와 oldkey 자리자꾸기
        x = sNode;
        ps.pop();
    }
    bool finished = false;
    deleteKey(T, m, &x, oldKey); //노드 x에서 oldkey 삭제
    Node *y = NULL;

    if (!ps.empty())
    {
        y = ps.top().second; // y는 x의 부모노드
        ps.pop();
    }
    do
    {
        if (*T == x || x->n >= (m - 1) / 2)
            finished = true;
        else // underflow 발생
        {
            int bestSib = bestSibling(T, m, x, y);

            if (y->p[bestSib]->n > (m - 1) / 2) //형제노드에서 키 재분배 가능
            {
                redistributeKeys(T, m, x, y, bestSib);
                finished = true;
            }
            else // 키 재분배 불가능, 노드 합병
            {
                mergeNode(T, m, x, y, bestSib);
                x = y;
                if (!ps.empty())
                {
                    y = ps.top().second;
                    ps.pop();
                }
                else
                    finished = true;
            }
        }
    } while (!finished);

    if (y != NULL && y->n == 0)
    {
        *T = y->p[0];
        delete y;
    }
}

int main()
{
    string line;
    for (int m = 3; m <= 4; m++)
    {
        ifstream file("BT-input.txt"); // .txt 파일을 연다. 없으면 생성.
        Node *n = NULL;
        if (file.is_open()) // 정상적으로 열리나 확인
        {
            while (getline(file, line)) // 텍스트 파일 한 줄씩 읽기, string 형태로 저장
            {
                string line_;
                if (line[0] == 'i')
                {
                    line_ = line.substr(2); // string key value
                    if (stoi(line_) == 25)
                        bool dfdf;
                    insertBT(&n, m, stoi(line_));
                    if (found)
                        cout << line << " : The key already exists\n";
                    inorderBT(n);
                    printf("\n");
                }
                else // delete
                {
                    line_ = line.substr(2);
                    deleteBT(&n, m, stoi(line_));
                    if (!found) //삭제할 키가 존재하는지 확인
                        cout << line << " : The key does not exist\n";
                    inorderBT(n);
                    printf("\n");
                }
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file";
        }
    }
    return 0;
}
