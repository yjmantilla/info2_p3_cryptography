#include <fstream>
#include <iostream>
#include <exception>
#define word 17
void printstr(char * ,int );
int main()
{
    std::fstream ifs("C:/Users/admin/Desktop/practica_3/e1/data.txt",std::ifstream::in);
    std::fstream ofs("C:/Users/admin/Desktop/practica_3/e2/text.txt",std::ifstream::in);

    char bufferi[word];
    char buffero[word];

    ifs.seekg(0,ifs.end);
    int length=ifs.tellg();
    ifs.seekg(0,ifs.beg);





    std::cout<<ifs.good()<<" "<<ofs.good()<<std::endl;
    while(ifs.good()&&ofs.good())
    {
        int carry=ifs.tellg();
        int howMany;
        if(carry+word<=length){howMany=word;}
            else{howMany=length-carry;}

        ifs.read(bufferi,howMany);
        ofs.read(buffero,howMany);


        bool equal=true;

        for(int i=0;i<howMany;i++)
        {
            if(bufferi[i]!=buffero[i])
            {
                equal=false;
            }
        }
        printstr(bufferi,howMany);
        std::cout<<" == ";
        printstr(buffero,howMany);
        std::cout<<" : "<<equal<<std::endl;

        if(howMany<word){break;}//last block

    }

    return 0;
}

void printstr(char * str,int n)
{
    for(int i=0;i<n;i++)
    {
        std::cout<<*(str+i);
    }
}
