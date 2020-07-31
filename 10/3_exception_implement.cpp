#include <string>
#include <iostream>

using namespace std;

struct InvalidFormatException
{
    string s;
};

struct DividedByZeroException
{
};

double ReadInt(string s)
{
    auto begin = s.c_str();
    char* end = nullptr;
    // double strtod(const char* str, char** str_end)
    // char*转double, *str_end为非法字符开始的位置
    double result = strtod(begin, &end);
    if (*end != '\0')
    {
        throw InvalidFormatException{s};
    }
    return result;
}

int main()
{
    string s;
    try
    {
        cout << "输入被除数：";
        getline(cin, s);
        auto i = ReadInt(s);

        cout << "输入除数：";
        getline(cin, s);
        auto j = ReadInt(s);

        if (j == 0.0) {
            throw DividedByZeroException{};
        }

        cout << "它们的商是" << i / j << "。" << endl;
    }
    catch (DividedByZeroException)
    {
        cout << "除数不能是0。" << endl;
    }
    catch (const InvalidFormatException& e)
    {
        cout << "格式错误，" << e.s << "不是一个数字。" << endl;
    }
    return 0;
}

// 不要滥用异常, 因为程序处理不了突发状况，也不能恢复的话，理应崩溃
// 有时候如果强行运行下去，有可能会对用户的数据造成不可预知的损害
// 仅仅不能完成任务，要比伤害用户强得多