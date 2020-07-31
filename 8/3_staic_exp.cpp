#include <iostream>
#include <string>
#include <memory>

using namespace std;

// 上次使用friend解决问题, 此次使用static
struct Node
{
private:
    Node() = default;
    ~Node() = default;
public:
    void Introduce()
    {
        cout << "我是Node。" << endl;
    }

    static Node* CreateNode()
    {
        return new Node;
    }

    static void DestroyNode(Node* node)
    {
        delete node;
    }
};



int main()
{
    auto node = Node::CreateNode();
    node->Introduce();
    Node::DestroyNode(node);
    return 0;
}