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

int userLogin(GamePage *store, int store_size);
int admLogin(GamePage *store, int store_size);
int createGame(GamePage *store, int store_size);
void removeGame(GamePage *vector, int vector_size, string game_to_remove);
void showContent(GamePage *vector, int pos);
void showAllContent(GamePage *vector, int store_size);
void writeData(GamePage *store, int store_size);
int downloadContent(GamePage *store, int pos, GamePage *library, int library_size);

void admActions();
void userActions();
void ordenate(GamePage *vector, int vector_size);
int binarySearch(GamePage *vector, int begin, int end, string search);
string convertString(string num_players);
bool isAllDigits(int number);


void updateVector(GamePage *store, int store_size);

int main(void) {
    int store_size = 1, action = 0, user, pos;
    string search, temp_string;
    GamePage *store = new(nothrow) GamePage[1000];
    if (!store) {
        cout << "Sem memória suficiente" << endl;
        return -1;
    }

    system("cls|clear");
    cout << "Entrar como:" << endl << "1 - usuário" << endl << "2 - administrador" << endl;
    while (cin >> user && user != 1 && user != 2) {
        cout << "Ação não reconhecida" << endl << "Tente novamente..." << endl;
    }

    cout << fixed << setprecision(2);

    switch (user) {
        case 1:
            user = userLogin(store, store_size);
            return user;
        case 2:
            user = admLogin(store, store_size);
            return user;
    }
    delete[] store;
    store = NULL;
    cout << "Entrada inválida" << endl << "Encerrando programa" << endl;
    return -1;

    //updateVector(store, store_size);
    //updateVector(store, store_size);

}

int userLogin(GamePage *store, int store_size) {
    int library_size = 0;
    GamePage *library = new(nothrow) GamePage[1000];
    if (!library) {
        cout << "Sem memória suficiente" << endl;
        return -1;
    }
    int action = 0, pos;
    string search;
    system("cls|clear");
    userActions();
    while (cin >> action && (action == 0 || action == 1 || action == 2 || action == 3 || action == 4)) {
        system("cls|clear");
        switch (action) {
            case 0:
                delete[] store;
                store = NULL;
                system("cls|clear");
                cout << "Fechando programa" << endl;
                delete[] store;
                delete[] library;
                store = library = NULL;
                return 0;
            case 1:
                ordenate(store, store_size);
                system("cls|clear");
                cout << "digite o nome do jogo que quer pesquisar" << endl;
                cin.ignore();
                getline(cin, search);
                pos = binarySearch(store, 0, store_size - 1, search);
                if (pos == 0) {
                    cout << "O jogo não existe na base de dados" << endl << endl;
                    userActions();
                }
                else {
                    system("cls|clear");
                    showContent(store, pos);
                    userActions();
                }
                break;
            case 2:
                system("cls|clear");
                ordenate(store, store_size);
                cout << "digite o nome do jogo que quer baixar" << endl;
                cin.ignore();
                getline(cin, search);
                pos = binarySearch(store, 0, store_size - 1, search);
                if (pos == 0) {
                    cout << "O jogo não existe na base de dados" << endl << endl;
                    userActions();
                }
                else {
                    system("cls|clear");
                    library_size = downloadContent(store, pos, library, library_size);
                    userActions();
                }
                break;
            case 3:
                if (library_size > 0) {
                    ordenate(library, library_size);
                    showAllContent(library, library_size);
                } else {
                    cout << "Você ainda não baixou nenhum jogo baixado" << endl << endl;
                }
                userActions();
                break;
            case 4:
                if (library_size > 0) {
                    system("cls|clear");
                    cin.ignore();
                    cout << "Qual jogo deseja remover? (Insira o título corretamente)" << endl;
                    showAllContent(store, store_size);
                    getline(cin, search);
                    ordenate(store, store_size);
                    removeGame(store, store_size, search);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "Não há jogos para serem removidos" << endl << endl;
                }
                userActions();
                break;
        }
    }
    cout << "Entrada inválida" << endl << "Encerrando programa" << endl;
    delete[] store;
    delete[] library;
    store = library = NULL;
    return -1;

}

