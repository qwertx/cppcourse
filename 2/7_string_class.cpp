#include <iostream>
#include <cstdlib>
#include <cstring>
// 条件编译, g++没有实现strcpy_s
#ifndef _MSC_VER
#define strcpy_s(DST,SIZE,SRC) strcpy((DST),(SRC))
#endif
using namespace std;

struct String
{
private:
    size_t length;
    char* buffer;

public:
    String():length{0}, buffer{new char[1]{'\0'}}
    // 此处如果先写buffer的话, 仍然先初始化length
    {
    }

    String(const char* theBuffer)
    : length{strlen(theBuffer)}, buffer{new char[length+1]}
    {   
        // strcpy, 不可指定长度
        // strncpy, 可以指定长度, 不自动加\0
        // strcpy_s, 安全版本, size在中间而非末尾(ms)
        strcpy_s(buffer, length+1, theBuffer);
    }

    String(const String& theString)
    : length{theString.length}, buffer{new char[theString.length+1]}
    {
        strcpy_s(buffer, length+1, theString.buffer);
    }

    ~String()
    {
        delete[] buffer;
    }

    String& operator=(const String& theString) //没有初始化列表
    {
        if (this != &theString) // 如果不加上, 就会导致s=s时删掉buffer
        {
            delete[] buffer; // this此处可省略, 包括下面的length
            length = theString.length; 
            buffer = new char[length+1];
            strcpy_s(buffer, length+1, theString.buffer);
        }
        return *this;
    }

    const char* GetBuffer()const
    {
        return buffer;
    }

    size_t GetLength()const
    {
        return length;
    }
};

// TDD 测试驱动开发, 下为assert宏, 最简单的是抛出异常
// g++ -g 7_string_class.cpp
// gdb a.out
// run
// bt得到出错的行数
#define JSK_ASSERT(EXPRESSION) if(!(EXPRESSION)) throw 0;

int main()
{
    {
        String s;
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer()[0] == '\0');
        JSK_ASSERT(s.GetLength() == 0);
    }
    {
        String s = "This is a string!";
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(strcmp(s.GetBuffer(), "This is a string!") == 0);
        JSK_ASSERT(s.GetBuffer()[17] == '\0');
        JSK_ASSERT(s.GetLength() == 17);
    }
    {
        String s = "This is a string!";
        String t = s; // 声明时赋值调用拷贝构造函数, 传递参数或返回值也调用拷贝构造函数
        JSK_ASSERT(t.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer() != t.GetBuffer());
        JSK_ASSERT(s.GetLength() == t.GetLength());
        JSK_ASSERT(strcmp(s.GetBuffer(), t.GetBuffer()) == 0);
    }
    {
        String s = "This is a string!";
        s = s;
        JSK_ASSERT(s.GetBuffer() != nullptr);
        JSK_ASSERT(strcmp(s.GetBuffer(), "This is a string!") == 0);
        JSK_ASSERT(s.GetBuffer()[17] == '\0');
        JSK_ASSERT(s.GetLength() == 17);
    }
    {
        String s = "This is a string!";
        String t;
        t = s; // 对象已存在时调用operator=
        JSK_ASSERT(t.GetBuffer() != nullptr);
        JSK_ASSERT(s.GetBuffer() != t.GetBuffer());
        JSK_ASSERT(s.GetLength() == t.GetLength());
        JSK_ASSERT(strcmp(s.GetBuffer(), t.GetBuffer()) == 0);
    }
    return 0;
}