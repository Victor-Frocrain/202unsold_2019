/*
** EPITECH PROJECT, 2020
** yams
** File description:
** yams.cpp
*/

#include "unsold.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

int parseArgs(char *arg1, char *arg2, Datas &datas)
{
    std::string s1(arg1);
    std::string s2(arg2);

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9')
            return MY_ERROR;
    }
    for (size_t i = 0; i < s2.length(); i++) {
        if (s2[i] < '0' || s2[i] > '9')
            return MY_ERROR;
    }
    datas.x = std::stoi(s1);
    datas.y = std::stoi(s2);
    if (datas.x <= 50 || datas.y <= 50)
        return MY_ERROR;
    return MY_SUCCESS;
}

bool computeTab(Datas &datas, double y, size_t i)
{
    double value = 0.0;

    if ((5 * datas.x - 150) * (5 * datas.y - 150) == 0)
        return false;
    for (double x = 10; x <= 50; x += 10) {
        value = ((datas.x - x) * (datas.y - y)) / ((5 * datas.x - 150) * (5 * datas.y - 150));
        datas.tab[i].push_back(value);
    }
    return true;
}

bool printResults(Datas &datas)
{
    double xTotal = 0;
    double yTotal = 0;
    std::vector<double> totalsX;
    std::vector<double> totalsY;

    std::cout << "--------------------------------------------------------------------------------" << std::endl << "\t";
    for (int i = 10; i <= 50; i += 10) {
        std::cout << "X=" << i << "\t";
    }
    std::cout << "Y law" << std::endl;
    for (size_t i = 0; i < 5; i++) {
        xTotal = 0;
        std::cout << "Y=" << (i + 1) * 10 << "\t";
        if (!computeTab(datas, (i + 1) * 10, i))
            return false;
        for (size_t j = 0; j < datas.tab[i].size(); j++) {
            std::cout << std::fixed << std::setprecision(3) << datas.tab[i][j] << "\t";
            xTotal += datas.tab[i][j];
        }
        totalsY.push_back(xTotal);
        std::cout << std::fixed << std::setprecision(3) << xTotal << std::endl;
    }
    std::cout << "X law" << "\t";
    for (size_t i = 0; i < 5; i++) {
        yTotal = 0;
        for (size_t j = 0; j < 5; j++) {
            yTotal += datas.tab[j][i];
        }
        totalsX.push_back(yTotal);
        std::cout << std::fixed << std::setprecision(3) << yTotal << "\t";
    }
    std::cout << "1.000" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl << "z";
    for (size_t i = 20; i <= 100; i += 10) {
        std::cout << "\t" << i;
    }
    std::cout << std::endl << "p(Z=z)";
    for (size_t z = 20; z <= 100; z += 10) {
        double value = 0;
        for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
                if (((i + 1) * 10) + ((j + 1) * 10) == z)
                    value += datas.tab[i][j];
            }
        }
        std::cout << "\t" << std::fixed << std::setprecision(3) << value;
    }
    std::cout << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    xTotal = 0;
    yTotal = 0;
    double zTotal = 0;
    double varX = 0;
    double varY = 0;
    double varZ = 0;
    int i = 0;
    for (double x = 10; x <= 50; x += 10, i++) {
        xTotal += totalsX[i] * x;
        yTotal += totalsY[i] * x;
    }
    zTotal = xTotal + yTotal;
    for (i = 0; i < 5; i++) {
        varX += ((i + 1) * 10 - xTotal) * ((i + 1) * 10 - xTotal) * totalsX[i];
        varY += ((i + 1) * 10 - yTotal) * ((i + 1) * 10 - yTotal) * totalsY[i];
    }
    varZ = varX + varY;
    std::cout << "expected value of X:\t" << std::fixed << std::setprecision(1) << xTotal << std::endl;
    std::cout << "variance of X:\t\t" << std::fixed << std::setprecision(1) << varX << std::endl;
    std::cout << "expected value of Y:\t" << std::fixed << std::setprecision(1) << yTotal << std::endl;
    std::cout << "variance of Y:\t\t" << std::fixed << std::setprecision(1) << varY << std::endl;
    std::cout << "expected value of Z:\t" << std::fixed << std::setprecision(1) << zTotal << std::endl;
    std::cout << "variance of Z:\t\t" << std::fixed << std::setprecision(1) << varZ << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    return true;
}

int beginCompute(Datas &datas)
{
    if (!printResults(datas))
        return MY_ERROR;
    return MY_SUCCESS;
}

int unsold(int ac, char **args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac < 2)
        result = MY_ERROR;
    else if (ac == 2) {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
        else
            return MY_ERROR;
    }
    else if (ac == 3) {
        result = parseArgs(args[1], args[2], datas);
    }
    else
        result = MY_ERROR;
    if (result != MY_ERROR)
        result = beginCompute(datas);
    return result;
}