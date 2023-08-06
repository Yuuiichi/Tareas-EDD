// Se incluyen las librerías estándar
#include <iostream>
#include <math.h>
#include <cstring>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std; // Se usa para ahorrarse el uso de std:: antes de cada variable

// Se añade el struct base para las personas
struct Persona {
    string nombre; // El nombre de la persona como string
    char fecha[11]; // La fecha de nacimiento de la persona, como array de 11 slots, en formato AAAA-MM-DD
    int tamanio_tarjeta; // Entero que indica la cantidad de números en la tarjeta
    int* tarjeta; // Puntero que indica un array de enteros
    bool quiere_intercambiar; // Booleano que indica si quiere intercambiar o no (0 es que no quiere, 1 es que si quiere)
}personaMejorPuntaje; // Struct que guardará datos de la persona con mejor puntaje

int cantidadPersonas; // Variable global, que guarda la cantidad de personas con las que trabajará el programa
int puntajeMax; // Variable global, que guarda el puntaje máximo

/*****
* int* comprarTarjeta
******
* Al ejecutar la función, se crea un arreglo dinámico que servirá como la tarjeta de la persona que invocó la función 
* La memoria del new se liberará al momento de llamar la función comprarTarjeta.
******
* Input:
*   string nombre: nombre de la persona que quiere comprar la tarjeta.
*   int dia: el día en el que compra la tarjeta.
*   int &m: el tamaño del array que retornará la función.
******
* Return:
*   Retorna un array de enteros de igual tamaño que el nombre (m), donde en la posición i se encontrará el valor nombre[i]%dia.
*****/
int* comprarTarjeta(string nombre, int dia, int &m) {
    int* arr = new int[m];
    for (int i = 0; i < m; i++){
        arr[i] = nombre[i]%dia;
    }
    return arr;
}

/*****
* void intercambiarTarjeta
******
* Al ejecutar la función, toma los 2 parametros entregados, que son personas, y se intercambian las tarjetas si es que están dispuestas a hacerlo.
* Para saber si están dispuestas, se usan los valores 1 y 0, explicados anteriormente, si el intercambio se realiza, la persona en la posición 1 deja de querer intercambiar
* En caso de empate, la persona en la menor posición se considera ganador.
******
* Input:
*   Persona* p1: Persona n1 a realizar el intercambio.
*   Persona* p2: Persona n2 a realizar el intercambio.
******
* Return:
*   No devuelve ningún valor específico, al ser función de tipo void, sólo realiza el intercambio.
*****/
void intercambiarTarjeta(Persona* p1, Persona* p2) {
    int tempCardSize;
    tempCardSize = p1->tamanio_tarjeta;
    p1->tamanio_tarjeta = p2->tamanio_tarjeta;
    p2->tamanio_tarjeta = tempCardSize;

    int* tempCard;
    tempCard = p1->tarjeta;
    p1->tarjeta = p2->tarjeta;
    p2->tarjeta = tempCard;

    // p1->quiere_intercambiar = 0;
    return;
}

/*****
* int puntaje
******
* Recibe una persona y retorna un entero correspondiente a su puntaje, obtenido por la fórmula dada.
******
* Input:
*   Persona* p1: Persona a calcular el puntaje.
******
* Return:
*   Retorna un int, con el puntaje de la persona entregada.
*****/
int puntaje(Persona* p1) {
    int sumatoria = 0;
    for (int i = 0; i < p1->tamanio_tarjeta; i++){
        int temp = (p1->tarjeta[i])*(p1->fecha[i%10]);
        sumatoria += temp;
    } 
    return sumatoria;
}

