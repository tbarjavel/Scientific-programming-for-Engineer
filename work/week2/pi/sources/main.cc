/* -------------------------------------------------------------------------- */
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
/* -------------------------------------------------------------------------- */

int main(int argc, char ** argv){

    int precision = 20;

    // Number of iterations
    int n;
    int nmax = 1e7;
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n > nmax) {
            std::cout << "\033[31m" << "Warning: n = " <<
                n << " is too high -> setting n = " << nmax <<
                "\033[0m" << std::endl;
            n = nmax;
        }
    } else {
        n = 10;
    }

    // Normal Pi computation
    float sum = 0;
    for (float k = 1; k < n + 1; k++){
        sum = sum + 1 / (k * k);
        // std::cout<< std::fixed << std::setprecision(precision)
        //     << "k = " << k << ", PI = " << sqrt(6 * sum) << std::endl;
    }
    float pi = sqrt(6 * sum);
    std::cout<< std::fixed << std::setprecision(precision)
        << n << " iterations (normal): PI = " << pi << std::endl;

    // Reversed Pi computation
    sum = 0;
    for (float k = n; k > 0; k--){
        sum = sum + 1/(k*k);
        // std::cout<< std::fixed << std::setprecision(precision)
        //     << "k = " << k << ", PI = " << sqrt(6 * sum) << std::endl;
    }
    float rev_pi = sqrt(6 * sum);
    std::cout<< std::fixed << std::setprecision(precision)
        << n << " iterations (reversed): PI = " << rev_pi << std::endl;

    std::string str;
    if (abs(pi - M_PI) < abs(rev_pi - M_PI)) {
        str = "normal";
    } else {
        str = "reversed";
    }
    std::cout << str << " computation is more accurate" << std::endl;

    return EXIT_SUCCESS;
}



