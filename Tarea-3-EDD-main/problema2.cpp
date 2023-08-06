/* PUSHCMD */
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

typedef string tipoId;
typedef int tipoPrioridad;
typedef string tipoInstruccion;

struct command{
    tipoId id;
    tipoPrioridad priority;
    tipoInstruccion instruction;
};

class Q_prioridad {
private:
    unsigned int qp_size = 100; // tamaño del heap
    command* qp_array; // arreglo para almacenar los elementos del heap
    command centinel;
    unsigned int item_quantity = 0;
    unsigned int pendientes = 0;
    int creados = 0;
    int enviados = 0;

    int padre(int i) {
        return (i - 1) / 2;
    }
    int left(int i) {
        return (2 * i + 1);
    }
    int right(int i) {
        return (2 * i + 2);
    }


    public:
        Q_prioridad(){ // constructor
            qp_array = new command[qp_size + 1];
            qp_array[0] = centinel;
        }
        
        ~Q_prioridad(){ // destructor
            delete[] qp_array;
        }

        /*****
        * void Q_float (ind index)
        ******
        * Resumen Función:
        *   Obtiene el valor del índice, y los compara con los anteriores, para ir flotando el valor en caso de ser menor,
        *   para que conserve la propiedad de Min-heap
        ******
        * Input:
        *     int index: entero que indica el indice, para saber cuál dato flotar
        ******
        * Returns:
        *     Al ser una función de tipo void, no retorna nada.
        *****/ 
    void Q_float(int index) {
        int min = index;
        unsigned int left = Q_prioridad::left(index);
        unsigned int right = Q_prioridad::right(index);

        if (left <= item_quantity && qp_array[left].priority < qp_array[min].priority) {
            min = left;
        }
        if (right <= item_quantity && qp_array[right].priority < qp_array[min].priority) {
            min = right;
        }

        if (min != index) {
            swap(qp_array[index], qp_array[min]);
            Q_float(min);
        }
    }

        /*****
        * void Q_pop()
        ******
        * Resumen Función:
        *     elimina el elemento en la raiz del heap
        ******
        * Input:
        *     esta función no obtiene nada como parámetro
        ******
        * Returns:
        *     al ser una funcion de tipo void, no retorna nada
        *****/ 
    void Q_pop() {
        if (item_quantity == 0) {
            throw "Cola vacía";
        }

        command minElem = qp_array[1];
        cout << minElem.id << endl;
        cout << minElem.instruction << endl;

        qp_array[1] = qp_array[item_quantity];
        item_quantity--;
        Q_float(1);
    }


        /*****
        * void pushCommand(command c)
        ******
        * Resumen Función:
        *     Recibe un struct e ingresa sus valores al min-heap, insgresando su ID,
        *     Su prioridad y lo que siga después, como una cadena de texto que corresponde a la instrucción.
        ******
        * Input:
        *     command c: recibe un struct para añadir sus valores al min-heap
        ******
        * Returns:
        *     Al ser una función de tipo void, no retorna nada, sólo añade el struct al min-heap
        *****/ 
    void pushCommand(command c) {
        if (item_quantity == qp_size) {
            cout << "Cola llena" << endl;
        }
        int index = ++item_quantity;
        qp_array[index] = c;
        while (index != 1 && qp_array[index / 2].priority > qp_array[index].priority) {
            swap(qp_array[index], qp_array[index / 2]);
            index = (index / 2);
        }
        pendientes++;
        creados++;
        cout << pendientes << " PENDING" << endl;
    };

        /*****
        * void get(int N) 
        ******
        * Resumen Función:
        *     Muestra el entero pasado por parámetro seguido de los identificadores de los comandos a enviar
        *     luego imprime las instrucciones de cada comando, y posteriormente, los elimina del heap
        ******
        * Input:
        *     int N: cuantos comandos va a obtener
        ******
        * Returns:
        *     Al ser de tipo void, esta no retorna nada
        *****/ 
    void get(unsigned int N) {
            if (N > item_quantity) {
                cout << "0" << endl;
                return;
            }

            cout << N << " ";
            for (unsigned int i = 1; i <= N; i++) {
                Q_pop();
            }
            pendientes -= N;
            enviados += N;
        }


        /*****
        * void terminate()
        ******
        * Resumen Función:
        *     Termina el programa, borrando el Min-heap y mostrando por pantalla cuantos comandos push
        *     fueron creados (PUSHCOMMAND) y cuantos fueron ejecutados (GET)
        ******
        * Input:
        *     Esta función no recibe ningún input
        ******
        * Returns:
        *     Al ser una función de tipo void, no retorna nada, sólo termina el programa y entrega los datos solicitados
        *****/ 
    void terminate() {
        cout << enviados << " SENT " << creados << " CREATED" << endl;
    };
};

int main() {
    string operation, id, priority, instruction, n;
    Q_prioridad comandos;
    cin >> operation;
    while (operation != "TERMINATE") {
        if (operation == "GET") {
            cin >> priority;
            comandos.get(stoi(priority));
        }
        else if (operation == "PUSHCOMMAND") {
            cin >> id >> priority;
            getline(cin, instruction);
            command c;
            c.id = id;
            c.priority = stoi(priority);
            c.instruction = instruction;
            comandos.pushCommand(c);
        }
        cin >> operation;
    }
    comandos.terminate();
    return 0;
}

/*
PUSHCOMMAND WNWSM4 1 TZ 1 0 86400
PUSHCOMMAND AJDoMI 3 TZ 3 61200 32400
PUSHCOMMAND wsOvMk 2 TZ 2 32400 100000
GET 2
GET 1
GET 1
PUSHCOMMAND 9HmMas 8 USER 926 Diego 1 2 0
PUSHCOMMAND JotUAw 5 USER 861 Juan 1 1 0
PUSHCOMMAND hIuRAh 7 USER 456 Roberto 1 1 0
PUSHCOMMAND hjCbZ7 6 USER 486 Gabriel 1 1 0
GET 3
TERMINATE
*/