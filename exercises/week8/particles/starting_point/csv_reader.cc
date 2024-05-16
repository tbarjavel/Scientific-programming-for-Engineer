#include "csv_reader.hh"
#include "particles_factory_interface.hh"
#include <fstream>
#include <sstream>
/* -------------------------------------------------------------------------- */
CsvReader::CsvReader(const std::string& filename) : filename(filename) {}
/* -------------------------------------------------------------------------- */
void CsvReader::read(System& system) { this->compute(system); }
/* -------------------------------------------------------------------------- */

void CsvReader::compute(System& system) {
}

/* -------------------------------------------------------------------------- */
