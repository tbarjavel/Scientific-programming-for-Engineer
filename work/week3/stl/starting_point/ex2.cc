#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
/* -------------------------------------------------------------------------- */

void write(const char * filename, double x, double y, double z) {
    // write 3D point to file
    std::ofstream fout(filename);
    std::cout << "Writing coordinates (" << x << ", " << y << ", " << z <<
        ") into " << filename << std::endl;
    fout << x << " " << y << " " << z;
    fout.close();
}

void read(const char * filename) {
    // read 3D point from file
    std::ifstream fin(filename);
    std::stringstream ss;
    ss << fin.rdbuf();
    double x, y, z;
    ss >> x >> y >> z;
    std::cout << "Reading coordinates from " << filename << ": (" <<
        x << ", " << y << ", " << z << ")" << std::endl;
}

int main(int argc, char ** argv){

    const char* filename = "toto.txt";
    double x, y, z;
    if (argc == 4) {  // x, y, z provided
        x = atof(argv[1]);
        y = atof(argv[2]);
        z = atof(argv[3]);
    } else if (argc == 1) {  // x, y, z not provided
        x = 1.7;
        y = 1.0;
        z = 2.0;
    } else {
        std::cout << "\033[31m" << "Invalid number of arguments: " << argc <<
            "\033[0m" << std::endl;
        return 0;
    }

    write(filename, x, y, z);
    read(filename);

    return EXIT_SUCCESS;
}




