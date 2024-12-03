#include <iostream>
#include <cstring> 

class String {

    public :
        String() : str(nullptr) {
            str = new char[1];
            str[0] = '\0';
        }

        String (const char* val) {
            if (val == nullptr) {
                str = new char[1];
                str[0] = '\0';
            } else {
                size_t str_len = strlen(val);
                str = new char[str_len + 1];
                strcpy(str, val);
            }
        }

        String (const char & val) {
            if (val == '\0') {
                str = new char[1];
                str[0] = '\0';
            } else {
                str = new char[2];
                str[0] = val;
                str[1] = '\0';
            }
            
        } 

        ~String () {
            delete[] str;
        }

        String (const String & string) {
            if (string.str == nullptr){
                str = new char[1];
                str[0] = '\0';
            } else {
                size_t str_len = strlen(string.str);
                str = new char[str_len + 1];
                strcpy(str, string.str);
            }
        }

        String (String && string) : str(string.str) {
            str = std::move(string).str;
            string.str = nullptr;
        }

        // Conversion
        const char* stringToChar() {
            return str;
        }

        String operator + (const String & other) const {
            size_t new_size = strlen(this->str) + strlen(other.str) + 1;
            char* new_str = new char[new_size];
            strcpy(new_str, this->str);
            strcat(new_str, other.str);
            return String(new_str);
        }

        bool operator == (const String& other) const {
            return strcmp(this->str, other.str) == 0;
        }

        bool operator >= (const String& other) const {
            return strcmp(this->str, other.str) >= 0;
        }

        bool operator <= (const String& other) const {
            return strcmp(this->str, other.str) <= 0;
        }

        bool operator > (const String& other) const {
            return strcmp(this->str, other.str) > 0;
        }

        bool operator < (const String& other) const {
            return strcmp(this->str, other.str) < 0;
        }

        bool operator != (const String& other) const {
            return strcmp(this->str, other.str) != 0;
        }

        char& operator[] (const int & i) {
            if (i < 0 || i >= this->len()) {
                std::cerr << "Index hors limites !" << std::endl;
                throw std::out_of_range("Index hors limites !");
            }
            return str[i];
        }

        const char& operator[] (const int & i) const {
            if (i < 0 || i >= this->len()) {
                std::cerr << "Index hors limites !" << std::endl;
                throw std::out_of_range("Index hors limites !");
            }
            return str[i];
        }



        size_t len() const{
            return strlen(this->str);
        }

        bool empty() const{
            return (this->str == nullptr || this->str[0] == '\0');
        }

        String subString (const int & deb, const int & fin) {
            if (deb < 0 || fin >= this->len() || deb > fin) {
                std::cerr << "Indices invalides!" << std::endl;
                return String();
            }
            size_t size = fin - deb + 1;
            char* new_str = new char[size + 1];

            for (int i = 0; i < size; i++) {
                new_str[i] = str[deb + i]; 
            }

            new_str[size] = '\0';

            return String(new_str);

        }

        friend std::ostream& operator << (std::ostream& os, const String & s) {
            os << s.str;
            return os;
        }


        
    protected :
        char* str;
};

int main() {
    // Construction avec une chaîne ordinaire
    String s1("Hello");
    std::cout << "s1: " << s1 << std::endl;

    // Construction avec un caractère
    String s2('A');
    std::cout << "s2: " << s2 << std::endl;

    // Construction avec la valeur par défaut (chaîne vide)
    String s3;
    std::cout << "s3: " << s3 << std::endl;

    // Test de concaténation
    String s4 = s1 + " World";
    std::cout << "s4: " << s4 << std::endl;

    // Test de comparaison
    std::cout << "s1 == s4 ? " << (s1 == s4 ? "true" : "false") << std::endl;
    std::cout << "s1 != s4 ? " << (s1 != s4 ? "true" : "false") << std::endl;

    // Test d'accès à un caractère
    std::cout << "s1[1]: " << s1[1] << std::endl;

    // Test d'accès à la longueur
    std::cout << "Longueur de s1: " << s1.len() << std::endl;

    // Test d'une chaîne vide
    std::cout << "s3 est vide ? " << (s3.empty() ? "oui" : "non") << std::endl;

    // Test de sous-chaîne
    String s5 = s1.subString(1, 3);
    std::cout << "Sous-chaîne de s1 (1-3): " << s5 << std::endl;

    // Test d'affichage d'un objet
    std::cout << "Affichage de s1: " << s1 << std::endl;

    return 0;
}
