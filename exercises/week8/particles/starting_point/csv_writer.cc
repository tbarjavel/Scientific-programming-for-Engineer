#include "csv_writer.hh"
#include <cstdlib>
#include <fstream>
/* -------------------------------------------------------------------------- */
CsvWriter::CsvWriter(const std::string& filename) : filename(filename) {}

/* -------------------------------------------------------------------------- */
void CsvWriter::write(System& system) { this->compute(system); }

/* -------------------------------------------------------------------------- */

void CsvWriter::compute(System& system) {
}
