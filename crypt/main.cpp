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
#define max_filename 100
#define max_msg 1024
#define start_flag 'k'
#define stop_flag 'k'

int encrypt();
int decrypt();
int compare();
int sync();
int async();
void port_cfg(QSerialPort * serial, char * port);
int toBinary();
int toText();
int decode_arduino(char * arduino_file);
int printFile();

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
            std::cout<<"1.Encriptar\n";
            std::cout<<"2.Desencriptar\n";
            std::cout<<"3.Comparar\n";
            std::cout<<"4.Sincrona\n";
            std::cout<<"5.Asincrona\n";
            std::cout<<"6.Convertir a Binario\n";
            std::cout<<"7.Convertir a Texto\n";
            std::cout<<"8.Visualizar Archivo de Texto\n";
            std::cout<<"0.Salir\n";
            line line
            std::cin>>opc;
            line
            if(opc==0||opc==1||opc==2||opc==3||opc==4||opc==5||opc==6||opc==7||opc==8){break;}
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
        case 8 :{printFile(); break;}
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

    char file_input[max_filename]; //archivo de entrada de texto
    char file_encrypted[max_filename];//archivo de salida que aloja el texto en su representacion binaria encriptada

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

        char filein[max_filename];
        char fileout[max_filename];

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

    char file1[max_filename];
    char file2[max_filename];

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
    char port[max_filename];

    QSerialPort serial;
    port_cfg(&serial,port);

    /*Configuracion del mensaje*/
//    int length=0; //tamanyo del bloque de lectura maximo
//    line
//    std::cout<<"Ingrese el tamanyo maximo del bloque de lectura:\n";
//    std::cin>>length;
//    line

    char * message;
    message = new char[max_msg];

    /*Archivo donde se va a guardar*/
    char file[max_filename];
    line
    std::cout<<"Ingrese el nombre del archivo donde se guardara los datos enviados por el arduino:\n";
    std::cin>>file;
    line

    //arduino file stream
    std::fstream afs(file,std::ifstream::out| std::fstream::trunc);


    /*Comienzo de la transmision*/


    int howMany=0; //how many did we read
    serial.putChar(start_flag); //enviamos caracter al arduino para empezarla



        serial.waitForReadyRead(100);
        while(serial.bytesAvailable()>0)
        {
            if(serial.bytesAvailable()>0)
            {
                //Data was returned
                 howMany= serial.readLine(message,max_msg); //Leer toda la línea que envía arduino, - 1 porque al final agrega \0 automaticamente
                qDebug()<<"Response: "<<message;

                /*Guardamos en el archivo*/
                afs.write(message,howMany);
            }

            else
            {
                //No data
                qDebug()<<"Time out";
            }
            serial.waitForReadyRead(100);
        }


    afs.close();
    serial.close();

    int opc;
    while(1)
    {
        std::cout<<"\nDesea descodificar?\n1 para si, 0 para no.\n";
        std::cin>>opc;
        if(opc==1 || opc==0){break;}

    }
    if(opc){decode_arduino(file);}

    return 0;
}

