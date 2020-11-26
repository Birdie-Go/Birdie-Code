#include <bits/stdc++.h>
using namespace std;

typedef struct AvlNode {
    int data;
    AvlNode *m_pLeft;
    AvlNode *m_pRight;
    int height;
}*AvlTree,*Position,AvlNode;

int Height(AvlTree T) {
    if (T==NULL) return -1;
        else return T->height;
}

AvlTree singleRotateWithRight(AvlTree T) {
    AvlTree L=T->m_pLeft;
    T->m_pLeft=L->m_pRight;
    L->m_pRight=T;
    T->height=max(Height(T->m_pLeft),Height(T->m_pRight))+1;
    L->height=max(Height(L->m_pLeft),Height(L->m_pRight))+1;
    return L;
}

AvlTree singleRotateWithLeft(AvlTree T) {
    AvlTree R=T->m_pRight;
    T->m_pRight=R->m_pLeft;
    R->m_pLeft=T;
    T->height=max(Height(T->m_pLeft),Height(T->m_pRight))+1;
    R->height=max(Height(R->m_pLeft),Height(R->m_pRight))+1;
    return R;
}

AvlTree doubleRotateWithLeft(AvlTree T) {
    T->m_pLeft=singleRotateWithLeft(T->m_pLeft);
    return singleRotateWithRight(T);
}

AvlTree doubleRotateWithRight(AvlTree T) {
    T->m_pRight=singleRotateWithRight(T->m_pRight);
    return singleRotateWithLeft(T);
}

AvlTree AvlTreeInsert(AvlTree T,int x) {
    if (T==NULL) {
        T=(AvlNode*)malloc(sizeof(struct AvlNode));
        T->data=x;
        T->m_pLeft=NULL;
        T->m_pRight=NULL;
        T->height=0;
    }
    else if (x<T->data) {
        T->m_pLeft=AvlTreeInsert(T->m_pLeft,x);
        if (Height(T->m_pLeft)-Height(T->m_pRight)==2) {
            if (x<T->m_pLeft->data) T=singleRotateWithRight(T);
                else T=doubleRotateWithLeft(T);
        }
    }
    else if (x>T->data) {
        T->m_pRight=AvlTreeInsert(T->m_pRight,x);
        if (Height(T->m_pRight)-Height(T->m_pLeft)==2) {
            if (x>T->m_pRight->data) T=singleRotateWithLeft(T);
                else T=doubleRotateWithRight(T);
        }
    }

    T->height=max(Height(T->m_pLeft),Height(T->m_pRight))+1;
    return T;
}

void AvlBfs(AvlTree T) {
    queue <AvlTree> que;
    que.push(T);
    while (!que.empty()) {
        AvlTree now=que.front();
        que.pop();
        if (now==NULL) continue;
        printf("%d ",now->data);
        que.push(now->m_pLeft);
        que.push(now->m_pRight);
    }
}

int main()
{
    int n;scanf("%d",&n);
    AvlTree root=NULL;
    for (int i=1;i<=n;i++) {
        int x;scanf("%d",&x);
        root=AvlTreeInsert(root,x);
    }
    AvlBfs(root);
    return 0;
}