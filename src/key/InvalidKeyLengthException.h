//
// Created by Ivano on 18/08/2018.
//

#ifndef AES_INVALIDKEYLENGTHEXCEPTION_H
#define AES_INVALIDKEYLENGTHEXCEPTION_H

#include <stdexcept>

class InvalidKeyLenghtException : public std::runtime_error {

public:
    explicit InvalidKeyLenghtException(const std::string& what_arg) : std::runtime_error(what_arg){}
};

#endif //AES_INVALIDKEYLENGTHEXCEPTION_H
