#include <iostream>
class GeneratorMultiples
{
    private :
        int cmp;
        int base;
    
    public :
        GeneratorMultiples() : cmp(0), base(0){}
        GeneratorMultiples(int i) : cmp(0), base(i){}

        int operator ()() {
            ++cmp;
            return (cmp * base);
        }
};

/*
int main () 
{
    GeneratorMultiples gen5 = GeneratorMultiples(5);
    for (int i =0; i < 5; ++i)
    {
    std::cout << gen5() << std::endl;
    }
    return 0;
}
*/