/*
2. Escriba un programa para decodificar el archivo generado por el programa anterior.
Igualmente debe recibir la semilla, el método de codificación y los nombres de los archivos
de entrada y salida.
*/

#include <fstream>
#include <iostream>
#include <exception>
#include "C:\Users\admin\Desktop\practica_3\e1\crypto.h"

#define line std::cout<<std::endl;

int main(){

    /*Nombres de los archivos a trabajar*/

        /*Ingresado por el usuario*/
        /*
        char filein[100];
        char fileout[100];

        std::cout<<"Ingrese el nombre del archivo binario a decodificar: "<<std::endl;
        std::cin>>filein;

        std::cout<<"Ingrese el nombre del archivo de texto decodificado: "<<std::endl;
        std::cin>>fileout;
        */

        /*Para debug*/
        char filein[]="C:/Users/admin/Desktop/practica_3/e1/cypher.bin";
        char fileout[]="C:/Users/admin/Desktop/practica_3/e2/text.txt";

        /*Archivo intermedio que aloja el archivo en binario decodificado, se borrara al final*/
        char filebin[]="data.bin";

    line
        /*Parametros del Programa*/
            int method=0;
            int seed=0;

            while(method!=1 && method!=2)
            {
            std::cout<<"Ingrese el metodo de encriptacion (1 o 2): "<<std::endl;
            std::cin>>method;
            }

            while (seed < 3)
            {
                std::cout<<"Ingrese semilla de encriptacion (mayor o igual a 3): "<<std::endl;
                std::cin>>seed;
            }
    line

try{
    /*Creacion de los streams para los archivos*/

    //input file stream
    std::fstream ifs(filein,std::ifstream::in);
    if(!ifs.good()){throw '1';}

    //mid file stream
    std::fstream mfs(filebin,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    if(!mfs.good()){throw '2';}

    //text file stream
    std::fstream text(fileout,std::ifstream::out);
    if(!text.good()){throw '3';}

    /*Fase de decodificacion*/

    //obtenemos tamanyo del archivo de entrada
    ifs.seekg(0,ifs.end);
    int length=ifs.tellg();
    ifs.seekg(0,ifs.beg);


    char * buffer; //para el archivo de entrada binario codificado
    char * buffer2;//para el archivo intermedio binario descodificado
    buffer=new char[seed];
    buffer2=new char[seed];

    int rule=0;//Inicializamos en cero ya que el primer bloque en el metodo 1 aplica esa regla
    int cursor;
    int howMany;
    int last=0;

    while(ifs.good()&&mfs.good())

    {
        cursor=ifs.tellg();

        //detectamos cuanto hay que leer y si estamos en el ultimo bloque
        if(cursor+seed<length){howMany=seed;}
            else{howMany=length-cursor;last=1;}

        ifs.read(buffer,howMany);

        /*Segun el metodo, descodificamos*/
            if (method==1)
            {
                if(rule==0)
                {
                    for(int i=0;i<howMany;i++)
                    {
                        mfs<<notbin(buffer[i]);
                        //invertimos todos
                    }
                }

                if(rule>0)
                {
                    for(int i=0;i<howMany;i++)
                    {
                        if(i%2!=0){mfs<<notbin(buffer[i]);}
                        else{mfs<<buffer[i];}
                        //invertimos cada dos
                    }
                }

                if(rule<0)
                {
                    for(int i=0;i<howMany;i++)
                    {
                        if((i+1)%3==0){mfs<<notbin(buffer[i]);}
                        else{mfs<<buffer[i];}
                        //invertimos cada 3

                    }
                }

                /*Para debug*/
                    //line
                    //std::cout<<mfs.good()<<" "<<mfs.tellp()<<mfs.tellg();
                    //line

                /*Correcion del seek del stream mfs*/

                /*
                Cada vez que usamos mfs<< el cursor howMany posiciones y nuestra meta es leer lo que acabamos de descodificar para determinar que regla usar
                Por lo tanto restamos al cursor howMany posiciones
                */
                mfs.seekg(-howMany,mfs.cur);
                mfs.read(buffer2,howMany);

                /*Determinamos que regla se aplica en el siguiente bloque*/
                int z=0;
                int o=0;
                for(int i=0;i<howMany;i++)
                {
                    if (buffer2[i]=='0'){z++;}
                    if (buffer2[i]=='1'){o++;}
                }
                rule=z-o;

            }

            if (method==2)
            {
                for(int i=0;i<howMany;i++)
                {
                    /*El primero del buffer (codificado) es el ultimo descodificado*/
                    if(i==howMany-1){mfs<<buffer[0];}
                    /*En los demas el siguiente del buffer (codificado) es el actual descodificado*/
                    else {mfs<<buffer[i+1];}
                }
            }

        if(last){break;}//ultimo bloque

        if(!ifs.good()){throw '1';}
        if(!mfs.good()){throw '2';}
     }

/*Conversion from binary to text*/
    mfs.seekg(0,mfs.beg);

    //creamos un buffer para el archivo de texto descodificado
    char buffet[8]; //1 byte is 8 bits, therefore 8 chars in binary are 1 char in text
    mfs.read(buffet,8); //leemos los primeros 8 caracteres (que representan bits)

    while(1)
    {       
        text<<binaryToChar(8,buffet);
        //line
        //std::cout<<mfs.eof();line

        mfs.read(buffet,8);//leemos los siguientes 8 bits para la siguiente iteracion
        //de esta manera si ya estabamos en los ultimos 8 entonces al movernos llegaremos a eof y podremos salir
        if(mfs.eof()){break;}

        if(!mfs.good()){throw '2';}
        if(!text.good()){throw '3';}
    }


    /*Cerramos los archivos*/
    ifs.close();
    mfs.close();
    text.close();

    //Eliminamos el archivo extra binario sin codificar
    int removed = remove(filebin);//remove retorna 0 si se borro correctamente y otro numero si no
    if(removed){throw '4';}

    line
    std::cout<<"Archivo desencriptado exitosamente!";
    line


}//cierre del try

    /*Excepciones*/
        catch (char c){
                std::cout<<"Error # "<<c<<": ";
                if(c=='1'){std::cout<<"Error al abrir el archivo de entrada.\n";}
                if(c=='2'){std::cout<<"Error al generar archivo de texto binario intermedio no encriptado.\n";}
                if(c=='3'){std::cout<<"Error al generar archivo de texto decodificado.\n";}
                if(c=='4'){std::cout<<"Error al eliminar el archivo de texto binario no encriptado.\n";}
                }

        catch(...){ //cualquier otra excepcion
            std::cout << "Error desconocido." <<std::endl;
        }

    return 0;
}
