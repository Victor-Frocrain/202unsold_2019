/*
** EPITECH PROJECT, 2020
** unsold
** File description:
** unsold.hpp
*/

#include <vector>

#ifndef UNSOLD_HPP_
#define UNSOLD_HPP_

#define MY_ERROR 84
#define MY_SUCCESS 0

int unsold(int ac, char **args);

class Datas {
    public:
    int x;
    int y;
    std::vector<double> tab[5];
};

#endif /* UNSOLD_HPP_ */
