#include <iostream>

using ll = long long;

ll flappy_x     = 0;
ll flappy_y     = 0;
ll flappy_y_add = 0;

ll cost = 0;

int main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    ll n, m; std::cin >> n >> m;

    while (n--) {
        ll x, lower_bound, higher_bound; std::cin >> x >> lower_bound >> higher_bound;

        // zaokraglamy yl i yh do siatki flappy birda
        // narysuj sobie wszystkie mozliwe ruchy flappy birda w 4 turach zeby zrozumiec o co chodzi
        if (x % 2 == 0) {   // przeszkoda parzysta, mozemy byc w parzystych wysokosciach
            lower_bound  += (lower_bound  % 2 ? 1 : 2);
            higher_bound -= (higher_bound % 2 ? 1 : 2);
        }
        else {              // przeszkoda nieparzysta, mozemy byc w nieparzystych wysokosciach
            lower_bound  += (lower_bound  % 2 == 0 ? 1 : 2);
            higher_bound -= (higher_bound % 2 == 0 ? 1 : 2);
        }

        // nie mozliwa przeszkoda, nie do przekroczenia po przylozeniu siatki
        if (lower_bound > higher_bound) {
            std::cout << "NIE";
            return 0;
        }

        // obecnie jestesmy na zakresie [wysokosc, wysokosc + luz]
        // z tego zakresu chcemy pojsc do mozliwie najmniejszego y [lower_bound, higher_bound]

        // taki dystans miedzy przeszkodami, tyle mozemy maksymalnie wzrosnac i spasc
        ll dx = x - flappy_x;

        // obliczamy zakres mozliwych pozycji
        ll lowest  = flappy_y - dx;
        ll highest = flappy_y + flappy_y_add + dx;

        // jestesmy za wysoko zeby mozliwe bylo spadniecie do przeszkody
        if (lowest > higher_bound) {
            std::cout << "NIE";
            return 0;
        }

        // jestesmy za nisko zeby mozliwe bylo wzlecenie do przeszkody
        if (highest < lower_bound) {
            std::cout << "NIE";
            return 0;
        }

        // ograniczamy zakres do granicy przeszkody
        lowest  = std::max(lowest, lower_bound);
        highest = std::min(highest, higher_bound);

        // tutaj dodaj rozmijki: gdy boundy wyzej niz highest i gdy boundy nizej niz lowest

        // nie wiem co musialo by sie dziac zeby to wypalilo
        // ale na wszelki wypadek
        if (lowest > highest) {
            std::cout << "NIE";
            return 0;
        }

        // zakres [lowest, highest] jest teraz poprawnym zakresem w nowej przeszkodzie
        // pozostaje naliczyc koszt i go zaaplikowac
        // koszt = (dx + dy) / 2, z teorii ruchow flappy birda
        // zakladamy ze idziemy do najnizszej pozycji i dla niej to liczymy dy

        ll dy; // szukana

        // przypadek 0: podtrzymujemy wysokosc
        if (flappy_y == lowest) {
            dy = 0;
        }
        // przypadek 1: spadamy
        if (flappy_y > lowest) {
            dy = (lowest - flappy_y);
        }
        // przypadek 2: wzlatujemy
        else {
            // z jakiego Y statujemy?
            // niekoniecznie z flappy_y - to moze byc za nisko
            // ale sprobojmy i zobaczmy ile brakuje
            ll missing_y = std::max(0ll, lower_bound - (flappy_y + dx));

            // nie wyda, nie podlecimy tyle
            if (missing_y > flappy_y_add) {
                std::cout << "NIE";
                return 0;
            }

            // lecimy z podwyższenia
            dy = (lowest - (flappy_y + missing_y));

            // ale za nie trzeba zaplacic niestety
            cost += (missing_y / 2);
        }

        // aplikujemy przeszkode
        cost         += (dx + dy) / 2;
        flappy_y_add =  highest - lowest;
        flappy_x     =  x;
        flappy_y     =  lowest;
    }

    std::cout << cost;
}
