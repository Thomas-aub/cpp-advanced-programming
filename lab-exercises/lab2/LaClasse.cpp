#include <iostream>
#include <cstring> 
class LaClasse {
    public :
        //Construction, conversion, affectation et destruction
        LaClasse() : l(0){ // initialise l à 0
            std::cout << "LaClasse::LaClasse()\n";
        }
        // Construction par copie (profonde)
        LaClasse(const LaClasse & lc) : l(lc.l) {
            std::cout << "LaClasse::LaClasse(const LaClasse & )\n";
        }
    
        LaClasse(int i) : l(i) {
            std::cout << "LaClasse::LaClasse(int)\n";
        }

        operator bool() const {
            std::cout << "LaClasse::operator bool() const\n"; return true;
        }
        // Destructeur
        ~LaClasse() {
            std::cout << "~LaClasse::LaClasse()\n";
        }
        // Opérateur d'affectation par copie 
        LaClasse & operator=(const LaClasse & c) {
            l=c.l; std::cout << "LaClasse::operator=(const LaClasse &)\n"; return *this;
        }

        // EXERCICE 2

        // Constructeur par déplacement
        LaClasse(LaClasse &&x) : l(x.l){};

        // Opérateur d'affecation par déplacement
        LaClasse & operator=(LaClasse &&x) {
            l=x.l;
            return *this;
        };

        //Autre fonction membre
        LaClasse F(LaClasse);

        // Déclaration fonction extérieure amie
        friend std::ostream & operator << (std::ostream & os, const LaClasse & lc);
    
    private :
        int l;
};

LaClasse F(const LaClasse & vv){
    std::cout << " in F \n";
    return 8;
}

LaClasse LaClasse::F(LaClasse v) {
    std::cout << " in LaClasse::F \n";
    return ::F(v);
}

std::ostream & operator << (std::ostream & os, const LaClasse & lc) {
    os << " in ostream << LaClasse "<< lc.l << std::endl;
    return os;
}





class LaClasseSpecialisee : public LaClasse{
    public :
        //Construction, conversion, affectation et destruction
        LaClasseSpecialisee() : t{nullptr}{ 
            std::cout << "LaClasseSpecialisee::LaClasseSpecialisee()\n";
        }

        LaClasseSpecialisee(const LaClasseSpecialisee &lcs) : t{lcs.t} {
            std::cout << "LaClasseSpecialisee::LaClasseSpecialisee(const LaClasseSpecialisee & )\n";
        }

        LaClasseSpecialisee(int* i) {
            t = new int(*i);  // Allocation dynamique de mémoire 
            std::cout << "LaClasseSpecialisee::LaClasseSpecialisee(int*)\n";
            std::cout << t << "\n";
        };

        operator bool() const {
            std::cout << "LaClasseSpecialisee::operator bool() const\n"; 
            return true;
        }

        ~LaClasseSpecialisee() {
            std::cout << "Destruction\n";
            delete t;  // Libération de la mémoire pointée par t
            std::cout << "~LaClasseSpecialisee::LaClasseSpecialisee()\n";
        }

        LaClasse F(LaClasse);

        friend std::ostream & operator << (std::ostream & os, const LaClasse & lc);
 
    private :
        int* t;

       
};





/* EXERCICE 3 */

class String {

    public :
    
    // Constructeur sans argument
    String() : str(nullptr){
        str = new char[1];
        str[0] = '\0';
    }
 
    // Constructeur à partir d'un char*
        String(const char* val) {
        if (val == nullptr) {
            str = new char[1];
            str[0] = '\0';
        } else {
            // Trouver la longueur de `val`
            size_t str_len = strlen(val);
            // Allouer la mémoire
            str = new char[str_len + 1];  // +1 pour le caractère nul
            // Copier le contenu de `val` dans `str`
            strcpy(str, val);  // Utilisation de strcpy pour copier la chaîne
        }
    }

    // Constructeur à partir d'un char
    String(const char val) {
        if (val == '\0') { 
            str = new char[1];
            str[0] = '\0';
        } else { 
            str = new char[2];
            str[0] = val;
            str[1] = '\0';
        }
    }
 
