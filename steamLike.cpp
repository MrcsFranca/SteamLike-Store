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
void removeGame(GamePage *store, int vector_size);
void updateGame(GamePage *store, int vector_size);
void showContent(GamePage *store, int vector_size);
void actions();
void ordenate(GamePage *store, int vector_size);
string convertString(string num_players);


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
                updateGame(store, vector_size);
                system("cls|clear");
                actions();
                break;
            case 4:
                ordenate(store, vector_size);
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
    string temp_string;
    cin.ignore();
    cout << "digite o título do jogo" << endl;
    getline(cin, (store + vector_size)->title);
    if (vector_size >= 1) {
        for (int i = 0; (i < (vector_size + 1)) || ((store + vector_size)->title == (store + i)->title); i++) {
            if ((store + vector_size)->title == (store + i)->title) {
                temp_string = (store + i)->title;
            }
        }
        while ((store + vector_size)->title == temp_string) {
            cout << "o jogo ja existe" << endl;
            getline(cin, (store + vector_size)->title);
        }
    }

    cout << "digite a categoria do jogo" << endl;
    getline(cin, (store + vector_size)->category);

    cout << "digite o nome do desenvolvedor do jogo" << endl;
    getline(cin, (store + vector_size)->developer);

    cout << "digite o mês de lançamento" << endl;
    while (cin >> (store + vector_size)->publishment.month && ((store + vector_size)->publishment.month > 12 || (store + vector_size)->publishment.month < 1)) {
        cout << "Insira um mês válido" << endl;
    }
    cout << "digite o dia de lançamento" << endl;
    if ((store + vector_size)->publishment.month == 2) {
        while (cin >> (store + vector_size)->publishment.day && ((store + vector_size)->publishment.day < 1 || (store + vector_size)->publishment.day > 28)) {
            cout << "insira um dia válido para o mês" << endl;
        }
    }
    else {
        while (cin >> (store + vector_size)->publishment.day && ((store + vector_size)->publishment.day > 31 || (store + vector_size)->publishment.day < 1)) {
            cout << "Insira um dia válido" << endl;
        }
    }
    cout << "digite o ano de lançamento" << endl;
    while (cin >> (store + vector_size)->publishment.year && ((store + vector_size)->publishment.year > 2024 || (store + vector_size)->publishment.year < 1960)) {
        cout << "Insira um ano válido" << endl;
    }

    cout << "de uma nota de 0.0 a 5.0 ao jogo" << endl;
    while (cin >> (store + vector_size)->note && ((store + vector_size)->note < 0 || (store + vector_size)->note > 5)) {
        cout << "avalie o jogo corretamente" << endl;
    }

    cout << "digite o preço do jogo" << endl;
    while (cin >> (store + vector_size)->price && ((store + vector_size)->price > 400)) {
        cout << "digite um preço justo" << endl;
    }

    cout << "digite o tempo para zerar o jogo em horas" << endl;
    while (cin >> (store + vector_size)->time_to_beat && (store + vector_size)->time_to_beat < 1) {
        cout << "digite um tempo válido" << endl;
    }

    cout << "Quanto jogadores podem jogar?" << endl << "- Single player" << endl << "- Multiplayer" << endl << "- Coop" << endl;
    cin.ignore();
    getline(cin, (store + vector_size)->num_players);
    (store + vector_size)->num_players = convertString((store + vector_size)->num_players);
    while ((store + vector_size)->num_players != "SINGLE PLAYER" && (store + vector_size)->num_players != "MULTIPLAYER" && (store + vector_size)->num_players != "COOP") {
        cout << "escolha uma opção válida" << endl;
        getline(cin, (store + vector_size)->num_players);
        (store + vector_size)->num_players = convertString((store + vector_size)->num_players);
    }

    cout << "Selecione o idioma" << endl; 
    getline(cin, (store + vector_size)->language);
    
    system("cls|clear");

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
           (store + i)->title = ""; 
           (store + i)->category = "";
           (store + i)->developer = "";
           (store + i)->publishment.day = 0;
           (store + i)->publishment.month = 0;
           (store + i)->publishment.year = 0;
           (store + i)->note = 0;
           (store + i)->price = 0;
           (store + i)->time_to_beat = 0;
           (store + i)->num_players = "";
           (store + i)->language = "";
        }
    }
}

