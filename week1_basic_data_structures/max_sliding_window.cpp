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
    vector<int> v;
    int item;
    for (int i = 0; i < n; ++i){
        cin >> item;
        v.push_back(item);
    }
    int m;
    cin >> m;
    deque<pair<int, int>> q;
    int cnt = 0;
    for (int i = 0; i < m; ++i){
        cnt = 0;
        while (q.size() != 0 and v[i] > q.back().first){
            ++cnt;
            q.pop_back();
        }
        q.push_back(make_pair(v[i], i));
    }
    int index = 0;
    for (int i = m; i <= n; ++i){
        if (q.front().second > index){
            cout << q.front().first << ' ';
            ++index;
        } else {
            cout << q.front().first << ' ';
            ++index;
            q.pop_front();
        }
        while (q.size() != 0 and v[i] > q.back().first){
            ++cnt;
            q.pop_back();
        }
        q.push_back(make_pair(v[i], i));
    }
    return 0;
}

