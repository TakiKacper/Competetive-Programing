#include <iostream>
#include <vector>

constexpr int limit = 200;

struct portfel {
    int m, s, z;
};

struct zasada {
    int m,  s,  z;
    int nm, ns, nz;
};

bool operator>=(const portfel& a, const portfel& b) {
    return a.m >= b.m && a.s >= b.s && a.z >= b.z;
}

void rozwiaz() {
    portfel alibaba, sezam;
    std::cin >> alibaba.m >> alibaba.s >> alibaba.z;
    std::cin >> sezam.m >> sezam.s >> sezam.z;

    zasada zas[11];
    int z; std::cin >> z;
    for (int i = 0; i < z; i++) {
        std::cin >> zas[i].m  >> zas[i].s  >> zas[i].z;
        std::cin >> zas[i].nm >> zas[i].ns >> zas[i].nz;
    }
    
    std::vector<portfel> q, nq;
    q.push_back(alibaba);

    if (alibaba >= sezam) {
        std::cout << 0 << '\n';
        return;
    }

    bool reached[limit][limit][limit];
    for (int m = 0; m < limit; m++) {
        for (int s = 0; s < limit; s++) {
            for (int z = 0; z < limit; z++) {
                reached[m][s][z] = false;
            }
        }
    }
    reached[alibaba.m][alibaba.s][alibaba.z] = true;

    int tura = 1;
    while (q.size()) {
        for (auto v : q) {
            for (int zi = 0; zi < z; zi++) {
                auto& za = zas[zi];
                portfel u;

                if (v.m < za.m || v.s < za.s || v.z < za.z) continue;

                u.m = v.m + zas[zi].nm - zas[zi].m;
                u.s = v.s + zas[zi].ns - zas[zi].s;
                u.z = v.z + zas[zi].nz - zas[zi].z;

                if (u.m >= limit || u.s >= limit || u.z >= limit) {
                    std::cout << "NIE\n";
                    return;
                }

                if (reached[u.m][u.s][u.z]) continue;

                if (u >= sezam) {
                    std::cout << tura << '\n';
                    return;
                }
                
                reached[u.m][u.s][u.z] = true;
                nq.push_back(u);
            }
        }

        tura++;
        q.swap(nq);
        nq.clear();
    }
 
    std::cout << "NIE\n";
}

int main() {
    std::cin.tie(0); std::ios_base::sync_with_stdio(0);
    int d; std::cin >> d;
    for (int i = 0; i < d; i++) rozwiaz();
}
