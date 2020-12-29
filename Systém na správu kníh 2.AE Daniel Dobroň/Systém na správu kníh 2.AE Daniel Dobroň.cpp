// Systém na správu kníh 2.AE Daniel Dobroň.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <clocale>  
#include <list>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int kat, zan;

struct Kniha
{
    int id, kategoria, zaner;
    string nazov, popis;

    Kniha(int id, int kategoria, int zaner, string nazov, string popis)
    {
        this->id = id;
        this->kategoria = kategoria;
        this->zaner = zaner;
        this->nazov = nazov;
        this->popis = popis;
    }

};

string Kategorie[6] = { "Deti", "Študenti ", "Dospelí", "Pridať knihu", "Odstrániť knihu", "Uložiť knihy" };
string Zanre[3][3] = { {"Omaľovánky", "Rozprávky"}, {"Romány", "Detektívky", "Cestopisy"}, {"Priručky", "Novely", "Kuchárky"} };

list<Kniha> zoznam =
{
    Kniha(0, -1, 0, "Nič", "Len tak na vyplnenie kvôli zistovaniu id z predošlého záznamu :)") //Nikde sa nezobrazuje
};

void Ciara()
{
    cout << "-------------------------------------------------------------" << endl;
}

int Vstup(string otazka, int min = -1, int max = -1)
{
    string hodnota;
    int hodnotaInt;
    cout << otazka << " :" << endl;
    cin >> hodnota;
    try
    {
        hodnotaInt = stoi(hodnota);
    }
    catch (exception& err)
    {
        cout << "Nesprávny vstup !" << endl;
        return -2;
    }

    if (((min == -1 && max == -1) || (min <= hodnotaInt && max >= hodnotaInt)) && max != 0) return hodnotaInt;
    else return -1;
}

string VstupText(string otazka)
{
    string text;
    cout << otazka << " :" << endl;
    cin >> text;
    cout << endl << endl;

    return text;
}

int Zaner(int zaner)
{
    system("cls");
    cout << "---------------------------Menu:" << Kategorie[kat - 1] << "--------------------" << endl;
    for (int i = 1; i <= sizeof(Zanre[zaner - 1]) / sizeof(*Zanre[zaner - 1]); ++i)
    {
        if (Zanre[zaner - 1][i - 1] == "") break;
        cout << i << " " << Zanre[zaner - 1][i - 1] << endl;
    }

    Ciara();

    return Vstup("Vyber žáner", 0, sizeof(Zanre[zaner - 1]) / sizeof(*Zanre[zaner - 1]));
}

void Uloz()
{
    system("cls");
    string text = "";

    for (int i = 0; i < zoznam.size(); ++i)
    {
        list<Kniha>::iterator it = zoznam.begin();
        advance(it, i);
        Kniha kniha = *it;

        if (kniha.kategoria < 0) continue;

        string nazov = kniha.nazov;
        string popis = kniha.popis;
        replace(nazov.begin(), nazov.end(), ' ', '-');
        replace(popis.begin(), popis.end(), ' ', '-');

        text += to_string(kniha.kategoria) + " " + to_string(kniha.zaner) + " " + nazov + " " + popis + "\n";
    }

    ofstream subor;
    subor.open("knihy.txt");
    subor << text;
    subor.close();

    cout << "Uložené !" << endl;
}

void PridatKnihu(int kategoria, int zaner, string nazov, string popis)
{
    int id = zoznam.back().id + 1;
    zoznam.push_back(Kniha(id, kategoria, zaner, nazov, popis));
}

bool Over(int vstup)
{
    return vstup >= 0;
}

void NovaKniha()
{
    int kategoria = Vstup("Kategória") - 1;
    int zaner = Vstup("Žáner") - 1;
    string nazov = VstupText("Názov Knihy (Medzery píš pomocou -)");
    string popis = VstupText("Popis knihy (Medzery píš pomocou -)");

    if (Over(kategoria) && Over(zaner))
    {
        replace(nazov.begin(), nazov.end(), '-', ' ');
        replace(popis.begin(), popis.end(), '-', ' ');
        PridatKnihu(kategoria, zaner, nazov, popis);
    }
    else cout << "Nesprávna kategória alebo žáner" << endl;
}

