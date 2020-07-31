#include <stddef.h>
#include <iostream>

using namespace std;


class Node {
public:
    int data;
    Node* lchild, * rchild;
    Node(int _data)
    {
        data = _data;
        lchild = NULL;
        rchild = NULL;
    }
    ~Node()
    {
        if (lchild != NULL)
        {
            delete lchild;
        }
        if (rchild != NULL)
        {
            delete rchild;
        }
    }
    void InOrder();
};

void Node::InOrder() {
    if (lchild != NULL) { // 递归访问左节点
        lchild->InOrder();
    }
    cout << data << " "; // 访问当前节点
    if (rchild != NULL) { // 递归访问右节点
        rchild->InOrder();
    }
}