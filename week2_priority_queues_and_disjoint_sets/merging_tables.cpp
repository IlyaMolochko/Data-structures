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

struct DisjointSetsElement {
    int size, parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
            size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        // find parent and compress path
        while (sets[table].parent != table){
            sets[table].parent = getParent(sets[table].parent);
            table = sets[table].parent;
        }
        return table;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            if (sets[realDestination].rank > sets[realSource].rank){
                sets[realSource].parent = realDestination;

                sets[realDestination].size += sets[realSource].size;
                sets[realSource].size = 0;

                if (sets[realDestination].size > max_table_size){
                    max_table_size = sets[realDestination].size;
                }
            } else {
                if (sets[realDestination].rank == sets[realSource].rank){
                    ++sets[realDestination].rank;
                }
                sets[realDestination].parent = realSource;

                sets[realSource].size += sets[realDestination].size;
                sets[realDestination].size = 0;

                if (sets[realSource].size > max_table_size){
                    max_table_size = sets[realSource].size;
                }
            }
        }
    }
};

int main() {
    int n, m;
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;

    DisjointSets tables(n);
    for (auto &table : tables.sets) {
        cin >> table.size;
        tables.max_table_size = max(tables.max_table_size, table.size);
    }

    for (int i = 0; i < m; i++) {
        int destination, source;
        cin >> destination >> source;
        --destination;
        --source;

        tables.merge(destination, source);
        cout << tables.max_table_size << '\n';
    }

    return 0;
}

