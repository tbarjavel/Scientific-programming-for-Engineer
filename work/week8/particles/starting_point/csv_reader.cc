#include <fstream>
#include <sstream>

#include "csv_reader.hh"
#include "particles_factory_interface.hh"
#include "planet.hh"

/* -------------------------------------------------------------------------- */
CsvReader::CsvReader(const std::string& filename) : filename(filename) {}
/* -------------------------------------------------------------------------- */
void CsvReader::read(System& system) { this->compute(system); }
/* -------------------------------------------------------------------------- */

void CsvReader::compute(System& system) {

    std::ifstream is(filename.c_str());
    std::string line;

    // Check if file is already open
    if (is.is_open() == false) {
        std::cerr << "Error: file not opened" << filename << std::endl;
        throw;
    }

    while (is.good()) {

        // Gets line from CSV file
        getline(is, line);
        // Copy line in sstr
        std::stringstream sstr(line); //Real line should be corresponding to: x y z  v vx vy vz fx fy fz mass radius name

        // Check line structure before copying
        if (line.size() == 0) continue;

        // Create Particle class and dynamic cast to Planet
        // std::unique_ptr<Particle> p; // not to use, because the object will be destroyed by System
        // p.reset(new Planet());
        std::shared_ptr<Particle> p;
        p.reset(new Planet());
        // Initialize Planet
        p->initself(sstr);

        // Add particle to the system
        system.addParticle(p);
    }

    // Close file
    is.close();
}

/* -------------------------------------------------------------------------- */
