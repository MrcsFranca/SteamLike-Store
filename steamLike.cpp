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


int createGame(GamePage *store, int vector_size);
void showContent(GamePage *store, int vector_size);
GamePage updateVector(GamePage *store, int vector_size, int &capacity);

int main(void) {
    int vector_size = 0;
    int capacity = 1;
    GamePage *store = new(nothrow) GamePage[capacity];
    if (!store) {
        cout << "Out of memory" << endl;
        return -1;
    }

    cout << fixed << setprecision(2);
    cout << sizeof(store) << endl;
    vector_size = createGame(store, vector_size);
    vector_size = createGame(store, vector_size);
    showContent(store, vector_size);

    delete[] store;
    store = NULL;
    return 0;
}

GamePage updateVector(GamePage *store, int &vector_size, int &capacity) {
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

int createGame(GamePage *store, int vector_size) {
    store = updateVector(store, vector_size, vector_size);
    if (!store) {
        return vector_size;
    }

    // cin >> (store + vector_size)->title >> (store + vector_size)->category >> (store + vector_size)->developer >> (store + vector_size)->publishment.day >> (store + vector_size)->publishment.month >> (store + vector_size)->publishment.year >> (store + vector_size)->note >> (store + vector_size)->price >> (store + vector_size)->time_to_beat >> (store + vector_size)->num_players >> (store + vector_size)->language;
    cin >> (store + vector_size)->title;
    return vector_size + 1;
}

void showContent(GamePage *store, int vector_size) {
    for (int i = 0; i < vector_size; i++) {
        // cout << (store + i)->title << endl << (store + i)->category << endl << (store + i)->developer << endl << (store + i)->publishment.day << endl << (store + i)->publishment.month << endl << (store + i)->publishment.year << endl << (store + i)->note << endl << (store + i)->price << endl << (store + i)->time_to_beat << endl << (store + i)->num_players << endl << (store + i)->language << endl;
        cout << (store + i)->title << endl; 
    }
}
