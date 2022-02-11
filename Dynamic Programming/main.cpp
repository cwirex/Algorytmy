#include <iostream>
using namespace std;

int max2(int a, int b){
    return a >= b ? a : b;
}

int max3(int a, int b, int c){
    return a >= b ? (a >= c ? a : c) : (b >= c ? b : c);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int *arr;
    int **table;
    int n, m;
    cin >> n;
    cin >> m;
    arr = new int[n];
    table = new int*[2];
    table[0] = new int[m]; table[1] = new int[m];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < m; j++){
            table[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[j];
        }
        int current = i%2;
        int previous = (i+1)%2;
        table[current][0] = arr[0] + max2(table[previous][0], table[previous][1]);
        table[current][m-1] = arr[m-1] + max2(table[previous][m-1], table[previous][m-2]);
        for(int k = 1; k < m - 1; k++)
            table[current][k] = arr[k] + max3(table[previous][k - 1], table[previous][k], table[previous][k + 1]);
    }
    int final = (n+1)%2;
    int INDEX = 0;
    int MAX = table[final][0];
    for(int i = 1; i < m; i++){
        if(table[final][i] > MAX){
            INDEX = i;
            MAX = table[final][i];
        }
    }
    cout << INDEX << " " << MAX;
}
