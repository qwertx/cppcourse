
// 最基础的
struct point1 {
    int x;
    int y;
};
point1 p1{1, 2};

// 增加构造函数, 无默认构造函数
struct point2 {
    int x;
    int y;
    point2(int v):x{v}, y{v} { } // 尽量不要在构造函数函数体操作成员变量, 要使用初始化列表
    point2(): x{0}, y{0} { } // 默认构造函数
    point2(int theX, int theY): x{theX}, y{theY} {}
};
point2 p2{1};

// POD(plain old data)类型: 基本类型, 枚举, 成员都是POD的结构体, 也就是类似C的类型
// 对于POD类型, 如果初始化括号中不写任何东西, 会把每个bit初始为0, 也就是可以省略0
struct point3 {
    int x;
    int y;
    point3(): x{}, y{} {} // 默认初始化为0
    point3(int theX, int theY): x{theX}, y{theY} {}
    point3(int v):x{v}, y{v} { } 
};


// universal construction用于成员变量, 且对所有构造函数生效
struct point4 {
    int x{};
    int y{};
    point4() = default; // 编译器生成默认构造函数
    point4(int theX, int theY): x{theX}, y{theY} {}
    point4(int v):x{v}, y{v} { } 
};

// 只有在不包含任何构造函数时,编译器才会生成默认构造函数
// 除非使用=default
// 如果类的某个成员不包含默认构造函数, 编译器也无法生成默认构造函数
// 强行使用=default等同于=delete,即没有默认构造函数

// 若某个类没有写拷贝构造函数, 那么会始终生成(除非某个成员没有)
// 若写出了一个, 不会生成其他的
struct point5 {
    int x{};
    int y{};
    point5(const point5& p) = default;
    point5(point5&& p) = default; // 移动构造函数
};

// 左值: 身份, 持久
// 右值: 值, 一般是字面常量或者求值过程中的临时变量
// 右值引用: 只能绑定到临时对象, 但右值引用对象自身是左值