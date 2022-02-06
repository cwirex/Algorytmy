#include <iostream>
using namespace std;

const int MAX = 2147483647;
int n, min_cost;
short* s, *c;

void rek(int i, int cost, int style){   // rek(0, c[0], s[0]) || rek(0,0,0);
    if(cost >= min_cost) return;
    if(style == 0 && cost > 0){
        min_cost = cost;
        return;
    }
    if(i == n-1){
        return;
    }
    rek(i+1, cost, style);
    rek(i+1, cost+c[i+1], style + s[i+1]);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        s = new short[n];
        c = new short[n];
        for(int i = 0; i < n; i++){
            cin >> s[i] >> c[i];
        }
        min_cost = MAX;
        rek(0, c[0], s[0]);
        rek(0, 0, 0);
        if(min_cost != MAX)
            cout << min_cost << endl;
        else
            cout << "NIE\n";
    }
    return 0;
}
