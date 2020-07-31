struct X {
    X() = delete;
    X(const X&) = delete;
    X(int) {}
};

// 1. 编译通过
struct Y {
    X x;
    Y() = delete;
    Y(const Y&) = delete;
};

int main() {
    return 0;
}

// 2. 错误, 因为X的默认构造和拷贝构造函数为delete, 所以Y的默认构造函数和拷贝构造函数也为delete
// struct Y {
//     X x;
// };

// int main() {
//     Y y1;
//     Y y2 = y1;
//     return 0;
// }

// 3. 错误, 因为X的默认构造为delete, 指定了default也没有用
// struct Y {
//     X x;
//     Y() = default;
//     Y(const Y&) = delete;
// };

// int main() {
//     Y y1;
//     return 0;
// }

// 4. 错误, 即使指定default, Y的拷贝构造函数也为delete
// struct Y {
//     X x;
//     Y() = delete;
//     Y(const Y&) = default;
//     Y(int): x{0}{}
// };

// int main() {
//     Y y1{0};
//     Y y2 = y1;
//     return 0;
// }