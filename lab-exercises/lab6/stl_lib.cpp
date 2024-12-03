#include <iostream>
#include <iterator>
#include <deque>
#include <vector>
#include <algorithm>
#include <set>
#include "GenMult.cpp"

int main ()
{

    //  Construisez un deque d de 5 entiers
    std::deque<int> d(5);

    //  Remplissez d avec des multiples de 4 (on utilisera le générateur du TP 04)
    GeneratorMultiples gen = GeneratorMultiples(4);
    std::generate(d.begin(), d.end(), gen);


    //  Affichez le contenu de d sur la sortie standard (on construira pour cela un ostream_iterator
    // associé à la sortie standard et on aura recours à l’algorithme copy de la STL pour copier le
    // contenu de d sur la sortie standard via les itérateurs adéquats).
    std::ostream_iterator<int> sortie(std::cout);
    std::copy(d.begin(), d.end(), sortie);

    //  Construisez un ensemble s1 d’entiers à partir de d
    std::set<int> s1(d.begin(), d.end());

    //  Videz d de son contenu
    d.clear();

    //  Construisez un ensemble s2 d’entiers par insertion successive de 10 multiples de 2 (cette
    // fois, vous avez le droit d’utiliser une boucle for)
    GeneratorMultiples gen2 = GeneratorMultiples(2);
    std::set<int> s2;
    for (int i; i < 10; ++i)
    {
        s2.insert(gen2());
    }


    //  Construisez un ensemble vide s3
    std::set<int> s3;
    GeneratorMultiples gen3 = GeneratorMultiples(3);

    //  Remplissez s3 avec 6 multiples de 3 (on utilisera un insertor sur cet ensemble, ainsi que
    // l’algorithme generate_n, voir site web de la STL)
    std::generate_n(std::inserter(s3, s3.end()), 6, gen3);

    //  Affichez le contenu des ensembles s1, s2 et s3 en séparant les éléments par des "; "
    for (int s : s1)
    {
        std::cout << s << "; ";
    }
    std::cout << std::endl;
    for (int s : s2)
    {
        std::cout << s << "; ";
    }
    std::cout << std::endl;
    for (int s : s3)
    {
        std::cout << s << "; ";
    }
    std::cout << std::endl;
    
    return 0;
}