int admLogin(GamePage *store, int store_size) {
    int action = 0, pos;
    string search;
    system("cls|clear");
    admActions();
    while (cin >> action && (action == 0 || action == 1 || action == 2 || action == 3 || action == 4 || action == 5 || action == 6)) {
        system("cls|clear");
        admActions();
        switch (action) {
            case 0:
                delete[] store;
                store = NULL;
                system("cls|clear");
                cout << "Fechando programa" << endl;
                return 0;
            case 1:
                system("cls|clear");
                if (store_size > 1) {
                    ordenate(store, store_size);
                }
                cin.ignore();
                store_size = createGame(store, store_size);
                admActions();
                break;
            case 2:
                if (store_size > 1) {
                    system("cls|clear");
                    cin.ignore();
                    cout << "Qual jogo deseja remover? (Insira o título corretamente)" << endl;
                    showAllContent(store, store_size);
                    getline(cin, search);
                    ordenate(store, store_size);
                    removeGame(store, store_size, search);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "Não há jogos para serem removidos" << endl << endl;
                }
                admActions();
                break;
            case 3:
                if (store_size > 0) {
                    ordenate(store, store_size);
                    system("cls|clear");
                    cin.ignore();
                    cout << "Qual jogo deseja alterar? (Insira o título corretamente)" << endl;
                    showAllContent(store, store_size);
                    getline(cin, search);
                    ordenate(store, store_size);
                    removeGame(store, store_size, search);
                    ordenate(store, store_size);
                    store_size = createGame(store, store_size);
                    system("cls|clear");
                }
                else {
                    system("cls|clear");
                    cout << "ainda não há jogos na loja" << endl << endl; 
                }
                admActions();
                break;
            case 4:
                ordenate(store, store_size);
                system("cls|clear");
                cout << "digite o nome do jogo que quer pesquisar" << endl;
                cin.ignore();
                getline(cin, search);
                pos = binarySearch(store, 0, store_size - 1, search);
                if (pos == 0) {
                    cout << "O jogo não existe na base de dados" << endl << endl;
                    admActions();
                }
                else {
                    system("cls|clear");
                    admActions();
                    showContent(store, pos);
                }
                break;
            case 5:
                ordenate(store, store_size);
                showAllContent(store, store_size);
                break;
            case 6:
                try {
                    writeData(store, store_size); 
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

void admActions() {
    cout << "O que fazer?" << endl;
    cout << "0 - Fechar programa" << endl << "1 - Adicionar jogo" << endl << "2 - Remover jogo" << endl << "3 - Alterar jogo" << endl << "4 - Pesquisar" << endl << "5 - Mostrar todo conteúdo da loja" << endl << "6 - Salvar conteúdo da loja" << endl;
}

void userActions() {
    cout << "O que deseja fazer?" << endl;
    cout << "0 - Fechar programa" << endl << "1 - Pesquisar" << endl << "2 - Baixar jogo" << endl << "3 - Ver jogos baixados" << endl << "4 - Excluir jogo" << endl;
}


int downloadContent(GamePage *store, int pos, GamePage *library, int library_size) {
    (library + library_size)->title = (store + pos)->title; 
    (library + library_size)->category = (store + pos)->category;
    (library + library_size)->developer = (store + pos)->developer = "";
    (library + library_size)->publishment.day = (store + pos)->publishment.day;
    (library + library_size)->publishment.month = (store + pos)->publishment.month;
    (library + library_size)->publishment.year = (store + pos)->publishment.year;
    (library + library_size)->note = (store + pos)->note;
    (library + library_size)->price = (store + pos)->price;
    (library + library_size)->time_to_beat = (store + pos)->time_to_beat;
    (library + library_size)->num_players = (store + pos)->num_players;
    (library + library_size)->language = (store + pos)->language;
    return library_size + 1;
}

int createGame(GamePage *store, int store_size) {
    /*
    store = updateVector(store, store_size, store_size);
    if (!store) {
        return store_size;
    }
    */

    int pos;
    string temp_string;
    bool valid_name = false;
    cout << "digite o título do jogo" << endl;
    getline(cin, (store + store_size)->title);
    if (store_size > 1) {
        while (!valid_name) {
            if ((store + store_size)->title != temp_string) {
                valid_name = true;
            }
            pos = binarySearch(store, 0, store_size - 1, (store + store_size)->title);
            temp_string = (store + pos)->title;
            if ((store + store_size)->title == temp_string) {
                valid_name = false;
                cout << "o jogo ja existe" << endl;
                getline(cin, (store + store_size)->title);
            }
        }
    }

    cout << "digite a categoria do jogo" << endl;
    getline(cin, (store + store_size)->category);

    cout << "digite o nome do desenvolvedor do jogo" << endl;
    getline(cin, (store + store_size)->developer);

    cout << "digite o mês de lançamento" << endl;
    while (cin >> (store + store_size)->publishment.month && ((store + store_size)->publishment.month > 12 || (store + store_size)->publishment.month < 1)) {
        cout << "Insira um mês válido" << endl;
    }
    cout << "digite o dia de lançamento" << endl;
    if ((store + store_size)->publishment.month == 2) {
        while (cin >> (store + store_size)->publishment.day && ((store + store_size)->publishment.day < 1 || (store + store_size)->publishment.day > 28)) {
            cout << "insira um dia válido para o mês" << endl;
        }
    }
    else {
        while (cin >> (store + store_size)->publishment.day && ((store + store_size)->publishment.day > 31 || (store + store_size)->publishment.day < 1)) {
            cout << "Insira um dia válido" << endl;
        }
    }
    cout << "digite o ano de lançamento" << endl;
    while (cin >> (store + store_size)->publishment.year && ((store + store_size)->publishment.year > 2024 || (store + store_size)->publishment.year < 1960)) {
        cout << "Insira um ano válido" << endl;
    }

    cout << "de uma nota de 0.0 a 5.0 ao jogo" << endl;
    while (cin >> (store + store_size)->note && ((store + store_size)->note < 0 || (store + store_size)->note > 5)) {
        cout << "avalie o jogo corretamente" << endl;
    }

    cout << "digite o preço do jogo" << endl;
    while (cin >> (store + store_size)->price && ((store + store_size)->price > 400)) {
        cout << "digite um preço justo" << endl;
    }

    cout << "digite o tempo para zerar o jogo em horas" << endl;
    while (cin >> (store + store_size)->time_to_beat && (store + store_size)->time_to_beat < 1) {
        cout << "digite um tempo válido" << endl;
    }

    cout << "Quanto jogadores podem jogar?" << endl << "- Single player" << endl << "- Multiplayer" << endl << "- Coop" << endl;
    cin.ignore();
    getline(cin, (store + store_size)->num_players);
    (store + store_size)->num_players = convertString((store + store_size)->num_players);
    while ((store + store_size)->num_players != "SINGLE PLAYER" && (store + store_size)->num_players != "MULTIPLAYER" && (store + store_size)->num_players != "COOP") {
        cout << "escolha uma opção válida" << endl;
        getline(cin, (store + store_size)->num_players);
        (store + store_size)->num_players = convertString((store + store_size)->num_players);
    }

    cout << "Selecione o idioma" << endl; 
    getline(cin, (store + store_size)->language);
    
    system("cls|clear");

    return store_size + 1;
}

void removeGame(GamePage *vector, int vector_size, string game_to_remove) {
    int pos;
    pos = binarySearch(vector, 0, vector_size - 1, game_to_remove);
    (vector + pos)->title = ""; 
    (vector + pos)->category = "";
    (vector + pos)->developer = "";
    (vector + pos)->publishment.day = 0;
    (vector + pos)->publishment.month = 0;
    (vector + pos)->publishment.year = 0;
    (vector + pos)->note = 0;
    (vector + pos)->price = 0;
    (vector + pos)->time_to_beat = 0;
    (vector + pos)->num_players = "";
    (vector + pos)->language = "";
}

void showContent(GamePage *vector, int pos) {
    cout << endl << "----- JOGOS -----" << endl;
        if ((vector + pos)->title != "") {
            cout << "Titulo: " << (vector + pos)->title << endl << "Categoria: " << (vector + pos)->category << endl << "Desenvolvedor: " << (vector + pos)->developer << endl << "Pulicação: " << (vector + pos)->publishment.day << "/" << (vector + pos)->publishment.month << "/" << (vector + pos)->publishment.year << endl << "Avaliação geral: " << (vector + pos)->note << endl << "Preço: R$" << (vector + pos)->price << endl << "Tempo de jogo: " << (vector + pos)->time_to_beat << " horas" << endl << "Número de jogadores: " << (vector + pos)->num_players << endl << "Idioma: " << (vector + pos)->language << endl;
        }
    cout << endl;
}

void showAllContent(GamePage *vector, int vector_size) {
    cout << endl << "----- JOGOS -----" << endl;
    for (int i = 0; i < vector_size; i++) {
        if ((vector + i)->title != "") {
            cout << "Titulo: " << (vector + i)->title << endl << "Categoria: " << (vector + i)->category << endl << "Desenvolvedor: " << (vector + i)->developer << endl << "Pulicação: " << (vector + i)->publishment.day << "/" << (vector + i)->publishment.month << "/" << (vector + i)->publishment.year << endl << "Avaliação geral: " << (vector + i)->note << endl << "Preço: R$" << (vector + i)->price << endl << "Tempo de jogo: " << (vector + i)->time_to_beat << " horas" << endl << "Número de jogadores: " << (vector + i)->num_players << endl << "Idioma: " << (vector + i)->language << endl << endl;
        }
    }
}

void writeData(GamePage *store, int store_size) {
    ofstream file;
    file.open("data.csv");
    file << "Título,Categoria,Desenvolvedor,Data de publicação, Avaliação, Preço, Tempo de jogo, Número de jogadores, Idioma" << endl;
    for (int i = 0; i < store_size; i++) {
        if ((store + i)->title != "") {
            file << (store + i)->title << ',' << (store + i)->category << ',' << (store + i)->developer << ',' << (store + i)->publishment.month << '/' << (store + i)->publishment.day << '/' << (store + i)->publishment.year << ',' << (store + i)->note << ',' << "R$" << (store + i)->price << ',' << (store + i)->time_to_beat << ',' << (store + i)->num_players << ',' << (store + i)->language << endl;
        }
    }
   file.close(); 
}

void ordenate(GamePage *vector, int vector_size) {
    if (vector_size == 1) {
        return;
    }
    for (int i = 0; i < (vector_size - 1); i++) {
        if ((vector + i)->title > (vector + i + 1)->title) {
            swap((vector + i)->title, (vector + i + 1)->title);
        }
    }
    ordenate(vector, vector_size - 1);
}

int binarySearch(GamePage *vector, int begin, int end, string search) {
    if (begin > end) {
        return 0;
    }
    
    int mid;
    mid = begin + (end - begin) / 2;
    if ((vector + mid)->title == search) {
        return mid;
    }

    if ((vector + mid)->title > search) {
        return binarySearch(vector, begin, mid - 1, search);
    }

    return binarySearch(vector, mid + 1, end, search);

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
void updateVector(GamePage *store, int store_size) {
    GamePage *aux = store;
    store = NULL;
    store = new(nothrow) GamePage[store_size+2];
    store = aux;

    if (store_size >= capacity) {
        capacity *= 2;
        GamePage *store_aux = new(nothrow) GamePage[capacity];
        if (!store_aux) {
            cout << "Out of memory" << endl;
            return -1;
        }
        for (int i = 0; i < store_size; i++) {
            *(store_aux + i) = *(store + i);
        }
        delete[] store;
        return *store_aux;
    }
    return *store;
    }
*/
