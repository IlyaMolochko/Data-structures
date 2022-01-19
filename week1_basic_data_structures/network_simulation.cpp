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
    int size, n;
    cin >> size >> n;
    vector<int> a(n);
    vector<int> d(n);
    deque<int> q;
    int t = 0, fill = 0;
    for (int i = 0; i < n; ++i){
        cin >> a[i] >> d[i];
        if (q.size() == 0){
            cout << a[i] << endl;
            q.push_back(a[i] + d[i]);
            ++fill;
        } else if (fill < size){
            ++fill;
            cout << max(a[i], q.back()) << endl;
            q.push_back(max(a[i] + d[i], q.back() + d[i]));
            auto it = upper_bound(q.begin(), q.end(), a[i]);
            for (int j = 0; j < it - q.begin(); ++j){
                q.pop_front();
                --fill;
            }
        } else {
            auto it = upper_bound(q.begin(), q.end(), a[i]);
            if (it != q.begin()){
                cout << max(q.back(), a[i]) << endl;
                q.push_back(max(q.back() + d[i], a[i] + d[i]));
                ++fill;
            } else{
                cout << -1 << endl;
            }
            for (int j = 0; j < it - q.begin(); ++j){
                q.pop_front();
                --fill;
            }
        }
    }
    return 0;
}

