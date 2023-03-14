#pragma once

#include "exception"

class InvalidArgument : public std::exception {
    virtual const char* what() const throw();
};

class InvalidFile : public std::exception {
    virtual const char* what() const throw();
};

class InvalidFilterName : public std::exception {
    virtual const char* what() const throw();
};
