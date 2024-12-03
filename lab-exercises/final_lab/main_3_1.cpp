#include <iostream>
#include <ostream>



template <typename T>
class ZipList
{
    public :

        ZipList() : tete(nullptr), queue(nullptr) {}

        void push_front(const T & valeur)
        {
            Cell* new_cell = new Cell();
            new_cell->val = valeur;

            if (tete)
            {
                new_cell->pt = this->tete;
                this->tete = new_cell;
            } else 
            {
                this->tete = new_cell;
                this->queue = new_cell;
            }
        }

        const T front() const 
        {
            return tete->val;
        }

        ~ZipList()
        {
            while (tete)
            {
                Cell* tmp = tete->pt;
                delete tete;
                tete = tmp;
            }
            if (queue)
            {
                queue = nullptr;
            } 
        }

        size_t size()
        {
            size_t cmp = 0;
            Cell* tmp = this->tete;
            while(tmp)
            {
                ++cmp;
                tmp = tmp->pt;
            }
            return cmp;
        }

        // affichage
        friend std::ostream& operator << (std::ostream & os, const ZipList& zip)
        {
            Cell* tmp = zip.tete;
            while(tmp)
            {
                os << tmp->val << " ";
                tmp = tmp->pt;
            }
           
        return os;
        }

        struct Cell 
        {
            Cell* pt;
            T val;

            Cell() : val(), pt(nullptr) {};
        };

    private :
        Cell* tete;
        Cell* queue;
        
};

int main()
{
    ZipList<int> lili;
    for(int i=0;i<15;i++)
        lili.push_front(i%4);
    std::cout << lili << std::endl;
    return 0;
}