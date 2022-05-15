
#include <iostream>
#include <vector> //STL Vektorok

using namespace std;

class Graf { //gr�f oszt�ly vektorokkal megval�s�tva.
    vector<int> v_; //pontok
    vector<pair<int,int>> e_; //�lek 
public:
    Graf(vector<int> &v, vector<pair<int, int>> &e): v_(v), e_(e){} //konstruktor
    void EulerUt(); //van-e euler �t: 0 vagy 2 db p�ratlan foksz�m� cs�cs, VAGY az �sszes cs�cs p�ros foksz�m�
    void elHozzaad( int v, int w);
    void csucsHozzaad(int v);
    void csucsTorol(int v);
    friend ostream& operator<<(ostream& s, const Graf& c); //gr�f ki�rat�sa oper�tor t�lterhel�ssel
};

void Graf::csucsTorol(int v) //cs�cs t�rl�se �lekkel egy�tt
{
    vector<int>::iterator it = find(v_.begin(), v_.end(), v);
    if (it != v_.end())
    {
        cout << "Csucs megtalalva: " << v << " itt: " << it - v_.begin() << endl;
        v_.erase(it);
        cout << "Csucs torolve!" << endl;
        for (const pair<int, int> el : e_) //ha a cs�csot t�r�lj�k, akkor az �leit is t�r�lni kell.
        {
            if (el.first == v || el.second == v) {
                vector<pair<int, int>>::iterator it = find(e_.begin(), e_.end(), el); //ha b�rmely �l tartalmazza a t�r�lt pontot, akkor megkeress�k hol van az �l
                if (it != e_.end()) {
                    e_.erase(it); //majd kit�r�lj�k
                    cout << v << " .szamu csucs elei torolve " << endl;
                }
                
            }
        }

    }
    else {
        cout << "Csucs nem letezik a grafban" << endl;
    }
        
}

void Graf::csucsHozzaad(int v)//cs�cs hozz�ad�sa tesztel�shez
{
    v_.push_back(v);
    cout << v << " csucs hozzaadva" << endl;
}

//Az oper�tor rendre minden cs�csra ki�rja mely m�sik cs�csokkal vannak �sszek�tve.

ostream& operator<<(ostream& s, const Graf& c) //kiirat� oper�tor
{
    cout << "A graf jelenlegi allapota: " << endl;
    for (auto v : c.v_) {
        s << v << ": ";
        for (auto e : c.e_) {
            if (e.first == v){
                s << e.second << ",";
            }
            else if(e.second == v) {
                s << e.first << ",";
            }
        }
        cout << endl;
    }
    return s;
}

void Graf::elHozzaad(int v, int w) //�l hozz�ad�sa tesztel�shez
{
    e_.push_back({ v, w });
    cout << v<< "," << w << " el hozzaadva" << endl;
}

void Graf::EulerUt()
{
    vector<int> fokszam(v_.size()); //Cs�csok elemsz�m�val megegyez� hossz�s�g� vektor
    for (auto e : e_) { //�lek bej�r�sa
        fokszam[e.first]++;
        fokszam[e.second]++;
    }
    int paratlanFokszam = 0;
    for (auto d : fokszam) {
        if (d % 2 == 1) {
            paratlanFokszam++;
        }
    }
    if(paratlanFokszam == 0 || paratlanFokszam == 2) {
        cout << "Talalhato a grafban Euler-ut " << endl;
    }
    else {
        cout << "Nem talalhato a grafban Euler-ut " << endl;
    }
}


int main()
{
    vector <int> v = { 0,1,2,3,4 }; //pontok inicializ�l�sa
    vector<pair<int, int>> e = { {0,3},{1,2},{1,4} }; //�lek inicializ�l�sa 
    Graf G(v, e);

    /*
    Fontos inform�ci� : Cs�csok �s �lek hozz�ad�sakor figyelni kell a sz�mokra.Pl. : 10 - es cs�cs hozz�ad�sakor nem tudunk �leket l�trehozni, ...
    ...ha a legnagyobb sz�m� cs�cs mondjuk 5. Sajnos hozz�ad�skor figyelni kell arra, hogy milyen sz�mokkal jel�lj�k a cs�csokat.
    ha erre nem figyel�nk, akkor "expression vector subscript out of range" hib�t fog adni a program.
    */

    cout << G; 
    G.csucsHozzaad(5);
    G.EulerUt();
    G.elHozzaad(1, 5);
    G.EulerUt();
    G.csucsTorol(5);
    G.EulerUt();
    G.elHozzaad(2, 4);
    cout << G;
    G.EulerUt(); //van -e euler �tja/vonala a gr�fnak
}