void OdobratKnihu()
{
    int id = Vstup("Zadaj ID knihy");
    bool naslo = false;
    for (int i = 0; i < zoznam.size(); ++i)
    {
        list<Kniha>::iterator it = zoznam.begin();
        advance(it, i);
        Kniha kniha = *it;

        if (kniha.id == id)
        {
            zoznam.erase(it);
            cout << "Kniha odstránená !" << endl;
            naslo = true;
            break;
        }
        else continue;
    }
    if (!naslo) cout << "Kniha neexistuje !" << endl;
}

void Knihy()
{
    int max = sizeof(Kategorie) / sizeof(*Kategorie);
    kat = Vstup("Vyber vekovú kategóriu", 0, max);
    switch (kat)
    {
    case -2:
        return;
    case -1:
        cout << "Nesprávna kategória" << endl;
        return;
    default:
        break;
    }

    if (kat == max)
    {
        Uloz();
        return;
    }
    else if (kat == max - 1)
    {
        OdobratKnihu();
        return;
    }
    else if (kat == max - 2)
    {
        NovaKniha();
        return;
    }

    zan = Zaner(kat);
    switch (zan)
    {
    case -1:
        cout << "Nesprávny žáner" << endl;
        return;
    case -2:
        return;
    default:
        break;
    }

    for (int i = 0; i < zoznam.size(); ++i)
    {
        list<Kniha>::iterator it = zoznam.begin();
        advance(it, i);
        Kniha kniha = *it;

        if (kniha.kategoria == kat - 1 && kniha.zaner == zan - 1)
        {
            cout << "[ID:" << kniha.id << "] " << kniha.nazov << " - " << kniha.popis << endl;
        }
        else continue;
    }
}


void Sprava()
{
    cout << "---------------------Systém na správu kníh-------------------" << endl;
    cout << "----------------------------Menu-----------------------------" << endl;
    cout << "Keď pridáš knihu nezabudni ju uložiť!" << endl;
    cout << "Keď odoberieš knihu nezabudni uložiť program!" << endl;
    cout << "Pre Deti (žáner) : 1-Omaľovánky,2-Rozprávky " << endl;
    cout << "Pre Študentov (žáner) : 1-Romány, 2-Detektívky, 3-Cestopisy" << endl;
    cout << "Pre Dospelých (žáner) : 1-Príručky, 2-Novely, 3-Kuchárky" << endl;
    cout << "Vekové kategórie sú pod 1,2,3; Úprava pod 4,5; Uloženie pod 6." << endl;
    for (int i = 1; i <= sizeof(Kategorie) / sizeof(*Kategorie); ++i)
    {
        cout << i << " " << Kategorie[i - 1] << endl;
    }
    Ciara();
    Knihy();
    if (Vstup("Chcete pokračovať ? (0-nie, 1-ano)", 0, 1) == 1) Sprava();
}


void NacitajKnihy()
{
    int i = 0;
    vector<string> zozn;
    string riadok;
    ifstream subor("knihy.txt");
    if (subor.is_open())
        while (getline(subor, riadok))
        {
            istringstream iss(riadok);

            while (iss)
            {
                string prvok;
                iss >> prvok;
                if (prvok == "") break;
                replace(prvok.begin(), prvok.end(), '-', ' ');
                zozn.push_back(prvok);
                ++i;
            }
        }
    subor.close();

    for (int i = 1; i <= ((zozn.size()) / 4); ++i)
    {
        zoznam.push_back(Kniha(i, stoi(zozn[(i * 4) - 4]), stoi(zozn[(i * 4) - 3]), zozn[(i * 4) - 2], zozn[(i * 4) - 1]));
    }
}

int main()
{
    std::setlocale(LC_ALL, "");

    NacitajKnihy();
    Sprava();
}
/*
Použité zadané kritéria:
Cyklus
Štruktúra
Práca s poľom
Pointre
Rekurzia
Unárny operátor
switch
pretypovanie
Načítanie vstupu zo súboru
Uloženie výstupu do súboru

Navyše:
List
Konštruktor v štruktúre
Try Catch
*/