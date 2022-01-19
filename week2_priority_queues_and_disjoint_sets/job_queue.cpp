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

void siftUp(vector<pair<ll, int>> &a, int i){
    while (a[i].first <= a[(i - 1) / 2].first){
        if ((a[i].first == a[(i - 1) / 2].first and a[i].second < a[(i - 1) / 2].second) or a[i].first < a[(i - 1) / 2].first){
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}

void siftDown(vector<pair<ll, int>> &a, ll i){
    ll l, r, j;
    while (2 * i + 1 < a.size()){
        l = 2 * i + 1;
        r = 2 * i + 2;
        j = l;
        if (r < a.size() and ((a[r].first == a[l].first and a[r].second < a[l].second) or (a[r].first < a[l].first))){
            j = r;
        }
        if (((a[i].first == a[j].first and a[i].second < a[j].second) or (a[i].first < a[j].first))){
            break;
        }
        swap(a[i], a[j]);
        i = j;
    }
}

void insert(vector<pair<ll, int>> &a, pair<ll, int> key){
    a.push_back(key);
    siftUp(a, a.size() - 1);
}

pair<ll, int> extract(vector<pair<ll, int>> &a){
    pair<ll, int> mn = a[0];
    a[0] = a[a.size() - 1];
    a.pop_back();
    siftDown(a, 0);
    return mn;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> a(m);
    for (int i = 0; i < m; ++i){
        cin >> a[i];
    }
    vector<pair<ll, int>> v;
    ll t = 0;
    for (int i = 0; i < n; ++i){
        insert(v, make_pair(0ll, i));
    }
    pair<ll, int> p;
    for (int i = 0; i < m; ++i){
        p = extract(v);
        cout << p.second << ' ' << p.first << '\n';
        insert(v, make_pair(p.first + a[i], p.second));
    }
}

