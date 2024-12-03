#include <iostream>
class Expression 
{
    public: 
        virtual int eval () const = 0;
        virtual Expression * clone() const = 0;
        virtual Expression * cloneMove() const = 0;
        ~Expression(){};
};

class Constante : public Expression
{
    private:
        int val;

    public:
        explicit Constante(const int & i) : val(i){};

        int eval () const override 
        {
            return val;
        }

        Expression * clone() const override 
        {
            return new Constante(val);
        }

        Expression * cloneMove() const override
        {
            return new Constante(std::move(val));
        }

};

class ExpressionArithmethique : public Expression 
{
    protected :
        Expression* gauche;
        Expression* droite;

    public :

        explicit ExpressionArithmethique(const Expression& gch, const Expression& drt) :
        gauche(gch.clone()), droite(drt.clone()) {}

        ~ExpressionArithmethique() 
        {
            delete gauche;
            delete droite;
        }

        
};



class Plus : public ExpressionArithmethique 
{
    public :
        Plus(const Expression& exp1, const Expression& exp2) : 
        ExpressionArithmethique(exp1, exp2) {};

        Plus(Expression && exp1, Expression && exp2)  : 
        ExpressionArithmethique(std::move(exp1), std::move(exp2)){}

        int eval() const override 
        {
            return (gauche->eval() + droite->eval());
        }

        Expression * clone () const override
        {
            return new Plus(*gauche, *droite);
        }

        Expression * cloneMove () const override
        {
            return (new Plus (std::move(*gauche), std::move(*droite)));
        }
};

class Mult : public ExpressionArithmethique
{
    public :
        Mult (const Expression& exp1, const Expression& exp2) : 
        ExpressionArithmethique(exp1, exp2) {}

        Mult (Expression&& exp1, Expression&& exp2) :
        ExpressionArithmethique(std::move(exp1), std::move(exp2)) {}

        int eval() const override 
        {
            return (gauche->eval() * droite->eval());
        }

        Expression * clone() const override 
        {
            return new Mult(*gauche, *droite);
        }

        Expression * cloneMove() const override
        {
            return new Mult(std::move(*gauche), std::move(*droite));
        }

};


int main()
{
    int a=5;
    const Expression & e = Mult(
                                Plus( Constante(a), Constante(-2)), 
                                Plus( Constante(1), Constante(3)) 
                            );
    std::cout << e.eval() << std::endl;
    return 0;
}
