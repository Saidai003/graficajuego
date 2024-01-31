#include <iostream>
#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <sstream>

struct BananaFile{
    std::string name;
    std::string exte;
    std::string autor;
    std::string data;
    bool read;
    bool write;
    bool exec;
    bool open;
    int date = time(nullptr);
    int size = sizeof(BananaFile); //en bytes

};

struct BananaDire{
    std::string name;
    std::string autor;
    bool write;
    bool open;
    int date = time(nullptr);
    int size = sizeof(BananaDire); //en bytes
    std::vector<BananaFile> files;
    std::vector<BananaDire> dires;
};

std::string BananaMetadata(BananaFile file){
    std::stringstream ss;
    ss << "Name: " << file.name << std::endl;
    ss << "Extension type: " << file.exte << std::endl;
    ss << "Author: " << file.autor << std::endl;
    ss << "Data: " << file.data << std::endl;
    ss << "Read: " << file.read << std::endl;
    ss << "Write: " << file.write << std::endl;
    ss << "Execute: " << file.exec << std::endl;
    ss << "Open: " << file.open << std::endl;
    ss << "Date in seconds: " << file.date << std::endl;
    ss << "Size (bytes): " << file.size;
    return ss.str();
};

bool comp (BananaDire a, BananaDire b) {
        return a.name == b.name;
}

std::string BananaMetadata(BananaDire dire){
    std::stringstream ss;
    ss << dire.name << std::endl;
    ss << dire.date << std::endl;
    ss << dire.open << std::endl;
    ss << "Tfiles: " << dire.files.size() << std::endl;
    ss << "TDire: " << dire.dires.size() << std::endl;
    ss << "Size(bytes): " << dire.size << std::endl; //Podria ser mas preciso
    return ss.str();
};

void BananaSave(BananaFile file, std::string newdata){
    file.data = newdata;
};

void BananaUpSize(BananaDire dire){
    int totalsize = 0;
    for (auto it = dire.dires.rbegin(); it != dire.dires.rend(); ++it) {
        totalsize += sizeof(*it);
    }
    for (auto it = dire.files.rbegin(); it != dire.files.rend(); ++it) {
        totalsize += sizeof(*it);
    }
    dire.size = totalsize;
};

void BananaAddDire(BananaDire dire, BananaDire newdire){
    dire.dires.push_back(newdire);
};

class BananaMechanicsFS
{
private:
    std::string ADir; //
    BananaDire root; //
public:
    BananaMechanicsFS(){
        root.name = "root";
        root.autor = "root";
        root.write = true;
        root.open = true;
        root.date = time(nullptr);
    };
    ~BananaMechanicsFS();
    BananaDire getRoot(){
        return root;
    };
    std::string getADir(){
        return ADir;
    };
    void setADir(std::string newdir){
        ADir = newdir;
    };

}; //deprecado




/*

Old Banana Classes

class F{ //Archivo
    public:
    std::string name;
    std::string exte = ".txt";
    std::string autor = "";
    std::string data = "";
    bool read = true;
    bool write = true;
    bool exec = true;
    bool open = true;
    int date;
    int size = 0; //en bytes


    F(std::string name, std::string exte){
        this->name = name;
        this->exte = exte;
        this->date = time(nullptr);
    };

    std::string metadata() {
    std::stringstream ss;
    ss << "Name: " << name << std::endl;
    ss << "Extension type: " << exte << std::endl;
    ss << "Author: " << autor << std::endl;
    ss << "Data: " << data << std::endl;
    ss << "Read: " << read << std::endl;
    ss << "Write: " << write << std::endl;
    ss << "Execute: " << exec << std::endl;
    ss << "Open: " << open << std::endl;
    ss << "Date in seconds: " << date << std::endl;
    ss << "Size (bytes): " << size;


    
    return ss.str();
    }

    void save(std::string newdata){
       data = newdata;
    }

};

class D{ //Directorio

    public:

    std::string name;
    std::string autor;
    bool write = true;
    bool open = true;
    int date;
    int size; //en bytes
    std::vector<F> files;
    std::vector<D> dires;

    D(){
        
    };

    D(std::string name, std::string autor, bool write, bool open){
        this->name = name;
        this->autor = autor;
        this->write = write;
        this->open = open;
        this->date = time(nullptr);
    };

    std::string metadata() {
    std::stringstream ss;
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


*/







