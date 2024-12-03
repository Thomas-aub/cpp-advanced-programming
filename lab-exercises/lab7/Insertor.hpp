#include "Tableau.hpp"

template <typename T>
class Insertor 
{
    private :
        T* data;
        Tableau<T, AGRANDISSEMENT>* tab;

    public :

        // Constructeur par défaut
        Insertor();

        // Constructeur par copie profonde
        Insertor(const Insertor<T> &);

        // Constructeur par déplacement
        Insertor(Insertor<T> &&);

        // Opérateur d'affectation par copie 
        Insertor<T> & operator=(const Insertor<T> &);

        // Opérateur d'affectation par déplacement
        Insertor<T> & operator=(Insertor<T> &&);

        // Destructeur 
        ~Insertor();

};

template <typename T>
Insertor<T>::Insertor() : data(nullptr), tab(nullptr) {}
