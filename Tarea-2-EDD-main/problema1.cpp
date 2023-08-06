#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Implementación Nodo
struct tNodo {
    char info;
    tNodo* sig;
};

// Implementación Lista Enlazada
class tLista {
    private:
        tNodo* head;
        tNodo* tail;
        tNodo* curr;
        unsigned int listSize;
        unsigned int pos; // Posición curr en la lista
    public:
        // Casteo y Destrucción
        tLista() { 
            head = tail = curr = nullptr;
            listSize = 0;
            pos = 0;
        }
        ~tLista(){
            clear();
        }
        typedef char tElemLista;

        // IMPLEMENTACIÓN DE MÉTODOS

        /*****
        * void clear()
        ******
        * Resumen: 
        *   borra todos los elementos de la lista, reinicializándola vacía.
        ******
        * Input:
        *   No se le entregan inputs/parámetros.
        ******
        * Returns:
        *   No devuelve ningún valor específico, al ser función de tipo void, sólo reinicia la lista.
        *****/

        void clear() {
            tNodo* aux;
            curr = head; 
            while (curr != nullptr){
                aux = curr;
                curr = curr->sig;
                delete aux;
            }
            head = tail = curr = nullptr;
            listSize = 0;
            pos = 0;
        }

        /*****
        * void insert()
        ******
        * Resumen: 
        *   Inserta un valor entregado como parámetro en la lista, si la cabeza está vacía, se inserta ahí.
        *   De lo contrario, se inserta en la posición siguiente y va aumentando la lista enlazada.
        ******
        * Input:
        *   char value: el valor que va a ser insertado.
        ******
        * Returns:
        *   No devuelve ningún valor específico, al ser función de tipo void, sólo inserta el valor.
        *****/

        void insert(char value) {
            tNodo* newNode = new tNodo;
            newNode->info = value;
            newNode->sig = nullptr;

            if (head == nullptr) {
                head = tail = newNode;
            } else {
                tail->sig = newNode;
                tail = newNode;
            }
            listSize++;
        }

        /*****
        * int currPos()
        ******
        * Resumen: 
        *   Al llamar la función, esta devuelve el valor en formato int de la posición donde se
        *   encuentra curr actualmente
        ******
        * Input:
        *   No se le entregan inputs/parámetros.
        ******
        * Returns:
        *   Retorna la posición del elemento curr.
        *****/
        int currPos() {
            return pos;
        }

        /*****
        * bool moveToPos()
        ******
        * Resumen: 
        *   Se le entrega un valor númerico representando la posición en la lista a la que se desea ir, y esta
        *   función se "mueve" hacia ella.
        ******
        * Input:
        *   unsigned int pos: Se entrega la posición a la que se quiere desplazar.
        ******
        * Returns:
        *   Si la posición entregada se escapa de los límites de la lista (out of bounds por así decirlo),
        *   se retorna un valor false.
        *   Si la posición entregada se encuentra en la lísta, se mueve el elemento curr hacia la posición deseada.
        *****/

        bool moveToPos(unsigned int pos) {
            if (pos < 0 || pos > listSize) {
                return false;
            }
            curr = head;
            this->pos = 0;
            while (this->pos < pos) {
                curr = curr->sig;
                this->pos++;
            }
            return true;
        }

        /*****
        * char getValue()
        ******
        * Resumen Función:
        *   Obtiene el valor del elemento actual de la lista.
        ******
        * Input:
        *   No se le entrega ningun parametro/input
        ******
        * Returns:
        *   char, Valor del elemento actual de la lista. Si no hay elemento actual, retorna el carácter nulo '\0'.
        *****/ 
        char getValue() {
            if (curr == nullptr){
                return '\0';
            }
            return curr->info;
        }

        /*****
        * void display()
        ******
        * Resumen Función:
        *   Muestra en la salida estándar los elementos de la lista.
        ******
        * Input:
        *   No se le entrega ningun parametro/input
        ******
        * Returns:
        *   No retorna ningun dato, al ser una función de tipo void, solo muestra los elementos de la lista.
        *****/                    
        void display() {
            tNodo* curr = head;
            while (curr != nullptr) {
                cout << curr->info << " ";
                curr = curr->sig;
            }
            cout << endl;
        }

        /*****
        * void INSERTAR()
        ******
        * Resumen Función:
        *   Inserta un elemento con un valor dado en la posición especificada de la lista.
        ******
        * Input:
        *   unsigned int pos, Posición en la que se desea insertar el elemento.
        *   char value, Valor del elemento a insertar.
        ******
        * Returns:
        *   No retorna ningun dato, al ser una función de tipo void, solo inserta el elemento.
        *****/ 
        void INSERTAR(unsigned int pos, char value){
            if (pos < 0 || pos > listSize) {
                return; // La posición está fuera de rango, no se puede insertar
            }

            if (pos == listSize) {
                // Si la posición es igual al tamaño de la lista, se inserta al final
                insert(value);
            } else {
                if (pos == 0) {
                    // Si la posición es 0, se inserta al principio
                    tNodo* newNode = new tNodo;
                    newNode->info = value;
                    newNode->sig = head;
                    head = newNode;
                    listSize++;
                } else {
                    // Si la posición es en medio de la lista
                    moveToPos(pos - 1); // Mover a la posición anterior
                    tNodo* newNode = new tNodo;
                    newNode->info = value;
                    newNode->sig = curr->sig;
                    curr->sig = newNode;
                    listSize++;
                }
            }
        }