void updateGame(GamePage *store, int vector_size) {
    int position;
    string game_to_update, temp_string;
    system("cls|clear");
    cin.ignore();
    cout << "Qual jogo deseja alterar? (Insira o título corretamente)" << endl;
    showContent(store, vector_size);
    getline(cin, game_to_update);
    for (int i = 0; i < (vector_size + 1); i++) {
        if (game_to_update == (store + i)->title) {
            position = i;
        }
    }

    cout << "digite o título do jogo" << endl;
    getline(cin, (store + position)->title);

    cout << "digite a categoria do jogo" << endl;
    getline(cin, (store + position)->category);

    cout << "digite o nome do desenvolvedor do jogo" << endl;
    getline(cin, (store + position)->developer);

    cout << "digite o mês de lançamento" << endl;
    while (cin >> (store + position)->publishment.month && ((store + position)->publishment.month > 12 || (store + position)->publishment.month < 1)) {
        cout << "Insira um mês válido" << endl;
    }
    cout << "digite o dia de lançamento" << endl;
    if ((store + position)->publishment.month == 2) {
        while (cin >> (store + position)->publishment.day && ((store + position)->publishment.day < 1 || (store + position)->publishment.day > 28)) {
            cout << "insira um dia válido para o mês" << endl;
        }
    }
    else {
        while (cin >> (store + position)->publishment.day && ((store + position)->publishment.day > 31 || (store + position)->publishment.day < 1)) {
            cout << "Insira um dia válido" << endl;
        }
    }
    cout << "digite o ano de lançamento" << endl;
    while (cin >> (store + position)->publishment.year && ((store + position)->publishment.year > 2024 || (store + position)->publishment.year < 1960)) {
        cout << "Insira um ano válido" << endl;
    }

    cout << "de uma nota de 0.0 a 5.0 ao jogo" << endl;
    while (cin >> (store + position)->note && ((store + position)->note < 0 || (store + position)->note > 5)) {
        cout << "avalie o jogo corretamente" << endl;
    }

    cout << "digite o preço do jogo" << endl;
    while (cin >> (store + position)->price && ((store + position)->price > 400)) {
        cout << "digite um preço justo" << endl;
    }

    cout << "digite o tempo para zerar o jogo em horas" << endl;
    while (cin >> (store + position)->time_to_beat && (store + position)->time_to_beat < 1) {
        cout << "digite um tempo válido" << endl;
    }

    cout << "Quanto jogadores podem jogar?" << endl << "- Single player" << endl << "- Multiplayer" << endl << "- Coop" << endl;
    cin.ignore();
    getline(cin, (store + position)->num_players);
    (store + position)->num_players = convertString((store + position)->num_players);
    while ((store + position)->num_players != "SINGLE PLAYER" && (store + position)->num_players != "MULTIPLAYER" && (store + position)->num_players != "COOP") {
        cout << "escolha uma opção válida" << endl;
        getline(cin, (store + position)->num_players);
        (store + position)->num_players = convertString((store + position)->num_players);
    }

    cout << "Selecione o idioma" << endl; 
    getline(cin, (store + position)->language);
    
    system("cls|clear");
}

void showContent(GamePage *store, int vector_size) {
    cout << endl << "----- JOGOS -----" << endl;
    for (int i = 0; i < vector_size; i++) {
        cout << "Titulo: " << (store + i)->title << endl << "Categoria: " << (store + i)->category << endl << "Desenvolvedor: " << (store + i)->developer << endl << "Pulicação: " << (store + i)->publishment.day << "/" << (store + i)->publishment.month << "/" << (store + i)->publishment.year << endl << "Avaliação geral: " << (store + i)->note << endl << "Preço: R$" << (store + i)->price << endl << "Tempo de jogo: " << (store + i)->time_to_beat << " horas" << endl << "Número de jogadores: " << (store + i)->num_players << endl << "Idioma: " << (store + i)->language << endl;
        //cout << (store + i)->title << (store + i)->category << endl; 
    }
}

void ordenate(GamePage *store, int vector_size) {
    if (vector_size == 1) {
        return;
    }
    for (int i = 0; i < (vector_size - 1); i++) {
        if ((store + i)->title > (store + i + 1)->title) {
            swap((store + i)->title, (store + i + 1)->title);
        }
    }
    ordenate(store, vector_size - 1);
}

string convertString(string temp_string) {
    int i = 0;
    while (temp_string[i] != '\0') {
        if (temp_string[i] >= 97 && temp_string[i] <= 122) {
            temp_string[i] -= 32;
        }
        i++;
    }
    return temp_string;
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
