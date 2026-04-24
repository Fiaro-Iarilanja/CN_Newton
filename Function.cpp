#include "Function.h"
#include <iostream>
#include <cmath>
#include <vector>

void Function::set_function()
{
    std::cout << "Entrez votre fonction polynomiale: ";
    std::cin >> expression;
}

std::string Function::getExpression()
{
    return expression;
}

double Function::function(double x)
{
    std::string ex = getExpression();
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
    double resA = std::isnan(function(a));
    double resB = std::isnan(function(b));
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
        if (function(borne1) * function(s) < 0)
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
    } while (fabs(function(s)) >= epsilon);
    return function(s) < epsilon;
}

double Function::derivative(double x, double epsilon)
{
    return ((function(x + epsilon) - function(x)) / epsilon);
}

double Function::ftan(double x, double epsilon)
{
    return x - (function(x) / derivative(x, epsilon));
}

double Function::newtonResolution(double a, double b, double epsilon)
{
    double ao{a};
    int essai{0};
    do
    {
        ao = ftan(ao, epsilon);
        if (essai >= fabs(a - b) / (2 * epsilon))
        {
            return INFINITY;
        }
    } while (fabs(function(ao)) >= epsilon);
    return ao;
}
