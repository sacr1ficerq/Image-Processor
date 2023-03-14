#include "my_exception.h"

const char* InvalidArgument::what() const throw() {
    return "Invalid argument";
}

const char* InvalidFile::what() const throw() {
    return "Invalid file";
}

const char* InvalidFilterName::what() const throw() {
    return "Invalid filter name";
}