        /*****
        * void BORRAR()
        ******
        * Resumen Función:
        *   Borra el elemento en la posición especificada de la lista.
        ******
        * Input:
        *   unsigned int pos, Posición del elemento a borrar.
        ******
        * Returns:
        *   No devuelve ningún valor específico, al ser función de tipo void, solo borra el elemento.
        *****/ 
        void BORRAR(unsigned int pos) {
            if (pos < 0 || pos >= listSize) {
                return; // La posición está fuera de rango, no se puede borrar
            }
            if (pos == 0) {
                // Si la posición es 0, se borra el primer nodo
                tNodo* nodoBorrar = head;
                head = head->sig;
                delete nodoBorrar;
                listSize--;
            } else {
                // Si la posición es en medio de la lista o al final
                moveToPos(pos-1); // Mover a la posición anterior
                tNodo* nodoBorrar = curr->sig;
                curr->sig = nodoBorrar->sig;
                delete nodoBorrar;
                listSize--;
                if (pos == listSize) {
                    // Si la posición es la última, se actualiza la cola de la lista
                    tail = curr;
                }
            }
        }
    
        /*****
        * void INTERCAMBIO()
        ******
        * Resumen Función:
        *   Intercambia/reemplaza un elemento en la posición especificada con un nuevo valor dado.
        ******
        * Input:
        *   int pos, Posición del elemento a intercambiar.
        *   char n, Nuevo valor para el elemento intercambiado.
        ******
        * Returns:
        *   Al ser una funcion void, no retorna nada, sólo intercambia los nucleótidos.
        *****/ 

        void INTERCAMBIO(int pos, char n){
            INSERTAR(pos, n);
            BORRAR(pos+1);
            return;
        }
        
        /*****
        * string convertirAString() const
        ******
        * Resumen Función:
        *   Convierte los elementos de la lista en una cadena de caracteres
        ******
        * Input:
        *   No se le entregan parametros/inputs
        * .......
        ******
        * Returns:
        *   string, Cadena de caracteres que contiene la lista enlazada
        *****/
        string convertirAString() const {
            string listaString;
            tNodo* curr = head;
            while (curr!= nullptr){
                listaString += curr->info;
                curr = curr->sig;
            }
            return listaString;
        }

};


int main() {
    tLista lista;
    string nombre_archivo = "secuencias-nucleotidos.txt"; // Se lee el archivo
    ifstream archivo(nombre_archivo.c_str());
    string linea, secuencia;
    int largo, k, m; // largo, secuencias finales, modificaciones (respectivamente), posición
    string modificacion; // Método a llamar
    char nucleotido; // Nucletóido
    int counter = 0;

    if (!archivo.is_open()) { 
        cout << "Error al abrir el archivo" << endl; exit(1); // En caso de no abrir
    }

    else {
        while (counter < 2 && getline(archivo, linea)){ // Leer las lineas del txt
            counter++;
            if (counter == 1) {
                size_t pos = linea.find(" ");
                largo = stoi(linea.substr(0, pos)); // Obtiene el Largo
                secuencia = linea.substr(pos+1, largo); // Guarda la secuencia de nucleótidos
                for(char c : secuencia){
                    lista.insert(c);
                }
            } else if(counter == 2){
                k = stoi(linea); // Guarda las secuencias a realizar
            }

        }
        for(int i=0; i < k; i++) {
            archivo >> m; // Guarda las modificaciones
            for(int x=0; x<m; x++) {
                string modificacion;
                int pos;
                archivo >> modificacion;
                if(modificacion == "INSERTAR"){
                    archivo >> pos >> nucleotido;
                    lista.INSERTAR(pos, nucleotido);
                }
                if(modificacion == "BORRAR") { // Revisa qué modificación hacer
                    archivo >> pos;
                    lista.BORRAR(pos);
                }
                if(modificacion == "INTERCAMBIAR"){
                    archivo >> pos >> nucleotido;
                    lista.INTERCAMBIO(pos, nucleotido);
                }
            }

            string nombre_archivo_salida = "secuencias-reconstruidas.txt"; // Crea el archivo de salida
            ofstream archivoEscritura;
            archivoEscritura.open(nombre_archivo_salida.c_str(), fstream::app);
            if (!archivoEscritura.is_open()) {
                cout << "Error al abrir el archivo" << endl;
                return 1;
            } 
            //Escribe en el archivo de salida
            string listaModificada = lista.convertirAString();
            archivoEscritura << listaModificada<< endl;
            archivoEscritura.close();
            // Escribe secuencia reestructurada al terminar el for
            lista.clear();
            for(char c : secuencia){
                lista.insert(c);
            }
        };

        archivo.close(); // Cierra el archivo (de algo sirvió IWI131)
    }
    lista.~tLista();
    return 0;
}

