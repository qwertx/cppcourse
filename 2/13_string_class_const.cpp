#include <iostream>
#include <cstdlib>
#include <cstring>
#ifndef _MSC_VER
#define strcpy_s(DST,SIZE,SRC) strcpy((DST),(SRC))
#endif
using namespace std;


// 加入const常量成员函数, 使this可以指向常量对象
struct String
{
private:
    size_t length;
    char* buffer;

    int Compare(const String& theString) const
    {
        return strcmp(buffer, theString.buffer);
    }
public:
    String()
        :length{ 0 }
        , buffer{ new char[1]{'\0'} }
    {
    }

    String(const char* theBuffer)
        :length{ strlen(theBuffer) }
        , buffer{ new char[length + 1] }
    {
        strcpy_s(buffer, length + 1, theBuffer);
    }

    String(const String& theString)
        :length{ theString.length }
        , buffer{ new char[theString.length + 1] }
    {
        strcpy_s(buffer, length + 1, theString.buffer);
    }

    String(String&& theString)
        :length{ theString.length }
        , buffer{ theString.buffer }
    {
        // 为了能使theString安全析构, 必须释放指针
        theString.buffer = nullptr;
    }

    ~String()
    {
        delete[] buffer;
    }

    String& operator=(const String& theString)
    {
        if (this != &theString)
        {
            delete[] buffer;
            length = theString.length;
            buffer = new char[length + 1];
            strcpy_s(buffer, length + 1, theString.buffer);
        }
        return *this;
    }

    String& operator=(String&& theString)
    {
        if (this != &theString)
        {
            delete[] buffer;
            length = theString.length;
            buffer = theString.buffer;
            theString.buffer = nullptr;
        }
        return *this;
    }

    bool operator == (const String& theString) const { return Compare(theString) == 0; }
    bool operator != (const String& theString) const { return Compare(theString) != 0; }
    bool operator <  (const String& theString) const { return Compare(theString) <  0; }
    bool operator <= (const String& theString) const { return Compare(theString) <= 0; }
    bool operator >  (const String& theString) const { return Compare(theString) >  0; }
    bool operator >= (const String& theString) const { return Compare(theString) >= 0; }

    const char* GetBuffer() const
    {
        return buffer;
    }

    size_t GetLength() const
    {
        return length;
    }
};
int main(){
    return 0;
}