#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <stdlib.h>

using namespace std;

void char_str_copy() {
	char s[] = "abcdefg";
	char b[4];
	// params: dest, source, count
	strncpy(b, s + 2, 3);
	b[3] = '\0';
	cout << b << endl;
}

void string_str_copy() {
	string s = "abcdefg";
	string d(begin(s) + 2, begin(s) + 5);
	cout << d << endl;
}

void char_str_sub() {
	// 1. 变长
	char a[10] = "abcdefg";
	// 0 1 2 3 4 5 6 7 8 9
	// a b c d e f g \0
	
	// memmove:在src和dst间有重叠的时候保证拷贝正确，通过先拷贝到中转空间实现
	// params: dest, source, size_t
	// strlen不包括\0长度，因此为了拷贝\0所以加1
	// 将abcdefg\0替换为abcdeffg\0
	memmove(a + 6, a + 5, strlen(a + 5) + 1);
	// a最终变为abXYZWfg\0
	strncpy(a + 2, "XYZW", 4);

	// 2. 变短
	char b[10] = "abcdefg";
	// abUVefg\0
	strncpy(b + 2, "UV", 2);
	// abUVfg\0
	memmove(b + 4, b + 5, strlen(b + 5) + 1);

	cout << a << endl;
	cout << b << endl;

}

void string_str_sub() {
	string a = "abcdefg";
	// 替换cde
	a.replace(begin(a) + 2, begin(a) + 5, "XYZW");
	string b = "abcdefg";
	b.replace(begin(b) + 2, begin(b) + 5, "UV");

	cout << a << endl;
	cout << b << endl;
}

void char_str_find_sub() {
	char s[] = "abcdefg";
	// 返回子串第一次出现的位置指针
	char* x = strstr(s, "cde"); // x == s + 2
	char* y = strstr(s, "CDE"); // y == nullptr
	cout << x << endl;
	cout << (y == nullptr) << endl;
}

void string_str_find_sub() {
	string s = "abcdefg";
	auto x = s.find("cde"); // x == 2
	auto y = s.find("CDE"); // y == string::npos, string::npos是string类的static成员

	cout << x << endl;
	cout << (y == string::npos) << endl;
}

void char_str_replace_all_sub(char* str, char* toFind, char* toReplace) {
	int s = strlen(str);
	int f = strlen(toFind);
	int r = strlen(toReplace);
	int counter = 0;

	while (char* found = strstr(str, toFind)) { // strstr: toFind为空时,总是返回str首地址, 若str为空toFind不为空, 返回NULL 
		counter++;
		if (f < r) {  // 变长
			//为了给替换字符串腾出空间需要将原字符串后半段后移, s+1是因为要包括\0, found + f - str是使用指针相减得到长度.
			int size = (s + 1) - (found + f - str);
			if (size > 0) { // 感觉此处size并不会 <= 0, 应该只是为了保险
				memmove(found + r, found + f, size); // 先构造所需的空间
			}
			strncpy(found, toReplace, r); // 复制替换的字符串
		}
		else { // 变短
			strncpy(found, toReplace, r); // 先替换
			int size = (s + 1) - (found + f - str);
			if (size > 0) { 		// cout << s << endl;
				memmove(found + r, found + f, size);// 再缩小字符串
			}
		}
		s = strlen(str); // 需要更新字符串长度s,否则无法正确计算size
	}
	str[s + 1] = '\0'; // 此处应该也是保险, 因为从上面的代码逻辑看并不会出现丢失\0的情况
}

void string_replace_all_sub(string& str, const string& toFind, const string& toReplace) {
	while (true) {
		auto pos = str.find(toFind);
		if (pos == string::npos) {
			break;
		}
		str.replace(begin(str) + pos, begin(str) + pos + toFind.size(), toReplace);
	}
}

int main() {
	char s[100] = "abcdecdefghcde"; // 应该预留充足的数组长度,否则很容易溢出
	char f[] = "cde";
	char r[] = "WXYZZZZZ";
	char_str_replace_all_sub(s, f, r);
	cout << s << endl;
	string s1 = "abcdecdefghcde";
	string s2 = "cde";
	string s3 = "WXYZZZZ";
	string_replace_all_sub(s1, s2, s3);
	cout << s1 << endl;
	return 0;
}
