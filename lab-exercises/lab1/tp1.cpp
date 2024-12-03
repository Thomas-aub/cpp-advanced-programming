#include <iostream>
class LaClasse {
    public :
        //Construction, conversion, affectation et destruction
        LaClasse() : l(0){ // initialise l à 0
            std::cout << "LaClasse::LaClasse()\n";
        }

        LaClasse(const LaClasse & lc) : l(lc.l) {
            std::cout << "LaClasse::LaClasse(const LaClasse & )\n";
        }
        LaClasse(int i) : l(i) {
            std::cout << "LaClasse::LaClasse(int)\n";
        }
        operator bool() const {
            std::cout << "LaClasse::operator bool() const\n"; return true;
        }
        ~LaClasse() {
            std::cout << "~LaClasse::LaClasse()\n";
        }
        LaClasse & operator=(const LaClasse & c) {
            l=c.l; std::cout << "LaClasse::operator=(const LaClasse &)\n"; return *this;
        }

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




// Testez et analysez la séquence d’appels aux fonctions membres
// de LaClasse dans le programme suivant :
int main() {
    LaClasse c1; // Appelle le constructeur de LaClasse()

    LaClasse c2 = LaClasse(); /* Equivaut à faire :
     LaClasse tmp; // Appelle aussi le contructeur par copie
     LaClasse(tmp) // Appel le constructeur par copie
     ~LaClasse(); // Appel destructeur pour tmp */

    LaClasse cc1(c1); // Appelle le constructeur par copie
    LaClasse cc2 = c1; // Appelle aussi le contructeur par copie comme => LaClasse cc2(c1);

    LaClasse cc3 = LaClasse(c1);  // Appelle le constructeur par copie
    LaClasse cv1(5); // Appelle le contructeur LaClasse(int i) : l(i) et donct l=5

    LaClasse cv2=5;/* Equivaut à faire :
     LaClasse tmp(8); // Instancie un objet temporaire avec le constructeur par int
     LaClasse(tmp) // Appel le constructeur par copie
     ~LaClasse(); // Appel destructeur pour tmp */
    LaClasse cv3 = LaClasse(5); // La même chose qu'avant

    LaClasse cv4 = (LaClasse)5;
    std::cout << std::endl;
    c1=cc1; //Appelle la fonction LaClasse & operator=(const LaClasse & c) qui affecte
    std::cout << std::endl;
    c2=8;/* Equivaut à faire :
     LaClasse tmp(8); // Instancie un objet temporaire avec le constructeur par int
     LaClasse & operator=(tmp) // Appelle la fonction LaClasse & operator=(const LaClasse & c) qui affecte
     ~LaClasse(); // Appel destructeur pour tmp */
    std::cout << std::endl;
    if(cv1) {
            std::cout << std::endl;
    std::cout << std::endl;

        cv1 = F(10); //
            std::cout << std::endl;
    std::cout << std::endl;

        cv1 = F(c1);
        cv1 = c1.F(c2);
    }
    std::cout << "Tableaux \n";
    LaClasse tab[3];
    LaClasse *pc = new LaClasse(tab[0]);
    delete pc;
    std::cout << "Avant de sortir ... \n";
    return 0;
}