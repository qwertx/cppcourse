struct Link
{
    int data;
    Link* next;
};

// 只有new出来才能用delete, 不能用FreeLink
// 访问被释放的对象是未定义行为, 不要这样做
void FreeLink(Link* head)
{
    while(head)
    {
        delete head;
        head = head -> next;
    }
}

int main()
{
    Link c{3, nullptr};
    Link b{2, &c};
    Link a{1, &b};
    FreeLink(&a);
    return 0;
}