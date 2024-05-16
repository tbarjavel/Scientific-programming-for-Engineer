#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <array>
/* -------------------------------------------------------------------------- */


int main(int argc, char ** argv){

    // read 3D point from file into array
    const char* filename = "toto.txt";
    std::ifstream fin(filename);
    std::stringstream ss;
    ss << fin.rdbuf();
    std::array<double, 3> arr;
    for (int i = 0; i < 3; ++i) {
        ss >> arr[i];
    }
    std::cout << "Reading coordinates from " << filename << " into array: ";
    for (const auto& e : arr){
        std::cout << e << " ";
    }
    std::cout << std::endl;

    // vector: 100 values from 0 to 2 PI
    std::vector<double> vec;
    int size = 100;
    for (int i = 0; i < size; ++i){
        vec.push_back(2.0 * M_PI / (size - 1) * i);
    }
    std::cout << "vec = " << vec.size() << " elements vector ranging from " <<
        vec[0] << " to " << vec[size - 1] << std::endl;

    // resize to 200 values -> indexes 100 to 199 are assigned to 0
    vec.resize(2 * size);
    std::cout << "vec resized to " << vec.size() << " elements. " <<
        "New elements contain the value " << vec[size] << std::endl;
    /* the "assign" method would assign new content to the vector, replacing its current content,
    and modifying its size accordingly. */
    vec.resize(size);
    std::cout << "vec resized to " << vec.size() << " elements " << std::endl;

    // Generate sinus vector
    std::vector<std::pair<double, double>> sin_vect;
    for (int i = 0; i < 100; ++i) {
        sin_vect.push_back(std::make_pair(vec[i], sin(vec[i])));
    }
    std::cout << "sin_vect = " << sin_vect.size() << " pairs vector ranging from (" <<
        sin_vect[0].first << ", " << sin_vect[0].second << ") to (" <<
        sin_vect[size - 1].first << ", " << sin_vect[size -1].second << ")" << std::endl;

    // Output sinus vector to text file
    filename = "sinus.csv";
    std::ofstream fout(filename);
    for (int i = 0; i < size; ++i) {
        fout << std::scientific << std::setprecision(20) <<
            sin_vect[i].first << ',' << sin_vect[i].second << std::endl;
    }
    fout.close();
    std::cout << "outputed sinus vector to " << filename << std::endl;

    return EXIT_SUCCESS;
}



