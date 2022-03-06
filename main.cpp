#include <iostream>
#include <string>
#include <cstring>




// Returns the value as a string from the data that is a instance variable on my class.

 std::string getString( char data[], int length) {

    char temp[length];
    memset(temp, 0, length);
    memcpy( (void *) &temp, data, length);

    std::string result = std::string(temp);

    return result;
}


int main() {
    /*
     * Este es el page (Area donde voy a guardar los bytes, eventualmente estos bytes los voy a escribir al disco
     * y voy a leer del disco.
     * acordar que en C++ los devs usamos el char[] para guardar bytes tambien. So por eso podemos inventar un poco con eso.
     */

    int MAX_LENGTH = 10;
    char buf[MAX_LENGTH];
    int offset = 0;

    // Record del estudiante
    int student_id = 123;
    std::string name = "Joe";



    std::cout << "Ahora imprimo el contenido random del byte array" << std::endl;
    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }


    std::cout << "Explicitamente seteo el valor que hay en memoria usando memset " << std::endl;
    memset(buf, 0, MAX_LENGTH);

    std::cout << "ahora mis valores cambiaron: " << std::endl;
    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }

    std::cout << "Aqui escribo la data al 'page' usando memcpy, esto sucede cada vez que inserte un record." << std::endl;
    memcpy(buf, (void *) &student_id, sizeof(int));
    offset = sizeof(int); // ya que anadi algo al page, debo modificar ese offset.

    std::cout << "Ahora imprimo la data que pase al byte[]: " << std::endl;
    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }

    std::cout << "Ahora leo los bytes que hay en el byte array y lo envio a la direccion de mi variable int." << std::endl;
    int id2 = 0;
    memcpy((void *) &id2, buf,sizeof(int));
    std::cout << "id2:  " << id2 << std::endl;
    std::cout << "\n " << std::endl;


    /*
     * Al implementar el unpack fixed length (record), tendremos que crear un heapfile al cual le tengo que decir
     * las columns que hay y ademas cuando espacio ocupa los types de cada columna. En el heapfile guardo la estrcutura
     * y el orden de los elementos. Este orden/metadata seguira hasta que se modifique la tabla.
     * basicamente cuando yo abro un file tengo que pasarle ese file de metadata.
     *
     * File Types:
     *          Heap File: Unordered collection of records. Simple to use and implement,
     *            but have to use exhaustive seach.
     *          Sorted File: Everything esta ordenado por algun campo, search rapido.
     *          Index File: Hay una estructura de datos en donde tienes algunas partes de las columnas organizadas
     *             y otras no. Solo hay que mantener en orden los index entries.
     *
     *
     *
     * How to pack the data?
     * First an offset must be mantained to know where is the next available byte.
     */

    // ahora para anadir el string "Joe", uso el offset para decidir donde empiezo a escribir
    std::cout << "Ahora, para guardar un string en mi byte[] creo un *ptr que apunta a el str.c_str() y uso eso como source en mi memcpy." << std::endl;
    const char *ptr = name.c_str();
    int strlen = name.length();
    std::cout << "Luego llamo memcpy usando el ptr al string original como src y el buff como destination." << std::endl;
    memcpy(buf + offset,ptr, strlen);


    std::cout << "Luego cuando quiera leer como un string los bytes del string que guarde, \n " << std::endl;
    std::cout << "creo un char[] temp, lo seteo a 0 usando memset y lo populo usando memcpy()" << std::endl;
    char temp[5];
    memset(temp, 0, 5);
    memcpy((void *) &temp, buf + offset, strlen);
    std::string name2 = std::string(temp);
    std::cout << "Name sacado de los bytes guardados en el char[].   : " << name2 << std::endl;

    /*
     * En lugar de usar memcpy puedo hacer un loop y ver como cada numero y verlo como un pointer a integer, asi veo
     * el numero como pointers en lugar de integers.
     * Esto es como si estuviera haciendo numbers[i] = 10 + 1 .
     * Es como si numbers fuera un int[].
     *
     * El problema de esto es que puedes accesar memoria que no tienes disponible.
     * Eso se llama memory alignment, y es que los words (deben) llegar al cpu en un word size,
     * y aveces uno puede pensar que cumple con esa regla pero no.
     *
     * Por eso usaremos memcpy.
     *
     */

    return 0;
}
