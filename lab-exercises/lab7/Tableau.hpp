
#include <iostream>
#include <stdexcept>
#include <sstream>

template <typename T, size_t AGRANDISSEMENT>
class Tableau 
{

    private:
        T* data;          // Pointeur vers les données du tableau
        int capacite;     // Capacité du tableau
        int taille;       // Taille du tableau

    public:
        // Constructeur défaut
        Tableau ();

        // Constructeur classique
        Tableau (const int& size);

        // Constructeur copie
        Tableau (const Tableau<T, AGRANDISSEMENT> & autre);

        // Constructeur déplacement
        Tableau ( Tableau<T, AGRANDISSEMENT> && autre);

        // Destructeur 
        ~Tableau ();

        // affectation copie
        Tableau<T, AGRANDISSEMENT> & operator = (const Tableau<T, AGRANDISSEMENT> & autre);
        
        // affectation déplacement
        Tableau<T, AGRANDISSEMENT> & operator = (Tableau<T, AGRANDISSEMENT> && autre);

        // []
        T& operator [] (int  index);
        const T& operator [] (int  index) const;

        // ajoute 
        void ajoute(const T & value);

        void agrandir();
};

// Constructeur défaut
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau () : data(nullptr), capacite(0), taille(0){}

// Constructeur classique
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau (const int & size) : data(new T[size]), capacite(size), taille(size){}

// Constructeur copie
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau (const Tableau<T, AGRANDISSEMENT> & autre) 
{
    capacite = autre.capacite;
    taille = autre.taille;
    data = new T[capacite];
    for (int i = 0; i < taille; ++i)
    {
        data[i] = autre[i];
    }
}

// Constructeur déplacement
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau ( Tableau<T, AGRANDISSEMENT> && autre) 
{
    capacite = autre.capacite;
    taille = autre.taille;
    data = std::move(autre).data;
    autre.data = nullptr;
    
}


// Destructeur 
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::~Tableau ()
{
    delete[] data;
    data = nullptr;
}

// affectation copie
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>& Tableau<T, AGRANDISSEMENT>:: operator = (const Tableau<T, AGRANDISSEMENT> & autre)
{
    if (autre != this) // auto affecation
    {
        capacite = autre.capacite;
        taille = autre.taille;
        data = new T[capacite];
        for (int i = 0; i < taille; ++i)
        {
            data[i] = autre[i];
        }
    }
    return *this;
}

// affectation déplacement
template <typename T, size_t AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT> & Tableau<T, AGRANDISSEMENT>:: operator = (Tableau<T, AGRANDISSEMENT> && autre)
{
    if (autre != this) // auto affecation
    {    
        delete[] data;
        
        capacite = autre.capacite;
        taille = autre.taille;
        data = std::move(autre).data;


        autre.data = nullptr;
        autre.capacite = 0;
        autre.taille = 0;
    }
    return *this;
}

// []
template <typename T, size_t AGRANDISSEMENT>
T& Tableau<T, AGRANDISSEMENT>::operator [] (int  index )
{
    if (index < 0 || index > taille)
    {
        return nullptr;
    }

    return data[index];
}
template <typename T, size_t AGRANDISSEMENT>
const T& Tableau<T, AGRANDISSEMENT>::operator [] (int  index) const
{
     if (index < 0 || index > taille)
    {
        return nullptr;
    }

    return data[index];
}

// ajoute 
template <typename T, size_t AGRANDISSEMENT>
void Tableau<T, AGRANDISSEMENT>::ajoute(const T & value)
{
    if (taille == capacite)
    {
        this->agrandir();
    }

    data[taille] = value;
    ++taille;
}


template <typename T, size_t AGRANDISSEMENT>
void Tableau<T, AGRANDISSEMENT>::agrandir()
{
    size_t new_capacite = capacite + AGRANDISSEMENT;
    T* new_data = new T[new_capacite];

    for (int i = 0; i < taille; ++i)
    {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacite = new_capacite;

}