int async()
{
    /*Configuracion del puerto*/
    char port[max_filename];

    QSerialPort serial;
    port_cfg(&serial,port);

    //int read=1;
    char * data;
    data = new char[max_msg];

    /*Archivo donde se va a guardar*/
    char file[max_filename];
    line
    std::cout<<"Ingrese el nombre del archivo donde se guardara los datos enviados por el arduino:\n";
    std::cin>>file;
    line

    //arduino file stream
    std::fstream afs(file,std::ifstream::out| std::fstream::trunc);

    int howMany = 0;

    serial.putChar(start_flag);
    while(true)
    {
        if(serial.waitForReadyRead(-1))
        {
            //data was returned
            howMany=serial.readLine(data,max_msg);

            qDebug()<<"Response: "<<data;



            if(data[howMany-1] == stop_flag) {break;}//fin de la transmision

            afs.write(data,howMany);

            //break;

        }
        else{
                        //No data
                        qDebug()<<"Time out";
                    }

    }

    serial.close();
    afs.close();


    int opc;
    while(1)
    {
        std::cout<<"\nDesea descodificar?\n1 para si, 0 para no.\n";
        std::cin>>opc;
        if(opc==1 || opc==0){break;}

    }
    if(opc){decode_arduino(file);}

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

    char file_txt[max_filename]; //archivo de entrada de texto
    char file_bin[max_filename];//archivo de salida que aloja el texto en su representacion binaria

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
            crypto::textToBinary(&fts,&fbs);

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

    char file_txt[max_filename]; //archivo de salida de texto
    char file_bin[max_filename];//archivo de entrada que aloja el texto en su representacion binaria


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
            crypto::binaryToText(&fbs,&fts);

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

int decode_arduino(char * arduino_file)
{
    char type;

    while(1)
    {
        std::cout<<"\n Seleccione el tipo de caracteres que envio el arduino\n\n a-->ascii\n b-->binario\n\n";
        std::cin>>type;

        if(type=='a' || type=='b')
        {break;}
    }

    int method,seed;

    crypto::encrypt_cfg(method,seed);

    //std::fstream whatToDecrypt();

    char file_decrypted[max_filename];

    std::cout<<"\nIngrese el nombre del archivo de salida descodificado:\n\n";
    std::cin>>file_decrypted;
    std::fstream dummy_stream("dummy.bin",std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    std::fstream arduinoDecrypted(file_decrypted,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    if(type=='a')
    {
        char arduino_bin[]="arduino.bin";
        try{

            //definicion de los streams

            //stream de entrada para el archivo de texto original (file text stream)
            std::fstream fts(arduino_file,std::ifstream::in);
            if(!fts.good()){throw '1';}
            //stream de entrada y salida para el archivo de texto en su representacion binaria (file binary stream)
            std::fstream fbs(arduino_bin,std::ifstream::out|std::ifstream::in| std::fstream::trunc);
            if(!fbs.good()){throw '2';}

            /*Conversion del archivo de entrada a su representacion binaria*/
                textToBinary(&fts,&fbs);

                fts.close();
                fbs.close();

                line
                std::cout<<"Archivo del arduino convertido a binario exitosamente!";
                line

                std::fstream whatToDecrypt(arduino_bin, std::fstream::in);
                crypto::decrypt(&whatToDecrypt,&dummy_stream,seed,method);
                binaryToText(&dummy_stream,&arduinoDecrypted);
                whatToDecrypt.close();

            }

        /*Excepciones*/
            catch (char c){
                    std::cout<<"Error # "<<c<<": ";
                    if(c=='1'){std::cout<<"Error al abrir el archivo de texto.\n";}
                    if(c=='2'){std::cout<<"Error al generar archivo en binario\n";}
                    }

            catch(...){ //cualquier otra excepcion
    }
    }

    else if(type=='b') //archivo es binario ya
    {
                std::fstream whatToDecrypt(arduino_file,std::fstream::in);
                crypto::decrypt(&whatToDecrypt,&arduinoDecrypted,seed,method);
                whatToDecrypt.close();

    }


                dummy_stream.close();
                arduinoDecrypted.close();

                if(type=='a')
                {
                remove("dummy.bin");
                remove("arduino.bin");
                }

                std::cout<<"\nMensaje del arduino descodificado exitosamente!\n";

                return 0;


}

int printFile()
{
    char file[max_filename];

    //while(1)
    {
    line
    std::cout<<"Ingrese el nombre del archivo que desea visualizar:\n";
    std::cin>>file;
    line

    }
    std::fstream ifs(file,std::ifstream::in);
    if(!ifs.good()){std::cout<<"\nNo se encontro el archivo.\n";return -1;}

    viewFile(&ifs);

    ifs.close();
    return 0;

}
