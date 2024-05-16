/* -------------------------------------------------------------------------- */
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
/* -------------------------------------------------------------------------- */
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "main.hh"
#include "print_series.hh"
#include "write_series.hh"
/* -------------------------------------------------------------------------- */

//********************************
// Definition of the options
//********************************

using ArgMap = std::map<std::string, std::string>;

ArgMap defaults{{"series_type", "pi"}, {"dumper_type", "print"},
                {"output", "cout"},    {"freq", "10"},
                {"maxiter", "1000"},   {"precision", "5"},
                {"delimiter", " "}};

ArgMap options{{"series_type", "pi/arithmetic"},
               {"dumper_type", "print/write"},
               {"output", "cout/filename"},
               {"freq", "Frequency to output series value"},
               {"maxiter", "Maximal series iteration"},
               {"precision", "number of digits to use"},
               {"delimiter", "separator to use for produced files"}};

void printUsage(std::string prog_name);
ArgMap parseArgv(int argc, char **argv);

/* ---------------------------------------------------------------------- */

int main(int argc, char **argv) {

  //********************************
  // Parsing
  //********************************

  auto params = parseArgv(argc, argv);

  auto series_type = params["series_type"];
  auto dumper_type = params["dumper_type"];
  auto max_iter = atoi(params["maxiter"].c_str());
  auto precision = atoi(params["precision"].c_str());
  auto delimiter = params["delimiter"];
  auto freq = atoi(params["freq"].c_str());
  auto output = params["output"];

  //********************************
  // Series object creation
  //********************************

  std::unique_ptr<Series> series = nullptr;

  if (series_type == "pi")
    series = std::make_unique<ComputePi>();
  else if (series_type == "algebraic")
    series = std::make_unique<ComputeAlgebraic>();
  else
    printUsage(argv[0]);

  //********************************
  // Dumper object creation
  //********************************

  std::unique_ptr<DumperSeries> dumper = nullptr;

  if (dumper_type == "print")
    dumper = std::make_unique<PrintSeries>(*series, freq);
  else if (dumper_type == "write")
    dumper = std::make_unique<WriteSeries>(*series, delimiter);
  else
    printUsage(argv[0]);

  //********************************
  // File object creation
  //********************************

  std::ostream *file = nullptr;

  if (output != "cout")
    file = new std::ofstream(output);
  else
    file = &std::cout;

  //********************************
  // Do the polymorphic job
  //********************************

  dumper->setPrecision(precision);
  dumper->setMaxIter(max_iter);
  *file << *dumper << std::endl;

  if (output != "cout")
    delete file;

  return EXIT_SUCCESS;
}

/* ---------------------------------------------------------------------- */
// argument parsing system
/* ---------------------------------------------------------------------- */

void printUsage(std::string prog_name) {
  std::cerr << "Usage: " << prog_name << " --option value\n" << std::endl;
  for (auto &&key_val : options) {
    std::cerr << "\t--" << key_val.first << ": " << key_val.second << std::endl;
  }
  std::cerr << std::endl;
  throw std::runtime_error("Wrong Usage");
}

/* ---------------------------------------------------------------------- */

ArgMap parseArgv(int argc, char **argv) {

  if (argc == 1)
    printUsage(argv[0]);

  auto params = defaults;

  std::vector<std::string> vec_options;
  for (int i = 1; i < argc; ++i) {
    vec_options.push_back(argv[i]);
  }

  if (vec_options.size() % 2 != 0)
    printUsage(argv[0]);

  UInt noptions = argc / 2;
  for (int i = 0; i < noptions; ++i) {
    auto key = vec_options[2 * i];
    auto value = vec_options[2 * i + 1];
    key = key.substr(2);
    if (key == "help")
      printUsage(argv[0]);

    if (options.count(key) == 0)
      printUsage(argv[0]);
    params[key] = value;
  }

  std::cout << "Selected options:" << std::endl;
  std::for_each(params.begin(), params.end(), [](auto &v) {
    std::cout << "\t" << v.first << ": " << v.second << "\n";
  });

  return params;
}
