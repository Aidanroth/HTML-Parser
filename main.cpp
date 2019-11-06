/***********************************/
/*Project: Lab 01                  */
/*Author: Aidan Roth               */
/*Class: CS 315                    */
/*Date: Fall 2019                  */
/***********************************/



#include <iostream>
#include <fstream>
#include "Tokenizer.hpp"
#include "TagParser.h"


int main(int argc, char *argv[]) {

    if( argc != 2 ) {  // we expect the name of the file as an argument to the program.
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile" << std::endl;
        exit(1);
    }

    // Here, we open the file to make sure that it exists before starting the program.
    // When using CLion, the input file has to be in cmake-build-debug directory.
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);    // open for reading
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        std::cout << strerror(errno) << std::endl;
        exit(2);
    }

    inputStream.close();
    TagParser tagParser(argv[1]);
    tagParser.parse();
    tagParser.printMap();

    return 0;
}