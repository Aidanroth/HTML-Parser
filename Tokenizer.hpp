//
// Created by Ali A. Kooshesh on 8/21/18.
//

#ifndef LAB01_2_TOKENIZER_HPP
#define LAB01_2_TOKENIZER_HPP


#include <string>
#include <fstream>
#include "Token.hpp"

class Tokenizer {

public:
    Tokenizer(std::string);
    Token getToken();
    void putBackToken(Token);

private:
    int lineNumber, charPosition;
    std::string inputFileName;
    std::ifstream inputStream;
    Token tokenStorage;
    bool isTokenStorage;

    bool charOfInterest(char c);
};


#endif //LAB01_2_TOKENIZER_HPP
