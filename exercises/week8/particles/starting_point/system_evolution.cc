#include "system_evolution.hh"
#include "csv_writer.hh"
/* -------------------------------------------------------------------------- */
#include <iomanip>
#include <sstream>
/* -------------------------------------------------------------------------- */

SystemEvolution::SystemEvolution(std::unique_ptr<System> system)
    : system(std::move(system)) {}

/* -------------------------------------------------------------------------- */

void SystemEvolution::evolve() {
}

/* -------------------------------------------------------------------------- */

void SystemEvolution::addCompute(const std::shared_ptr<Compute>& compute) {
  computes.push_back(compute);
}

/* -------------------------------------------------------------------------- */
void SystemEvolution::setNSteps(UInt nsteps) { this->nsteps = nsteps; }
/* -------------------------------------------------------------------------- */
void SystemEvolution::setDumpFreq(UInt freq) { this->freq = freq; }
/* -------------------------------------------------------------------------- */
System& SystemEvolution::getSystem() { return *system; }
/* -------------------------------------------------------------------------- */
