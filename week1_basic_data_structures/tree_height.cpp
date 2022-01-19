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

int f(vector<int> &v, vector<int> &h, int i){
    if (h[i] == 1){
        if (v[i] == -1){
            return h[i];
        } else {
            h[i] += f(v, h, v[i]);
            return h[i];
        }
    }
    return h[i];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> h = vector<int>(n, 1);
    vector<int> v = vector<int>(n);
    for (int i = 0; i < n; ++i){
        cin >> v[i];
    }
    int mx = 0;
    for (int i = 0; i < n; ++i){
        mx = max(mx, f(v, h, i));
    }
    cout << mx << '\n';
}

