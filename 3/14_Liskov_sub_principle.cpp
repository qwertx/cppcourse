// 里氏代换原则
// 子类的对象能够替换其基类的对象被使用
// 比如任何用Animal的地方, 都可以用Cat替换, 所有关于Animal的假设, Cat都不能打破

// 比如鱼属于动物, 但鱼不会走路, 因此不应该在动物类里存在关于走路的函数

// 又比如对于长方形类,可以调用长方形类的函数修改长宽, 那么正方形就不应该继承自长方形
// 因为长宽可能不同, 而也不能给正方形再添加一个函数
// 因为只要正方形继承自长方形, 那么正方形应该可以使用长方形的所有函数

// 那么矛盾在哪里?
// 在数学上, 通常认为这些东西创建出来就不可变了
// 因此, 只读的正方形可以继承自只读的长方形
class IReadableRectangle  // 无法实例化
{
public:
    virtual ~IReadableRectangle() = default;

    virtual int GetWidth() = 0;
    virtual int GetHeight() = 0;

    int GetArea()
    {
        return GetWidth() * GetHeight();
    }
};

class IReadableSquare : public IReadableRectangle
{
public:
};

// 对于可修改的长/正方形, 应该继承自只读的长/正方形
// 既符合集合语言, 也符合里氏代换原则
class Rectangle : public IReadableRectangle
{
private:
    int width = 0;
    int height = 0;

public:
    int GetWidth()override { return width; }
    int GetHeight()override { return height; }
    int SetWidth(int newWidth) { width = newWidth; }
    int SetHeight(int newHeight) { height = newHeight; }
};

class Square : public IReadableSquare
{
private:
    int size = 0;

public:
    int GetWidth()override { return size; }
    int GetHeight()override { return size; }
    int SetSize(int newSize) { size = newSize; }
};