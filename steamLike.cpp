#include <iostream>
#include <iomanip>
#include <fstream>

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
void removeGame(GamePage *store, int vector_size, string game_to_remove);
void showContent(GamePage *store, int pos);
void showAllContent(GamePage *store, int vector_size);
void writeData(GamePage *store, int vector_size);

void actions();
void ordenate(GamePage *store, int vector_size);
int binarySearch(GamePage *store, int begin, int end, string search);
string convertString(string num_players);
bool isAllDigits(int number);


void updateVector(GamePage *store, int vector_size);

int main(void) {
    int vector_size = 1, action = 0, pos;
    string search, temp_string;
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

    while (cin >> action && (action == 0 || action == 1 || action == 2 || action == 3 || action == 4 || action == 5 || action == 6)) {
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
                if (vector_size > 1) {
                    ordenate(store, vector_size);
                }
                cin.ignore();
                vector_size = createGame(store, vector_size);
                actions();
                break;
            case 2:
                if (vector_size > 0) {
                    system("cls|clear");
                    cin.ignore();
                    cout << "Qual jogo deseja remover? (Insira o título corretamente)" << endl;
                    showAllContent(store, vector_size);
                    getline(cin, temp_string);
                    ordenate(store, vector_size);
                    removeGame(store, vector_size, temp_string);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "Não há jogos para serem removidos" << endl << endl;
                }
                actions();
                break;
            case 3:
                if (vector_size > 0) {
                    ordenate(store, vector_size);
                    system("cls|clear");
                    cin.ignore();
                    cout << "Qual jogo deseja alterar? (Insira o título corretamente)" << endl;
                    showAllContent(store, vector_size);
                    getline(cin, temp_string);
                    ordenate(store, vector_size);
                    removeGame(store, vector_size, temp_string);
                    ordenate(store, vector_size);
                    vector_size = createGame(store, vector_size);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "ainda não há jogos na loja" << endl << endl; 
                }
                actions();
                break;
            case 4:
                ordenate(store, vector_size);
                system("cls|clear");
                cout << "digite o nome do jogo que quer pesquisar" << endl;
                cin.ignore();
                getline(cin, search);
                pos = binarySearch(store, 0, vector_size - 1, search);
                if (pos == 0) {
                    cout << "O jogo não existe na base de dados" << endl << endl;
                    actions();
                }
                else {
                    system("cls|clear");
                    showContent(store, pos);
                    actions();
                }
                break;
            case 5:
                ordenate(store, vector_size);
                showAllContent(store, vector_size);
                break;
            case 6:
                try {
                    writeData(store, vector_size); 
                    throw runtime_error("erro ao salvar os dados");
                } catch (const runtime_error &e) {
                    cout << "Ocorreu um erro com o salvamento dos dados" << endl;
                }
                break;
        }
    }
        cout << "Entrada inválida" << endl << "Encerrando programa" << endl;
        return -1;
}

void actions() {
    cout << "O que fazer?" << endl;
    cout << "0 - Fechar programa" << endl << "1 - adicionar jogo" << endl << "2 - remover jogo" << endl << "3 - alterar jogo" << endl << "4 - pesquisar" << endl << "5 - mostrar todo conteúdo da loja" << endl << "6 - salvar conteúdo da loja" << endl;
}

int createGame(GamePage *store, int vector_size) {
    /*
    store = updateVector(store, vector_size, vector_size);
    if (!store) {
        return vector_size;
    }
    */

    int pos;
    string temp_string;
    bool valid_name = false;
    cout << "digite o título do jogo" << endl;
    getline(cin, (store + vector_size)->title);
    if (vector_size > 1) {
        while (!valid_name) {
            if ((store + vector_size)->title != temp_string) {
                valid_name = true;
            }
            pos = binarySearch(store, 0, vector_size - 1, (store + vector_size)->title);
            temp_string = (store + pos)->title;
            if ((store + vector_size)->title == temp_string) {
                valid_name = false;
                cout << "o jogo ja existe" << endl;
                getline(cin, (store + vector_size)->title);
            }
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

void removeGame(GamePage *store, int vector_size, string game_to_remove) {
    int pos;
    pos = binarySearch(store, 0, vector_size - 1, game_to_remove);
    (store + pos)->title = ""; 
    (store + pos)->category = "";
    (store + pos)->developer = "";
    (store + pos)->publishment.day = 0;
    (store + pos)->publishment.month = 0;
    (store + pos)->publishment.year = 0;
    (store + pos)->note = 0;
    (store + pos)->price = 0;
    (store + pos)->time_to_beat = 0;
    (store + pos)->num_players = "";
    (store + pos)->language = "";
}

void showContent(GamePage *store, int pos) {
    cout << endl << "----- JOGOS -----" << endl;
        if ((store + pos)->title != "") {
            cout << "Titulo: " << (store + pos)->title << endl << "Categoria: " << (store + pos)->category << endl << "Desenvolvedor: " << (store + pos)->developer << endl << "Pulicação: " << (store + pos)->publishment.day << "/" << (store + pos)->publishment.month << "/" << (store + pos)->publishment.year << endl << "Avaliação geral: " << (store + pos)->note << endl << "Preço: R$" << (store + pos)->price << endl << "Tempo de jogo: " << (store + pos)->time_to_beat << " horas" << endl << "Número de jogadores: " << (store + pos)->num_players << endl << "Idioma: " << (store + pos)->language << endl;
        }
    cout << endl;
}

void showAllContent(GamePage *store, int vector_size) {
    cout << endl << "----- JOGOS -----" << endl;
    for (int i = 0; i < vector_size; i++) {
        if ((store + i)->title != "") {
            cout << "Titulo: " << (store + i)->title << endl << "Categoria: " << (store + i)->category << endl << "Desenvolvedor: " << (store + i)->developer << endl << "Pulicação: " << (store + i)->publishment.day << "/" << (store + i)->publishment.month << "/" << (store + i)->publishment.year << endl << "Avaliação geral: " << (store + i)->note << endl << "Preço: R$" << (store + i)->price << endl << "Tempo de jogo: " << (store + i)->time_to_beat << " horas" << endl << "Número de jogadores: " << (store + i)->num_players << endl << "Idioma: " << (store + i)->language << endl << endl;
        }
    }
}

void writeData(GamePage *store, int vector_size) {
    ofstream file;
    file.open("data.csv");
    file << "Título,Categoria,Desenvolvedor,Data de publicação, Avaliação, Preço, Tempo de jogo, Número de jogadores, Idioma" << endl;
    for (int i = 0; i < vector_size; i++) {
        if ((store + i)->title != "") {
            file << (store + i)->title << ',' << (store + i)->category << ',' << (store + i)->developer << ',' << (store + i)->publishment.month << '/' << (store + i)->publishment.day << '/' << (store + i)->publishment.year << ',' << (store + i)->note << ',' << "R$" << (store + i)->price << ',' << (store + i)->time_to_beat << ',' << (store + i)->num_players << ',' << (store + i)->language << endl;
        }
    }
   file.close(); 
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

int binarySearch(GamePage *store, int begin, int end, string search) {
    if (begin > end) {
        return 0;
    }
    
    int mid;
    mid = begin + (end - begin) / 2;
    if ((store + mid)->title == search) {
        return mid;
    }

    if ((store + mid)->title > search) {
        return binarySearch(store, begin, mid - 1, search);
    }

    return binarySearch(store, mid + 1, end, search);

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

bool isAllDigits(int number) {
   string converted_number = to_string(number);
   for (char c : converted_number) {
       if (!isdigit(c)) {
           return false;
       }
   }
   return true;
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
