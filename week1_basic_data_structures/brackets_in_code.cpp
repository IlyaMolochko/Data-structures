#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <iomanip>
#include <cmath>
#include <set>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

using ll = long long ;
using namespace std;
struct label{
    string key;
    int value;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    vector<pair<char, int>> stack;
    int index = 0;
    for (int i = 0; i < s.size(); ++i){
        if (s[i] == '('){
            stack.push_back(make_pair(s[i], i));
        } else if (s[i] == ')' and (!stack.empty() and stack.back().first == '(')){
            stack.pop_back();
        } else if (s[i] == '['){
            stack.push_back(make_pair(s[i], i));
            index = i;
        } else if (s[i] == ']' and (!stack.empty() and stack.back().first == '[')){
            stack.pop_back();
        }else if (s[i] == '{'){
            stack.push_back(make_pair(s[i], i));
            index = i;
        } else if (s[i] == '}' and (!stack.empty() and stack.back().first == '{')){
            stack.pop_back();
        } else if (s[i] == ')' or s[i] == '}' or s[i] == ']'){
            cout << i + 1 << '\n';
            return 0;
        }
    }
    if (!stack.empty()){
        cout << stack.back().second + 1 << '\n';
    } else {
        cout << "Success" << '\n';
    }
}
