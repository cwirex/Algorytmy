#include <iostream>

using namespace std;
struct Plant{
    string name;
    double* c = new double[3]; //cryteria;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    char c;
    Plant curr;

    //wczytaj liczbę rządków:
    cin >> n;

    Plant* plants = new Plant[n];
    string* names = new string[n];
    //wczytaj priorytet kryteriów:
    int* prio = new int[3];
    for(int i = 0; i < 3; i++){
        cin >> c;
        prio[c-'0'-1] = i;
    }

    for(int i = 0; i < n; i++){
        cin >> plants[i].name
            >> plants[i].c[prio[0]]
            >> plants[i].c[prio[1]]
            >> plants[i].c[prio[2]];
    }
    //sort:
    for (int i = 1; i < n; i++) {
        curr = plants[i];
        int j;
        for (j = i; j > 0; j--) {
            if (curr.c[0] > plants[j - 1].c[0]) {
                plants[j] = plants[j - 1];
            } else if (curr.c[0] == plants[j - 1].c[0]) {
                //// Kryterium 2:
                if (curr.c[1] > plants[j - 1].c[1]) {
                    plants[j] = plants[j - 1];
                } else if (curr.c[1] == plants[j - 1].c[1]) {
                    //// Kryterium 3:
                    if (curr.c[2] > plants[j - 1].c[2]) {
                        plants[j] = plants[j - 1];
                    } else {
                        break;
                    }
                } else {
                    break;
                }

            } else {
                break;
            }
        }
        plants[j] = curr;
    }
    
    
    for(int i = 0; i < n; i++){
        names[i] = plants[i].name;
        cin >> plants[i].name
            >> plants[i].c[prio[0]]
            >> plants[i].c[prio[1]]
            >> plants[i].c[prio[2]];
    }
    //sort:
    for (int i = 1; i < n; i++) { //(int i = 1; i < n; i++)
        curr = plants[i];
        int j;
        for (j = i; j > 0; j--) { //(j = i; j > 0; j--)
            if (curr.c[0] > plants[j - 1].c[0]) {
                plants[j] = plants[j - 1];
            } else if (curr.c[0] == plants[j - 1].c[0]) {
                //// Kryterium 2:
                if (curr.c[1] > plants[j - 1].c[1]) {
                    plants[j] = plants[j - 1];
                } else if (curr.c[1] == plants[j - 1].c[1]) {
                    //// Kryterium 3:
                    if (curr.c[2] > plants[j - 1].c[2]) {
                        plants[j] = plants[j - 1];
                    } else {
                        break;
                    }
                } else {
                    break;
                }

            } else {
                break;
            }
        }
        plants[j] = curr;
    }


    for(int i = 0; i < n; i++){
        cout << names[i] << "-" << plants[i].name << " ";
    }

    delete[] plants;
    return 0;
}

