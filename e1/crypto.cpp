#include <iostream>

/*
funcion para calcular la potencia de un numero
*/

int pow(int a,int b)
    {
        int power=a;
        if (b==0){return 1;}
        else
        {
        for(int i=1;i<b;i++)
            {
                    power=power*a;
            }
        return power;
        }
    }

/*
funcion que convierte un caracter 'c' en un numero binario de 'n' bits y lo guarda en una cadena de caracteres 'bin'
*/	

void charToBinary(char c,char * bin,int n)
{
    int x = (int) c;
    int y;

    for(int i=n-1;i>=0;i--)
    {
        y = x/(pow(2,i));
        bin[n-1-i] = y + 48; //n-1 ya que un numero de n bits necesita un arreglo de 0 a n-1
        x = x - pow(2,i)*y;
        //cout<<i<<" "<<x<<" "<<y<<" "<<bin[n-1-i]<<endl; usado anteriormente para debug
    }

	/*
	El algoritmo funciona dividiendo el numero entero respectivo del caracter entre la potencia de 2 correspondiente
	a la posicion actual del algoritmo, obteniendo asi el 1 o 0 correspondiente en esa posicion. 
	
	Una vez obtenido ese numero se guarda en la cadena de caracteres el 1 o 0 pero trasladado 48 posiciones para obtener los valores de los numeros en ASCII
	
	Luego se resta del numero entero la cantidad que ya fue representada por el algoritmo.
	*/
}



/*
	funcion que niega un caracter binario (1 o 0) y lo retorna
*/
char notbin(char c)
{
    char xnot;
    if (c=='0'){xnot='1';}
    if (c=='1'){xnot='0';}

    return xnot;
}


/*implementacion vieja de la conversion a binario que requiere de la libreria bitset
std::bitset<8> binary(char c)
{
    std::bitset<8> x(c);
    return x;
}
*/

/*Funcion que convierte un numero binario de n bits en un caracter*/

char binaryToChar(int n, char * string)
{
int x=0;

    for(int i=0;i<n;i++)
    {
        x=((int) (string[i]-48))*pow(2,n-1-i)+x;

        //std::cout<<x;
        //line
    }

return (char) x;
}
