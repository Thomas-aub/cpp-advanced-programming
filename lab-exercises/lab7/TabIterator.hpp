template <typename T, int AGRANDISSEMENT>
class TabIterator
{
    private :
        T* pt;

    public : 
        // Constructeur par défaut
        TabIterator();

        // Constructeur par copie
        TabIterator(const TabIterator<T, AGRANDISSEMENT>  &);

        // Constructeur par déplacement
        TabIterator(TabIterator<T, AGRANDISSEMENT>  &&);

        // Constructeur à partir d'un pointeur
        TabIterator(T* ptr);


        // Opérateur d’affectation par copie
        TabIterator<T, AGRANDISSEMENT>  & operator=(const TabIterator<T, AGRANDISSEMENT>  &);

        // Opérateur d’affectation par déplacement
        TabIterator<T, AGRANDISSEMENT>  & operator=(TabIterator<T, AGRANDISSEMENT>  &&);

        // Opérateur de déréférencement
        T& operator*() const;

        // Opérateur d'incrémentation
        TabIterator<T, AGRANDISSEMENT> & operator++();
        TabIterator<T, AGRANDISSEMENT>  operator++(int);

        // Comparaison des itérateurs
        bool operator==(const TabIterator<T, AGRANDISSEMENT>  &other) const;
        bool operator!=(const TabIterator<T, AGRANDISSEMENT>  &other) const;
    

};

// Constructeur par défaut
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>::TabIterator() : pt(nullptr) {};

// Constructeur par copie
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>::TabIterator(const TabIterator &other) : pt(new T(*other.pt)) {}

// Constructeur par déplacement
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>::TabIterator(TabIterator &&other) : pt(other.pt) {
    other.pt = nullptr; // Nullifie le pointeur de l'objet déplacé
}

// Constructor with pointer initialization
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>::TabIterator(T* ptr) : pt(ptr) {}




// Opérateur d’affectation par copie
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>& TabIterator<T, AGRANDISSEMENT>::operator=(const TabIterator &other) {
    if (this != &other) {
        delete pt; // Libère l'ancien pointeur
        pt = new T(*other.pt); // Alloue une nouvelle mémoire et copie
    }
    return *this;
}

// Opérateur d’affectation par déplacement
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>& TabIterator<T, AGRANDISSEMENT>::operator=(TabIterator &&other) {
    if (this != &other) {
        delete pt; // Libère l'ancien pointeur
        pt = other.pt; // Transfère le pointeur
        other.pt = nullptr; // Nullifie le pointeur de l'objet déplacé
    }
    return *this;
}

// Opérateur de déréférencement
template <typename T, int AGRANDISSEMENT>
T& TabIterator<T, AGRANDISSEMENT>::operator*() const {
    return *pt;
}

// Opérateur d'incrémentation (avant)
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT>& TabIterator<T, AGRANDISSEMENT>::operator++()
{
    ++pt;
    return *this;
}

// Opérateur d'incrémentation (après)
template <typename T, int AGRANDISSEMENT>
TabIterator<T, AGRANDISSEMENT> TabIterator<T, AGRANDISSEMENT>::operator++(int)
{
    T nt = *this;
    this ++;
    return nt;
}


// Comparaison des itérateurs
template <typename T, int AGRANDISSEMENT>
bool TabIterator<T, AGRANDISSEMENT>::operator==(const TabIterator& other) const {
    return pt == other.pt;
}

template <typename T, int AGRANDISSEMENT>
bool TabIterator<T, AGRANDISSEMENT>::operator!=(const TabIterator& other) const {
    return pt != other.pt;
}

