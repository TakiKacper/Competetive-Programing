#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <set>

// 1) wolny bit to taki, ze w obu rownanianch na jego pozycji, nie ma 0 lub 1
// 2) zauwz ze zmienna moze sie pojawic dwukrotnie w jedynm rownaniu, ale moze miec tylko jedno przypisanie

// idziemy bo obu rownaniach, iterujac po bitach
// bedziemy kolejnym bitom przypisywac powiazania
// odpowiedzia bedzie 2 ^ (scc - 2) (-2 za to ze 2 scc sa polaczone z 1 albo 0)
// swoja droga jezeli jeden i zero znajda sie w jednym scc to mamy sprzecznosc i 0 rozwiazan

constexpr int max_k = 27;

struct node {
    bool            visited = false;
    std::set<node*> equal_nodes;
};

node bit_0_node;
node bit_1_node;

// bits assigned to each variable
std::vector<node> var_bits[max_k];

void clear() {
    bit_0_node.visited = false;
    bit_0_node.equal_nodes.clear();

    bit_1_node.visited = false;
    bit_1_node.equal_nodes.clear();

    for (int i = 0; i < max_k; i++) var_bits[i].clear();
}

void solve() {
    clear();

    int k; std::cin >> k;
    for (int i = 0; i < k; i++) {
        int bits; std::cin >> bits;
        var_bits[i].resize(bits);
    }

    std::string r1, r2;
    {
        int length;
        std::cin >> length >> r1;
        std::cin >> length >> r2;
    }

    // iterator po tokenach rownania
    int r1_itr = 0, r2_itr = 0;

    // iterator po zmiennych
    int r1_b_itr = 0, r2_b_itr = 0;

    auto get_next_bit_node = [](
        const std::string& r,
        int& r_itr,
        int& r_b_itr
    ) {
        // wez noda z r1 rownania
        node* result;

        if (r[r_itr] == '0' || r [r_itr] == '1') {
            result = (r[r_itr] == '0' ? &bit_0_node : &bit_1_node);
            r_itr++;
        }
        else {
            int var_id = (r[r_itr] - 'a');
            result = &var_bits[var_id][r_b_itr];
            r_b_itr++; 

            // if we reached var end
            if (r_b_itr == var_bits[var_id].size()) {
                r_b_itr = 0;
                r_itr++;
            }
        }

        return result;
    };

    // idziemy po kolejnych tokenach obu slow
    while (r1_itr != r1.size() && r2_itr != r2.size()) {
        // wez bity z obu rownan
        auto r1_n = get_next_bit_node(r1, r1_itr, r1_b_itr);
        auto r2_n = get_next_bit_node(r2, r2_itr, r2_b_itr);

        // polacz je
        r1_n->equal_nodes.insert(r2_n);
        r2_n->equal_nodes.insert(r1_n);
    }

    // rowania nie sa rownej dlugosci
    if (r1_itr != r1.size() || r2_itr != r2.size()) {
        std::cout << "0\n"; return;
    }

    // oznacz cala grupe polaczonych bitow jako odwiedzone
    auto visit_scc = [](node* begin) {
        std::vector<node*> q, nq;
        q.push_back(begin);

        while (q.size()) {
            for (auto v : q) {
                if (v->visited) continue;
                v->visited = true;

                for (auto u : v->equal_nodes) {
                    if (u->visited) continue;
                    nq.push_back(u);
                }
            }

            q.swap(nq);
            nq.clear();
        }
    };

    // oznaczamy obie te grupy jako odwiedzone
    visit_scc(&bit_0_node);

    // 0 i 1 sa w tej samej grupie, czyli rownanie jest sprzeczne i niemozliwe
    if (bit_1_node.visited) {
        std::cout << "0\n"; return;
    }

    visit_scc(&bit_1_node);

    // idz po zmiennych i badaj ile grup "wolnych" mamy
    int free_scc = 0;

    for (int i = 0; i < max_k; i++) {
        for (int j = 0; j < var_bits[i].size(); j++) {
            node* bit_node = &var_bits[i][j];
            if (bit_node->visited) continue;
            visit_scc(bit_node); free_scc++;
        }
    }

    // rozwiazaniem jest 2^free_scc jako iz kazdej
    // grupie mozemy przypisac albo 0 albo 1
    
    // mnozymy pisemnie, dodajac kolejne liczby nie z przodu, ale z tylu liczby
    // dla performance lepszego, potem odwrocimy

    std::string result = "1";
    while (free_scc--) {
        int cargo = 0;
        
        // kolejne cyfry wyniku, od tylu
        for (uint i = 0; i < result.size(); i++) {
            int val = (result[i] - '0');
            val *= 2;

            int next_cargo = (val >= 10 ? 1 : 0);
            if (next_cargo) val -= 10;

            result[i] = ('0' + val + cargo);
            cargo = next_cargo;
        }

        if (cargo) result.push_back('1');
    }

   std::reverse(result.begin(), result.end());
   std::cout << result << '\n';
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int x; std::cin >> x;
    while (x--) solve();
}
