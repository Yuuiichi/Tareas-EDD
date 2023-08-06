#include <iostream>
#include <algorithm>

using namespace std;

// Struct Arbol Binario
struct nodoABB {
    int info;
    nodoABB* izq;
    nodoABB* der;
};

// Implementación ABB
class tABB {
private:
    nodoABB* raiz; // puntero al nodo raíz del ABB
    int nElems;    // cantidad de elementos en el ABB
    typedef int tElem;

public:
    // Constructor
    tABB() {
        raiz = nullptr;
        nElems = 0;
    }

    // Destructor
    ~tABB() {
        clear();
    }       
    
    /*****
    * nodoABB* newNode()
    ******
    * Crea un nuevo nodo para el árbol binario de búsqueda (ABB) con el elemento dado.
    ******
    * Input:
    * int item : Elemento que será almacenado en el nuevo nodo del ABB
    * .......
    ******
    * Returns:
    * nodoABB*, Puntero al nuevo nodo creado
    *****/
    nodoABB* newNode(int item) {
        nodoABB* nuevoNodo = new nodoABB;
        nuevoNodo->info = item;
        nuevoNodo->izq = nullptr;
        nuevoNodo->der = nullptr;
        return nuevoNodo;
    }
    
    /*****
    * void insert
    ******
    * Resumen Función:
    *   Recibe un solo dato y lo inserta en el árbol
    ******
    * Input:
    *   tElem info : información que solamente la estructura de datos puede usar
    ******
    * Returns:
    *   No otorga returns al tratarse de una función void().
    *****/
    void insert(tElem info) {
        if (raiz != nullptr)
            insercion(raiz, info);
        else {
            raiz = newNode(info);
        }
    }

    /*****
    * void insercion()
    ******
    * Resumen: Función auxiliar de insert(), Realiza la inserción de un nuevo elemento en un subárbol de el arbol.
    ******
    * Input:
    * nodoABB*& nodo: Puntero al nodo raíz del subárbol en el que se realizará la inserción.
    * tElem info: Elemento a insertar en el subárbol.
    ******
    * No otorga returns al tratarse de una función Void.
    *****/ 
    void insercion(nodoABB*& nodo, tElem info) {
        if (nodo == nullptr) {
            nodo = newNode(info);
        } else if (info < nodo->info) {
            insercion(nodo->izq, info);
        } else if (info > nodo->info) {
            insercion(nodo->der, info);
        }
    }

    /*****
    * nodoABB* find()
    ******
    * Resumen, Busca un elemento en el arbol y devuelve un puntero al nodo que contiene el elemento.
    ******
    * Input:
    * tElem info, dato a buscar en el árbol.
    ******
    * Returns:
    *   nodoABB*: Puntero al nodo que contiene el elemento buscado. Si el elemento no se encuentra, devuelve nullptr.
    *****/
    nodoABB* find(tElem info) {
        return findAux(raiz, info);
    }

    /*****
    * void clearHelp()
    ******
    *  Resumen, Libera la memoria de todos los nodos del árbol de forma recursiva.
    ******
    * Input:
    *   nodoABB*& nodo: Puntero al nodo raíz del subárbol que se desea liberar.
    ******
    *  No retorna ningun valor al tratarse de una función void.
    *****/
    void clearHelp(nodoABB* nodo) {
        if (nodo == NULL) return; // árbol vacío, se detiene
        clearHelp(nodo->izq); // visita subárbol izquierdo recursivamente
        clearHelp(nodo->der); // visita subárbol derecho recursivamente
        delete nodo; // después de borrar subárboles, se borra a sí mismo
    }
    /*****
    * void clear()
    ******
    * Resumen: Elimina todos los nodos del árbol binario de búsqueda (ABB) y reinicia el árbol.
    ******
    * Input:
    * No recibe ningún parámetro.
    ******
    * return, No retorna ningún valor.
    *****/
    void clear() {
        clearHelp(raiz); // función auxiliar para eliminar los nodos
        raiz = NULL;
        nElems = 0;
        }

    /*****
    * nodoABB* findAux()
    *****
    * Resumen: Busca un elemento específico en el arbol, de forma recursiva.
    ******
    * Input:
    * nodoABB* nodo: Puntero al nodo raíz del subárbol en el que se realizará la búsqueda.
    * tElem info: Elemento a buscar en el subárbol.
    ******
    * Returns:
    * nodoABB*: Puntero al nodo que contiene el elemento buscado. Si no se encuentra, retorna NULL.
    *****/
    nodoABB* findAux(nodoABB* nodo, tElem info){
            nodoABB* tempN;
            if (nodo == NULL) {
                tempN = NULL;
            } else if (info == nodo->info) {
                tempN = nodo;
            } else if (info < nodo->info) {
                tempN = findAux(nodo->izq, info);
            } else if (info > nodo->info) {
                tempN = findAux(nodo->der, info);
            }
            return tempN;
        }

