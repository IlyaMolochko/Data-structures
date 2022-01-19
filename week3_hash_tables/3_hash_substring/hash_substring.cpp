//#include <iostream>
//#include <string>
//#include <vector>
//
//using std::string;
//typedef unsigned long long ull;
//
//struct Data {
//    string pattern, text;
//};
//
//Data read_input() {
//    Data data;
//    std::cin >> data.pattern >> data.text;
//    return data;
//}
//
//void print_occurrences(const std::vector<int>& output) {
//    for (size_t i = 0; i < output.size(); ++i)
//        std::cout << output[i] << " ";
//    std::cout << "\n";
//}
//
//std::vector<int> get_occurrences(const Data& input) {
//    const string& s = input.pattern, t = input.text;
//    std::vector<int> ans;
//    for (size_t i = 0; i + s.size() <= t.size(); ++i)
//        if (t.substr(i, s.size()) == s)
//            ans.push_back(i);
//    return ans;
//}
//
//
//int main() {
//    std::ios_base::sync_with_stdio(false);
//    print_occurrences(get_occurrences(read_input()));
//    return 0;
//}
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
#include <list>

using ll = long long ;
using namespace std;


struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

ll get_hash(string s){
    ll multiplier = 263;
    ll prime = 1000000007;
    ll hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * multiplier + s[i]) % prime;
    return hash;
}


vector<ll> get_hashes(const string &s, int len){
    ll multiplier = 263;
    ll prime = 1000000007;
    vector<ll> hashes(s.size() - len + 1);
    string substr = s.substr(s.size() - len, len);
    hashes[hashes.size() - 1] = get_hash(substr);
    ll p = 1;
    for (int i = 0; i < len; ++i){
        p = (p * multiplier) % prime;
    }
    for (int i = hashes.size() - 2; i >= 0; --i){
        hashes[i] = (multiplier * hashes[i + 1] - p * s[i + len] + s[i]) % prime;
        if (hashes[i] < 0){
            hashes[i] += prime;
        }
    }
    return hashes;
}

bool is_equal(string p, string s, int b, int e){
    for (int i = b, j = 0; i < e; ++i, ++j){
        if (s[i] != p[j]){
            return false;
        }
    }
    return true;
}


std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    int hash = get_hash(s);
    std::vector<int> ans;
    vector<ll> hashes = get_hashes(t, s.size());
    for (size_t i = 0; i < hashes.size(); ++i){
        if (hashes[i] == hash){
            ans.push_back(i);
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}