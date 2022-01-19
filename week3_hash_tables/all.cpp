#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>

using namespace std;
using ll = long long;

void phone_book(){
    unordered_map<int, string> v;
    string query;
    int n;
    cin >> n;
    int num;
    string name;
    while (n--){
        cin >> query;
        if (query == "add"){
            cin >> num >> name;
            v[num] = name;
        } else if (query == "find"){
            cin >> num;
            if (v.count(num)){
                cout << v[num] << '\n';
            } else {
                cout << "not found" << '\n';
            }
        } else {
            cin >> num;
            v.erase(num);
        }
    }
}

ll mulmod(ll a, ll b, ll m){
    ll res = 0;
    a %= m;
    b %= m;
    while (a > 0){
        if (a & 1){
            res = (res + b) % m;
        }
        a >>= 1;
        if (b < m - b){
            b <<= 1;
        } else {
            b -= (m - b);
        }
    }
    return res;
}


ll pow(ll a, ll u, ll n){
    ll x = 1;
    while (u > 0){
        if (u & 1u){
            x = mulmod(x, a, n);
        }
        a = mulmod(a, a, n);
        u >>= 1u;
    }
    return x;
}

ll h(string &s, ll p, ll m, ll x){
    ll res = 0;
    vector<ll> p_pow = {1};
    for (int i = 1; i < s.size(); ++i){
        p_pow.push_back(mulmod(p_pow.back(), x, p));
    }
    for (int i = 0; i < s.size(); ++i){
        res += mulmod(ll(s[i]), p_pow[i], p);
        res %= p;
    }
    return res % m;
}

void hash_chains(){
    int n, m;
    cin >> m >> n;
    vector<list<string>> table(m);
    string query, s;
    ll p = 1000000007, x = 263;
    int id;
    for (int i = 0; i < n; ++i){
        cin >> query;
        if (query == "add"){
            cin >> s;
            id = h(s, p, m, x);
            if (table[id].empty()){
                table[h(s, p, m, x)].push_front(s);
            } else {
                auto it = find(table[id].begin(), table[id].end(), s);
                if (it == table[id].end()){
                    table[h(s, p, m, x)].push_front(s);
                }
            }
        } else if (query == "del"){
            cin >> s;
            id = h(s, p, m, x);
            if (!table[id].empty()){
                auto it = find(table[id].begin(), table[id].end(), s);
                if (it != table[id].end()){
                    table[id].erase(it);
                }
            }
        } else if (query == "find"){
            cin >> s;
            id = h(s, p, m, x);
            if (!table[id].empty() and find(table[id].begin(), table[id].end(), s) != table[id].end()){
                cout << "yes" << '\n';
            } else {
                cout << "no" << '\n';
            }
        } else {
            cin >> id;
            for (auto &lit : table[id]){
                cout << lit << ' ';
            }
            cout << '\n';
        }
    }
}

ll phash(string &s, ll p, ll x){
    ll res = 0;
    vector<ll> p_pow = {1};
    for (int i = 1; i < s.size(); ++i){
        p_pow.push_back(mulmod(p_pow.back(), x, p));
    }
    for (int i = 0; i < s.size(); ++i){
        res += mulmod(ll(s[i]), p_pow[i], p);
        res %= p;
    }
    return res;
}

ll poly_hash(string &s, ll p, ll x){
    ll res = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i){
        res = (res * x + s[i]) % p;
    }
    return res;
}

void rabin_karp(){
    string pattern, text;
    cin >> pattern >> text;
    ll p = 1000000007, x = 263;
    if (text.size() < pattern.size()){
        return;
    }
    int n = text.size() - pattern.size() + 1;
    vector<ll> h(n);
    h[0] = 0;
    ll y = 1;
//    for (int i = 0; i < pattern.size(); ++i){
//        y = mulmod(y, x, p);
//    }
    y = pow(x, pattern.size(), p);
    string substr = text.substr(text.size() - pattern.size(), pattern.size());
    h[n - 1] = phash(substr, p, x);
    ll hsh = phash(pattern, p, x);
    for (int i = n - 2; i >= 0; --i){
        h[i] = (h[i + 1] * x - text[i + pattern.size()] * y + text[i]) % p;
        if (h[i] < 0){
            h[i] += p;
        }
    }

    bool answ = true;
    vector<int> ans;
    for (int i = 0; i < n; ++i){
        if (hsh == h[i]){
            answ = true;
            for (int j = 0; j < pattern.size(); ++j){
                answ &= pattern[j] == text[i + j];
            }
            if (answ){
                ans.push_back(i);
            }
        }
    }
    for (auto &i : ans){
        cout << i << ' ';
    }
}

