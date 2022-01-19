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

void siftDown(vector<int> &a, vector<pair<int, int>> &v, int i){
    int l, r, j;
    while (2 * i + 1 < a.size()){
        l = 2 * i + 1;
        r = 2 * i + 2;
        j = l;
        if (r < a.size() and a[r] < a[l]){
            j = r;
        }
        if (a[i] < a[j]){
            break;
        }
        swap(a[i], a[j]);
        v.emplace_back(i, j);
        i = j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a){
        cin >> i;
    }
    vector<pair<int, int>> v;
    for (int i = n / 2; i >= 0; --i){
        siftDown(a, v, i);
    }
    cout << v.size() << '\n';
    for (int i = 0; i < v.size(); ++i){
        cout << v[i].first << ' ' << v[i].second << '\n';
    }
}

