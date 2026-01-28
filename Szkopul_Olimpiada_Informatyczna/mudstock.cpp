#include <iostream>
#include <vector>

// koszt punktu = wszyskie galezie do stolicy + stolica do punktu + za punktem

unsigned long long opt       = __INT_MAX__;
unsigned long long opt_linia = __INT_MAX__;
unsigned long long opt_osada = __INT_MAX__;

void odpowiedz(unsigned long long _opt, unsigned long long _linia, unsigned long long _osada) {
    if (opt > _opt) {
        opt       = _opt;
        opt_linia = _linia;
        opt_osada = _osada;
    }
}

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);
    
    unsigned long long l, m; std::cin >> l >> m;

    // first  -> dystans
    // second -> osoby
    std::vector<std::vector<std::pair<unsigned long long, unsigned long long>>> linie;

    for (unsigned long long i = 0; i < l; i++) {
        unsigned long long a; std::cin >> a;
        std::vector<std::pair<unsigned long long, unsigned long long>> linia(a);

        for (unsigned long long i = 0; i < a; i++) {
            std::cin >> linia[i].first >> linia[i].second;
        }

        linie.push_back(std::move(linia));
    }

    // [linia] [0]   -> cala galaz
    // [linia] [max] -> 0
    unsigned long long wszystkie_osoby = m;

    std::vector<std::vector<unsigned long long>> koszt_cofania_na_galezi;
    std::vector<unsigned long long>              osoby_na_galezi;

    for (auto& linia : linie) {
        unsigned long long osoby = 0;
        unsigned long long wynik = 0;

        auto result = std::vector<unsigned long long>(linia.size() + 1);

        for (unsigned long long i = result.size() - 1;; i--) {
            result[i] = wynik;

            if (i == 0) break;

            osoby += linia[i - 1].second;
            wynik += (osoby * linia[i - 1].first);
        }

        koszt_cofania_na_galezi.push_back(std::move(result));
        osoby_na_galezi.push_back(osoby);

        wszystkie_osoby += osoby;
    }

    // przypadek stolicy
    unsigned long long suma_na_stolicy = 0;
    {
        for (auto& k : koszt_cofania_na_galezi) suma_na_stolicy += k[0];
        odpowiedz(suma_na_stolicy, 0, 0);
    }

    // przypadki na galeziach
    for (unsigned long long i = 0; i < linie.size(); i++) {
        auto& linia = linie[i];

        unsigned long long wynik_zciagania = suma_na_stolicy - koszt_cofania_na_galezi[i][0];
        unsigned long long osoby_przed     = wszystkie_osoby - osoby_na_galezi[i];

        for (unsigned long long j = 1; j < koszt_cofania_na_galezi[i].size(); j++) {
            wynik_zciagania += osoby_przed * linia[j - 1].first;

            unsigned long long wynik_punktu = wynik_zciagania + koszt_cofania_na_galezi[i][j];
            odpowiedz(wynik_punktu, i + 1, j);

            osoby_przed += linia[j - 1].second;
        }
    }

    std::cout << opt << '\n';
    std::cout << opt_linia << ' ' << opt_osada << '\n';

    return 0;
}