void no_rabin_karp(){
    string pattern, text;
    cin >> pattern >> text;
    ll p1 = 1000000007, p2 = 1000000009, x = 263;
    int n = text.size() - pattern.size() + 1;
    vector<ll> h1(n), h2(n);
    ll y1 = 1, y2 = 1;
    y1 = pow(x, pattern.size(), p1);
    y2 = pow(x, pattern.size(), p2);
    string substr = text.substr(text.size() - pattern.size(), pattern.size());
    h1[n - 1] = phash(substr, p1, x);
    h2[n - 1] = phash(substr, p2, x);
    ll hsh1 = phash(pattern, p1, x);
    ll hsh2 = phash(pattern, p2, x);
    for (int i = n - 2; i >= 0; --i){
        h1[i] = (h1[i + 1] * x - text[i + pattern.size()] * y1 + text[i]) % p1;
        h2[i] = (h2[i + 1] * x - text[i + pattern.size()] * y2 + text[i]) % p2;
        if (h1[i] < 0){
            h1[i] += p1;
        }
        if (h2[i] < 0){
            h2[i] += p2;
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i){
        if (hsh1 == h1[i] and hsh2 == h2[i]){
            ans.push_back(i);
        }
    }
    for (auto &i : ans){
        cout << i << ' ';
    }
}

void substring_equality(){
    string s;
    cin >> s;
    int q;
    ll p1 = 1000000007, p2 = 1000000009;
    int x = 263;
    vector<ll> pm1(1, 1), pm2(1, 1);
    int n = s.size();
    for (int i = 1; i < n; ++i){
        pm1.push_back((pm1[i - 1] * x) % p1);
        pm2.push_back((pm2[i - 1] * x) % p2);
    }
    vector<ll> hsh1(n), hsh2(n);
    hsh1[n - 1] = int(s[n - 1]);
    hsh2[n - 1] = int(s[n - 1]);
    for (int i = n - 2; i >= 0; --i){
        hsh1[i] = (hsh1[i + 1] * x + s[i]) % p1;
        hsh2[i] = (hsh2[i + 1] * x + s[i]) % p2;
    }
    cin >> q;
    int a, b, l;
    ll ha1, ha2, hb1, hb2;
    for (int t = 0; t < q; ++t){
        cin >> a >> b >> l;
        if (a + l != n){
            ha1 = (hsh1[a] - hsh1[a + l] * pm1[l]) % p1;
            ha2 = (hsh2[a] - hsh2[a + l] * pm2[l]) % p2;
            if (ha1 < 0){
                ha1 += p1;
            }
            if (ha2 < 0){
                ha2 += p2;
            }
        } else {
            ha1 = hsh1[a];
            ha2 = hsh2[a];
        }
        if (b + l != n){
            hb1 = (hsh1[b] - hsh1[b + l] * pm1[l]) % p1;
            hb2 = (hsh2[b] - hsh2[b + l] * pm2[l]) % p2;
            if (hb1 < 0){
                hb1 += p1;
            }
            if (hb2 < 0){
                hb2 += p2;
            }
        } else {
            hb1 = hsh1[b];
            hb2 = hsh2[b];
        }
        if (ha1 == hb1 and ha2 == hb2){
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
}

struct st{
    ll h1;
    ll h2;
    int i;
};

bool operator<(st s1, st s2){
    if (s1.h1 == s2.h1){
        return s1.h2 < s2.h2;
    } else if (s1.h1 == s2.h1 and s1.h2 == s2.h2){
        return s1.i < s2.i;
    }
    return s1.h1 < s2.h1;
}

void longest_common_substring(){
    string s, t;
    int x = 263;
    int n1, n2;
    ll p1 = 1000000007, p2 = 1000000009;
    vector<pair<ll, ll>> pw(1, {1, 1});
    for (int i = 1; i < 100000; ++i){
        pw.emplace_back((pw[i - 1].first * x) % p1, (pw[i - 1].second * x) % p2 );
    }
    int lft, rht;
    vector<pair<ll, ll>> hsh1(50000), hsh2(50000);
    while (cin >> s >> t){
        n1 = s.size();
        n2 = t.size();
        if (n1 >= hsh1.size()){
            hsh1.resize(n1 + 1);
        }
        if (n2 >= hsh2.size()){
            hsh2.resize(n2 + 1);
        }
        hsh1[n1 - 1].first = int(s[n1 - 1]);
        hsh1[n1 - 1].second = int(s[n1 - 1]);
        hsh2[n2 - 1].first = int(t[n2 - 1]);
        hsh2[n2 - 1].second = int(t[n2 - 1]);
        hsh1[n1].first = 0;
        hsh1[n1].second = 0;
        hsh2[n2].first = 0;
        hsh2[n2].second = 0;
        for (int i = n1 - 2; i >= 0; --i){
            hsh1[i].first = ((hsh1[i + 1].first * x) % p1 + s[i]) % p1;
            hsh1[i].second = ((hsh1[i + 1].second * x) % p2 + s[i]) % p2;
        }
        for (int i = n2 - 2; i >= 0; --i){
            hsh2[i].first = ((hsh2[i + 1].first * x) % p1 + t[i]) % p1;
            hsh2[i].second = ((hsh2[i + 1].second * x) % p2 + t[i]) % p2;
        }
        int r = min(n1, n2);
        int l = 0;
        int answ = -1;
        lft = 0;
        rht = 1;
        while (l <= r){
            int mid = (l + r) / 2;
            vector<st> v;
            bool is_equal = false;
            for (int j = 0; j <= n1 - mid; ++j){
                v.push_back({(hsh1[j].first - hsh1[j + mid].first * pw[mid].first) % p1,
                             (hsh1[j].second - hsh1[j + mid].second * pw[mid].second) % p2, j});
                if (v.back().h1 < 0){
                    v.back().h1 += p1;
                }
                if (v.back().h2 < 0){
                    v.back().h2 += p2;
                }
            }
            sort(v.begin(), v.end());
            st h{};
            for (int j = 0; j <= n2 - mid and !is_equal; ++j){
                h.h1 = (hsh2[j].first - hsh2[j + mid].first * pw[mid].first) % p1;
                h.h2 = (hsh2[j].second - hsh2[j + mid].second * pw[mid].second) % p2;
                if (h.h1 < 0){
                    h.h1 += p1;
                }
                if (h.h2 < 0){
                    h.h2 += p2;
                }
                h.i = 0;
                auto it = lower_bound(v.begin(), v.end(), h);
                if (it != v.end() and it->h1 == h.h1 and it->h2 == h.h2){
                    is_equal = true;
                    lft = it->i;
                    rht = j;
                    answ = mid;
                }
            }
            if (is_equal){
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        if (answ == -1){
            cout << lft << ' ' << rht << ' ' << 0 << '\n';
        } else {
            cout << lft << ' ' << rht << ' ' << answ << '\n';
        }
    }
}

/*
1 ababab baaa
012345
ababab
abab
baaa
baba
*/

int get_index(vector<pair<ll, ll>> &hsh1, vector<pair<ll, ll>> &hsh2,
        vector<pair<ll, ll>> &pw, int l, int r, int i, ll p1, ll p2, int n2){
    int s = n2 - r;
    while (l <= r){
        int m = (l + r) / 2;
        st h1{}, h2{};
        h1.h1 = (hsh1[i].first - (hsh1[i + m].first * pw[m].first) % p1) % p1;
        h1.h2 = (hsh1[i].second - (hsh1[i + m].second * pw[m].second) % p2) % p2;
        h2.h1 = (hsh2[s].first - (hsh2[s + m].first * pw[m].first) % p1) % p1;
        h2.h2 = (hsh2[s].second - (hsh2[s + m].second * pw[m].second) % p2) % p2;
        if (h1.h1 < 0){
            h1.h1 += p1;
        }
        if (h1.h2 < 0){
            h1.h2 += p2;
        }
        if (h2.h1 < 0){
            h2.h1 += p1;
        }
        if (h2.h2 < 0){
            h2.h2 += p2;
        }
        if (h1.h1 == h2.h1 and h1.h2 == h2.h2){
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}

void pattern_matching_with_mismatches(){
    string s, t;
    int k;
    int x = 263;
    ll p1 = 1000000007, p2 = 1000000009;
    vector<pair<ll, ll>> pw(1, {1, 1});
    for (int i = 1; i <= 100000; ++i){
        pw.emplace_back((pw[i - 1].first * x) % p1, (pw[i - 1].second * x) % p2);
    }
    while (cin >> k >> s >> t){
        int n1 = s.size();
        int n2 = t.size();
        vector<pair<ll, ll>> hsh1(n1 + 1), hsh2(n2 + 1);
        hsh1[n1 - 1].first = int(s[n1 - 1]);
        hsh1[n1 - 1].second = int(s[n1 - 1]);
        hsh2[n2 - 1].first = int(t[n2 - 1]);
        hsh2[n2 - 1].second = int(t[n2 - 1]);
        for (int i = n1 - 2; i >= 0; --i){
            hsh1[i].first = (s[i] + (hsh1[i + 1].first * x) % p1) % p1;
            hsh1[i].second = (s[i] + (hsh1[i + 1].second * x) % p2) % p2;
        }
        for (int i = n2 - 2; i >= 0; --i){
            hsh2[i].first = (t[i] + (hsh2[i + 1].first * x) % p1) % p1;
            hsh2[i].second = (t[i] + (hsh2[i + 1].second * x) % p2) % p2;
        }
        int cnt = 0;
        vector<int> answ;
        for (int i = 0; i <= n1 - n2; ++i){
            cnt = 0;
            st h{};
            h.h1 = (hsh1[i].first - (hsh1[i + n2].first * pw[n2].first) % p1) % p1;
            h.h2 = (hsh1[i].second - (hsh1[i + n2].second * pw[n2].second) % p2) % p2;
            if (h.h1 < 0){
                h.h1 += p1;
            }
            if (h.h2 < 0){
                h.h2 += p2;
            }
            if (h.h1 == hsh2[0].first and h.h2 == hsh2[0].second){
                answ.push_back(i);
            } else {
                int l = 1, r = n2;
                int b = i;
                int end = i + n2;
                int begin = 0;
                while (cnt < k){
                    int pos = get_index(hsh1, hsh2, pw, l, r, b, p1, p2, n2);
                    begin += pos;
                    b += pos;
                    r -= pos;
                    ++cnt;
                    st h1{}, h2{};
                    h1.h1 = (hsh1[b].first - (hsh1[end].first * pw[r].first) % p1) % p1;
                    h1.h2 = (hsh1[b].second - (hsh1[end].second * pw[r].second) % p2) % p2;
                    h2.h1 = (hsh2[begin].first - (hsh2[n2].first * pw[r].first) % p1) % p1;
                    h2.h2 = (hsh2[begin].second - (hsh2[n2].second * pw[r].second) % p2) % p2;
                    if (h1.h1 < 0){
                        h1.h1 += p1;
                    }
                    if (h1.h2 < 0){
                        h1.h2 += p2;
                    }
                    if (h2.h1 < 0){
                        h2.h1 += p1;
                    }
                    if (h2.h2 < 0){
                        h2.h2 += p2;
                    }
                    if (h1.h1 == h2.h1 and h1.h2 == h2.h2){
                        answ.push_back(i);
                        break;
                    }
                }
            }
        }
        cout << answ.size() << ' ';
        for (auto &i : answ){
            cout << i << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    hash_chains();
//    phone_book();
//    rabin_karp();
//    no_rabin_karp();
//    substring_equality();
//    longest_common_substring();
    pattern_matching_with_mismatches();
    return 0;
}
/*
1 ababab baaa
012345
ababab
baaa

*/