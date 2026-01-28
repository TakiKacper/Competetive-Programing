#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

constexpr int all_letters_max = 10e5 + 10;
constexpr int letters_amount = 'z' - 'a' + 1;

struct tree_leaf {
    char letter;
    bool word;
    int  child[letters_amount] = {};

    // child longest word, child id
    std::vector<std::pair<int, int>> child_order;
};

int       trie_allocator = 1;
tree_leaf trie[all_letters_max];

// trie[0]  <- empty word ""
// child[x] == 0 -> no child

// O (n * str.size()) -> O(10e6)
void load() {
    int n; std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::string str; std::cin >> str;
        int trie_pos = 0;

        for (auto& letter : str) {
            auto& leaf     = trie[trie_pos];
            auto& child_id = leaf.child[letter - 'a'];
            
            if (child_id == 0) {
                int new_leaf = trie_allocator++;
                child_id = new_leaf;
                trie_pos = new_leaf;
                trie[child_id].letter = letter;
            }
            else {
                trie_pos = child_id;
            }
        }

        trie[trie_pos].word = true;
    }
}

// dfs
// O(n * str.size()) -> O(10e6)
// returns length of the longest word
int find_order(int root, int dst) {
    auto& leaf = trie[root];

    for (int l = 0; l < letters_amount; l++) {
        auto& child_id = leaf.child[l];
        if (child_id == 0) continue;
        leaf.child_order.push_back({find_order(child_id, dst + 1), child_id});
    }

    if (leaf.child_order.size()) {
        std::sort(leaf.child_order.begin(), leaf.child_order.end());
        return leaf.child_order.back().first;
    }

    return dst;
}

std::stringstream   stream;
std::string         backtrace;

// if tab node have children, then another word will appear before we start backing
// therefore the lca(tab, current position) will be tab itself
// otherwise if tab is the last node there will be other node witch is lca between tab and current position
bool going_from_tab_to_lca = false;

int tab_dst     = 1; // distance between tab position and current position
int tab_lca_dst = 0; // distance between tab and lca(tab, current position)
int lca_dst     = 0; // distance between lca and trie[0]

// dfs
// O(n * str.size()) -> O(10e6)
void walk(int root, int dst) {
    auto& leaf = trie[root];

    tab_dst += !going_from_tab_to_lca;

    if (leaf.word) {
        if (dst < tab_dst + 1) {
            stream << backtrace;
        }
        else {
            stream << "T";
            while (tab_lca_dst--) stream << "B";
            stream << backtrace.substr(lca_dst, dst - lca_dst);
        }

        stream << "E";

        // if tab have childs there will be no lca
        going_from_tab_to_lca = !leaf.child_order.size();

        tab_lca_dst = 0;
        tab_dst     = 0;

        lca_dst     = going_from_tab_to_lca ? 0 : dst;
    }

    for (auto& pair : leaf.child_order) {
        auto& child_id = pair.second;
        auto& child    = trie[child_id];

        if (going_from_tab_to_lca) {
            lca_dst     = dst;
            tab_lca_dst = tab_dst;
            going_from_tab_to_lca = false;
        }
        
        backtrace.push_back(child.letter);
        walk(child_id, dst + 1);
        backtrace.pop_back();
    }

    tab_dst += going_from_tab_to_lca;
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);    

    load();
    find_order(0, 0);
    walk(0, 0);

    auto result = stream.str();

    std::cout << result.size() << '\n';
    std::cout << result;

    return 0;
}
