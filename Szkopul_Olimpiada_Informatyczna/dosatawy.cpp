#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

constexpr int max_dim = 10e6;

size_t n, q;
size_t arr;

// linear array
std::vector<int>    distances;
std::vector<bool>   have_fort;
std::vector<size_t> linear_to_tree_id;

// tree
std::vector<int>  scores;
std::vector<int>  delays;

std::vector<size_t> initial_forts;

// O(1) ok
inline size_t pos_to_linear_id(int row, int column) noexcept {
    return row * n + column;
};

// O(1) ok
inline size_t pos_to_tree_id(int row, int column) noexcept {
    return arr + row * n + column;
};

// O(n^2) ok
void load() {
    std::cin >> n >> q;

    distances = std::vector<int>(n*n);
    have_fort = std::vector<bool>(n*n);

    arr = n * n;
    arr = 2 << std::__lg(arr - 1);

    scores = std::vector<int>(2 * arr, 0);
    delays = std::vector<int>(2 * arr, 0);

    for (int r = 0; r < n; r++) {
        std::string row; std::cin >> row;
        for (int c = 0; c < n; c++) {
            size_t pos = pos_to_linear_id(r, c);
            distances[pos] = (row[c] == '#' ? -1 : 0);
            if (row[c] == 'F') initial_forts.push_back(pos);
        }
    }
}

// O(n^2) ok
void update_distances() {
    std::vector<std::pair<int, int>> queue = {{0, 0}};
    std::vector<std::pair<int, int>> next_queue;

    int dist = 0;

    while (queue.size()) {
        for (auto& pos : queue) {
            auto id = pos_to_linear_id(pos.second, pos.first);
            if (distances[id]) continue; // -1 if obstacle, > 0 if already visited

            distances[id] = dist;
            
            if (pos.first - 1 > -1)  next_queue.push_back({pos.first - 1, pos.second});
            if (pos.first + 1 < n)   next_queue.push_back({pos.first + 1, pos.second});

            if (pos.second - 1 > -1) next_queue.push_back({pos.first, pos.second - 1});
            if (pos.second + 1 < n)  next_queue.push_back({pos.first, pos.second + 1});
        }

        dist++;

        queue.swap(next_queue);
        next_queue.clear();
    }
}

void make_mapping() {
    // dist, linear id
    std::vector<std::pair<int, int>> premap(n*n);
    for (int i = 0; i < n * n; i++) premap[i] = {distances[i], i};
    std::sort(premap.rbegin(), premap.rend());

    linear_to_tree_id = std::vector<size_t>(n*n);
    for (int i = 0; i < n * n; i++) linear_to_tree_id[premap[i].second] = i + arr;
}

// O(log (n^2)) ok
void walk_up_tree(size_t id, int delay_change) {
    size_t ppid = id;
    size_t pid  = id / 2; //parent id

    while (pid != 0) {
        // we went right if we were a left child
        // if so apply delay
        if (ppid % 2 == 0) 
            delays[pid * 2 + 1] += delay_change;

        int lv = scores[pid * 2];
        int rv = (scores[pid * 2 + 1] + delays[pid * 2 + 1]) * (scores[pid * 2 + 1] != 0); 

        scores[pid] = std::max(lv, rv);

        ppid = pid;
        pid /= 2;
    };
}

// ok
inline void toggle_fort(size_t linear_id) {
    have_fort[linear_id] = !have_fort[linear_id];

    size_t tree_id  = linear_to_tree_id[linear_id];
    scores[tree_id] = distances[linear_id] * have_fort[linear_id]; 

    walk_up_tree(tree_id, have_fort[linear_id] ? 1 : -1);
}

// O(1) ok
inline int get_score() {
    return scores[1];
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    load();
    update_distances();
    make_mapping();

    for (auto fort : initial_forts) toggle_fort(fort);
    std::cout << get_score() << '\n';

    for (int i = 0; i < q; i++) {
        int r, c; std::cin >> r >> c; r--; c--;
        auto id = pos_to_linear_id(r, c);
        toggle_fort(id);
        std::cout << get_score() << '\n';
    }
}
