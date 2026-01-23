#include <iostream>
#include <string>
#include <vector>
//#include <SFML/Graphics.hpp>
/*#include <memory>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <random>
#include <cstdlib>
#include <ctime>*/

using namespace std; using namespace sf;

string plikTerytoriow = "Terytoria.txt";
const int n=4;
string typSurowca[n] = {"żywność","ruda","mana","dowolny"};
string typPola[n] = {"pole","wzgórza","las","ruiny"};

//predeklaracja klas
class Gracz;
class Runda;
class Pionek;
class Terytorium;
class Region;

class Runda
{
public:
    unsigned int aktywny=0;
    bool budowa;
    bool badania;
    bool rozwoj;
    bool patrol;
    bool misja;
    bool handel;
    bool koniec;

    //procedury
    Runda(int akt)
    {

    }
    ~Runda(){}

    void zakoncz()
    {

    }
};


class Gracz
{
protected:
    string kolor;//zamiana na kolor typu pozycyjnego?
    string nazwa;

    //zasoby
    unsigned int zywnosc;//3
    unsigned int ruda;//1
    unsigned int mana;//2

    //stopnie rozwoju
    unsigned int poziomWiezy;
    unsigned int poziomMagii;
    //plansze
public:
    vector<Pionek>pionki;//Lub: zmiana na tablice statyczn¹ i poprostu dania nulla jako region i umieszczenia orzy rozwoju
    Terytorium *mojeTerytorium;
    //Pionek pionki[7];

    
//public:
    Gracz(string kol, string nazw)
    {
        kolor = kol;
        nazwa = nazw;
        poziomWiezy = 0;
        poziomMagii = 0;
        zywnosc = 3;
        ruda = 1;
        mana = 2;
        mojeTerytorium=nullptr;
    }
    ~Gracz(){}
    //surowce
    void setSurowceStartowe(unsigned int zywn, unsigned int rud, unsigned int man)
    {
        zywnosc = zywn;
        ruda = rud;
        mana = man;
    }
    void przyrostSurowcow()
    {

    }
    void handel()
    {

    }
    //rozwijanie ludu
    void budowa()
    {

    }
    void badania()
    {

    }
    void rozwoj()
    {

    }
    //ruch
    void patrol()
    {

    }
    void misja()
    {

    }
    Gracz wojna(Gracz wrog)//Gracz//bool//void
    {

    }
    int liczeniePktZwyc()
    {

    }
};



/*
class Terytoriumgrafika?

class Regiongrafika
{
    sf::CircleShape shape;
    sf::Vector2f position;
    bool selected = false;
};

class Pionekgrafika
{
    sf::RectangleShape shape;
    sf::Vector2f position;
    Node* current_node = nullptr;
};*/


class Terytorium
{
public:
    vector<Region> regiony;
    Gracz *posiadacz;

    Terytorium(Gracz* posiada, bool ustandaryzowane)
    {
        posiadacz=posiada;
        if(ustandaryzowane)
        {
            //terytorium z pojednym ka¿dego typu pola
            for (int i=0; i<=n; i++)
            {
                vector<int> s;
                for (int j=0; j<n; j++)
                {
                    if(j!=i)
                    {
                        s.push_back(j);
                    }
                }
                Region nowy(typPola[i],typSurowca[i],true,this,s);
                regiony.push_back(nowy);
            }
        }
        //przejście do wczytania w klasie gry
    }
    ~Terytorium(){}
    void wczytaj(string nazwaPliku, int pozycja, char formatPozycji)
    {
        //otwarcie i odczyt z pliku wszystkich regionów
    }
};

class Region
{
private:
    //wewnêtrzne cechy:
    string nazwa;
    bool przekraczalny;
    //grafika
public:
    string surowiec;
    //relacje
    Terytorium* wewnatrz;
    //vector <Region*> sasiednie;//alternatywa wskaŸnikowa
    vector <int> sasiednie;//alternatywa indeksowa
    vector <Pionek*> pionki;

