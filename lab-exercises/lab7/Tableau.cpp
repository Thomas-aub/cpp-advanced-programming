#include <iostream>
#include "Tableau.hpp"


int main() {
    Tableau<int,6> A;
    for (int i = 0; i < 5; ++i){
        A.push_back(i);
    }
    TabIterator<int,6> it=A.begin();
    TabIterator<int,6> ite=A.end();
    
    for(;it!=ite;++it)
        std::cout << *it << std::endl;
}
