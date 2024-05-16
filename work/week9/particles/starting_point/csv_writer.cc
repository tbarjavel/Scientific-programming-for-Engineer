#include "csv_writer.hh"
#include <cstdlib>
#include <fstream>
/* -------------------------------------------------------------------------- */
CsvWriter::CsvWriter(const std::string& filename) : filename(filename) {}

/* -------------------------------------------------------------------------- */
void CsvWriter::write(System& system) { this->compute(system); }

/* -------------------------------------------------------------------------- */

void CsvWriter::compute(System& system) {
    std::ofstream os(this->filename);
    UInt nParticles = system.getNbParticles();
    // std::cout << nParticles << std::endl;

    for (UInt i=0; i<nParticles; i++){
        Particle &p = system.getParticle(i);
        
  	    p.printself(os);
        os << std::endl;
    }
    os.close();
}
