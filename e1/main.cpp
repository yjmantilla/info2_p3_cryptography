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
//#include <bitset>

#define buffer_size 8
#define line std::cout<<std::endl;
//std::bitset<8> binary(char);
char notbin(char );
void toBinary(char ,char * ,int );
int pow(int ,int );

int main(){


    char filein[100];
    char fileb[100];
    char filec[100];

    std::cout<<"Enter name of file to encrypt: "<<std::endl;
    //std::cin>>filein;

    std::cout<<"Enter name of binary conversion file: "<<std::endl;
    //std::cin>>fileb;

    std::cout<<"Enter name of encryption file: "<<std::endl;
    //std::cin>>filec;

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

    char * buffer;
    buffer = new char [seed];

    std::fstream ofsc("C:/Users/admin/Desktop/practica_3/e1/cypher.bin",std::fstream::binary|std::ifstream::out| std::fstream::trunc);
    std::fstream ofsb("C:/Users/admin/Desktop/practica_3/e1/data.bin",std::fstream::binary|std::ifstream::out|std::ifstream::in| std::fstream::trunc);
    std::fstream ifs("C:/Users/admin/Desktop/practica_3/e1/data.txt",std::ifstream::in);

    std::cout<<ifs.good();
    //converting the ifs to binary in ofsb

    ifs.seekg(0,ifs.end);
    int lenght=ifs.tellg();
    ifs.seekg(0,ifs.beg);

    /*Convert File To Binary*/
    char bin[8];

    while(ifs.good())
        {
        int carryg=ifs.tellg();

        if(carryg+seed<lenght)
        {
            ifs.read(buffer,seed);
            line
            for(int i=0;i<seed;i++)
                {
                //ofsb<<binary(buffer[i]);
                toBinary(buffer[i], bin, 8);
                ofsb.write(bin,8);
                }
        }
        else
            {
            ifs.read(buffer,lenght-carryg);
            line
            for(int i=0;i<lenght-carryg;i++)
                {
                //ofsb<<binary(buffer[i]);
                toBinary(buffer[i], bin, 8);
                ofsb.write(bin,8);
                }
            break;
            }
        }

    ifs.close();

    /*Encrypting Phase*/

    ofsb.seekg(0,ofsb.end);
    int lenghtb=ofsb.tellg();
    ofsb.seekg(0,ofsb.beg);

    char * bufferb;
    int way=0;
    bufferb=new char[seed];

    while(ofsb.good()&&ofsc.good())
    {
        int carrybg=ofsb.tellg();
        int howMany;
        if(carrybg+seed<=lenghtb){howMany=seed;}
            else{howMany=lenghtb-carrybg;}

        ofsb.read(bufferb,howMany);

        if (cipher==1)
        {
            if(way==0)//first block too since way is initialized in 0
            {
                for(int i=0;i<howMany;i++)
                {
                    ofsc<<notbin(bufferb[i]);
                }
            }

            if(way>0)
            {
                for(int i=0;i<howMany;i++)
                {
                    if(i%2==0){ofsc<<bufferb[i];}
                    else{ofsc<<notbin(bufferb[i]);}
                }
            }

            if(way<0)
            {
                for(int i=0;i<howMany;i++)
                {
                    if((i+1)%3==0){ofsc<<notbin(bufferb[i]);}
                    else{ofsc<<bufferb[i];}

                }
            }

            int z=0;
            int o=0;
            for(int i=0;i<howMany;i++)
            {
                if (bufferb[i]=='0'){z++;}
                if (bufferb[i]=='1'){o++;}
            }
            way=z-o;
        }

        if (cipher==2)
        {
            for(int i=0;i<howMany;i++)
            {
                if(i==0){ofsc<<bufferb[howMany-1];}
                else {ofsc<<bufferb[i-1];}
            }
        }

        if(howMany<seed){break;}//last block
        }



    ofsb.close();
    ofsc.close();
	return 0;			
}

//std::bitset<8> binary(char c)
//{
//    std::bitset<8> x(c);
//    return x;
//}

char notbin(char c)
{
    char xnot;
    if (c=='0'){xnot='1';}
    if (c=='1'){xnot='0';}

    return xnot;
}

void toBinary(char c,char * bin,int n)
{
    int x = (int) c;
    int y;

    for(int i=n-1;i>=0;i--)
    {
        y = x/(pow(2,i));
        bin[n-1-i] = y + 48;
        x = x - pow(2,i)*y;
        //cout<<i<<" "<<x<<" "<<y<<" "<<bin[n-1-i]<<endl;
    }
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
