#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void c_array() 
{
  int a[10];
  int b[10] = { 0 };
  int c[] = { 1, 2, 3, 4, 5 };
  int x = c[2];
  c[3] = x;
}

void use_vector() 
{ 
	vector<int> a(10);
    vector<int> b(10, 0);
    vector<int> c = { 1, 2, 3, 4, 5 };
    int x = c[2];
    c[3] = x;
}

void c_array_sum() {
    int a[] = { 1, 2, 3, 4, 5 };
    int sum = 0;
	for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
		sum += a[i];
	}
	cout << *a << ' ' << sum << endl;
}

void vector_sum() {
	vector<int> a = { 1, 2, 3, 4, 5 };
	int sum = 0;
	for (auto x : a) {
		sum += x;
	}
	cout << sum << endl;
}

void find_last_of_a_in_b() {
	int a[] = { 1, 2, 3, 4, 5 };
	int b[] = { 3, 4, 5, 6, 7 };
	int* it = nullptr;
	for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
		for (int j = 0; j < sizeof(b) / sizeof(*b); j++) {
			if (a[i] == b[j]) {
				it = &a[i];
				break;
			}
		}
	}
	bool found = (it != nullptr);
	cout << *it << ' ' << boolalpha << found << endl;
}

void find_first_of_a_in_b() {
	vector<int> a = { 1, 2, 3, 4, 5 };
	vector<int> b = { 3, 4, 5, 6, 7 };
	auto it = find_first_of(begin(a), end(a), begin(b), end(b));
	bool found = (it != end(a));
	cout << *it << ' ' << boolalpha << found << endl;
}

int compare(const void* x, const void* y) {
	// reinterpret_cast:在位模式上的重新解释
	// 此处虽然是底层const，但没有改变x和y的const性质，其实此处用static_cast即可
	// return *reinterpret_cast<const int*>(y) - *reinterpret_cast<const int*>(x);
	return *static_cast<const int*>(y) - *static_cast<const int*>(x);
}

void array_reverse_sort() {
	// last param in qsort() is a func ptr
	// int (*compar)(const void*, const void*));
	// compare: <0, p1---p2; >0, p2---p1
	int a[] = { 1, 2, 3, 4, 5 };
	qsort(a, sizeof(a) / sizeof(*a), sizeof(*a), &compare);
	for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
}

void vector_reverse_sort() {
	vector<int> a = { 2, 4, 5, 3, 1 };
	//和qsort不同，sort用true, false比较元素位置，性能好于qsort
	sort(begin(a), end(a), [](int x, int y){ return x >= y; });
	for (auto x : a) {
		cout << x << ' ';
	}
	cout << endl;
}

int main() {
	vector_reverse_sort();
	return 0;
}


