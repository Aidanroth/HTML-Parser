//
// Created by Aidan Roth on 9/9/19.
//

#ifndef LAB01_2_TRAVERSABLESTACK_H
#define LAB01_2_TRAVERSABLESTACK_H

#include <vector>
#include "Token.hpp"


class TraversableStack {
public:
    TraversableStack ();
    void add(Token);
    Token top();
    void pop();

    bool backSearch(Token);
    std::vector<Token> openTags;


private:
    std::vector<Token> travStack;


};


#endif //LAB01_2_TRAVERSABLESTACK_H
