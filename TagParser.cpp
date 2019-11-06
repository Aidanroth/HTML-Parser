//
// Created by Aidan Roth on 2019-09-04.
//

#include "TagParser.h"
#include <iostream>

TagParser::TagParser(std::string name): inStream{name} {
    Tokenizer tokenizer(name);
    //tokenMap;
    startStack = {};
}

void TagParser::parse() {

    Tokenizer tokenizer(inStream);

    Token token = tokenizer.getToken();
    while (!token.endOfFile()) {
        if (token.isOpenTag())
            handleOpenTag(tokenizer, token);
        else if (token.isCloseTag())
            handleCloseTag(tokenizer, token);
        else if(token.isCloseStandAloneTag()) {
            token.print();
            std::cout << " doesn't have a matching open tag. Will discard it." << std::endl;
        }
        else if(token.isCloseAngleBracket() || token.isOpenAngleBracket()) {
            token.print();
            std::cout << (token.isCloseAngleBracket() ? " ignoring random close angle-bracket."
                                                    : " ignoring random open angle-bracket.") << std::endl;
        } else {
            token.print();
            std::cout << " unknown token."  << std::endl;
        }
        token = tokenizer.getToken();
    }
// more things to do here...
}

void TagParser::handleOpenTag(Tokenizer &tokenizer, Token token) { //is the tokenizer parameter to find the closing > for the tag?

    Token nextToken = tokenizer.getToken(); //get next token
    if (nextToken.isCloseAngleBracket()) { //if next token is a close angle bracket, everything is fine, exit function
        startStack.add(token);
        return;
    }

    if (nextToken.isCloseStandAloneTag()) {  //for if nextToken.isCloseStandaloneTag
        handleCloseStandAloneTag(token, nextToken);
        return;
    }


    else {      //if next token is anything else, start tag is malformed, report error
        token.print();
        std::cout << " is missing a '>' or '/>'. Will discard it." << std::endl;
        tokenizer.putBackToken(nextToken);
        return;
    }
}

void TagParser::handleCloseTag(Tokenizer &tokenizer, Token token) {
    //still need functionality for one the tag correctly closes, but ones inside it remain open.

    if (startStack.top().tagName() == token.tagName()) { //if tag matches token on top of stack
        Token closeToken = tokenizer.getToken();
        if (tokenMap.find(token.tagName()) == tokenMap.end()) { //if tagName is not in map yet

            tokenMap[token.tagName()] = std::vector<Token>(); //creates an empty vector as value for key, token.tagName()
            tokenMap[token.tagName()].push_back(startStack.top()); //adds start tag token to newly created vector
            tokenMap[token.tagName()].push_back(token); //adds current token to vector


        }
        else { //add current token to pre-existing vector in tokenMap
            tokenMap[token.tagName()].push_back(startStack.top());
            tokenMap[token.tagName()].push_back(token);
        }

        startStack.pop();
        return;

    }
    else { //report erroneous syntax

        if (startStack.backSearch(token) == true) { //call backSearch here to check if other tags remained open
            token.print();
            std::cout << " closes while the following tags remain open. \n";
            for (int i = 0; i < startStack.openTags.size(); i++) {
                std::cout << "\t\t";
                startStack.openTags[i].print();
                std::cout << '\n';
            }
            Token closeToken = tokenizer.getToken();
        }

        else {
            Token nextToken = tokenizer.getToken(); //get next token
            token.print();
            std::cout << " (with close angle bracket ";
            nextToken.print();
            std::cout << ") doesn't have a matching open tag. Will Discard it." << std::endl;
            //tokenizer.putBackToken(nextToken);
        }
        return;
    }
}

void TagParser::handleCloseStandAloneTag(Token openToken, Token closeToken) {

    if (tokenMap.find(openToken.tagName()) == tokenMap.end()) { //if tagName of top of startStack is not in map yet
        tokenMap[openToken.tagName()] = std::vector<Token>(); //creates an empty vector as value for key, token.tagName()
        tokenMap[openToken.tagName()].push_back(openToken); //adds start tag token to newly created vector
        tokenMap[openToken.tagName()].push_back(closeToken); //adds current token to vector
    }
    else {
        tokenMap[openToken.tagName()].push_back(openToken);
        tokenMap[openToken.tagName()].push_back(closeToken);
    }

}

void TagParser::printMap() {
    std::cout << "\nThe following is a list of well-formed HTML tags." << std::endl;
    // Use an iterate to step through all elements of maps (in this example, map has one element only.)
    for(auto mapIter = tokenMap.begin(); mapIter != tokenMap.end(); ++mapIter) {
        // our map, pairs an array of Tokens with tag-name strings.
        std::vector<Token> locations = mapIter->second;// 'second' is a vector, 'first' is the tagName

        std::cout << std::endl;
        if (locations.size() / 2 > 1)
                std::cout << mapIter->first << " appeared in the following " << locations.size() / 2 << " locations." << std::endl;
        else
            std::cout << mapIter->first << " appeared in the following location." << std::endl;

        for(auto vIter = locations.begin(); vIter != locations.end(); ++vIter) {
            std::cout << "\t\t";
            vIter->print();
            std::cout << " -- ";
            vIter++;
            vIter->print();
            std::cout << std::endl;
        }
    }
}