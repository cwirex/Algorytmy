#include <iostream>
#define sh short
using namespace std;
////    ZADANIE 3   ////
struct Node{
    string name;
    sh val = 0;
    Node* next = nullptr;
    Node* prev= nullptr;
};
Node** HEAD;
sh CURR = 0;

void appendNode(Node* first, const string& name, sh val);
void deleteNode(Node* node);
void moveNodesBy(sh moves);
bool isLast(Node* node);
int calcSize(sh n);
void print(int area, sh n);
void deleteNodes(sh &n);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    sh n, m, c;
    int l, h;
    string str;
    /// Obsługa wejścia:
    cin >> n; //liczba grup (list)
    HEAD = new Node*[n]; //Utwórz n wskaźników na grupy (listy)
    for(sh i = 0; i < n; i++){
        HEAD[i] = new Node;
        HEAD[i]->next = HEAD[i];
        HEAD[i]->prev = HEAD[i];
    }
    for (sh i = 0; i < n; i++) {
        cin >> m;       //liczba kolejnych linii (typu 'Brawatek 3')
        cin >> HEAD[i]->name >> HEAD[i]->val;   // Ustaw wartości pierwszego elementu z grupy (listy)
        for (sh j = 1; j < m; j++) {    // Dodaj pozostałe elementy do grupy (listy)
            cin >> str >> c;
            appendNode(HEAD[i], str, c);
        }
    }

    cin >> l;       // Wczytaj powierzchnie rabat:
    int *areas = new int[l];
    int area;
    cin >> areas[0];
    for (int i = 1; i < l; i++) {
        cin >> area;
        int j = i;
        while(j > 0 && areas[j-1] > area){
            areas[j] = areas[j-1];
            j--;
        }
        areas[j] = area;
    }

    cin >> h;       //wczytaj dane o krokach:
    sh *x = new sh[h];
    sh *y = new sh[h];
    for (int i = 0; i < h; i++) {
        cin >> x[i];
        cin >> y[i];
    }

    /// Właściwy program:
    int i = 0;
    int suma = calcSize(n); //początkowa suma
    while (true) {      // Obchódź dopóki masz możliwe kroki do wykonania
        bool found = false;
        /// Use binary search:
        int left = 0; int right = l-1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (areas[mid] == suma) {
                print(areas[mid], n);
                deleteNodes(n);
                //zapisz stan znalezienia:
                found = true;
                for(int j = mid; j < l-1; j++){
                    areas[j] = areas[j + 1];    // usuń aktualną sumę i przesuń większe elementy w lewo
                }
                l--;
                if (l == 0 || n == 0) return 0;  //gdy skończyły się rabaty
                suma = calcSize(n);
                break;
            }
            else if (suma > areas[mid]) left = mid + 1;
            else right = mid - 1;
        }

        if (!found) { /// MOVE
            if (i >= h) return 0;   //nie ma gdzie się ruszyć, koniec programu
            CURR = (CURR + x[i])%n;
            suma -= HEAD[CURR]->val;
            moveNodesBy(y[i]);
            suma += HEAD[CURR]->val;
            i++;
        }
    }
}

/// Node methods:
void appendNode(Node* first, const string& name, sh val){   //dodaj element z tyłu listy, zapętlając ją
    Node* node = new Node;
    node->val = val; node->name = name;     //ustawienie wartości elementu
    //włączenie elementu do listy:
    node->next = first;
    node->prev = first->prev;

    first->prev->next = node;
    first->prev = node;
}

void deleteNode(Node* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

void moveNodesBy(sh moves){
    Node* temp = HEAD[CURR];
    while(moves > 0){ // keep moving right
        temp = temp->next;
        moves--;
    }
    while(moves < 0){ //keep moving left
        temp = temp->prev;
        moves++;
    }
    HEAD[CURR] = temp;
}

bool isLast(Node* node){ // czy jest ostatni w liście cyklicznej (czy pozostał jeden)
    return node->next == node;
}

int calcSize(sh n) {
    int suma = 0;
    for(sh i = 0; i < n; i++){
        suma += HEAD[i]->val;
    }
    return suma;
}

void print(int area, sh n){
    string result;
    for(sh i = 0; i < n; i++){
        result += " " + HEAD[i]->name;
    }
    cout << area << result << "\n";
}

void deleteNodes(sh &n){
    for(sh i = 0; i < n; i++){      //przebiegnij wszystkie grupy
                                    //i usuń z nich po jednym elemencie:
        if(isLast(HEAD[i])){    /// then delete group:
            for(int j = i; j < n-1; j++){
                HEAD[j] = HEAD[j+1];        //przesuń pozostałe elementy w lewo
            }
            HEAD[n-1] = nullptr;            //na końcu listy ustaw nullptr
            if(i < CURR && CURR+1 != n)     //zabezpiecz wartość CURR
                CURR--;
            else if(CURR+1 == n)
                CURR = 0;
            n--;        //zmniejsz ilość grup
            i--;        //powtórz obieg pętli (kolejna grupa wskoczyła na ten index)
        }
        else{     /// then delete node:
            HEAD[i] = HEAD[i]->next;
            deleteNode(HEAD[i]->prev);
        }
    }
}