//Nota: compilación requiere -lncourses


// need to find a way to make screen terminal size adaptive

char screen[32][32] = {
    {'<', ' ', 'x', '+', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|'},
    {' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '|'}
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

    

BananaDire RecursiveNav(BananaDire root, int cursorX, int cursorY){

        BananaDire updatepreviousfolder;
        //Carpeta actual
        BananaDire current = root;

    while(1){
         for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 32; j++) {
                if(i == cursorY && j == cursorX) {
                    if(i == 0 && j == 0){
                        printf("(<)");
                    }else if(i == 0 && j == 1){
                        printf("(>)");
                    }else if(i == 0 && j == 2){
                        printf("(X)");
                    }else if(i == 0 && j == 3){
                        printf("(+)");
                    }else if(i >= 3 && j == 0){
                        printf("|||->"); 
                    }else{
                        printf("@");
                    }
                 
                }else{
          if (i == 0 && j > 4 && j < current.name.size()+5){
    printf("%c", current.name[j-5]);
}else{
     bool printed = false;

    for(int z = current.dires.size() - 1; z >= 0; --z){
        auto dafolder = current.dires[z];
        
        if(i > 3 && z == (i - 4) && j > 1 && (j-2) < dafolder.name.size()){
          
            printf("%c", dafolder.name[j-2]);
            printed = true;
            break;
        }
    }
    if(!printed){
        for(int b = current.files.size() - 1; b >= 0; --b){
            auto dafile = current.files[b];

            if(i > (3 + current.dires.size()) && b == (i - 4 - current.dires.size()) && j > 0 && (j-2) < dafile.name.size()){
                
                printf("%c", dafile.name[j-2]);
                printed = true;
                break;
            }
        }
    }
    if(!printed){
        printf("%c", screen[i][j]); 
    }
} 
                }
                    
                
            }
            printf("\n");
        }

        // input
        int input = getch();

        //Actualizar la posicion del cursor basada en la entrada
        if (input == 'w' && cursorY > 0) {
            cursorY--;
        } else if (input == 'a' && cursorX > 0) {
            cursorX--; 
        } else if (input == 's' && cursorY < 15) {
            cursorY++;
        } else if (input == 'd' && cursorX < 31) {
            cursorX++;
        }
        //Metodo: Crear carpeta
        if(input == 'e' && cursorX == 3 && cursorY == 0){
            try{
                printf("\033[H\033[J"); 
                printf("Write folder's name and press Enter to create it\n");
                printf("Folder's name: ");

                endwin(); 
                std::string dirname;
                
                std::cin >> dirname;

                //F newdir("[" + dirname + "]","user", true, true);  Crear un nuevo directorio  Con Clases
                BananaDire newdir;
                newdir.name = "["+ dirname +"]";
                newdir.autor = "user";
                newdir.write = true;
                newdir.open = true;
                  // Crear un nuevo directorio∫
                current.dires.emplace_back(newdir); // Añadir el nuevo directorio a 'dires'

                //showdire = &newdir; // esto sirve para cambiar de directorio

                dirname = "";
                

                printf("\033[H\033[J"); 

                initscr(); 
                noecho(); 
                cbreak(); 

            }catch (const std::out_of_range& e) {
                //no existe la carpeta en ese indice=posicion
                std::cerr << "Out of Range error: " << e.what() << '\n';
            }
        }

       
        
        //Metodo: Acceder a carpeta.
        //Revisar más adelante con max.
              for(int z = current.dires.size() - 1; z >= 0; --z){
                BananaDire it = current.dires[z];
                        if(input == 'e'  && cursorY-4 == z && cursorX > 0){
                            try{
                                   printf("\033[H\033[J");
                                updatepreviousfolder = RecursiveNav(it, cursorX, cursorY);
                                    if(comp(it, updatepreviousfolder)){
                                        current.dires.erase(current.dires.begin() + z);
                                    }
                                    
                                current.dires.emplace_back(updatepreviousfolder); // Añadir el nuevo directorio a 'dires'
                                
                            }catch (const std::out_of_range& e) {
                                //no existe la carpeta en ese indice=posicion
                                std::cerr << "Out of Range error: " << e.what() << '\n';
                            }
                        }
                        if(input == 'e' && cursorY-4 == z && cursorX == 1){
                            printf("\033[H\033[J");
                            //mostrar metadata
                              std:: cout << "Name: " << it.name << std::endl;
                            std:: cout << "Autor: " << it.autor << std::endl;
                            std:: cout << "Date in seconds: " << it.date << std::endl;
                            std:: cout << "Size in bytes: " << it.size << std::endl;
                          

                        }
                }
                 for(int b = current.dires.size() - 1; b >= 0; --b){
                      BananaFile it = current.files[b];
                     if(input == 'e' && cursorY-4-current.dires.size() == b && cursorX == 1){
                        printf("\033[H\033[J");
                            //mostrar metadata
                              std:: cout << "Name: " << it.name << std::endl;
                            std:: cout << "Autor: " << it.autor << std::endl;
                            std:: cout << "Date in seocnds: " << it.date << std::endl;
                            std:: cout << "Size in bytes: " << it.size << std::endl;
                            std:: cout << "Autor: " << it.autor << std::endl;
                            std:: cout << "Open: " << it.open << std::endl;
                            std:: cout << "Write: " << it.write << std::endl;
                            std:: cout << "Data: " << it.data << std::endl;
                            std:: cout << "Extension: " << it.exte << std::endl;

                        }
                 }
        
        //Crear archivo
         if(input == 'e' && cursorY > 3 && cursorX < 1){
             try{
                printf("\033[H\033[J"); 
                printf("Write files's name and press Enter to create it\n");
                printf("Files's name: ");

                endwin(); 
                std::string filename;
                
                std::cin >> filename;

                //F newdir("[" + dirname + "]","user", true, true);  Crear un nuevo archivo  Con Clases
                BananaFile newfile;
                newfile.name = " "+ filename;
                newfile.autor = "user";
                newfile.write = true;
                newfile.open = true;
                  // Crear un nuevo directorio∫
                current.files.emplace_back(newfile); // Añadir el nuevo directorio a 'files'

                filename = "";
                
                printf("\033[H\033[J"); 

                initscr(); 
                noecho(); 
                cbreak(); 

            }catch (const std::out_of_range& e) {
                //no existe la carpeta en ese indice=posicion
                std::cerr << "Out of Range error: " << e.what() << '\n';
            }
         }
           
       

        usleep(100000);
        if(input == 'e' && cursorX == 0  && cursorY == 0){
            return current;
        }
            printf("\033[H\033[J");
    } // Print the screen

}





int main() {
    initscr(); 
    noecho(); 
    cbreak(); 
        // Move the cursor back to the beginning
        //printf("\033[H");

    //BananaDire desktop("main","user", true, true) Old method;
    BananaDire desktop;
    desktop.name = "main";
    desktop.autor = "user";
    desktop.write = true;
    desktop.open = true;
    BananaDire *showdire = &desktop;

    int cursorX = 1;
    int cursorY = 1;

    int start;

  for (int i = 0; i < 15; i++) {
            for (int j = 8; j < 24; j++) {
                        printf("%c ", bootscreen[i][j]);
            }
            printf("\n");
    }
    //usleep(1000000);
    printf("Presione 2 veces cualquier tecla para comenzar");
    scanf("%d", &start);
      printf("\033[H\033[J");
        RecursiveNav(*showdire, cursorX, cursorY);

    endwin(); 

    return 0;
}