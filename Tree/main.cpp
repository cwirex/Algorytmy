#include <iostream>
#include "string"
using namespace std;

struct Node{
    string name;
    int val = 0;
    Node* son = nullptr;
    Node* next = nullptr;
};

Node* root = nullptr;

void addNode(const string& name, const int* path, int size){
    if(root->son == nullptr){
        auto* curr = root;
        for(int i = 0; i < size; i++){
            curr->son = new Node;
            curr = curr->son;
            curr->name = "X";
            curr->val = path[i];
        }
        curr->name = name;
        return;
    }
    auto* curr = root->son;
    for(int i = 0; i < size; i++){
        while(!(curr->val == path[i] || curr->next == nullptr)){ // znajdź brata, po którym masz przejść
            curr = curr->next;
        }
        if(curr->val == path[i]){ // ZNALEZIONO WEZEL O DANYM KOSZCIE!
            if(i == size-1){         //jeśli to ostatni węzeł
                curr->name = name;   // auto break
            }
            else if(curr->son == nullptr) { // gdy węzeł nie ma potomka
                while(++i < size) {
                    curr->son = new Node;
                    curr = curr->son;
                    curr->val = path[i];
                    curr->name = "X";
                }
                curr->name = name;
            }
            else{   // gdy węzeł ma potomka(ów), zejdz niżej:
                curr = curr->son;
            }
        }
        else if(curr->next == nullptr){ //jeśli taki brat nie istnieje, to stwórz nowy węzeł (jako brata)
            auto* new_node = new Node;
            new_node->name = "X";
            new_node->val = path[i];
            curr->next = new_node;
            curr = curr->next;
            while(++i < size) {
                curr->son = new Node;
                curr = curr->son;
                curr->val = path[i];
                curr->name = "X";
            }
            curr->name = name;
        }
    }
}

void preorder(Node* current = root){
    cout << current->name << "\n";
    if(current->son != nullptr){
        preorder(current->son);
    }
    if(current->next != nullptr){
        preorder(current->next);
    }
}

void postorder(Node* current = root){
    if(current->son != nullptr){
        postorder(current->son);
    }
    cout << current->name << "\n";
    if(current->next != nullptr){
        postorder(current->next);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    root = new Node;
    root->val = 0;
    root->name = "Stan spoczynku";
    int n;  cin >> n;
    string name; int size;

    for(int i = 0; i < n; i++){
        getline(cin, name);
        getline(cin, name);
        cin >> size;
        int *path = new int[size];
        for(int j = 0; j < size; j++){
            cin >> path[j];
        }
        addNode(name, path, size);
    }

    cin >> n;
    getline(cin, name);

    if(n == 1){
        preorder();
    }
    else if(n == 2){
        postorder();
    }
    return 0;
}
