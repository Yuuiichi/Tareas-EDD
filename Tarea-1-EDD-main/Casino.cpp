#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace std; 


//Se definen las constantes
const int SERV_DESAYUNO = 0;
const int SERV_ALMUERZO = 1;
const int SERV_ONCE = 2;
const int SERV_CENA = 3;
//Se define la estructura de colaborador

struct SaldoColaborador {
char rut [11];
int saldo_desayuno ;
int saldo_almuerzo ;
int saldo_once ;
int saldo_cena ; 
};

/*****
* bool puedeConsumir
******
* La funcion puedeConsumir tiene como principal objetivo el verificar si un colaborador puede o no consumir un ticket de alimentación (desayuno, almuerzo, once o cena)
* Para esto, la funcion lee el archivo binario llamado "saldos.bin" que es proporcionado y que contiene la información de 
* los colaboradores y sus saldos de tickets de alimentación.
* Luego lee un archivo de texto que contiene los consumos del día, y verifica si el colaborador ya consumió un ticket de alimentación (este archivo se crea con el primer consumo del dia)
* y crea o abre el archivo para poder escribir los nuevos consumos del día.
* Se busca el colaborador cuyo saldo de servicios queremos revisar y se leen los consumos realizados por él en el archivo de consumos del día
* en base a esto se calcula el saldo disponible de cada servicio comparandolo con el saldo que fue informado en el archivo binario. 
* Finalmente se verifica si el colaborador tiene saldo suficiente para consumir el servicio que quiere consumir y se retorna True o False
******
* Input:
* char* rut : Un string que contiene el rut en formato NNNNNNNN-D del colaborador que quiere consumir un ticket de alimentación
* int servicio : Un entero que indica el servicio que se quiere consumir, de igual manera este parametro debe ser una de las constantes SERV_ definidas anteriormente
* string consumo_dia : Un string que contiene el nombre del archivo donde se guardan los consumos del día
* .......
******
* Returns:
* Bool, la funcion retorna True si es que el colaborador tiene saldo suficiente para recibir un ticket de alimentación y False si no tiene saldo suficiente
*****/

bool puedeConsumir(char* rut, int servicio, string consumos_dia) {

    //Se lee el archivo de colaboradores
    ifstream saldos("saldos.bin" , ios::binary);
    SaldoColaborador colaborador;

    //Se busca el colaborador y se crean las variables a utilizar
    int cantidad_colaboradores, saldo_desayuno, saldo_almuerzo, saldo_once, saldo_cena; 
    saldos.read((char*)&cantidad_colaboradores, sizeof(int));

    //Se verifica si el archivo de consumos del día ya fue creado
    ifstream archivo_consumos_validar(consumos_dia);
    bool creado = archivo_consumos_validar.good();
    archivo_consumos_validar.close();

    //Se crea o abre el archivo de consumos del día
    fstream archivo_consumos;
    if (!creado) {
        archivo_consumos.open(consumos_dia, ios::out);
        archivo_consumos.close();
    } else {
        archivo_consumos.open(consumos_dia, ios::app);
        archivo_consumos.close();
    }
    //Se declaran ciertas variables a utilizar 
    int c = 0;
    int consumos_desayuno = 0;
    int consumos_almuerzo = 0;
    int consumos_once = 0;
    int consumos_cena = 0;
    string linea;
    string rut_consultor = rut; 
    //Se busca el colaborador y se leen sus consumos del día 
    while (c < cantidad_colaboradores) {
        saldos.read((char*)&colaborador, sizeof(SaldoColaborador));
        if (colaborador.rut == rut_consultor) {
            archivo_consumos.open(consumos_dia, ios::in);
            string rut_consumo, servicio_consumo;
            while(getline(archivo_consumos, linea)){
                rut_consumo = linea.substr(0, 10);
                servicio_consumo = linea.substr(11, 20);
                if (strcmp(colaborador.rut, rut_consultor.c_str()) == 0){
                    if (servicio_consumo == "DESAYUNO"){
                        consumos_desayuno++;
                    }
                    if (servicio_consumo == "ALMUERZO"){
                        consumos_almuerzo++;
                    }
                    if (servicio_consumo == "ONCE"){
                        consumos_once++;
                    }
                    if (servicio_consumo == "CENA"){
                        consumos_cena++;
                    }
                }
            }
            archivo_consumos.close();
            //Se calcula el saldo disponible de cada servicio en base a los consumos del día
            saldo_desayuno = colaborador.saldo_desayuno - consumos_desayuno;
            saldo_almuerzo = colaborador.saldo_almuerzo - consumos_almuerzo;
            saldo_once = colaborador.saldo_once - consumos_once; 
            saldo_cena = colaborador.saldo_cena - consumos_cena;
            //Se revisará cual servicio irá a consumir
                if (SERV_DESAYUNO == servicio) {
                    if (saldo_desayuno > 0){
                        string servicio_requerido = "DESAYUNO";

                        //Se ingresa el consumo del colaborador
                        archivo_consumos.open(consumos_dia, ios::app);
                        archivo_consumos << colaborador.rut << " " << servicio_requerido << endl;
                        archivo_consumos.close();
                        return true;
                    }
                }
                if (SERV_ALMUERZO == servicio) {
                    if (saldo_almuerzo > 0){
                        string servicio_requerido = "ALMUERZO";

                        //Se ingresa el consumo del colaborador
                        archivo_consumos.open(consumos_dia, ios::app);
                        archivo_consumos << colaborador.rut << " " << servicio_requerido << endl;
                        archivo_consumos.close();
                        return true;
                    }
                }
                if (SERV_ONCE == servicio) {
                    if (saldo_once > 0){
                        string servicio_requerido = "ONCE";

                        //Se ingresa el consumo del colaborador
                        archivo_consumos.open(consumos_dia, ios::app);
                        archivo_consumos << colaborador.rut << " " << servicio_requerido << endl;
                        archivo_consumos.close();
                        return true;
                    }
                }
                if (SERV_CENA == servicio) {
                    if (saldo_cena > 0){
                        string servicio_requerido = "CENA";
                        //Se ingresa el consumo del colaborador
                        archivo_consumos.open(consumos_dia, ios::app);
                        archivo_consumos << colaborador.rut << " " << servicio_requerido << endl;
                        archivo_consumos.close();
                        return true;
                    }
                }
        } else { //Si es que el colaborador no existe, se consideran saldos nulos
            saldo_almuerzo = 0;
            saldo_desayuno = 0;
            saldo_once = 0;
            saldo_cena = 0;
        }
    c++;
    }
        saldos.close();
        archivo_consumos.close();
        return false;
}

int main() {
    char rut[11] = "11111111-1";
    char rut2[11] = "36753562-9";
    char rut3[11] = "93606261-8";
    char rut4[11] = "94909177-1";
    cout << puedeConsumir(rut, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut2, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut3, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut4, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut2, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut2, 0, "dasdas.txt") << endl;
    cout << puedeConsumir(rut2, 0, "dasdas.txt") << endl;
}