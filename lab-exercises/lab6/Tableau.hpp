// Tableau.hpp
#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <iostream>
#include <stdexcept>
#include <sstream>
#include "TabIterator.hpp"


template <typename T, int AGRANDISSEMENT>
class Tableau 
{
private:
    T* data;          // Pointeur vers les données du tableau
    int capacite;     // Capacité du tableau
    int taille;       // Taille du tableau


public:
    // Constructeur par défaut
    Tableau();

    // Constructeur avec taille 
    Tableau(const int& t);

    // Constructeur par copie
    Tableau(const Tableau<T, AGRANDISSEMENT>  &);

    // Constructeur par déplacement
    Tableau(Tableau<T, AGRANDISSEMENT>  &&);

    // Opérateur d’affectation par copie
    Tableau<T, AGRANDISSEMENT>  & operator=(const Tableau<T, AGRANDISSEMENT>  &);

    // Opérateur d’affectation par déplacement
    Tableau<T, AGRANDISSEMENT>  & operator=(Tableau<T, AGRANDISSEMENT>  &&);

    // Afficher le contenu
    template <typename U, int A>
    friend std::ostream& operator<<(std::ostream& os, const Tableau<U, A>& tableau);

    // Surcharge de l'opérateur [] pour accéder aux éléments
    T& operator[](int index);              // Version non-const
    const T& operator[](int index) const;  // Version const

    // Surcharge de l'opérateur >>
    template <typename U, int A>
    friend std::istream& operator>>(std::istream& in, Tableau<U, A>& tableau);

    // Ajout d'un élément
    void push_back(const int& value);

    // Fonction d'agrandissement
    void agrandir();

    // Premier élément
    TabIterator<T, AGRANDISSEMENT>  begin();
    // Dernier élément
    TabIterator<T, AGRANDISSEMENT>  end();

    // Destructeur
    ~Tableau();

};



// Implémentation des méthodes de la classe template

// Constructeur par défaut
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau() : data(nullptr), capacite(0), taille(0) {};

// Constructeur avec taille
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau(const int& t) : data(new T[t]), capacite(t), taille(t){};

// Constructeur par copie
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau(const Tableau& autre) : capacite(autre.capacite), taille(autre.taille)
{
    data = new T[capacite];
    for (int i = 0; i < taille; ++i){
        data[i] = autre.data[i];
    }
};

// Constructeur par déplacement
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::Tableau(Tableau&& autre) : capacite() 
{
    data = std::move(autre).data;
    autre.data = nullptr;

}

// Opérateur d’affectation par copie
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>& Tableau<T, AGRANDISSEMENT>::operator=(const Tableau& autre) 
{
    // Vérification d'auto-affectation
    if (this == &autre)
    {
        return *this; // Retourner l'objet courant s'il s'agit du même
    }

    // Libérer la mémoire actuelle
    delete[] data;

    // Copier les attributs taille et capacité
    capacite = autre.capacite;
    taille = autre.taille;

    // Allouer de la mémoire pour le nouveau tableau
    data = new T[capacite];

    // Copier les éléments du tableau source
    for (int i = 0; i < taille; ++i)
    {   
        data[i] = autre.data[i];
    }

    // Retourner l'objet courant pour permettre l'affectation en chaîne
    return *this;
}

// Opérateur d’affectation par déplacement
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>& Tableau<T, AGRANDISSEMENT>::operator=(Tableau&& autre) 
{
    // Vérification d'auto-affectation
    if (this == &autre)
    {
        return *this; // Retourner l'objet courant s'il s'agit du même
    }

    // Libérer la mémoire actuelle
    delete[] data;

    // Tranférer données de l'objet autre
    data = autre.data;
    capacite = autre.capacite;
    taille = autre.taille;

    // Supprimer les données de l'objet autre
    data = nullptr;
    capacite = 0;
    taille = 0;

    // Retourner l'objet courant pour permettre l'affectation en chaîne
    return *this;
}



// Destructeur
template <typename T, int AGRANDISSEMENT>
Tableau<T, AGRANDISSEMENT>::~Tableau() 
{
    delete[] data; // Libérer la mémoire allouée pour le tableau de données
    data = nullptr; // Mettre le pointeur à nullptr pour éviter les accès invalides
}


// Surcharge opérateur [] - Version non-const 
template <typename T, int AGRANDISSEMENT>
T& Tableau<T, AGRANDISSEMENT>::operator [](int index) 
{
    if (index >= taille || index < 0)
    {
        std::ostringstream oss;
        oss << "Index " << index << " out of range"; // Créer le message d'erreur
        throw std::out_of_range(oss.str()); // Lancer l'exception avec le message
    
    }
    return this->data[index];
}


// Surcharge opérateur []- Version const 
template <typename T, int AGRANDISSEMENT>
const T& Tableau<T, AGRANDISSEMENT>::operator [](int index) const 
{
    if (index >= taille || index < 0)
    {
        std::ostringstream oss;
        oss << "Index " << index << " out of range"; // Créer le message d'erreur
        throw std::out_of_range(oss.str()); // Lancer l'exception avec le message
    
    }
    return this.data[index];
}


template <typename T, int AGRANDISSEMENT>
void Tableau<T, AGRANDISSEMENT>::push_back(const int& value){
    if (taille == capacite){
        this->agrandir();
    }
    data[taille] = value;
    ++taille;
}


template <typename T, int AGRANDISSEMENT>
void Tableau<T, AGRANDISSEMENT>::agrandir()
{
    // Créer un nouveau tableau avec une capacité augmentée
    int nvCapacite = capacite + AGRANDISSEMENT;
    T* nvData = new T[nvCapacite];
    // Copier les éléments existants dans le nouveau tableau
    for (int i = 0; i < taille; ++i)
    {
        nvData[i] = data[i];
    }

    // Libérer l'ancien tableau
    delete[] data;

    // Mettre à jour le pointeur et la capacité
    data = nvData;
    capacite = nvCapacite;

}



// Implémentation de l'opérateur <<
template <typename T, int AGRANDISSEMENT>
std::ostream& operator<<(std::ostream& os, const Tableau<T, AGRANDISSEMENT>& tableau) {
    if (tableau.taille == 0) {
        return os;
    }
    for (int i = 0; i < tableau.taille; ++i) {
        os << tableau.data[i] << " ";
    }
    return os;
}

// Dernier élément
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT> Tableau<T, AGRANDISSEMENT>::end(){
        return TabIterator<T, AGRANDISSEMENT>(data + taille); 
}

// Premier élément
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT> Tableau<T, AGRANDISSEMENT>::begin() {
    return TabIterator<T, AGRANDISSEMENT>(data); 
}

// Surcharge de l'opérateur >>
template <typename T, int AGRANDISSEMENT>
std::istream& operator>>(std::istream& in, Tableau<T, AGRANDISSEMENT>& tableau) {
    T value;
    while (in >> value) {
        tableau.push_back(value);
    }
    return in;
}




#endif // TABLEAU_HPP

