#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    map<int, int> xs;
    for (int i = 1; i <= 10; i++)
    {
        xs.insert(make_pair(i, i*i));
    }

    while (true)
    {
        int x;
        cin >> x;
        if (x == -1)
        {
            break;
        }

        auto it = xs.find(x);
        if (it == xs.end())
        {
            for(auto pair: xs) {
                cout << pair.first << " ";
            }
            cout << endl;
        }
        else
        {
            cout << it->second << endl;
        }
    }
    return 0;
}