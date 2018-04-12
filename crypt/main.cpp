#include <fstream>
#include <iostream>
#include <exception>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "crypto.h"

#define line std::cout<<std::endl;
#define word 8

int encrypt();
int decrypt();
int compare();
int sync();
int async();
void port_cfg(QSerialPort * serial, char * port);
int toBinary();
int toText();

int main()
{
    int opc=-1;
    while(1)
    {
        while(1)
        {
            line
            std::cout<<"Que desea hacer? (Seleccione 0,1,2,3,4,5,6,7)";
            line line
            std::cout<<"0.Salir\n";
            std::cout<<"1.Encriptar\n";
            std::cout<<"2.Desencriptar\n";
            std::cout<<"3.Comparar\n";
            std::cout<<"4.Sincrona\n";
            std::cout<<"5.Asincrona\n";
            std::cout<<"6.Convertir a Binario\n";
            std::cout<<"7.Convertir a Texto\n";
            line line
            std::cin>>opc;
            line
            if(opc==0||opc==1||opc==2||opc==3||opc==4||opc==5||opc==6||opc==7){break;}
        }

        switch (opc)
        {
        case 0 :{return 0;}
        case 1 :{encrypt();break;}
        case 2 :{decrypt();break;}
        case 3 :{compare();break;}
        case 4 :{sync();break;}
        case 5 :{async();break;}
        case 6 :{toBinary();break;}
        case 7 :{toText();break;}
        }
    }
    return 0;
}

int encrypt()
{


    /*Nombre de los archivos*/

    //archivo intermedio que aloja el texto en su representacion binaria
    char file_binary[]="data.bin";
    //std::cout<<"Ingrese el nombre del archivo convertido en binario: "<<std::endl;
    //std::cin>>file_binary;

    /*Ingresado por el usuario*/

    char file_input[100]; //archivo de entrada de texto
    char file_encrypted[100];//archivo de salida que aloja el texto en su representacion binaria encriptada

    std::cout<<"Ingrese el nombre del archivo original: "<<std::endl;
    std::cin>>file_input;

    line line

    std::cout<<"Ingrese el nombre del archivo donde se guardara la encriptacion: "<<std::endl;
    std::cin>>file_encrypted;


    /*Para debug*/
    /*
    char file_input[]="C:/Users/admin/Desktop/practica_3/e1/data.txt";
    char file_encrypted[]="C:/Users/admin/Desktop/practica_3/e1/cypher.bin";
    */

    /*Parametros del Programa*/
    int method,seed;
    encrypt_cfg(method,seed);

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
        textToBinary(&ifs,&ofsb);
        ifs.close();//cerramos el stream de entrada

   /*Fase de encriptacion*/
        crypto::encrypt(&ofsb, &ofsc,seed,method);

        ofsb.close();
        ofsc.close();

    //Eliminamos el archivo extra de conversion a binario sin codificar
    int removed = remove(file_binary);//remove retorna 0 si se borro correctamente y otro numero si no
    if(removed){throw '4';}

    line
    std::cout<<"Archivo encriptado exitosamente!";
    line

}//cierre del try

/*Excepciones*/
    catch (char c){
            std::cout<<"Error # "<<c<<": ";
            if(c=='1'){std::cout<<"Error al abrir el archivo de entrada.\n";}
            if(c=='2'){std::cout<<"Error al generar archivo de texto binario intermedio no encriptado.\n";}
            if(c=='3'){std::cout<<"Error al generar archivo de texto binario encriptado.\n";}
            if(c=='4'){std::cout<<"Error al eliminar el archivo de texto binario no encriptado.\n";}
            }

    catch(...){ //cualquier otra excepcion
        std::cout << "Error desconocido." <<std::endl;
    }



    return 0;
}

