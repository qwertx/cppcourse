// stack:
// top(返回栈顶)/push/pop/empty/size

// queue:
// front/back/push/pop/empty/size

// list链表:
// push_front/push_back,头尾插
// pop_front/pop_back,头尾弹出
// size/clear/insert/erase
// 支持各种版本的begin/end

// emplace系列函数类似insert，但接受的不是值而是元素的构造函数参数
// c.insert(p, t) / c.emplace(p, args)
// 但如果有右值引用的拷贝构造函数的话，emplace并没有多大用处