#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Tree
{
    int data;
    weak_ptr<Tree> parent;
    shared_ptr<Tree> left;
    shared_ptr<Tree> right;

    Tree(int theData, shared_ptr<Tree> theLeft = nullptr, shared_ptr<Tree> theRight = nullptr)
        :data{ theData }
        , left{ theLeft }
        , right{ theRight }
    {
    }
};

shared_ptr<Tree> MakeTree()
{
    return make_shared<Tree>(1, 
        make_shared<Tree>(2, make_shared<Tree>(4), nullptr),
        make_shared<Tree>(3, make_shared<Tree>(5), make_shared<Tree>(6)));
}

void SetupTree(shared_ptr<Tree> tree)
{
    if(tree->left) {
        tree->left->parent = tree;
        SetupTree(tree->left);
    }
    if(tree->right) {
        tree->right->parent = tree;
        SetupTree(tree->right);
    }
}

void PrintTree(shared_ptr<Tree> tree)
{
    shared_ptr<Tree> last;
    shared_ptr<Tree> current = tree;

    while (current)
    {
        if (last == current->parent.lock())
        {
            goto TryLeft;
        }
        if (current->left && current->left == last)
        {
            goto TryCurrent;
        }
        else if (current->right && current->right == last)
        {
            goto TryParent;
        }

    TryLeft:
        if (current->left)
        {
            last = current;
            current = current->left;
            continue;
        }
    TryCurrent:
        cout << current->data << " ";
        goto TryRight;
    TryRight:
        if (current->right)
        {
            last = current;
            current = current->right;
            continue;
        }
    TryParent:
        last = current;
        current = current->parent.lock();
    }
    cout << endl;
}

int main()
{
    auto tree = MakeTree();
    SetupTree(tree);
    PrintTree(tree);
    return 0;
}