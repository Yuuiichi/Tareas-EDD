/* Users Login */
#include <iostream>
#include <string>
#include <cmath> // c papu
using namespace std;

#define VACIO ""
#define OCUPADO true
#define LIBRE false
const float A_hashing = 0.7354;

typedef string tipoClave;
typedef string tipoInfo;

class DatoHash {
    public:
        tipoClave clave;
        tipoInfo info;
        bool estado; // Banco estado
        DatoHash(tipoClave clave, tipoInfo info, bool estado){
            this->clave = clave;
            this->info = info;
            this->estado = estado;
        }
};

class HashingTable {
    private:
        int size;
        typedef string tipoClave;
        typedef string tipoInfo;
        DatoHash **HT; // Tabla de hash

    public:
        float cantidad_datos = 0.0;
        // Constructor (como bob)
        HashingTable(int size) {
            this->size = size;
            HT = new DatoHash*[size];
            for (int i = 0; i < size; i++) {
                HT[i] = nullptr;
            }
        }

        // Destructor
        ~HashingTable() {
            for (int i = 0; i < size; i++) {
                if (HT[i] != nullptr){
                delete HT[i];
                }
            }   delete[] HT;
        }

        /*****
        * int hash(tipoClave k)
        ******
        * Resumen Función:
        *   Calcula el índice hash para una clave en una tabla de hashing.
        ******
        * Input:
        *   tipoClave k: Clave para la cual se calculará el índice hash.
        ******
        * Returns:
        *   int: Índice hash calculado.
        *****/
        int hash(tipoClave k) { // función hash
            int suma = 0, index = 0;
            unsigned int i;
            float aux = 0.0;
            for (i = 0; i < k.length(); i++){
                suma += k[i]; // suma de los caracteres de la clave 
            };
            aux = suma * A_hashing;
            aux = aux - (int)aux;
            index = floor(size*aux);
            return index; 
        }

        /*****
        * int hash2(tipoClave k)
        ******
        * Resumen Función:
        *   Función de hash para manejar colisiones en la tabla hash.
        ******
        * Input:
        *   tipoClave k: Clave a utilizar en el cálculo del índice.
        ******
        * Returns:
        *   int: Índice calculado para la clave k.
        *****/ 
        int hash2(tipoClave k) { // función hash colisiones lineales
            int start, index;
            start = hash(k);
            index = (start + 1 ) % size;
            return index; 
        }

        /*****
        * void insertar(tipoInfo c, tipoClave k)
        ******
        * Resumen: 
        *   Esta función inserta un usuario en la Hashing Table, utilizando la contraseña entregado como c
        *   y el nombre de usuario entregado como k, por parámetro, aunque antes de insertalo, revisa que el
        *   factor de carga no sea mayor a 0.7, ya que de lo contrario, la tabla se estaría llenando demasiado,
        *   y produciría muchas colisiones, así que entra a un if que guarda en una tabla auxiliar todos los 
        *   valores ingresados, borra la Hashing Table existente y crea una nueva Hashing Table con el doble
        *   de espacio que la anterior, y luego, se le entregan todos los usuarios y sus contraseñas guardados
        *   en la tabla auxiliar.
        *   Posteriormente, borra la Tabla auxiliar, quedando solo con la nueva tabla ReHasheada.
        ******
        * Input:
        *   tipoInfo c: contraseña a ser insertada
        *   tipoClave k: nombre de usuario a ser insertado
        ******
        * Returns:
        *   No devuelve nada en específico, al ser función de tipo void, sólo inserta el valor
        *****/
        void insertar(tipoInfo c, tipoClave k){
            int j = 1, start;
            int index = start = hash(k);
            cantidad_datos++;
            float carga = cantidad_datos / size;
            // Rehash para factor de carga mayor a 0.7
            if (carga > 0.7) {
                int old_size = size;
                size = 2 * size;
                DatoHash** aux = new DatoHash*[size];
                for (int i = 0; i < size; i++) {
                    aux[i] = nullptr;
                }
                // Extraer datos de la HT a la aux
                for (int i = 0; i < old_size; i++) {
                    if (HT[i] != nullptr && HT[i]->estado == OCUPADO) {
                        tipoClave key = HT[i]->clave;
                        tipoInfo value = HT[i]->info;
                        int newIndex = hash(key);
                        int newJ = 1;
                        while (aux[newIndex] != nullptr && aux[newIndex]->estado == OCUPADO && aux[newIndex]->clave != key) {
                            newIndex = (newIndex + newJ * hash2(key)) % size;
                            newJ++;
                        }
                        if (aux[newIndex] != nullptr) {
                            delete aux[newIndex];
                        }
                        aux[newIndex] = new DatoHash(key, value, OCUPADO);
                    }
                }
                for (int i = 0; i < old_size; i++) {
                    if (HT[i] != nullptr) {
                        delete HT[i];
                    }
                }
                delete[] HT;
                HT = aux;
                delete[] aux;
            }
            while (HT[index] != nullptr && HT[index]->estado == OCUPADO && HT[index]->clave != k)
            {
                index = (start + j * hash2(k)) % size;
                    j++;
                cout << "Colision en la posicion " << start << endl;
            }
            if (HT[index] != nullptr)
                delete HT[index];
            HT[index] = new DatoHash(k, c, OCUPADO);
        }
                
