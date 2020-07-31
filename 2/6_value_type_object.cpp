// 值类型对象: 可以构造, 复制, 传递, 无需担心new和delete
// 要求: 
// 1. 构造和析构可见
// 2. 可以用operator=和复制构造函数实现复制, 还需要移动构造函数
// 复制构造函数的引用指向自己怎么办?

// 全是问题的代码示例
struct String {
    private:
        char* buffer = nullptr;
    public:
        // 未实现operator=, 这样执行c=b时,b,c指向同一个地址, 析构delete两次会异常

        // new char必须指定长度
        String():buffer{new char[]{'\0'}} {
        }
        // 错误, const char*不能复制给char*
        // 而且应该复制内容而不是指针
        String(const char* theBuffer): buffer{theBuffer} {
        }
        // 应该复制字符串内容而不是复制指针
        String(const String& theString): buffer{theString.buffer} {
        }
        ~String() {
            // 正确, 无需检查是否为nullptr
            delete[] buffer;
        }
};

int main() {
    String a = "This is a string!";
    String b = a;
    String c;
    c = b;
    return 0;
}