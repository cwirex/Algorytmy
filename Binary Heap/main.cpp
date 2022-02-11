#include <iostream>
#include <queue>
using namespace std;

struct Osoba{
    int towarzyskosc;
    int numer_osoby;
};
Osoba* kopiec;
int index_ostatniego;

static int Ojciec(int index)
{
    return index/2;
}
static int LewySyn(int index)
{
    return 2*index;
}
static int PrawySyn(int index)
{
    return 2*index+1;
}

bool czy_Swap(int index_dziecka){
    if(kopiec[Ojciec(index_dziecka)].towarzyskosc < kopiec[index_dziecka].towarzyskosc)
        return true;
    if(kopiec[Ojciec(index_dziecka)].towarzyskosc == kopiec[index_dziecka].towarzyskosc) {
        if (kopiec[Ojciec(index_dziecka)].numer_osoby > kopiec[index_dziecka].numer_osoby)
            return true;
    }
    return false;
}

int lewy_czy_prawy(int index_ojca){
    if(kopiec[LewySyn(index_ojca)].towarzyskosc < kopiec[PrawySyn(index_ojca)].towarzyskosc)
        return PrawySyn(index_ojca);
    if(kopiec[LewySyn(index_ojca)].towarzyskosc == kopiec[PrawySyn(index_ojca)].towarzyskosc) {
        if (kopiec[LewySyn(index_ojca)].numer_osoby > kopiec[PrawySyn(index_ojca)].numer_osoby)
            return PrawySyn(index_ojca);
    }
    return LewySyn(index_ojca);
}

void Przesiewanie_w_dol(){
    int indeks_wstawionego = 1;
    int index_dziecka = 2;
    while(index_dziecka <= index_ostatniego){
        if(PrawySyn(indeks_wstawionego) <= index_ostatniego)
            index_dziecka = lewy_czy_prawy(indeks_wstawionego);
        if(!czy_Swap(index_dziecka))
            break;
        swap(kopiec[indeks_wstawionego], kopiec[index_dziecka]);
        indeks_wstawionego = index_dziecka;
        index_dziecka = LewySyn(indeks_wstawionego);
    }
}

void Przesiewanie_w_gore(){
    int index_wstawionego = index_ostatniego;
    while(index_wstawionego > 1){
        if(czy_Swap(index_wstawionego)){
            swap(kopiec[index_wstawionego], kopiec[Ojciec(index_wstawionego)]);
            index_wstawionego /= 2;
        }
        else
            break;
    }
}

Osoba UsunWierzcholek(){
    Osoba o=kopiec[1];
    kopiec[1]=kopiec[index_ostatniego];
    index_ostatniego--;
    Przesiewanie_w_dol();
    return o;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    cin >> t;
    queue<int> Qwyjscie;
    Osoba rozmowca1{}, rozmowca2{};
    while(t--){
        int n;
        cin >> n;
        kopiec = new Osoba[n+1];
        int temp;
        index_ostatniego = 0;
        for(int i = 1; i <= n; i++){
            cin >> temp;
            if(temp > 0){
                index_ostatniego++;
                kopiec[index_ostatniego].towarzyskosc = temp;
                kopiec[index_ostatniego].numer_osoby=i;
                Przesiewanie_w_gore();
            }
        }
        int ilosc_rozmow = 0;
        while(index_ostatniego > 1 && kopiec[2].towarzyskosc > 0){
            ilosc_rozmow++;
            rozmowca1 = UsunWierzcholek();
            rozmowca2 = UsunWierzcholek();
            if(rozmowca1.numer_osoby > rozmowca2.numer_osoby)
            {
                Qwyjscie.push(rozmowca2.numer_osoby);
                Qwyjscie.push(rozmowca1.numer_osoby);
            }
            else{
                Qwyjscie.push(rozmowca1.numer_osoby);
                Qwyjscie.push(rozmowca2.numer_osoby);
            }
            if(rozmowca1.towarzyskosc > 1){
                rozmowca1.towarzyskosc--;
                index_ostatniego++;
                kopiec[index_ostatniego].towarzyskosc = rozmowca1.towarzyskosc;
                kopiec[index_ostatniego].numer_osoby = rozmowca1.numer_osoby;
                Przesiewanie_w_gore();
            }
            if(rozmowca2.towarzyskosc > 1){
                rozmowca2.towarzyskosc--;
                index_ostatniego++;
                kopiec[index_ostatniego].towarzyskosc = rozmowca2.towarzyskosc;
                kopiec[index_ostatniego].numer_osoby = rozmowca2.numer_osoby;
                Przesiewanie_w_gore();
            }
        }
        cout << ilosc_rozmow << '\n';
        while(!Qwyjscie.empty())
        {
            cout << Qwyjscie.front() << " ";
            Qwyjscie.pop();
            cout << Qwyjscie.front() << '\n';
            Qwyjscie.pop();
        }
        delete[] kopiec;
    }
}