        /*****
        * DatoHash buscar(tipoClave k)
        ******
        * Resumen Función:
        *     Busca un elemento en la tabla hash utilizando la clave proporcionada.
        ******
        * Input:
        *     tipoClave k: Clave del elemento a buscar en la tabla hash.
        ******
        * Returns:
        *     DatoHash: El elemento encontrado en la tabla hash, o un objeto DatoHash vacío si no se encuentra.
        *****/ 
        DatoHash buscar(tipoClave k) {
            int start, j=1;
            int index = start = hash(k);

            DatoHash HT_vacio(VACIO,VACIO,LIBRE);
            while(HT[index] != nullptr && HT[index]->estado == OCUPADO && HT[index]->clave != k){
                index = (start + j * hash2(k)) % size;
                j++;
            }
            if (HT[index] == nullptr)
                return HT_vacio;
            else
                return *HT[index];
        }

        /*****
        * int buscarHASH(tipoClave k)
        ******
        * Resumen Función:
        *     Busca un elemento en la tabla hash utilizando la clave proporcionada y devuelve su índice en la tabla.
        *     (distinto de lo entregado en la función buscar)
        ******
        * Input:
        *     tipoClave k: Clave del elemento que se desea buscar.
        ******
        * Returns:
        *     int: Índice del elemento en la tabla hash. Devuelve -1 si el elemento no se encuentra.
        *****/ 
        int buscarHASH(tipoClave k) {
            int start, j=1;
            int index = start = hash(k);
            DatoHash HT_vacio(VACIO,VACIO,LIBRE);
            while(HT[index] != nullptr && HT[index]->estado == OCUPADO && HT[index]->clave != k){
                index = (start + j * hash2(k)) % size;
                j++;
            }
            if (HT[index] == nullptr)
                return -1;
            else
                return index;
        }

        /*****
        * bool iniciar_sesion(string usuario, string contrasena)
        ******
        * Resumen Función:
        *     Verifica las credenciales de inicio de sesión para un usuario dado.
        ******
        * Input:
        *     string usuario: Nombre de usuario.
        *     string contrasena: Contraseña del usuario.
        ******
        * Returns:
        *     bool: Indica si la sesión se inició correctamente. Devuelve true si las credenciales son válidas, de lo contrario, devuelve false.
        *****/ 
        bool iniciar_sesion(string usuario, string contrasena){
            DatoHash user = buscar(usuario);
            if(user.estado == LIBRE){
                cout<<"El usuario no se encuentra registrado"<<endl;
                return false;
            } else {
                if(contrasena != user.info){
                    cout<<"La clave ingresada no coincide"<<endl;
                    return false;
                } else {
                    cout<<"Sesión iniciada con éxito"<<endl;
                    return true;
                }
            }
        }
        
        /*****
        * bool crear_nuevo_usuario(string usuario, string contrasena)
        ******
        * Resumen Función:
        *     Crea un nuevo usuario con el nombre de usuario y la contraseña proporcionados.
        ******
        * Input:
        *     string usuario: Nombre de usuario.
        *     string contrasena: Contraseña del usuario.
        ******
        * Returns:
        *     bool: Indica si el nuevo usuario se creó correctamente. Devuelve true si el usuario se registró con éxito, de lo contrario, devuelve false.
        *****/ 
        bool crear_nuevo_usuario(string usuario, string contrasena){
            bool user_status = buscar(usuario).estado;
            if(user_status == OCUPADO){
                cout<<"El usuario ya se encuentra registrado"<<endl;
                return false;
            } else {
                if(contrasena.length() < 8){
                    cout<<"La clave debe tener al menos 8 carácteres"<<endl;
                    return false;
                } else {                
                    insertar(contrasena, usuario);
                    cout<<"Usuario registrado con éxito"<<endl;
                    return true;
                }
            }
        }

        /*****
        * bool cambiar_clave(string usuario, string nueva_clave)
        ******
        * Resumen Función:
        *     Cambia la contraseña de un usuario proporcionado con la nueva contraseña entregada.
        ******
        * Input:
        *     string usuario: Nombre de usuario.
        *     string nueva_clave: Nueva contraseña para el usuario.
        ******
        * Returns:
        *     bool: Indica si se cambió la clave correctamente. Devuelve true si se actualizó la clave con éxito, de lo contrario, devuelve false.
        *****/ 
        bool cambiar_clave(string usuario, string nueva_clave){
            DatoHash user = buscar(usuario);
            if(user.estado == LIBRE){
                cout<<"El usuario no se encuentra registrado"<<endl;
                return false;
            } else {
                if(nueva_clave.length() < 8){
                    cout<<"La clave debe tener al menos 8 carácteres"<<endl;
                    return false;
                } else {
                    int index = buscarHASH(usuario);
                    if (index == -1){
                        cout<<"El usuario no se encuentra registrado"<<endl;
                        return false;
                        }else{
                    HT[index]->info = nueva_clave;
                    cout<<"Clave actualizada con éxito"<<endl;
                    return true;
                    }
                }
            }
                
        }

    };


int main() {
    HashingTable HT(32);
    string operation, username, password;
    cin>>operation;
    while(operation!="FINALIZAR"){
        cin>>username>>password;
        if(operation == "REGISTRAR")
            HT.crear_nuevo_usuario(username,password);
        else if(operation == "INICIAR_SESION")
            HT.iniciar_sesion(username,password);
        else if(operation == "ACTUALIZAR")
            HT.cambiar_clave(username,password);
        cin>>operation;
    }
    return 0;
}