#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string line;
    regex email(R"(\w+@(\w+\.)+\w+)"); // R"xxx(yyy)xxx" xxx可为空,同时yyy不转义
    while(getline(cin, line)) {
        smatch matches; // std::match_results<std::string::const_iterator>
    	auto current = cbegin(line); // 不能修改line中的字符, 类似底层const
        auto last = cend(line);
        while(current != last) {
            if (regex_search(current, last, matches, email)) {
            	ssub_match match = matches[0];
                current = match.second;
            	cout << match.str() << endl; 
        	}
            else {
                break;
            }
        }
    }
    return 0;
}