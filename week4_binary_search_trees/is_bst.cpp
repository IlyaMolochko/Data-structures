#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_node(int node, const vector<Node>& tree, vector<int>& result){
    if (node == -1){
        return;
    }
    in_order_node(tree[node].left, tree, result);
    result.push_back(tree[node].key);
    in_order_node(tree[node].right, tree, result);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
    vector<int> result;
    if (tree.size() > 0){
        in_order_node(0, tree, result);
        for (int i = 1; i < result.size(); ++i){
            if (result[i - 1] > result[i]){
                return false;
            }
        }
    }
    return true;
}

int main() {
    int nodes;
    cin >> nodes;
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
        int key, left, right;
        cin >> key >> left >> right;
        tree.emplace_back(key, left, right);
    }
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
