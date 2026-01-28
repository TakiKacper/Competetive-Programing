#include <iostream>
#include <vector>
#include <set>

constexpr int max_n_m = 10e6;

// ilosc klockow, ilosc stosow
int n, m;

// indeks stosu na ktorym klocek sie znajduje
int stos_klocka[max_n_m];

// stos na ktorym konstruujemy wieże
int stos_docelowy = -1;

// dlugosci stosow
std::vector<int> dlugosci;

// zkad, dokad
std::vector<std::pair<int, int>> ruchy;

// wartosc wierzchu, indeks stosu
std::vector<std::pair<int, int>> wierzchy;

struct sort_spodow_indeksow {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        return a.first > b.first;
    }
};

// wartosc spodu, indeks stosu
std::set<std::pair<int, int>, sort_spodow_indeksow> spody;

void laduj() {
    std::cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a; std::cin >> a;
        std::vector<int> stos(a);
        
        dlugosci.push_back(a);

        for (int j = 0; j < a; j++) {
            int klocek; std::cin >> klocek; klocek--;
            stos[j]             = klocek;
            stos_klocka[klocek] = i;
        }

        // stos jest pusty i nie ma jeszcze docelowego
        if (a == 0 && stos_docelowy == -1) {
            stos_docelowy = i;
        }
        // stos niepusty i ciagly od 0 do n - 1
        else if (a != 0 && stos.front() == 0 && stos.back() == stos.size() - 1) {
            stos_docelowy = i;
        }
        // stos niepusty, i nie ciagly
        else if (a != 0) {
            wierzchy.push_back({stos.front(), i});
            spody.insert({stos.back(), i});
        }   
    }
}

void zbuduj_pusty_stos() {
    int stos_zabierania   = -1;
    int stos_przekladania = -1;

    // lecimy po stosach
    for (auto& w : wierzchy) {
        // ten stos ma wieksza lub taka sama dlugosc co juz odkryty
        // nie bedzie juz optymalny, lub zamiana na niego jest zbedna
        if (stos_zabierania != -1 && dlugosci[w.second] >= dlugosci[stos_zabierania]) continue;

        // szukamy pierwszego takiego innego stosu
        // ktorego spod < wierch stosu
        auto itr = spody.lower_bound({w.first, -1}); 

        // jezeli to ten sam stos to przesun dalej (zdarza sie dla zbiorow jedno-elementowych, bo lower_bound to <= a nie <)
        if (itr != spody.end() && itr->second == w.second) itr++;
        
        // nie ma takiego
        if (itr == spody.end()) continue;

        // mamy gdzie przeniesc i bedzie to optymalne!
        stos_zabierania   = w.second;
        stos_przekladania = itr->second;
    }

    // lecimy po klockach i przekladamy
    if (stos_zabierania != -1) {
        std::pair<int, int> ruch = {stos_zabierania + 1, stos_przekladania + 1};

        for (int i = 0; i < n; i++) {
            if (stos_klocka[i] == stos_zabierania) {
                stos_klocka[i] = stos_przekladania;
                ruchy.push_back(ruch);
            }
        }
        
        // czysto -> mozna budowac!
        stos_docelowy = stos_zabierania;
    }
}

void rozwiaz() {
    for (int i = 0; i < n; i++) {
        int z = stos_klocka[i] + 1;
        int d = stos_docelowy + 1;
        if (z != d) ruchy.push_back({stos_klocka[i] + 1, stos_docelowy + 1});
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    laduj();

    if (stos_docelowy == -1) zbuduj_pusty_stos();

    if (stos_docelowy == -1) {
        std::cout << "-1";
        return 0;
    }

    rozwiaz();

    std::cout << ruchy.size() << '\n';
    for (auto& r : ruchy) std::cout << r.first << ' ' << r.second << '\n';
}
