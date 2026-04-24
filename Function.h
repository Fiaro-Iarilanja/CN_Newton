#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

class Function
{
private:
    std::string expression;

public:
    double function(double x);
    double derivative(double x, double epsilon);
    void set_function();
    bool isContinue(double a, double b);
    bool haveASolution(double a, double b, double eps);
    double newtonResolution(double a, double b, double epsilon);
    double ftan(double x, double epsilon);
    std::string getExpression();
    std::string getDerivative();
};

#endif