    /*****
    * int lower_bound()
    ******
    * Resumen: Encuentra el límite inferior en un árbol binario de búsqueda (ABB) para un valor dado.
    ******
    * Input:
    * tElem x, Valor para el cual se busca el límite inferior.
    ******
    * Returns:
    * int, Límite inferior encontrado.
    *****/
    int lower_bound(tElem info) {
        return lower_boundAux(raiz, info, -1);
    }
    
    /*****
    * int lower_boundAux()
    ******
    * Resumen: Encuentra el límite inferior en un árbol binario de búsqueda (ABB) para un valor dado.
    * Asiste a lower_bound() permitiendole usar la raiz de un árbol ya creado.
    ******
    * Input:
    * nodoABB* nodo: Puntero al nodo raíz del subárbol en el que se realizará la búsqueda.
    * tElem x, Valor para el cual se busca el límite inferior.
    * tElem lower_boundValue: Valor actual del límite inferior.
    ******
    * Returns:
    * int, Límite inferior encontrado.
    *****/
    int lower_boundAux(nodoABB* nodo, tElem x, tElem lower_boundValue) {
        if (nodo == nullptr) {
            return lower_boundValue;
        }
        if (nodo->info <= x) {
            lower_boundValue = max(lower_boundValue, nodo->info);
            return lower_boundAux(nodo->der, x, lower_boundValue);
        }
        return lower_boundAux(nodo->izq, x, lower_boundValue);
    }
};


/*****
* void ENCENDER
******
* Resumen Función
*   Busca en el arbol ABB si el poste en la posición i (entregada por parámetro) está encendido.
*   Si este está encendido, no hace nada, pero si está apagado, lo enciende (lo añade al ABB)
******
* Input:
*   tABB& arbol: arbol para analizar (postes encendidos)
*   int i: posición a tomar a cuenta para encender el poste
******
* Returns:
*   Al ser una función de tipo void, esta no retorna nada, sólo se encarga de prender el poste
*   (o a nivel técnico, añadirlo al árbol ABB como nodo)
*****/
void ENCENDER(tABB& arbol, int i) {
    if (!arbol.find(i)) {
        arbol.insert(i);
    }
    return;
}

/*****
* void CUANTOS_ENCENDER
******
* Resumen Función:
*   Entrega cuántos postes están apagados (o que no se encuentran en el Árbol ABB) entre el
*   parámetro entregado y el poste encendido más cercano, obtenido con el método lower_bound.
*   min equivale a el poste encendido más cercano, y este se le resta a i, que es el parámetro
*   entregado. Luego se imprime por pantalla.
******
* Input:
*   tABB& arbol: arbol para analizar (postes encendidos)
*   int i: posición a tomar a cuenta para ver los postes apagados
******
* Returns:
*   Al ser una función de tipo void, esta no retorna nada, sólo imprime por pantalla la cantidad de
*   postes apagados requerida por la tarea, seguida de un endl
*****/
void CUANTOS_ENCENDER(tABB& arbol, int i) {
    int min = arbol.lower_bound(i);
    cout << i - min << endl;
    return;
}


/*****
* void PARAR_PROGRAMA
******
* Resumen Función:
*   Se le pasa por parametro "count", que equivale a cuantos postes
*   han sido encendidos.
******
* Input:
*   count: cantidad de postes encendidos
******
* Returns:
*   Al ser una función de tipo void, no retorna nada, sólo imprime por pantalla el total
*   de postes encendidos.
*****/
void PARAR_PROGRAMA(int count) {
    cout << count << endl;
}

int main() {
    tABB tree;
    string command;
    int pos = 0, count = 0;

    cin >> command;
    while (command != "PARAR_PROGRAMA") {
        cin >> pos;
        if (command == "CUANTOS_ENCENDER") {
            CUANTOS_ENCENDER(tree, pos);
        } else if (command == "ENCENDER") {
            if (!tree.find(pos)) {
                count++;
            }
            ENCENDER(tree, pos);
        }
        cin >> command;
    }

    if (command == "PARAR_PROGRAMA") {
        PARAR_PROGRAMA(count);
    }

    tree.~tABB();
    return 0;
}