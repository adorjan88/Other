
#include <iostream>
#include <vector> //STL Vektorok

using namespace std;

class Graf { //gráf osztály vektorokkal megvalósítva.
    vector<int> v_; //pontok
    vector<pair<int,int>> e_; //élek 
public:
    Graf(vector<int> &v, vector<pair<int, int>> &e): v_(v), e_(e){} //konstruktor
    void EulerUt(); //van-e euler út: 0 vagy 2 db páratlan fokszámú csúcs, VAGY az összes csúcs páros fokszámú
    void elHozzaad( int v, int w);
    void csucsHozzaad(int v);
    void csucsTorol(int v);
    friend ostream& operator<<(ostream& s, const Graf& c); //gráf kiíratása operátor túlterheléssel
};

void Graf::csucsTorol(int v) //csúcs törlése élekkel együtt
{
    vector<int>::iterator it = find(v_.begin(), v_.end(), v);
    if (it != v_.end())
    {
        cout << "Csucs megtalalva: " << v << " itt: " << it - v_.begin() << endl;
        v_.erase(it);
        cout << "Csucs torolve!" << endl;
        for (const pair<int, int> el : e_) //ha a csúcsot töröljük, akkor az éleit is törölni kell.
        {
            if (el.first == v || el.second == v) {
                vector<pair<int, int>>::iterator it = find(e_.begin(), e_.end(), el); //ha bármely él tartalmazza a törölt pontot, akkor megkeressük hol van az él
                if (it != e_.end()) {
                    e_.erase(it); //majd kitöröljük
                    cout << v << " .szamu csucs elei torolve " << endl;
                }
                
            }
        }

    }
    else {
        cout << "Csucs nem letezik a grafban" << endl;
    }
        
}

void Graf::csucsHozzaad(int v)//csúcs hozzáadása teszteléshez
{
    v_.push_back(v);
    cout << v << " csucs hozzaadva" << endl;
}

//Az operátor rendre minden csúcsra kiírja mely másik csúcsokkal vannak összekötve.

ostream& operator<<(ostream& s, const Graf& c) //kiirató operátor
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

void Graf::elHozzaad(int v, int w) //él hozzáadása teszteléshez
{
    e_.push_back({ v, w });
    cout << v<< "," << w << " el hozzaadva" << endl;
}

void Graf::EulerUt()
{
    vector<int> fokszam(v_.size()); //Csúcsok elemszámával megegyezõ hosszúságú vektor
    for (auto e : e_) { //élek bejárása
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
    vector <int> v = { 0,1,2,3,4 }; //pontok inicializálása
    vector<pair<int, int>> e = { {0,3},{1,2},{1,4} }; //élek inicializálása 
    Graf G(v, e);

    /*
    Fontos információ : Csúcsok és élek hozzáadásakor figyelni kell a számokra.Pl. : 10 - es csúcs hozzáadásakor nem tudunk éleket létrehozni, ...
    ...ha a legnagyobb számú csúcs mondjuk 5. Sajnos hozzáadáskor figyelni kell arra, hogy milyen számokkal jelöljük a csúcsokat.
    ha erre nem figyelünk, akkor "expression vector subscript out of range" hibát fog adni a program.
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
    G.EulerUt(); //van -e euler útja/vonala a gráfnak
}
