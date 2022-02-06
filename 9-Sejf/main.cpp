#include <iostream>
#include <bitset>
using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, k, m, Lo, Lx;
    char c;
    cin >> n >> k >> m;
    auto* arr = new bitset<20>[n];
    //// Wczytywanie danych:
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){
            cin >> c;
            if(c == 'X')
                arr[i][j] = true;
        }
    }
    for(int K = k-1; K >= 0; K--) {             // K - current column
        auto *arrSorted = new bitset<20>[n];
        //// Zliczanie wystąpień 'X' i 'o':
        Lo = 0;
        Lx = n;
        for (int i = 0; i < n; i++) {
            if (!arr[i][K])
                Lo++;
        }
        //// Przepisywanie tablicy (sortowanie):
        for (int i = n - 1; i >= 0; i--) {
            if (arr[i][K])
                arrSorted[--Lx] = arr[i];
            else
                arrSorted[--Lo] = arr[i];
        }
        delete[] arr;
        arr = arrSorted;
        
    }

    //// Wypisanie wyniku:
    for(int i = n - 1; i >= n - m; i--){
        for(int j = 0; j < k; j++){
            if(arr[i][j])
                cout << 'X';
            else
                cout << 'o';
        }
        cout << "\n";
    }
}
