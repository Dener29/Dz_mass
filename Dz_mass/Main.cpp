#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>

const int KOL_SAMOLETOV = 2;
const int KOL_GRUPP_VESA = 3;

const double obemBaka[KOL_SAMOLETOV] = { 300, 1000 };
const double predelVesa[KOL_SAMOLETOV][KOL_GRUPP_VESA] = {
    {750, 1500, 2000},
    {1000, 2000, 3000}
};
const double rashod[KOL_SAMOLETOV][KOL_GRUPP_VESA] = {
    {1, 4, 7},
    {2, 4, 6}
};
const double dopBak = 100;

double rashodTopliva(int samolet, double ves)
{
    for (int i = 0; i < KOL_GRUPP_VESA; i++) {
        if (ves <= predelVesa[samolet][i]) {
            return rashod[samolet][i];
        }
    }
    return -1;
}

double toplivoDlyaDozapravki(int samolet, double rasstAB, double rasstBC, double ves)
{
    double rashodNaKm = rashodTopliva(samolet, ves);
    if (rashodNaKm < 0) {
        return -1;
    }

    double osnovnoyBak = obemBaka[samolet];

    double toplivoAB = rashodNaKm * rasstAB;
    if (toplivoAB > osnovnoyBak + dopBak) {
        return -1;
    }

    double ostatokDop = 0;
    double ostatokOsn = osnovnoyBak;
    if (toplivoAB <= dopBak) {
        ostatokDop = dopBak - toplivoAB;
    }
    else {
        ostatokOsn = osnovnoyBak - (toplivoAB - dopBak);
    }

    double toplivoBC = rashodNaKm * rasstBC;
    if (toplivoBC - ostatokDop > osnovnoyBak) {
        return -1;
    }

    double dozapravka = toplivoBC - ostatokDop - ostatokOsn;
    if (dozapravka < 0) {
        return 0;
    }
    return dozapravka;
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0));

    int nomer;
    std::cout << "Выберите самолет (1 или 2): ";
    std::cin >> nomer;
    if (nomer < 1 || nomer > KOL_SAMOLETOV) {
        std::cout << "Такого самолета нет\n";
        return 1;
    }

    double rasstAB, rasstBC, ves;
    std::cout << "Введите расстояние между A и B (км): ";
    std::cin >> rasstAB;
    std::cout << "Введите расстояние между B и C (км): ";
    std::cin >> rasstBC;
    std::cout << "Введите вес груза (кг): ";
    std::cin >> ves;
    if (rasstAB < 0 || rasstBC < 0 || ves < 0) {
        std::cout << "Значения не могут быть отрицательными\n";
        return 1;
    }

    double dozapravka = toplivoDlyaDozapravki(nomer - 1, rasstAB, rasstBC, ves);
    if (dozapravka < 0) {
        std::cout << "Полет невозможен\n";
    }
    else {
        std::cout << "Нужно дозаправить в пункте B: " << dozapravka << " л\n";
    }

    return 0;
}