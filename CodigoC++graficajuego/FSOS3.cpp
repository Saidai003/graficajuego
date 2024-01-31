#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <sstream>

using namespace std;

class F{ //Archivo
    public:
    string name;
    string exte;
    string autor;
    string data;
    bool read = true;
    bool write = true;
    bool exec = true;
    bool open = true;
    int id;
    int date;
    int size; //en bytes


    F(string name, string exte, string autor, bool read, bool write, bool exec, bool open, int id, int date, int size){
        this->name = name;
        this->exte = exte;
        this->autor = autor;
        this->read = read;
        this->write = write;
        this->exec = exec;
        this->open = open;
        this->id = id;
        this->date = date;
        this->size = size;
    };

    string metadata() {
    stringstream ss;
    ss << name << endl;
    ss << exte << endl;
    ss << autor << endl;
    ss << data << endl;
    ss << read << endl;
    ss << write << endl;
    ss << exec << endl;
    ss << open << endl;
    ss << id << endl;
    ss << date << endl;
    ss << size;
    return ss.str();
    }

    void save(string newdata){
       data = newdata;
    }

};

class D{ //Directorio

    public:

    string name;
    string autor;
    bool write = true;
    bool open = true;
    int date;
    int size; //en bytes
    vector<F> files;
    vector<D> dires;

    D(){
        
    };

    D(string name, string autor, bool write, bool open){
        this->name = name;
        this->autor = autor;
        this->write = write;
        this->open = open;
        this->date = time(nullptr);
    };

    string metadata() {
    stringstream ss;
    ss << name << endl;
    ss << date << endl;
    ss << open << endl;
    ss << "Tfiles: " << files.size() << endl;
    ss << "TDire: " << dires.size() << endl;
    ss << "Size(bytes): " << size << endl; //Podria ser mas preciso
    return ss.str();
    }

    void updateSize(){
        int totalsize = 0;
        for (auto it = dires.rbegin(); it != dires.rend(); ++it) {
            totalsize += sizeof(*it);
        }
        for (auto it = files.rbegin(); it != files.rend(); ++it) {
            totalsize += sizeof(*it);
        }
        size = totalsize;
    }
    void addDire(D newdire){
        dires.push_back(newdire);
    }


};

    char screen[32][32] = {
    {'<', '>', 'x', '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };


    char bootscreen[32][32] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', '@', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B', 'A', 'N', 'A', 'N', 'A', 'O', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '@', '@', '@', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };

int main() {
    initscr(); // Initialize the window
    noecho(); // Don't echo() while we do getch
    cbreak(); // Disable line buffering

    D desktop("main","user", true, true);
    D *showdire = &desktop;

    int cursorX = 1;
    int cursorY = 1;

    int start;

  for (int i = 0; i < 32; i++) {
            for (int j = 8; j < 24; j++) {
                        printf("%c ", bootscreen[i][j]);
            }
            printf("\n");
    }


 scanf("%d", &start);

    while (1) {
        // Move the cursor back to the beginning
        printf("\033[H");

        //Carpeta actual
        D current = *showdire;
       
     
        // Print the screen
 for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if(i == cursorY && j == cursorX) {
                    if(i == 0 && j == 0){
                        printf("(<)");
                    }else if(i == 0 && j == 1){
                        printf("(>)");
                    }else if(i == 0 && j == 2){
                        printf("(X)");
                    }else if(i == 0 && j == 3){
                        printf("(+)");
                    }
                    printf("o");
                }else{
                    if (i == 0 && j > 4 && j < current.name.size()+5){
                        printf("%c", current.name[j-5]);
                    }else{
                        for(int z = current.dires.size() - 1; z >= 0; --z){
                            auto it = current.dires[z];
                            if(i > 3 && z == (i - 4)){//imprimer las carpetas
                                printf("%c", it.name[j]);
                   
                            }
                        }
                        for(int z = current.files.size() - 1; z >= 0; --z){
                            auto it = current.files[z];
                            if(i > 3 + current.dires.size() && z == (i - 4 - current.dires.size()) && j < it.name.size()){//imprimer las carpetas
                                printf("%c", it.name[j]);
                            }
                        }
                                     printf("%c", screen[i][j]); 
                    }
                }
            }
            printf("\n");
        }

        // Get the user's input
        int input = getch();

        // Update the user's position based on the input
        if (input == 'w' && cursorY > 0) {
            cursorY--;
        } else if (input == 'a' && cursorX > 0) {
            cursorX--; 
        } else if (input == 's' && cursorY < 15) {
            cursorY++;
        } else if (input == 'd' && cursorX < 15) {
            cursorX++;
        }
   if(input == 'e' && cursorX == 3 && cursorY == 0){
    try{ //existe la carpeta en ese indice=posicion
        printf("\033[H\033[J");  // Limpia la pantalla y mueve el cursor al comienzo
        printf("Select the directory's name and press Enter to create it\n");
        printf("Directory name: ");

        endwin(); // End curses mode
        string dirname;

        
            std::cin >> dirname;
        

        D newdir(dirname,"user", true, true); // Crear un nuevo directorio

        desktop.dires.emplace_back(newdir); // Añadir el nuevo directorio a 'dires'

        //showdire = &newdir; // esto sirve para cambiar de directorio

        printf("\033[H\033[J");  // Limpia la pantalla y mueve el cursor al comienzo

        initscr(); // Initialize the window
        noecho(); // Don't echo() while we do getch
        cbreak(); // Disable line buffering

    }catch (const std::out_of_range& e) {
        //no existe la carpeta en ese indice=posicion
    }
}
        usleep(100000);
    }

    endwin(); // End curses mode

    return 0;
}
//Sin voz para no despertar a nadie

// Video rapido y bruto de como funciona el sistema de archivos

// Perdi mucho tiempo en buscar una forma adecuada de compilar C++ con los recursos que tengo

//y para variar

//Me entusiasme y quise hacer una interfaz con Ascii. MALA idea.

// demostracion de la funcionalidad ahora. La mayor parte de las funcionalidades quedaron detras de el uso de