/*****
* Persona* unDia //(vi, una vaca sin cola vestida de uniforme)
******
* Recibe un array de personas, y debe comprar una tarjeta a cada persona utilizando el parámetro dia,
* Se le asigna un tamaño de tarjeta igual al largo del nombre y le compra una tarjeta a cada persona 
* haciendo a cada persona intentar intercambiar hasta que sea imposible seguir intercambiando tarjetas. 
* Se debe partir siempre por la persona en la posición 0 hasta la persona en la posición p − 1. 
* Finalmente, se retorna la persona que haya obtenido el mayor puntaje.
******
* Input:
*   Persona* personas: Es un puntero hacia un array de personas, que serán las ingresadas a la función.
*   int dia: el día en el que se realiza.
******
* Return:
*   Retorna un struct con la persona de mayor puntaje.
*****/
Persona* unDia(Persona* personas, int dia) {
    for (int i = 0; i < cantidadPersonas; i++){
        personas[i].tamanio_tarjeta = personas[i].nombre.size();
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre,dia,personas[i].tamanio_tarjeta);
    }
    for (int i = 0; i < cantidadPersonas; i++){ // Itera sobre las personas hasta encontrar una persona que quiera intercambiar.
        bool intercambio_pendiente = true;
        if (personas[i].quiere_intercambiar == true){ // Itera sobre personas desde la posición adelante de la anterior hasta encontrar otra persona que quiera intercambiar.
            for (int j = i+1; j < cantidadPersonas; j++){
                if (personas[j].quiere_intercambiar == true){
                    for (int x=0; x < personas[i].tamanio_tarjeta; x++){ // Itera sobre la tarjeta de la primera persona en busca de números en común
                        for (int y=0; y < personas[j].tamanio_tarjeta; y++){ // Itera sobre la tarjeta de la segunda persona en busca de números en común
                            if (personas[i].tarjeta[x] == personas[j].tarjeta[y]) { // Cuando los dos números coinciden, se realiza el intercambio
                                intercambiarTarjeta(&personas[i],&personas[j]);
                                intercambio_pendiente = false; 
                                break;
                            }
                        }
                        if (intercambio_pendiente == false) {
                            break;
                        }
                    }
                }
                if (intercambio_pendiente == false) {
                    break;
                }
            }
        }
    }

    puntajeMax = -1; 

    for (int i = 0; i < cantidadPersonas; i++) {
        int puntajeActual = puntaje(&(personas[i]));
        delete[] personas[i].tarjeta; // Elimina el arreglo dinámico entregado por comprarTarjeta, ya que no se usará.
        if (puntajeActual > puntajeMax) { // Compara con puntajes anteriores para establecer puntaje más alto, y guardarlo en puntajeMax.
            puntajeMax = puntajeActual;
            personaMejorPuntaje = personas[i];
        }
    }
    
    return &personaMejorPuntaje;
}

/*****
* void VariosDias
******
* Recibe un array de personas, y la cantidad de días en total a realizar, entregado a través de la función main. Debe llamar a la función unDia 
* pasando por parámetro los días 1 hasta cant_dias. Por cada día que pasa, debe mostrar por pantalla (Mediante cout) el nombre, fecha de nacimiento 
* y puntaje de la persona que obtuvo el mayor ese día.
******
* Input:
*   Persona* personas: puntero hacia un array de personas, que serán ingresadas a la función
*   int cant_dias: La cantidad de días que usará la función para ejecutarse, que obtendrá por la función main
******
* Return:
*   No retorna ningún valor específico, al ser función de tipo void, pero imprime lo solicitado por pantalla, a través del terminal.
*****/
void variosDias(Persona* personas, int cant_dias) {
    for (int i = 1; i <= cant_dias; i++){
        Persona* pmp = unDia(personas,i);// Invocar la función unDia
        cout << pmp->nombre << " " << pmp->fecha << " " << puntajeMax << endl;    
    }
    return;
}

// la entrada estandar de datos en C++ es el teclado, por lo que hay que usar un loop para el cin >>
int main() {
    int cantidadDias = 2; // Se entrega en Main, puede variar
    cin >> cantidadPersonas; // cantidad de personas ingresadas, puede variar
    Persona* persona = new Persona[cantidadPersonas]; // crear structs necesarios acuerdo a cantidadPersonas
    for (int i = 0; i < cantidadPersonas; i++){
        cin >> persona[i].nombre >> persona[i].fecha >> persona[i].quiere_intercambiar; //For que entrega los datos solicitados, pueden ser entregados individualmente,
                                                                                        //pero en for queda más óptimo, se entrega sí o sí en la main
    }
    cout << endl; //Salto de linea para que quede bonito :3
    variosDias(persona, cantidadDias); //OBLIGATORIO, hace funcionar el programa
    delete[] persona; //Elimina el new array creado para entregar los datos
    return 0;
}
