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

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<list<string>> elems;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
        elems.resize(bucket_count);
    }

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            if (query.ind < bucket_count){
                if (!elems[query.ind].empty()){
                    list<string> &items= elems[query.ind];
                    for (auto it = items.begin(); it != items.end(); ++it){
                        cout << *it << ' ';
                    }
                }
            }
            std::cout << "\n";
        } else {
            int hash_value = hash_func(query.s);
            list<string> &items = elems[hash_value];
            auto it = std::find(items.begin(), items.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != items.end());
            else if (query.type == "add") {
                if (it == items.end()){
                    items.push_front(query.s);
                }

            } else if (query.type == "del") {
                if (it != items.end())
                    items.erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
