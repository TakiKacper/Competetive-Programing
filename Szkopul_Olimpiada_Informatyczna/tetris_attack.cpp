#include <iostream>
#include <vector>
#include <stack>

// idziemy od dolu, tak dlugo jak kolory sa unikalne
// jezeli gosc nie jest unikalny sciagamy go na dol
// 

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    int n; std::cin >> n;

    std::stack<int> RS;
    std::stack<int> S;

    for (int i = 0; i < 2 * n; i++) {
        int x; std::cin >> x;
        RS.push(x);
    }

    while (RS.size()) { S.push(RS.top()); RS.pop(); }

    std::vector<int> ZR(n + 1); // rejestr zdjetych
    std::stack<int>  Z;         // zdjete elementy z S, wiec od dolu do gory

    std::vector<int> M; // ruchy

    while (S.size()) {
        int t = S.top(); S.pop();
        
        // kolejny unikalny
        if (ZR[t] == false) {
            ZR[t] = true;
            Z.push(t);
            continue;
        }
        // nie unikalny
        else {
            int p = Z.size();
            int o = Z.top(); Z.pop();

            ZR[o] = false;
            
            if (o != t) {
                M.push_back(p);
                S.push(o); S.push(t);
            }
        }
    }

    std::cout << M.size() << '\n';
    for (auto m : M) std::cout << m << '\n';
}
