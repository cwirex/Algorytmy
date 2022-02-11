#include <iostream>
#include <queue>
#define SHRT_MAX 32767

using namespace std;

struct Node{
    char info = 0;
    short mieszko = SHRT_MAX;
    short ogien = SHRT_MAX;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    short n, m;
    int t;                          // Liczba testów
    cin >> t;
    while(t--){
        //// setup
        cin >> n >> m;
        short move_count = 0;       // Path cost
        int nodes_left = 0;         // Nodes left in current layer
        int nodes_next = 0;         // Nodes waiting in next layer (next step)
        int dRows[4] = {-1,1,0,0};  // Direction vectors
        int dCols[4] = {0,0,1,-1};  //
        std::queue<int> qR;         // queue Rs
        std::queue<int> qC;         // queue Cs
        int r, c;                   // Current (r,c)
        int nr, nc;                 // Neightbour's (r,c)
        int mr, mc;                 // Mieszko's (r,c)
        short result;
        //// WCZYTAJ DANE
        Node** nodes = new Node*[n];
        char* line = new char[m+1];
        for(short i = 0; i < n; i++){
            nodes[i] = new Node[m];
        }
        for(short i = 0; i < n; i++){
            cin >> line;
            for(short j = 0; j < m; j++){
                if(line[j] == '#')
                    nodes[i][j].info = 100; // ściana
                else if(line[j] == '.')
                    nodes[i][j].info = 0; // 0 - unvisited, 1 - visited by Ogien, 2 - visited by Mieszko
                else if(line[j] == 'M'){
                    nodes[i][j].info = 0;
                    mr = i;
                    mc = j;
                }
                else{ // if OGIEN add to queue
                    nodes[i][j].info = 1;
                    qR.push(i);
                    qC.push(j);
                    nodes_left++;
                }
            }
        }
        //if no OGIEN?
        //// calc OGIEN costs
        while(!qR.empty()){
            r = qR.front(); qR.pop();
            c = qC.front(); qC.pop();
            nodes_left--;
            nodes[r][c].info = 1;
            nodes[r][c].ogien = move_count;
            //// Explore neightbours
            for(int i = 0; i < 4; i++){
                nr = r + dRows[i];
                nc = c + dCols[i];
                if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1)
                    continue;
                if(nodes[nr][nc].info != 0) // visited or a wall
                    continue;
                // (nr, nc) is neightbour:
                nodes[nr][nc].info = 1;
                qR.push(nr);
                qC.push(nc);
                nodes_next++;
            }
            if(!nodes_left){
                nodes_left = nodes_next;
                nodes_next = 0;
                move_count++;
            }
        }

        //// calc MIESZKO costs
        move_count = 0;         // Path cost
        nodes_left = 1;         // Nodes left in current layer
        nodes_next = 0;         // Nodes waiting in next layer (next step)
        //Queue should be empty for now
        qR.push(mr);
        qC.push(mc);
        while(!qR.empty()){
            r = qR.front(); qR.pop();
            c = qC.front(); qC.pop();
            nodes_left--;
            nodes[r][c].info = 2;
            nodes[r][c].mieszko = move_count;
            //// Explore neightbours
            for(int i = 0; i < 4; i++){
                nr = r + dRows[i];
                nc = c + dCols[i];
                if(nr < 0 || nc < 0 || nr > n-1 || nc > m-1)
                    continue;
                if(nodes[nr][nc].info >= 2) // visited or a wall
                    continue;
                if(nodes[nr][nc].ogien <= move_count)
                    continue;
                // (nr, nc) is neightbour:
                nodes[nr][nc].info = 2;
                qR.push(nr);
                qC.push(nc);
                nodes_next++;
            }
            if(!nodes_left){
                nodes_left = nodes_next;
                nodes_next = 0;
                move_count++;
            }
        }
        //// return result
        result = SHRT_MAX;
        for(int i = 0; i < n; i++){     //check top and bottom
            if(nodes[i][0].info != 100 ){                       // if not wall
                if(nodes[i][0].mieszko < nodes[i][0].ogien){    // if mieszko is faster
                    if(nodes[i][0].mieszko < result){         // if shortest path
                        result = nodes[i][0].mieszko;
                    }
                }
            }
            if(nodes[i][m-1].info != 100 ){
                if(nodes[i][m-1].mieszko < nodes[i][m-1].ogien){
                    if(nodes[i][m-1].mieszko < result){
                        result = nodes[i][m-1].mieszko;
                    }
                }
            }
        }
        for(int i = 1; i < m-1; i++){   //check left and right
            if(nodes[0][i].info != 100){
                if(nodes[0][i].mieszko < nodes[0][i].ogien){
                    if(nodes[0][i].mieszko < result){
                        result = nodes[0][i].mieszko;
                    }
                }
            }
            if(nodes[n-1][i].info != 100){
                if(nodes[n-1][i].mieszko < nodes[n-1][i].ogien){
                    if(nodes[n-1][i].mieszko < result){
                        result = nodes[n-1][i].mieszko;
                    }
                }
            }
        }
/*        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << nodes[i][j].info << "\t";
            }
            cout << endl;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << nodes[i][j].ogien << "\t";
            }
            cout << endl;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << nodes[i][j].mieszko << "\t";
            }cout << endl;
        }*/
        if(result == SHRT_MAX){
            cout << "NIE\n";
        }
        else{
            cout << result + 1<< endl;
        }
    }
    return 0;
}
