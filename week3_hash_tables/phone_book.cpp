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

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    unordered_map<int, string> pb;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            pb[queries[i].number] = queries[i].name;
//            bool was_founded = false;
//            // if we already have contact with such number,
//            // we should rewrite contact's name
//            for (size_t j = 0; j < contacts.size(); ++j)
//                if (contacts[j].number == queries[i].number) {
//                    contacts[j].name = queries[i].name;
//                    was_founded = true;
//                    break;
//                }
//            // otherwise, just add it
//            if (!was_founded)
//                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
//            for (size_t j = 0; j < contacts.size(); ++j)
//                if (contacts[j].number == queries[i].number) {
//                    contacts.erase(contacts.begin() + j);
//                    break;
//                }
            pb.erase(queries[i].number);
        } else {
            string response = "not found";
//            for (size_t j = 0; j < contacts.size(); ++j)
//                if (contacts[j].number == queries[i].number) {
//                    response = contacts[j].name;
//                    break;
//                }
            if (!pb[queries[i].number].empty()){
                response = pb[queries[i].number];
            }
            result.push_back(response);
        }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    write_responses(process_queries(read_queries()));

    return 0;
}

