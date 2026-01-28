#include <iostream>
#include <vector>

struct stan {
    int w[4];
};

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int n; std::cin >> n;

    stan pojemnosci;
    for (int i = 0; i < n; i++) std::cin >> pojemnosci.w[i];

    stan init = pojemnosci;
    stan koniec;
    for (int i = 0; i < n; i++) std::cin >> koniec.w[i];

    bool reached[50][50][50][50];
    reached[pojemnosci.w[0]][pojemnosci.w[1]][pojemnosci.w[2]][pojemnosci.w[3]] = true;

    std::vector<stan> q, nq;
    q.push_back(init);

    int tura = 0;

    while (q.size()) {
        for (stan v : q) {
            // czy to odpowiedz?
            bool takie_same = true;
            for (int i = 0; i < n; i++) takie_same &= (v.w[i] == koniec.w[i]);
            if (takie_same) {
                std::cout << tura;
                return 0;
            }

            // wszystkie mozliwe przelania
            // przelewamy z a do b
            for (int a = 0; a < n; a++) {
                for (int b = 0; b < n; b++) {
                    if (a == b) continue;
                    
                    stan u = v;
                    int suma = u.w[a] + u.w[b];
                    u.w[b] = std::min(pojemnosci.w[b], suma);
                    u.w[a] = suma - u.w[b];

                    auto& r = reached[u.w[0]][u.w[1]][u.w[2]][u.w[3]];
                    if (r) continue;
                    r = true;

                    nq.push_back(u);
                }
            }

            // wylanie do zlewu
            for (int i = 0; i < n; i++) {
                stan u = v;
                u.w[i] = 0;

                auto& r = reached[u.w[0]][u.w[1]][u.w[2]][u.w[3]];
                if (r) continue;
                r = true;

                nq.push_back(u);
            }
        }

        tura++;

        q.swap(nq);
        nq.clear();
    }

    std::cout << "NIE";
}
