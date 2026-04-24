#include <iostream>
#include "Function.h"
#include <cmath>

int main()
{
    Function *f = new Function();
    f->set_function();
    double a{}, b{}, epsilon{};
    std::cout << "Entrez a pour [a,b]: ";
    std::cin >> a;
    std::cout << "Entrez b pour [a,b]: ";
    std::cin >> b;
    std::cout << "Entrez epsilon: ";
    std::cin >> epsilon;
    int status = EXIT_FAILURE;
    if (f->isContinue(a, b) && f->haveASolution(a, b, epsilon))
    {
        if (f->newtonResolution(a, b, epsilon) != INFINITY && !std::isnan(fabs(f->newtonResolution(a, b, epsilon))))
        {
            std::cout << "La solution est: " << f->newtonResolution(a, b, epsilon) << std::endl;
            status = EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Verifiez votre dérivé ou vos bornes pour que f'(x) ne soit pas nulle sur [a,b]" << std::endl;
        }
    }
    else
    {
        if (!f->isContinue(a, b))
        {
            std::cout << "Votre fonction n'est pas continue sur [" << a << "," << b << "]" << std::endl;
        }
        else
        {
            std::cout << "Votre fonction ne peut pas être resolue sur [" << a << "," << b << "]" << std::endl;
        }
    }
    return status;
}
