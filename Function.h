#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

class Function
{
private:
    std::string expression;
    std::string derivative;

public:
    double function(std::string funcString, double x);
    void set_function();
    void set_derivative();
    bool isContinue(double a, double b);
    bool haveASolution(double a, double b, double eps);
    double newtonResolution(double a, double b, double epsilon);
    double ftan(double x);
    std::string getExpression();
    std::string getDerivative();
};

#endif