/*
2. Escriba un programa para decodificar el archivo generado por el programa anterior.
Igualmente debe recibir la semilla, el método de codificación y los nombres de los archivos
de entrada y salida.
*/

#include <fstream>
#include <iostream>
#include <exception>
#include <bitset>

#define buffer_size 8
#define line std::cout<<std::endl;
std::bitset<8> binary(char);
char notbin(char );
int pow(int ,int);
int main(){


    //char filein[100];
    //char fileout[100];

    std::cout<<"Enter name of binary file to decrypt: "<<std::endl;
    //std::cin>>filein;
    //char[] filein="C:/Users/admin/Desktop/practica_3/e2/cypher.bin";
    std::cout<<"Enter name of de-encrypted file: "<<std::endl;
    //std::cin>>fileout;
    //char[] fileout="C:/Users/admin/Desktop/practica_3/e2/cypher.ban";

    line
            /*Program Parameters*/
            int cipher=0;
            int seed=0;
            while(cipher!=1 && cipher!=2)
            {
            std::cout<<"Enter method to encrypt file (either 1 or 2): "<<std::endl;
            std::cin>>cipher;
            }

            while (seed < 4)
            {
                std::cout<<"Enter seed of the encryption (integer equal or greater than 4): "<<std::endl;
                std::cin>>seed;
            }
    line

    std::fstream ofs("C:/Users/admin/Desktop/practica_3/e2/cypher.ban",std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    std::fstream ifs("C:/Users/admin/Desktop/practica_3/e1/cypher.bin",std::ifstream::in);
    std::fstream text("C:/Users/admin/Desktop/practica_3/e2/text.txt",std::ifstream::out);
    line
    std::cout<<"Input file succesful: "<<ifs.good();
    line
    std::cout<<"Output file succesful: "<<ofs.good();
    line
    /*Encrypting Phase*/

    ifs.seekg(0,ifs.end);
    int length=ifs.tellg();
    ifs.seekg(0,ifs.beg);

    char * buffer;
    char * buffer2;
    int way=0;
    buffer=new char[seed];
    buffer2=new char[seed];
    while(ifs.good()&&ofs.good())

    {
        int carry=ifs.tellg();
        int howMany;
        if(carry+seed<=length){howMany=seed;}
            else{howMany=length-carry;}

        ifs.read(buffer,howMany);

        if (cipher==1)
        {
            if(way==0)//first block too since way is initialized in 0
            {
                for(int i=0;i<howMany;i++)
                {
                    ofs<<notbin(buffer[i]);
                }
            }

            if(way>0)
            {
                for(int i=0;i<howMany;i++)
                {
                    if(i%2==0){ofs<<buffer[i];}
                    else{ofs<<notbin(buffer[i]);}
                }
            }

            if(way<0)
            {
                for(int i=0;i<howMany;i++)
                {
                    if((i+1)%3==0){ofs<<notbin(buffer[i]);}
                    else{ofs<<buffer[i];}

                }
            }
            line
            //std::cout<<ofs.good()<<" "<<ofs.tellp()<<ofs.tellg();
            line
            ofs.seekg(-4,ofs.cur);//this was the problem, everytime we did ofs<< the carry moved
            ofs.read(buffer2,howMany);

            int z=0;
            int o=0;
            for(int i=0;i<howMany;i++)
            {
                if (buffer2[i]=='0'){z++;}
                if (buffer2[i]=='1'){o++;}
            }
            way=z-o;
        }

        if (cipher==2)
        {
            for(int i=0;i<howMany;i++)
            {
                if(i==howMany-1){ofs<<buffer[0];}
                else {ofs<<buffer[i+1];}
            }
        }
        if(howMany<seed){break;}//last block
     }

/*Conversion from binary to text*/
    ofs.seekg(0,ofs.beg);
    char buffet[8]; //1 byte is 8 bits, therefore 8 chars in binary are 1 char in text
    ofs.read(buffet,8);
    while(ofs.good()&&text.good())
    {

        int x=0;
        for(int i=0;i<8;i++)
        {
            x=((int) (buffet[i]-48))*pow(2,7-i)+x;

            line
        }
        std::cout<<x;

        text<<(char) x;
        line
        std::cout<<ofs.eof();line
        ofs.read(buffet,8);
        if(ofs.eof()){break;}

    }

    ifs.close();
    ofs.close();
    text.close();
    return 0;
}

std::bitset<8> binary(char c)
{
    std::bitset<8> x(c);
    return x;
}

char notbin(char c)
{
    char xnot;
    if (c=='0'){xnot='1';}
    if (c=='1'){xnot='0';}

    return xnot;
}

int pow(int a,int b)
    {
        int potencia=a;
        if (b==0){return 1;}
        else
        {
        for(int i=1;i<b;i++)
            {
                    potencia=potencia*a;
            }
        return potencia;
        }
    }