    // Constructeur par copie
    String(const String& source) {
        if (source.str == nullptr) {
            str = new char[1];
            str[0] = '\0';
        } else {
            // Allouer la mémoire en fonction de la taille de la chaîne source
            size_t str_len = strlen(source.str);
            str = new char[str_len + 1];  // +1 pour le caractère nul
            // Copier la chaîne
            strcpy(str, source.str);
        }
    }

 
    // Contructeur par déplacement
    String(String&& source) {
        str = std::move(source).str;
        source.str = nullptr;
    };
 
    // Destructeur
    ~String() {
         delete str; 
    }

    // Conversion en char*
    const char* stringToChar(){
        return str;
    }

    // Longueur
    const size_t len(){
        return strlen(str);
    }

    // Chaine vide ?
    const bool empty(){
        return str[0] = '\0';
    }

    /// Concaténation (opérateur +)
    String operator+(const String& other) const {
        size_t newSize = strlen(this->str) + strlen(other.str) + 1;
        char* newStr = new char[newSize];
        strcpy(newStr, this->str);
        strcat(newStr, other.str);
        return String(newStr);
    }

    // Comparaisons
    // Comparaison égalité (==)
    bool operator==(const String& other) const {
        return strcmp(this->str, other.str) == 0;
    }

    // Comparaison inégalité (!=)
    bool operator!=(const String& other) const {
        return !(*this == other); // Utilise l'opérateur ==
    }

    // Comparaison moins que (<)
    bool operator<(const String& other) const {
        return strcmp(this->str, other.str) < 0;
    }

    // Comparaison plus que (>)
    bool operator>(const String& other) const {
        return strcmp(this->str, other.str) > 0;
    }

    // Comparaison moins ou égal (<=)
    bool operator<=(const String& other) const {
        return !(*this > other); // Utilise l'opérateur >
    }

    // Comparaison plus ou égal (>=)
    bool operator>=(const String& other) const {
        return !(*this < other); // Utilise l'opérateur <
    }

    // Affichage de la chaîne
    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }

    String subString(int beg, int end) {
        // Vérification des indices valides
        if (beg < 0 || end >= this->len() || beg > end) {
            std::cerr << "Indices invalides!" << std::endl;
            return String();
        }

        // Calcul de la longueur de la sous-chaîne (inclusif)
        size_t sub_len = end - beg + 1;

        // Allocation de mémoire pour la sous-chaîne
        char* sub_str = new char[sub_len + 1];  // +1 pour le caractère nul

        // Copier les caractères dans la nouvelle sous-chaîne
        for (int i = 0; i < sub_len; i++) {
            sub_str[i] = str[beg + i];
        }

        // Ajouter le caractère nul de fin de chaîne
        sub_str[sub_len] = '\0';

        // Retourner la nouvelle chaîne
        return String(sub_str);
    }


    private :
        char* str;
};


// Testez et analysez la séquence d’appels aux fonctions membres
// de LaClasse dans le programme suivant :
int main() {

    // Exercice 1 et 2
    /*
    LaClasseSpecialisee c1; // Appelle le constructeur de LaClasse() et de LaClasseSpecialisee

    std::cout << std::endl;
    std::cout << std::endl;

    int x = 42;
    LaClasseSpecialisee c2(&x);

    std::cout << std::endl;
    std::cout << std::endl;
    */


    // Exercice 3
    String s1;
    std::cout << "test s1 : " << s1 << std::endl;

    String s2("Test");
    std::cout << "test s2 : " << s2 << std::endl;

    String s3(s2);
    std::cout << "test s3 : " << s3 << std::endl;

    String s4("Hello, World!");
    String sub = s4.subString(7, 11);
    std::cout << "Test s4 : " << sub << std::endl;

    std::cout << "test s3 < s4 : " << (s3 < s4) << std::endl;

    std::cout << "test s3 > s4 : " << (s3 > s4) << std::endl;

    std::cout << "test s2 == s3 : " << (s2 == s3) << std::endl;
    


    return 0;

}