    Region(string typ, string sur, bool przek, Terytorium* wew, vector <int> sas/*vector <*Region> sas*/)
    {
        nazwa=typ;
        surowiec=sur;//ew. zamiana by surowiec by³ zale¿ny od typu(nie implementowane w tej formie bo case nie dzia³a na stringi)
        //przekraczalny=true;//alternatywnie zamiast wersji z "przek"
        przekraczalny=przek;
        wewnatrz=wew;
        sasiednie=sas;
        //konwersja indeksów regionów na wskaŸniki.
        /*for (int i = 0; i < sas.size(); i++)
        {

        }*/
    }
    ~Region(){}

    string getNazwa() const
    {
        return nazwa;
    }
    string getSurowiec() const
    {
        return surowiec;
    }
};


//aspekt graficzny zintegrować potem w te same klasy(do konstruktorów pionka dodac okreslenie koloru na podstawie gracza), albo
class Pionek
{
public:
    Region *mojRegion;
    Gracz *posiadacz;
    bool stoi;

    Pionek(Gracz* posiada)
    {
        stoi=true;
        posiadacz=posiada;
    }
    Pionek(Gracz* posiada, Region* region)
    {
        stoi=true;
        posiadacz=posiada;
        mojRegion=region;
    }
    ~Pionek(){}

    void umieszczenie(Region* region)
    {
        mojRegion=region;
        //modyfikacje regionu
    }
    void przemieszczenie(Region* region)
    {
        //for()//warunek bycia s¹siadem obecnego regionu
        mojRegion=region;
        //modyfikacje regionów
    }
};


class Gra 
{
public:
    vector <Gracz> gracze;
    vector <Runda> rundy;
    int terytWPliku;

    Gra(bool nowa)
    {
        if (nowa)
        {
            cout<<"Czy chcesz zagrać z uproszczonymi terytoriami(T) zamiast pełnych(P)?";
            char odp;
            cin>>odp;
            int iluGraczy;
            string nazwa, kolor;
            cout<<"Podaj liczbę graczy(od 2 do 5): ";//liczby domyślne z normalnej gry
            cin>>iluGraczy;
            for (int i=0; i<iluGraczy; i++)
            {
                cout<<"Wprowadź nazwę i kolor gracza.";
                cout<<"Nazwa:";
                cin>>nazwa;
                cout<<"kolor(lista):";
                cin>>kolor;
                Gracz nowy(nazwa, kolor);
                Terytorium gracza(&nowy, (odp=='T'));//możliwa konieczność zmiany kolejności
                cout<<"\n "<<nazwa<<" możesz rozłożyć 6 surowców między żywność, rudę i manę, lub zachować rozłożenie domyślne:"<<
                "\nżywność = 3, ruda = 1, mana = 2,"<<
                "\nZ - zachowaj, R - rozłóż samemu";
                cin>>odp;
                if (odp!='Z')
                {
                    int z, m, r;
                    nowy.setSurowceStartowe(z,r,m);
                }
                gracze.push_back(nowy);
            }
        }
        else
        {
            string wczytywana;
            cout<<"Podaj nazwę wczytywanej gry(z rozszerzeniem): ";
            cin>>wczytywana;
            wczytaj(wczytywana);
        }
    }
    ~Gra()
    {
        //upewnij się czy wektory się same czyszczą
    }
    //koniec
    void zakoncz()
    {

    }
    vector <int> liczeniePktZwyc()
    {
        vector <int> wyniki;
        return wyniki;
    }
    //stan gry
    void wczytaj(string nazwaPliku)
    {

    }
    void pokaz()
    {

    }
    void zapisz()
    {

    }
};


int main()
{
    int odp=0;
    while(odp<4)
    {
        cout<<"\nOpcje:\n 1. Nowa gra. \n 2. Wczytaj Gre. \n 3. Zmień plik wczytania terytoriów(domyślnie: Terytoria.txt, obecnie: "<<plikTerytoriow<<"). \n 4. Zakończ.";
        cin>>odp;
        switch(odp)
        {
        case 1:
            {
            Gra gra(true);
            break;
            }
        case 2:
            {
            Gra gra(false);
            break;
            }
        case 3:
            {
            cout<<"Nowa nazwa pliku terytoriów(z rozszerzeniem): ";
            cin>>plikTerytoriow;
            break;
            }
        }
    }
    return 0;
}
