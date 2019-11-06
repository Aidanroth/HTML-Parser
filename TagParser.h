//
// Created by Aidan Roth on 2019-09-04.
//

#ifndef LAB01_2_TAGPARSER_H
#define LAB01_2_TAGPARSER_H

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "TraversableStack.h"
#include <map>
#include <vector>



class TagParser {
public:
    TagParser(std::string);

    void parse();
    void handleOpenTag(Tokenizer&, Token);
    void handleCloseTag(Tokenizer&, Token);
    void handleCloseStandAloneTag(Token, Token);
    void printMap();
    std::map<std::string, std::vector<Token>> tokenMap;


private:
    TraversableStack startStack;
    std::string inStream;


};


#endif //LAB01_2_TAGPARSER_H
