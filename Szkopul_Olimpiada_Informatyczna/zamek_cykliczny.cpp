#include <bits/stdc++.h>

std::string str;
std::vector<uint8_t> liczba;
std::unordered_map<uint8_t, int> ilosci_cyfr;

void zaladuj()
{
    str.reserve(1000000);
    std::getline(std::cin, str);

    liczba.reserve(str.size());

    for (int i = 0; i <= 9; i++)
    {
        ilosci_cyfr.insert({i, 0});
    }

    for (auto& c : str)
    {
        ilosci_cyfr.at(c - '0')++;
        liczba.push_back(c - '0');
    }     
}

int main()
{
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(0);

    zaladuj();

    if (str == "1")
    {
        std::cout << 0;
        return 0;
    }

    if (ilosci_cyfr.at(1) == 1 && ilosci_cyfr.at(0) == (str.size() - 1))
    {
        std::cout << 1;
        return 0;
    }

    if (liczba.size() == 1)
    {
        std::cout << 10 - liczba.at(0) + 1;
        return 0;
    }

    if (ilosci_cyfr.at(9) == str.size())
    {
        std::cout << 2;
        return 0;
    }

    std::vector<uint64_t> przenoszenia_koszty;  //Koszt przenoszenia wartosci az do danego indeksu
                                                //Startujac od konca idac do poczatku
    przenoszenia_koszty.reserve(liczba.size());

    uint64_t koszt = 0;
    uint64_t odroczony_kosz_9 = 0;

    for (int i = 0; i < liczba.size(); i++)
    {
        if (liczba.at(i) == 9)
            odroczony_kosz_9++;
        else if (liczba.at(i) != 0)
        {
            koszt += (9 - liczba.at(i) + 1) + odroczony_kosz_9;
            odroczony_kosz_9 = 0;
        }
        else if (liczba.at(i) == 0)
        {
            koszt += odroczony_kosz_9;
            odroczony_kosz_9 = 0;
        }

        przenoszenia_koszty.push_back(koszt);
    }

    std::vector<bool> skonczony_zerem;
    skonczony_zerem.reserve(liczba.size());
    
    std::vector<uint64_t> zapchania_koszty;
    zapchania_koszty.reserve(liczba.size());

    //Poza petla obliczymy pierwszy element by móc używać back
    zapchania_koszty.push_back((9 - liczba.at(liczba.size() - 1)) * std::pow(10, 0));

    for (int i = liczba.size() - 2; i != -1; i--)
    {
        int rzad = liczba.size() - 1 - i;

        if (rzad >= 10)
        {
            zapchania_koszty.push_back(UINT64_MAX);
        }
        else
        {
            uint64_t poprzedni = zapchania_koszty.back();
            zapchania_koszty.push_back(poprzedni + (9 - liczba.at(i)) * std::pow(10, rzad));
        }
    }

    uint64_t minimum = UINT64_MAX;
    koszt = 0;

    for (int i = 0; i < liczba.size() - 1; i++)
    {
        if (zapchania_koszty.at(i) == UINT64_MAX)
            break;

        koszt = zapchania_koszty.at(i) + przenoszenia_koszty.at(przenoszenia_koszty.size() - 2 - i);

        if (koszt < minimum)
            minimum = koszt; 
    }

    //Mozna tez przeniesc wszystkie
    if (minimum > przenoszenia_koszty.back())
        minimum = przenoszenia_koszty.back();

    std::cout << minimum + 2;
    return 0;
}
