#include <iostream>
#include <iomanip>

using namespace std;

typedef struct {
    int day;
    int month;
    int year;
} Publish;

typedef struct {
    string title;
    string category;
    string developer;
    Publish publishment;
    float note;
    float price;
    int time_to_beat;
    string num_players;
    string language;
} GamePage;

void actions();
int createGame(GamePage *store, int vector_size);
void removeGame(GamePage *store, int vector_size);
void showContent(GamePage *store, int vector_size);



void updateVector(GamePage *store, int vector_size);

int main(void) {
    int vector_size = 0, action = 0;
    GamePage *store = new(nothrow) GamePage[1000];
    if (!store) {
        cout << "Out of memory" << endl;
        return -1;
    }

    cout << fixed << setprecision(2);

    //updateVector(store, vector_size);
    //updateVector(store, vector_size);
    
    system("cls|clear");
    actions();

    while (cin >> action && (action == 0 || action == 1 || action == 2 || action == 3 || action == 4)) {
        system("cls|clear");
        actions();
        switch (action) {
            case 0:
                delete[] store;
                store = NULL;
                system("cls|clear");
                cout << "Fechando programa" << endl;
                return 0;
            case 1:
                system("cls|clear");
                vector_size = createGame(store, vector_size);
                actions();
                break;
            case 2:
                if (vector_size > 0) {
                    removeGame(store, vector_size);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "Não há jogos para serem removidos" << endl << endl;
                }
                actions();
                break;
            case 3:
                break;
            case 4:
                break;
        }
        showContent(store, vector_size);
    }
        cout << "Entrada inválida" << endl << "Encerrando programa" << endl;
        return -1;
}

void actions() {
    cout << "O que fazer?" << endl;
    cout << "0 - Fechar programa" << endl << "1 - adicionar jogo" << endl << "2 - remover jogo" << endl << "3 - alterar jogo" << endl << "4 - pesquisar" << endl;
}

int createGame(GamePage *store, int vector_size) {
    /*
    store = updateVector(store, vector_size, vector_size);
    if (!store) {
        return vector_size;
    }
    */

    // cin >> (store + vector_size)->title >> (store + vector_size)->category >> (store + vector_size)->developer >> (store + vector_size)->publishment.day >> (store + vector_size)->publishment.month >> (store + vector_size)->publishment.year >> (store + vector_size)->note >> (store + vector_size)->price >> (store + vector_size)->time_to_beat >> (store + vector_size)->num_players >> (store + vector_size)->language;
    cin.ignore();
    getline(cin, (store + vector_size)->title);
    //cin >> (store + vector_size)->title;
    return vector_size + 1;
}

void removeGame(GamePage *store, int vector_size) {
    string removing;
    system("cls|clear");
    cin.ignore();
    cout << "Qual jogo deseja remover? (Insira o título corretamente)" << endl;
    showContent(store, vector_size);
    getline(cin, removing);
    for (int i = 0; i < (vector_size + 1); i++) {
        if ((store + i)->title == removing) {
           (store + i)->title = "oi"; 
        }
    }
}

void showContent(GamePage *store, int vector_size) {
    cout << endl << "----- JOGOS -----" << endl;
    for (int i = 0; i < vector_size + 1; i++) {
        //cout << (store + i)->title << endl << (store + i)->category << endl << (store + i)->developer << endl << (store + i)->publishment.day << endl << (store + i)->publishment.month << endl << (store + i)->publishment.year << endl << (store + i)->note << endl << (store + i)->price << endl << (store + i)->time_to_beat << endl << (store + i)->num_players << endl << (store + i)->language << endl;
        cout << (store + i)->title << endl; 
    }
}


/*
void updateVector(GamePage *store, int vector_size) {
    GamePage *aux = store;
    store = NULL;
    store = new(nothrow) GamePage[vector_size+2];
    store = aux;

    if (vector_size >= capacity) {
        capacity *= 2;
        GamePage *store_aux = new(nothrow) GamePage[capacity];
        if (!store_aux) {
            cout << "Out of memory" << endl;
            return -1;
        }
        for (int i = 0; i < vector_size; i++) {
            *(store_aux + i) = *(store + i);
        }
        delete[] store;
        return *store_aux;
    }
    return *store;
    }
*/
