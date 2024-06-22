/*
** EPITECH PROJECT, 2024
** IError.hpp
** File description:
** DESCRIPTION
*/

#pragma once

#include <string>
#include <exception>

class IError : public std::exception {
    public:
        virtual ~IError() = default;
        const char *what() const  noexcept override = 0;
};
