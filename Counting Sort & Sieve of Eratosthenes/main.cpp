#include <iostream>
#include <bitset>

const int MAX = 1000001;
using namespace std;

int main() {
    //Optymalizacja:
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    //// Wczytaj dane
    bitset<MAX> set;
    bitset<MAX> dupl;
    int n; cin >> n;
    int value, min, max;
    min = MAX; max = 0;
    for(int i = 0; i < n; i++){
        cin >> value;
        if(set[value]) dupl[value] = true;
        set[value] = true;
        if(value < min) min = value;
        if(value > max) max = value;
    }
    //// Rozwiąż problem
    int ctr = 0;
    for(int i = min; i <= max; i++){
        if(set[i]){
            for(int j = i*2; j <= max; j += i){
                if(set[j]) ctr++;
            }
        }
        if(set[i] && dupl[i]) ctr++;
    }
    cout << ctr;
    return 0;
}