int decrypt()
{

    /*Nombres de los archivos a trabajar*/

        /*Ingresado por el usuario*/

        char filein[100];
        char fileout[100];

        std::cout<<"Ingrese el nombre del archivo binario a decodificar: "<<std::endl;
        std::cin>>filein;

        std::cout<<"Ingrese el nombre del archivo de texto decodificado: "<<std::endl;
        std::cin>>fileout;


        /*Para debug*/
        /*
        char filein[]="C:/Users/admin/Desktop/practica_3/e1/cypher.bin";
        char fileout[]="C:/Users/admin/Desktop/practica_3/e2/text.txt";
        */
        /*Archivo intermedio que aloja el archivo en binario decodificado, se borrara al final*/
        char filebin[]="data.bin";


        /*Parametros del Programa*/
        int method,seed;
        encrypt_cfg(method,seed);

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
    crypto::decrypt(&ifs,&mfs,seed,method);

    /*Conversion de binario a texto*/
    crypto::binaryToText(&mfs,&text);

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

int compare()
{
    /*Ingresado por el usuario*/

    char file1[100];
    char file2[100];

    std::cout<<"Ingrese el nombre del archivo 1: "<<std::endl;
    std::cin>>file1;

    std::cout<<"Ingrese el nombre del archivo 2: "<<std::endl;
    std::cin>>file2;

    std::fstream ifs1(file1,std::ifstream::in);
    std::fstream ifs2(file2,std::ifstream::in);

    char buffer1[word];
    char buffer2[word];

    ifs1.seekg(0,ifs1.end);
    int length=ifs1.tellg();
    ifs1.seekg(0,ifs1.beg);





    std::cout<<ifs1.good()<<" "<<ifs2.good()<<std::endl;
    while(ifs1.good()&&ifs2.good())
    {
        int carry=ifs1.tellg();
        int howMany;
        if(carry+word<=length){howMany=word;}
            else{howMany=length-carry;}

        ifs1.read(buffer1,howMany);
        ifs2.read(buffer2,howMany);


        bool equal=true;

        for(int i=0;i<howMany;i++)
        {
            if(buffer1[i]!=buffer2[i])
            {
                equal=false;
            }
        }
        printstr(buffer1,howMany);
        std::cout<<" == ";
        printstr(buffer2,howMany);
        std::cout<<" : "<<equal<<std::endl;

        if(howMany<word){break;}//last block

    }

    return 0;
}

int sync()
{
    /*Configuracion del puerto*/
    char port[100];

    QSerialPort serial;
    port_cfg(&serial,port);

    /*Configuracion del mensaje*/
    int length=0; //tamanyo del bloque de lectura maximo
    line
    std::cout<<"Ingrese el tamanyo maximo del bloque de lectura:\n";
    std::cin>>length;
    line

    char * message;
    message = new char[length+1];

    /*Archivo donde se va a guardar*/
    char file[100];
    line
    std::cout<<"Ingrese el nombre del archivo donde se guardara los datos enviados por el arduino:\n";
    std::cin>>file;
    line

    //arduino file stream
    std::fstream afs(file,std::ifstream::out| std::fstream::trunc);


    /*Comienzo de la transmision*/

    serial.write("\n"); //enviamos caracter al arduino para empezarla
    int howMany=0; //how many did we read

    if(serial.waitForReadyRead(100)){
                //Data was returned
                 howMany= serial.readLine(message,length+1); //Leer toda la línea que envía arduino, +1 porque al final agrega \0 automaticamente
                qDebug()<<"Response: "<<message;

                /*Guardamos en el archivo*/
                afs.write(message,howMany);

            }else{
                //No data
                qDebug()<<"Time out";
            }

    afs.close();
    serial.close();

    return 0;
}

int async()
{
    /*Configuracion del puerto*/
    char port[100];

    QSerialPort serial;
    port_cfg(&serial,port);

    int read=1;
    char data;

    /*Archivo donde se va a guardar*/
    char file[100];
    line
    std::cout<<"Ingrese el nombre del archivo donde se guardara los datos enviados por el arduino:\n";
    std::cin>>file;
    line

    //arduino file stream
    std::fstream afs(file,std::ifstream::out| std::fstream::trunc);

    while(read)
    {
        if(serial.waitForReadyRead(150))
        {
            //data was returned
            serial.read(&data,1);
            qDebug()<<"Response: "<<data;
            if(data == '\n') {read = 0;}
            afs.put(data);

        }
        else{
                        //No data
                        qDebug()<<"Time out";
                    }
    }

    serial.close();
    afs.close();

    return 0;

}

void port_cfg(QSerialPort * serial, char * port)
{
    /*Configuracion del puerto*/

    try
    {

        std::cout<<"\nIngrese nombre del puerto:\n";
        std::cin>>port;
        line

        serial->setPortName(port);

        if(!serial->open(QIODevice::ReadWrite)) {throw '0';}

        if(serial->open(QIODevice::ReadWrite)) {


            if(!serial->setBaudRate(QSerialPort::Baud9600))
            {qDebug()<<serial->errorString();throw '1';}

            if(!serial->setDataBits(QSerialPort::Data8))
            {qDebug()<<serial->errorString();throw '2';}

            if(!serial->setParity(QSerialPort::NoParity))
            {qDebug()<<serial->errorString();throw '3';}

            if(!serial->setStopBits(QSerialPort::OneStop))
            {qDebug()<<serial->errorString();throw '4';}

            if(!serial->setFlowControl(QSerialPort::NoFlowControl))
            {qDebug()<<serial->errorString();throw '5';}
        }


    }

    /*Excepciones*/
        catch (char c){
                std::cout<<"Error # "<<c<<": ";
                if(c=='0'){std::cout<<"Error al abrir puerto.\n";}
                if(c=='1'){std::cout<<"Error al configurar baudios.\n";}
                if(c=='2'){std::cout<<"Error al configurar cantidad data bits.\n";}
                if(c=='3'){std::cout<<"Error al configurar paridad del puerto.\n";}
                if(c=='4'){std::cout<<"Error al configurar bits de stop.\n";}
                if(c=='5'){std::cout<<"Error al configurar flow control.\n";}
                }

        catch(...){ //cualquier otra excepcion
            std::cout << "Error desconocido." <<std::endl;
        }

}

int toBinary()
{
    /*Nombre de los archivos*/

    /*Ingresado por el usuario*/

    char file_txt[100]; //archivo de entrada de texto
    char file_bin[100];//archivo de salida que aloja el texto en su representacion binaria

    std::cout<<"Ingrese el nombre del archivo de texto: "<<std::endl;
    std::cin>>file_txt;

    line line

    std::cout<<"Ingrese el nombre del archivo en binario: "<<std::endl;
    std::cin>>file_bin;

    try{

        //definicion de los streams

        //stream de entrada para el archivo de texto original (file text stream)
        std::fstream fts(file_txt,std::ifstream::in);
        if(!fts.good()){throw '1';}
        //stream de entrada y salida para el archivo de texto en su representacion binaria (file binary stream)
        std::fstream fbs(file_bin,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
        if(!fbs.good()){throw '2';}

        /*Conversion del archivo de entrada a su representacion binaria*/
            textToBinary(&fts,&fbs);

            fts.close();
            fbs.close();

            line
            std::cout<<"Archivo convertido a binario exitosamente!";
            line

        }

    /*Excepciones*/
        catch (char c){
                std::cout<<"Error # "<<c<<": ";
                if(c=='1'){std::cout<<"Error al abrir el archivo de texto.\n";}
                if(c=='2'){std::cout<<"Error al generar archivo en binario\n";}
                }

        catch(...){ //cualquier otra excepcion
            std::cout << "Error desconocido." <<std::endl;
        }

    return 0;
}

int toText()
{
    /*Nombre de los archivos*/

    /*Ingresado por el usuario*/

    char file_txt[100]; //archivo de salida de texto
    char file_bin[100];//archivo de entrada que aloja el texto en su representacion binaria


    std::cout<<"Ingrese el nombre del archivo en binario: "<<std::endl;
    std::cin>>file_bin;

    line line


    std::cout<<"Ingrese el nombre del archivo de texto: "<<std::endl;
    std::cin>>file_txt;


    try{

        //definicion de los streams

        //stream de entrada para el archivo de texto original (file text stream)
        std::fstream fbs(file_bin,std::ifstream::in);
        if(!fbs.good()){throw '1';}
        //stream de entrada y salida para el archivo de texto en su representacion binaria (file binary stream)
        std::fstream fts(file_txt,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
        if(!fts.good()){throw '2';}

        /*Conversion del archivo de entrada a su representacion binaria*/
            binaryToText(&fbs,&fts);

            fts.close();
            fbs.close();

            line
            std::cout<<"Archivo convertido a texto exitosamente!";
            line

        }

    /*Excepciones*/
        catch (char c){
                std::cout<<"Error # "<<c<<": ";
                if(c=='1'){std::cout<<"Error al abrir el archivo en binario.\n";}
                if(c=='2'){std::cout<<"Error al generar archivo de texto\n";}
                }

        catch(...){ //cualquier otra excepcion
            std::cout << "Error desconocido." <<std::endl;
        }

    return 0;
}
