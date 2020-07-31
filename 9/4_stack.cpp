#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;


// 简单的SLR语法分析器, 未考虑特殊情况

// 一个可以容纳操作符和运算数的类, 其中右操作数和操作符同时储存在一个item中
struct Item
{
    char op = '\0';
    int number = 0;

    Item() {}
    Item(char theOp) :op{ theOp } {}
};

// 对栈顶两个操作数(弹出右操作数)进行运算, 结果写回栈顶
void Run(stack<Item>& items)
{
    auto second = items.top(); // 包括右操作数和操作符
    items.pop();
    auto& first = items.top().number; // 左操作数
    switch (second.op)
    {
    case '+':
        first += second.number;
        break;
    case '-':
        first -= second.number;
        break;
    case '*':
        first *= second.number;
        break;
    case '/':
        first /= second.number;
        break;
    }
}

// 如果栈顶是右操作数, 那么进行运算直到遇到op为空的item, 最终弹出结果
int Pop(stack<Item>& items)
{
    while (items.top().op != '\0')
    {
        Run(items);
    }
    auto number = items.top().number;
    items.pop();
    return number;
}

// 为item栈顶元素指定右操作数, 如果栈顶是右操作数而且操作符是乘除法, 那么进行运算(因为乘除法优先级高,可以立即计算)
void Push(stack<Item>& items, int number)
{
    items.top().number = number;
    switch (items.top().op)
    {
    case '*':case '/':
        Run(items);
    }
}

int Calculate(string text)
{
    stringstream ss(text);
    stack<Item> items;
    items.push({});

    while (true)
    {
        // get读取字符, peek不读取(不从流中移除)
        char op = ss.peek(); // 看一眼下一个字符
        switch (op)
        {
        case '(':
            items.push({}); // 左括号入栈一个空item
            break;
        case ')':
            Push(items, Pop(items)); // 右括号的话, 不断运算直到遇到左括号, 然后把结果压入栈顶
            break;
        case '+':case '-':case '*':case '/': // 操作符压入栈顶
            items.push({op});
            break;
        }

        if (isdigit(op))
        {
            int number;
            ss >> number; // 获取数字
            Push(items, number); // 将数字压入栈顶
        }
        else if (ss.eof())
        {
            return Pop(items); // 进行最后的运算并返回结果
        }
        else
        {
            // 不是数字或eof的话在这边就忽略了(因为其他字符已经在switch中保存), 可以加入最大忽略数和停止字符作为参数
            ss.ignore(); 
        }
    }
}

int main()
{
    cout << Calculate("1") << endl;
    cout << Calculate("1+2") << endl;
    cout << Calculate("1+2*3+4") << endl;
    cout << Calculate("(11+22)*(33+44)") << endl;
    return 0;
}