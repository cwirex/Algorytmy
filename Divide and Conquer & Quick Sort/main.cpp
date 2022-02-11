#include <iostream>
using namespace std;

bool divide(int, int, bool);                    // ...divide and conquer
void sort(int [], int, int);              // ...sort
void swap(int, int);                      // ...sort.swap
int partition(const int [], int, int);    // ...sort.partition
int *X1, *X2, *Y1, *Y2;                   // ...arrays

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    short n;
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        cin >> n;
        X1 = new int[n]; Y1 = new int[n];
        X2 = new int[n]; Y2 = new int[n];
        for(int j = 0; j < n; j++){
            cin >> X1[j] >> Y1[j] >> X2[j] >> Y2[j];
        }
        sort(X1, 0, n-1);
        if(divide(0, n-1, true))  cout << "TAK\n";
        else  cout << "NIE\n";
        delete[] X1; delete[] X2; delete[] Y1; delete[] Y2;
    }
}

bool divide(int p, int q, bool poX) {
    if(p == q)  return true;
    if(poX){
        int current = X2[p];
        for(int i = p+1; i <= q; i++){
            if(X2[i] > current){            // Wytypuj miejsce do podziału
                int j; bool legal = true;   // Sprawdź, czy podział jest możliwy
                for(j = i; j <= q; j++){
                    if(current > X1[j]){    // Jeśli nie...
                        current = X2[i];
                        legal = false;
                        break;
                    }
                }
                if(legal)                   // Jeśli tak...
                    return divide(p, i-1, true) && divide(i,q, true);   // Podziel problem na podproblemy
            }
        }
        //// Try to divide by Y:
        sort(Y1, p, q);
        current = Y2[p];
        for(int i = p+1; i <= q; i++){
            if(Y2[i] > current){
                int j; bool legal = true;
                for(j = i; j <= q; j++){
                    if(current > Y1[j]){
                        current = Y2[i];
                        legal = false;
                        break;
                    }
                }
                if(legal)
                    return divide(p, i-1,false)  && divide(i,q, false);
            }
        }
        return false;
    }
    else{
        int current = Y2[p];
        for(int i = p+1; i <= q; i++){
            if(Y2[i] > current){
                int j; bool legal = true;
                for(j = i; j <= q; j++){
                    if(current > Y1[j]){
                        current = Y2[i];
                        legal = false;
                        break;
                    }
                }
                if(legal)
                    return divide(p, i-1, false) && divide(i,q, false);
            }
        }
        sort(X1, p, q);
        current = X2[p];
        for(int i = p+1; i <= q; i++){
            if(X2[i] > current){            // Wytypuj miejsce do podziału
                int j; bool legal = true;   // Sprawdź, czy podział jest możliwy
                for(j = i; j <= q; j++){
                    if(current > X1[j]){    // Jeśli nie...
                        current = X2[i];
                        legal = false;
                        break;
                    }
                }
                if(legal)                   // Jeśli tak...
                    return divide(p, i-1, true) && divide(i,q, true);   // Podziel problem na podproblemy
            }
        }
        return false;
    }
}

void sort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        sort(array, low, pi - 1);
        sort(array, pi + 1, high);
    }
}
void swap(int i1, int i2) {
    int t;
    t = X1[i1];
    X1[i1] = X1[i2];
    X1[i2] = t;
    t = X2[i1];
    X2[i1] = X2[i2];
    X2[i2] = t;
    t = Y2[i1];
    Y2[i1] = Y2[i2];
    Y2[i2] = t;
    t = Y1[i1];
    Y1[i1] = Y1[i2];
    Y1[i2] = t;
}
int partition(const int array[], int low, int high) {
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(i, j);
        }
    }
    swap(i + 1, high);
    return (i + 1);
}
