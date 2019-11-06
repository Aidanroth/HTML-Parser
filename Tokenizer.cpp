//
// Created by Ali A. Kooshesh on 8/21/18.
// Enhanced by Aidan Roth

#include <iostream>
#include "Tokenizer.hpp"

Tokenizer::Tokenizer(std::string name): lineNumber{1},
                                        charPosition{1},
                                        inputFileName{name},
                                        isTokenStorage{false},
                                        tokenStorage{Token(0,0)} {
    inputStream.open(inputFileName, std::ios::in);  // open the input file
}

bool Tokenizer::charOfInterest(char c) {
    if(c == '<' || c == '>')
        return true;

    else if(c == '/') {
        if (inputStream.peek() == '>')
            return true;
    }
    return false;
}

Token Tokenizer::getToken() {
    if (isTokenStorage) {
        isTokenStorage = false;
        return tokenStorage;
    }

    char c;

    if( ! inputStream.is_open()) {
        std::cout << "Tokenizer::getToken() called with a stream that is not open." << std::endl;
        std::cout << "Make sure that " << inputFileName << " exists and is readable. Terminating.";
        exit(2);
    }

    while( inputStream.get(c) && ! charOfInterest(c) ) {
        // keep track of the line number and the character position
        charPosition++;
        if (c == '\n')
            lineNumber++;
    }

    Token token(lineNumber, charPosition);
    if( inputStream.eof() ) {
        token.endOfFile() = true;
        return token;
    }

    if( c == '<' ) {                                // A possible open tag.
      charPosition++;
      if (inputStream.get(c) && c == '/') {
          std::string tagName;
          charPosition++;
          while(inputStream.get(c) && (c != '>' && c != ' ')) {
              tagName += c;
              charPosition++;
          }
          inputStream.putback(c);
          token.makeCloseTag(tagName);
          return token;
      }
      else if (isalpha(c)) {
          std::string tagName;
          tagName += c;
          charPosition++;
          while(inputStream.get(c) && (c != '>' && c != ' ')) {
              tagName += c;
              charPosition++;
          }
          inputStream.putback(c);
          token.makeOpenTag(tagName);

          return token;
      }
      else {
          charPosition++;
          token.isOpenAngleBracket() = true;
          return token;
      }

    }
    else if (c == '>') {
        charPosition++;
        token.isCloseAngleBracket() = true;
        return token;
    }
    else if (c == '/') {
        if (inputStream.get(c) && c == '>') {
            charPosition++;
            token.isCloseStandAloneTag() = true;
            return token;
        }
    }
    return token;
}

void Tokenizer::putBackToken(Token token) {
    tokenStorage = token;
    isTokenStorage = true;
}