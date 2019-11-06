//
// Created by Aidan Roth on 9/9/19.
//

#include "TraversableStack.h"
#include "Token.hpp"
#include <vector>
#include <iostream>

TraversableStack::TraversableStack () {
    std::vector<Token> travStack;
    std::vector<Token> openTags;
}

void TraversableStack::add(Token token) {
    return travStack.push_back(token);
}

Token TraversableStack::top() {
    return travStack.back();
}

void TraversableStack::pop() {
    return travStack.pop_back();
}


bool TraversableStack::backSearch(Token token) { //search backwards through stack to find matching tag
    openTags.clear();

    if (travStack.size() < 1)
        return false;

    for(int i = travStack.size(); i >= 0; i--) {
        if(travStack[i-1].tagName() == token.tagName()) {
            travStack.erase(travStack.begin()+i-1);
            return true;
        }
        else {
            openTags.push_back(travStack[i-1]);
        }
    }
    return false;
}
