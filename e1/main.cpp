/*
1. Escriba un programa para codificar archivos de texto. El programa debe recibir un número
entero n que será la semilla de codificación y un número para seleccionar el método de
codificación.

Primer método:
Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. En el
primer bloque se cambian todos los 1 por 0 y viceversa. Para los grupos siguientes se debe
contar el número de 1s y 0s en el grupo anterior y hacer cambios según la siguiente regla:
- Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
- Si hay mayor cantidad de 0s se invierte cada 2 bits.
- Si hay mayor cantidad de 1s se invierte cada 3 bits.

Ej:​ Si se ingresa 4 y el archivo contiene AbCd.
El archivo en binario sería:
01000001 01100010 01000011 01100100
El archivo codificado sería:
10110100001111010001011010011011
*Nota: ​ Tener en cuenta cuando se aplican las reglas a partir del segundo bloque, se debe
tomar los grupos de bits del archivo binario sin codificar.

Segundo método:
Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. Cada
bit dentro de un grupo se desplaza una posición, de manera que el primer bit del grupo
codificado corresponde al último bit del grupo sin codificar, el segundo bit codificado
corresponde al primero sin codificar y así sucesivamente hasta que el último corresponde
al penúltimo sin codificar.
Ej:​ Si se ingresa 4 y el archivo contiene AbCd.
El archivo en binario sería:
01000001011000100100001101100100
El archivo codificado sería:
00101000001100010010100100110010

Nota: El programa debe generar un archivo de salida con la información binaria
codificada​ . ​ El programa debe recibir los nombres del archivo fuente y el archivo de
salida por consola.
*/

#include <fstream>
#include <iostream>
#include <exception>
#include "crypto.h"
#define line std::cout<<std::endl;

