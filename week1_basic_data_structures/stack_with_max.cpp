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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    int item;
    vector<int> stack;
    vector<int> v;
    int mx = -1;
    for (int i = 0; i < n; ++i){
        cin >> s;
        if (s == "push"){
            cin >> item;
            stack.push_back(item);
            mx = max(mx, item);
            v.push_back(mx);
        } else if (s == "pop"){
            stack.pop_back();
            v.pop_back();
            if (v.size() != 0){
                mx = min(mx, v.back());
            } else {
                mx = -1;
            }
        } else {
            cout << v.back() << endl;
        }
    }

    return 0;
}

