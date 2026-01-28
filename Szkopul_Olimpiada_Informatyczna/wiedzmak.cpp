#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

using miecze = uint16_t;

constexpr int max_n = 200;
constexpr int max_m = 3000;
constexpr int max_p = 13;
constexpr int max_k = max_n;

constexpr uint16_t wszystkie_kombinacje_mieczy = 8192 * 2;

int n, m, p, k;

struct krawedz {
    int    u; // cel  krawedzi
    int    w; // waga krawedzi
    miecze p; // potwory na krawedzi
};

std::vector<krawedz> adj[max_n];
miecze               kow[max_n]; // kowale w wierzcholku

// czy zbior a jest taki sam, badz wiekszy od b
inline bool zbior_mieczy_lepszy_badz_rowny(miecze a, miecze b) noexcept {
    return (a == b) || (a - (a & b));
}

inline void ulepsz_zbior_kowal(miecze& z, miecze kowal) noexcept {
    z |= kowal;
}

inline void ulepsz_zbior_typ(miecze& z, uint16_t numer_typu_potwora) {
    z |= (1 << numer_typu_potwora);
}

inline bool czy_zbior_podola(miecze z, miecze p) noexcept {
    return (p - (z & p) == 0);
}

void laduj_dane() {
    std::cin >> n >> m >> p >> k;

    // zaladuj kowali
    for (int i = 0; i < k; i++) {
        int x0; std::cin >> x0; x0--;
        miecze& kowal = kow[x0];

        int a; std::cin >> a;
        for (int j = 0; j < a; j++) {
            uint16_t typ; std::cin >> typ;
            ulepsz_zbior_typ(kowal, typ);
        }
    }

    // zaladuj graf
    for (int i = 0; i < m; i++) {
        krawedz krw;

        int x0, x1; std::cin >> x0 >> x1; x0--; x1--;
        std::cin >> krw.w;

        miecze potwory = 0;
        int a; std::cin >> a;
        for (int j = 0; j < a; j++) {
            uint16_t typ; std::cin >> typ;
            ulepsz_zbior_typ(potwory, typ);
        }

        krw.p = potwory;

        krw.u = x1;
        adj[x0].push_back(krw);

        krw.u = x0;
        adj[x1].push_back(krw);
    }
}

int wynik = -1;

struct thread {
    int    v; // pozycja
    miecze m; // niesione miecze
};

// obcinamy stany tablica
int czas[max_n][wszystkie_kombinacje_mieczy];

bool operator<(const thread& a, const thread& b) {
    return czas[a.v][a.m] >= czas[b.v][b.m]; // odwrotna implementacja, zeby kolejka wybierala najmniejszy czas
}

void djk() {
    std::priority_queue<thread> q;
    q.push({0, kow[0]});

    while (q.size()) {
        auto t = q.top(); q.pop();
        if (t.v == (n - 1)) {
            wynik = czas[t.v][t.m]; break;
        }

        for (auto krw : adj[t.v]) {
            // nie damy rady przejsc krawedzia
            if (!czy_zbior_podola(t.m, krw.p)) continue;

            // wepchnij nowa pozycje
            auto nt = t;
            nt.v =  krw.u;

            // ulepsz sie o tutejszych kowali
            ulepsz_zbior_kowal(nt.m, kow[nt.v]);

            // czy mamy lepszy czas?
            int poprzedni_czas = czas[nt.v][nt.m];
            int nowy_czas      = czas[t.v][t.m] + krw.w;

            // lepszy czas, wpychamy stan
            if (poprzedni_czas == 0 || nowy_czas < poprzedni_czas) {
                czas[nt.v][nt.m] = nowy_czas;
                q.push(nt);
            }
        }
    }
}

int main() {
    std::cin.tie(0); 
    std::ios_base::sync_with_stdio(0);

    laduj_dane();

    if (n == 1) {
        std::cout << 0; 
        return 0;
    }

    djk();
    std::cout << wynik;
}