int main(){


    /*Nombre de los archivos*/
    //char file_input[100]; //archivo de entrada de texto
    char file_input[]="C:/Users/admin/Desktop/practica_3/e1/data.txt";
    //char file_binary[100];//archivo intermedio que aloja el texto en su representacion binaria
    char file_binary[]="C:/Users/admin/Desktop/practica_3/e1/data.bin";
    //char file_encrypted[100];//archivo de salida que aloja el texto en su representacion binaria encriptada
    char file_encrypted[]="C:/Users/admin/Desktop/practica_3/e1/cypher.bin";

    std::cout<<"Ingrese el nombre del archivo original: "<<std::endl;
    //std::cin>>file_input;

    //std::cout<<"Ingrese el nombre del archivo convertido en binario: "<<std::endl;
    //std::cin>>file_binary;

    std::cout<<"Ingrese el nombre del archivo donde se guardara la encriptacion: "<<std::endl;
    //std::cin>>file_encrypted;

    line
            /*Parametros de encriptacion*/
            int method=0; //metodo de cifrado

            int seed=0; //semilla del metodo

            //Se pide al usuario metodo y semilla hasta que coloque numeros validos

            while(method!=1 && method!=2)
            {
            std::cout<<"Ingrese el metodo de encriptacion (1 o 2): "<<std::endl;
            std::cin>>method;
            }

            while (seed < 3)
            {
                std::cout<<"Ingrese semilla de encriptacion (mayor o igual a 3): "<<std::endl;
                //minimo 3 para que siempre se asegure de que se encripte el archivo (por regla 3 del metodo 1)
                std::cin>>seed;
            }
    line

try{

    //definicion de los streams

    //stream de entrada para el archivo de texto original (input file stream)
    std::fstream ifs(file_input,std::ifstream::in);
    if(!ifs.good()){throw '1';}
    //stram de entrada y salida para el archivo de texto en su representacion binaria (output file stream binary)
    std::fstream ofsb(file_binary,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    if(!ofsb.good()){throw '2';}
    //stream de salida del archivo encriptado (output file stream crypted)
    std::fstream ofsc(file_encrypted,std::ifstream::out| std::fstream::trunc);
    if(!ofsc.good()){throw '3';}

    //se usa el 'trunc' para no tener errores de apertura de los archivos.


    /*Conversion del archivo de entrada a su representacion binaria*/

    char * buffer;// buffer del stream ifs, en el se alojaran los caracteres del archivo temporalmente
    buffer = new char [1]; //reservamos dinamicamente 1 solo caracter ya que convertiremos el archivo caracter a caracter


    //obtenemos el tamanyo del archivo
    ifs.seekg(0,ifs.end);
    int length=ifs.tellg();
    ifs.seekg(0,ifs.beg);

    //un caracter es 1 byte, es decir, 8 bits.
    char bin[8];//cadena de caracteres de 8 espacios para guardar temporalmente el caracter convertido a binario
    //depende del lugar donde se encuentra el cursor, el tamanyo del archivo y la semilla
    int last=0; //permite identificar si estamos en el ultimo bloque

    while(1)
        {
        int cursor=ifs.tellg();//identificamos el lugar del cursor
        if(cursor+1==length){last=1;} //vemos si nos encontramos en el ultimo caracter
        ifs.read(buffer,1);//leemos un caracter en el buffer
        //ofsb<<binary(buffer[i]); implementacion vieja
        charToBinary(buffer[0], bin, 8);//convertimos el caracter en binario en la cadena bin de 8 bits
        ofsb.write(bin,8);//escribimos el numero binario de 8 bits obtenido en el stream de conversion binaria
        if(last){break;}
        if(!ifs.good()){throw '1';}
        if(!ofsb.good()){throw '2';}
        }

    ifs.close();//cerramos el stream de entrada

    /*Fase de Encriptacion*/

    /*obtenemos el tamanyo del archivo en representacion binaria*/
    ofsb.seekg(0,ofsb.end);
    int lengthb=ofsb.tellg();
    ofsb.seekg(0,ofsb.beg);

    //creamos un buffer con tamanyo dependiente del seed (semilla del tamanyo del bloque)
    char * bufferb;
    bufferb=new char[seed];

    int rule=0;//variable auxiliar que determina en que regla se debe aplicar
    //esto es dado por la diferencia entre los ceros y unos del bloque anterior
    //en el primer bloque se imagina que el bloque anterior dio igual ceros y unos por lo que se inicializa en 0 la diferencia
    int z,o; //los numeros de ceros (zeros) y unos (ones) se guardaran en cada ciclo en estas variables

    while(1)
    {
        int cursorb=ofsb.tellg();//detectamos la posicion actual en el archivo
        int last=0;//variable que es una bandera de que estamos en el ultimo bloque
        int howMany;//variable auxiliar que permite saber cuanto debemos leer del archivo, generalmente es del tamanyo del bloque, excepto en el ultimo
        //ya que ahi puede ser igual o menor

        //si el lugar del cursor + un bloque (la semilla) no llega al final del archivo (notese el menor estricto) entonces...
        if(cursorb+seed<lengthb){howMany=seed;}//leo un bloque del tamanyo de la semilla si todavia queda espacio para un bloque mas

        //de lo contrario ya nos encontramos en el ultimo bloque, luego
            else{howMany=lengthb-cursorb;last=1;}//leo lo que quede, que es el tamanyo del archivo menos el lugar actual del cursor

        //guardamos en el buffer cuantos caracterese sea que tengamos que leer (determinado por howMany)
        ofsb.read(bufferb,howMany);

        //ejecutamos la encriptacion segun el metodo escogido por el usuario

        if (method==1)
        {
            if(rule==0) //si hay igual ceros que unos, negamos todos los bits
            {
                for(int i=0;i<howMany;i++)
                {
                    ofsc<<notbin(bufferb[i]);
                }
            }

            if(rule>0)//si hay mas ceros que unos, negamos cada dos (el primero no, el segundo si)
            {
                for(int i=0;i<howMany;i++)
                {
                    if(i%2!=0){ofsc<<notbin(bufferb[i]);} //notamos que indices impares se niegan
                    else{ofsc<<bufferb[i];}
                }
            }

            if(rule<0)//si hay mas unos que ceros, negamos cada 3 (primero no, segundo no, tercero si)
            //para facilitar esto, verificamos si i+1 es multiplo de 3 (si verificamos sobre i es mas complicado)
            {
                for(int i=0;i<howMany;i++)
                {
                    if((i+1)%3==0){ofsc<<notbin(bufferb[i]);}
                    else{ofsc<<bufferb[i];}

                }
            }

            /* determinamos que regla usar en el siguiente ciclo (ya que la regla depende del bloque sin encriptar procesado en el ciclo anterior)*/
            z=0;//numero de ceros (zeros)
            o=0;//numero de unos (ones)
            //notese que operamos sobre el bufferb sin encriptar
            for(int i=0;i<howMany;i++)
            {
                if (bufferb[i]=='0'){z++;}
                if (bufferb[i]=='1'){o++;}
            }
            rule=z-o; //determinamos la regla del ciclo siguiente , dada por la diferencia
        }

        if (method==2)
        {
            //desplazamos todo los bits uno a la derecha y el ultimo queda de primero
            //esto es equivalente a colocar en el archivo el caracter i-1 del buffer
            //excepto en la primera iteracion que colocamos es el ultimo caracter del buffer
            for(int i=0;i<howMany;i++)
            {
                if(i==0){ofsc<<bufferb[howMany-1];}
                else {ofsc<<bufferb[i-1];}
            }
        }

        if(last){break;}//ultimo bloque
        if(!ofsb.good()){throw '2';}
        if(!ofsc.good()){throw '3';}
    }

    ofsb.close();
    ofsc.close();

    int removed = remove(file_binary);
    if(removed){throw '4';}

    line
    std::cout<<"Archivo encriptado exitosamente!";
    line

}//cierre del try


    catch (char c){ //Excepciones
            std::cout<<"Error # "<<c<<": ";
            if(c=='1'){std::cout<<"Error al abrir el archivo de entrada.\n";}
            if(c=='2'){std::cout<<"Error al generar archivo de texto binario intermedio no encriptado.\n";}
            if(c=='3'){std::cout<<"Error al generar archivo de texto binario encriptado.\n";}
            if(c=='4'){std::cout<<"Error al eliminar el archivo de texto binario no encriptado.\n";}
            }

    catch(...){
        std::cout << "Error desconocido." <<std::endl;
    }



    return 0;
}



