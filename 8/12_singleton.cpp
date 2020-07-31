// 单例模式, 一个类只能有一个或几个实例, 比如桌面的鼠标指针只能有一个
// singleton pattern

// 特征: 构造/析构函数均为private, 拷贝构造/operator=为delete
// 通过定义一个指向实例的静态成员指针变量实现最多一个实例
// 只能通过public中的getInstance函数获取实例指针, 若指针非nullptr,就new一个实例, 否则返回现有实例
// getInstance函数也必须是静态成员, 否则在第一次get前就需要一个实例, 产生矛盾

#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

class Screen {
private:
  	unsigned int _width;
  	unsigned int _height;

  	Screen(unsigned int width, unsigned int height) {
    		_width = width;
    		_height = height;
  	};
  	Screen() {

  	}
  	~Screen() {
  		delete instance;
  	}
public:
    // 声明静态成员变量, 但不宜在类内初始化, 除非是常量表达式
    static Screen* instance;
    // 但静态成员函数可以定义在函数内, 不能用this/const
  	static Screen* getInstance(unsigned width = 1920, unsigned height = 1080) {
        if(!instance) {
            instance = new Screen{ // 记得用new!
                (width > 0 && width <= 1920) ? width : 1920, 
                (height > 0 && height <= 1080) ? height : 1080
            };         
        }
        return instance;
    }
    unsigned getWidth() {
        return instance->_width;
    }
    unsigned getHeight() {
        return instance->_height;
    }

    Screen(const Screen&)=delete;
    Screen & operator= (const Screen&)=delete;
};

Screen* Screen::instance = nullptr;

int main() {
  	int width, height;
  	Screen* screen = 0; // 空指针, 等价NULL/nullptr
  	cin >> width >> height;
  	screen = Screen::getInstance(width, height);
  	screen = Screen::getInstance();
  	cout << screen->getWidth() << " " <<
  		screen->getHeight() << endl;

  	return 0;
}

// 不完全类型: 声明后, 定义前