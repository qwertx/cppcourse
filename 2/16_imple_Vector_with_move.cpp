#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

// placement new
// 在分配好的内存上进行构造
// new (位置指针) Object(构造参数);

class Element {
private:
    int number;

public:
	Element() :number(0) {
	    cout << "ctor" << endl;
	}
  	Element(int num):number(num) {
  		cout << "ctor" << endl;
  	}
  	Element(const Element& e):number(e.number) {
  		cout << "copy ctor" << endl;
  	}
  	Element(Element&& e):number(e.number) {
  		cout << "right value ctor" << endl;
  	}
  	~Element() {
  		cout << "dtor" << endl;
  	}
  	void operator=(const Element& item) {
  		number = item.number;
  	}
  	bool operator==(const Element& item) {
  		return (number == item.number);
  	}
  	void operator()() {
  		cout << number ;
  	}
  	int GetNumber() {
  		return number;
  	}
};

// 一个效率很低的Vector, 每次增减元素都要重新分配空间
// 因为缺少保存当前分配的内存空间大小的变量
template<typename T>
class Vector {
private:
  	T* items;
  	int count;

public:
  	Vector() :count{ 0 }, items{nullptr} {

  	}
  	Vector(const Vector& vector) :count{vector.count} {
  		items = static_cast<T*>(malloc(sizeof(T) * count));
		// void *memcpy(void *str1, const void *str2, size_t n) 
		// 从str2复制n个字节到str1
  		memcpy(items, vector.items, sizeof(T) * count);
  	}
  	Vector(Vector&& vector) :count{ vector.count }, items{ vector.items } {
  		vector.items = nullptr;
  	}
  	~Vector() {
		for(int i = 0; i < count; i++) {
			items[i].~T();
		}
  		free(items);
		items = nullptr;
  	}
    T& operator[](int index){
    	if (index<0||index>=count) {
    		cout<<"invalid index"<<endl;
    		return items[0];
    	}
    	return items[index];
    }
    int returnCount(){
    	return count;
    }
  	void Clear() {
  		for(int i = 0; i < count; i++) {
			items[i].~T();
		}
  		free(items);
		items = nullptr;
		count = 0;		
  	}
  	void Add(const T& item) {
		// 要考虑当前items是否为空
		if(items) {
			T* new_items = static_cast<T*>(malloc(sizeof(T) * (count+1)));	
			for(int i = 0; i < count; i++) {
				// placement new
				// 此处旧的items无需再使用, 因此用move转为右值
				new (&new_items[i]) T(move(items[i]));
			}
			// 加入新元素
			new (&new_items[count]) T(move(item));
			// 释放旧空间
			for(int i = 0; i < count; i++) {
				items[i].~T();
			}
			free(items);
			// items指向新分配的空间
			items = new_items;
			count += 1;
		}
		else {
			items = static_cast<T*>(malloc(sizeof(T)));
			new (items) T(move(item));
			count = 1;
		}
  	}
  	bool Insert(const T& item,int index) {
		// 检查索引
		if(index < 0 || index > count)
			return false;
		
		// 分配空间, 转移index前的元素
  		T* new_items = static_cast<T*>(malloc(sizeof(T) * (count+1)));	
		for(int i = 0; i < index; i++) {
			new (&new_items[i]) T(move(items[i]));
		}
		// 插入元素
		new (&new_items[index]) T(move(item));
		// 转移index后面的元素
		for(int i = index + 1; i < count + 1; i++) {
			new (&new_items[i]) T(move(items[i-1]));
		}
		// 释放旧空间
		for(int i = 0; i < count; i++) {
			items[i].~T();
		}
  		free(items);
		// items指向新分配的空间
		items = new_items;
		count += 1;
		return true;
  	}
	// 和insert一样的思路
	bool Remove(int index) {
  		// 检查索引
		if(index < 0 || index >= count)
			return false;
		
		// 分配空间, 转移index前的元素
  		T* new_items = static_cast<T*>(malloc(sizeof(T) * (count-1)));	
		for(int i = 0; i < index; i++) {
			new (&new_items[i]) T(move(items[i]));
		}
		// 转移index后面的元素
		for(int i = index + 1; i < count; i++) {
			new (&new_items[i-1]) T(move(items[i]));
		}
		// 释放旧空间
		for(int i = 0; i < count; i++) {
			items[i].~T();
		}
  		free(items);
		// items指向新分配的空间
		items = new_items;
		count -= 1;
		return true;
  	}
	// 更简洁的写法, 无需重新分配空间
  	bool Remove2(int index) {
  		// 检查索引
		if(index < 0 || index >= count)
			return false;
		
		// 由于free传入非malloc指针是未定义行为, 也不能传入地址常量
		// 因此无法只free一部分分配的内存
		// 不能这样用 free(&ip[4]); 
		// 此处无需free

		// 删除元素
		items[index].~T();
		// 转移index后面的元素
		for(int i = index + 1; i < count; i++) {
			items[i-1] = T(move(items[i]));
		}
		// 析构最后一个元素
		items[count-1].~T();

		count -= 1;
		return true;
  	}
  	int Contains(const T& item) {
  		for(int i = 0; i < count; i++) {
			if(items[i] == item)
				return i;
		}
		return -1;
  	}
};

template<typename T>
void PrintVector(Vector<T>& v){
	  int count=v.returnCount();
	  for (int i = 0; i < count; i++)
	  {
		  v[i](); // 注意Element重载()为打印
		  cout << " ";
	  }
	  cout << endl;
}

int main() {
  	Vector<Element>v;
  	for (int i = 0; i < 4; i++) {
  		Element e(i);
  		v.Add(e);
  	}
  	PrintVector(v);
  	Element e2(4);
  	if (!v.Insert(e2, 10))
  	{
  		v.Insert(e2, 2);
  	}
  	PrintVector(v);
  	if (!v.Remove(10))
  	{
  		v.Remove(2);
  	}
  	PrintVector(v);
  	Element e3(1), e4(10);
  	cout << v.Contains(e3) << endl;
  	cout << v.Contains(e4) << endl;
  	Vector<Element>v2(v);
  	Vector<Element>v3(move(v2)); // 此处的右值引用把v2的items指针置空了
  	PrintVector(v3);
  	v2.Add(e3);
  	PrintVector(v2);
  	return 0;
}
