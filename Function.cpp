#include "Function.h"
#include <iostream>
#include <cmath>
#include <vector>

void Function::set_function()
{
    std::cout << "Entrez votre fonction polynomiale: ";
    std::cin >> expression;
}

void Function::set_derivative()
{
    std::cout << "Entrez sa dérivée: ";
    std::cin >> derivative;
}

std::string Function::getExpression()
{
    return expression;
}

std::string Function::getDerivative()
{
    return derivative;
}

double Function::function(std::string funcString, double x)
{
    std::string ex = funcString;
    std::string num{""};
    std::vector<char> ops;
    std::vector<std::string> nums;
    bool start{true};
    int nb_i{0};
    for (int i = 0; i < ex.length(); i++)
    {
        char c = ex[i];
        if (start)
        {
            start = false;
            if (c == '/' || c == '*')
            {
                return INFINITY;
            }
            else
            {
                num += c;
            }
        }
        else
        {
            int asci = ex[i];
            if ((48 <= asci && asci <= 57) || ex[i] == '.' || ex[i] == 'x')
            {
                num += ex[i];
            }
            else
            {
                int asci_1 = ex[i - 1];
                if ((48 <= asci_1 && asci_1 <= 57) || ex[i - 1] == 'x')
                {
                    ops.push_back(ex[i]);
                    nums.push_back(num);
                    num = "";
                    start = true;
                }
                else
                {
                    if (c == '/' || c == '*')
                    {
                        return INFINITY;
                    }
                    num += ex[i];
                }
            }
        }
    }
    nums.push_back(num);
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == "x")
        {
            nums[i] = std::to_string(x);
        }
    }
    for (int i = 0; i < ops.size(); i++)
    {
        if (ops[i] == '*' || ops[i] == '/')
        {
            double nb{};
            switch (ops[i])
            {
            case '*':
                nb = std::stod(nums[i]) * std::stod(nums[i + 1]);
                nums[i] = std::to_string(nb);
                nums.erase(nums.begin() + (i + 1));
                ops.erase(ops.begin() + i);
                i--;
                break;
            case '/':
                nb = std::stod(nums[i]) / std::stod(nums[i + 1]);
                nums[i] = std::to_string(nb);
                nums.erase(nums.begin() + (i + 1));
                ops.erase(ops.begin() + i);
                i--;
                break;
            }
        }
    }

    double resultat{std::stod(nums[0])};
    for (int i = 0; i < ops.size(); i++)
    {
        switch (ops[i])
        {
        case '+':
            resultat += std::stod(nums[i + 1]);
            break;
        default:
            resultat -= std::stod(nums[i + 1]);
            break;
        }
    }
    return resultat;
}

bool Function::isContinue(double a, double b)
{
    double resA = std::isnan(function(getExpression(), a));
    double resB = std::isnan(function(getExpression(), b));
    return (!resA && !resB && resA != INFINITY && resB != INFINITY);
}

bool Function::haveASolution(double a, double b, double eps)
{
    double epsilon{eps};
    double s{}, borne1{a}, borne2{b};
    double essai{0};
    do
    {
        s = (borne1 + borne2) / 2;
        if (function(getExpression(), borne1) * function(getExpression(), s) < 0)
        {
            borne2 = s;
        }
        else
        {
            borne1 = s;
        }
        essai++;
        if (essai > log2(fabs(a - b) / epsilon))
        {
            break;
        }
    } while (fabs(function(getExpression(), s)) >= epsilon);
    return function(getExpression(), s) < epsilon;
}

double Function::ftan(double x)
{
    return x - (function(getExpression(), x) / function(getDerivative(), x));
}

double Function::newtonResolution(double a, double b, double epsilon)
{
    double ao{a};
    int essai{0};
    do
    {
        ao = ftan(ao);
        if (essai >= fabs(a - b) / (2 * epsilon))
        {
            return INFINITY;
        }
    } while (fabs(function(getExpression(), ao)) >= epsilon);
    return ao;
}