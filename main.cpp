#include <iostream>
#include <string>
#include <cstring>
int main() {
    std::cout << "Hello, World!" << std::endl;

    // Este es el page (Area donde voy a guardar los bytes, eventualmente estos bytes los voy a escribir al disco
    // y voy a leer del disco
    int MAX_LENGTH = 10;
    char buf[MAX_LENGTH];
    int offset = 0;

    // Record del estudiante
    int student_id = 123;
    std::string name = "Joe";

    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }

    // Explicitamente seteo el valor que hay en memoria
    memset(buf, 0, MAX_LENGTH);

    std::cout << "Guepa" << std::endl;

    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }

    // Aqui escribo la data al 'page', esto sucede cada vez que inserte un record.
    memcpy(buf, (void *) &student_id, sizeof(int));
    offset = sizeof(int); // ya que anadi algo al page, debo modificar ese offset.

    std::cout << "Ya copie la data al char array, obviamente no se entiende porque estos son bytes." << std::endl;

    for(int i =0;i<MAX_LENGTH;++i){
        std::cout << buf[i] << std::endl;
    }

    // Aqui solo estoy escribiendo la data del 'page' a una variable de int. Lo hago para poder verla en forma de num
    int id2 = 0;
    memcpy((void *) &id2, buf,sizeof(int));

    std::cout << "id2:  " << id2 << std::endl;








    /*
     * Al implementar el unpack fixed length (record), tendremos que crear un heapfile al cual le tengo que decir
     * las columns que hay y ademas cuando espacio ocupa los types de cada columna. En el heapfile guardo la estrcutura
     * y el orden de los elementos. Este orden/metadata seguira hasta que se modifique la tabla.
     * basicamente cuando yo abro un file tengo que pasarle ese file de metadata.
     *
     * How to pack the data?
     * First an offset must be mantained to know where is the next available byte.
     */

    // ahora para anadir el string "Joe", uso el offset para decidir donde empiezo a escribir
    const char *ptr = name.c_str();
    int strlen = name.length();
    memcpy(buf + offset,ptr, strlen);

    char temp[5];
    memset(temp, 0, 5);
    // El profesor envia el array de chars sin convertirlo en un pointer a void,
    // Lo mas seguro es porque un char[] puede ser lo que uno quiera, sea un array de bytes o de chars como tal.
    memcpy((void *) &temp, buf + offset, strlen);

    for(int i =0;i<strlen; ++i){
        std::cout << temp[i] << std::endl;
    }

    std::string name2 = std::string(temp);
    std::cout << name2 << std::endl;
    return 0;
}
