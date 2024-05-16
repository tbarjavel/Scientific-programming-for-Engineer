#include <sstream>

int main(int argc, char **argv) {
  std::stringstream sstr;
  for (int i = 1; i < argc; ++i) {
    sstr << argv[i] << " ";
  }

  double arg1;
  sstr >> arg1;

  int arg2;
  sstr >> arg2;
}