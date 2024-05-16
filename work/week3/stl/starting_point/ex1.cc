#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
/* -------------------------------------------------------------------------- */


int main(int argc, char ** argv){
    std::string myName = "TNErocks";
    if (argc > 1) {
        std::string argument = std::string(argv[1]);
        if (argument == myName){
            std::cout << "You are a rockstar" << std::endl;
        } else {
            std::cout << "You are a NOT rockstar" << std::endl;
        }
    } else {
        std::cout << "You are nothing" << std::endl;
    }

    return EXIT_SUCCESS;
}



