#include "system_evolution.hh"
#include "csv_writer.hh"
/* -------------------------------------------------------------------------- */
#include <cmath>
#include <iomanip>
#include <sstream>
/* -------------------------------------------------------------------------- */

SystemEvolution::SystemEvolution(std::unique_ptr<System> system)
    : system(std::move(system)) {}

/* -------------------------------------------------------------------------- */

void SystemEvolution::evolve() {


  // Integrate system for each time step
  for (UInt i = 1; i < this->nsteps; ++i){
    this->computes[0]->compute(this->getSystem());


    // Write updated variables at a chosen frequency
    if (fmod(i, freq) == 0) {
      std::string writeInterFile;

      //fill step numbers with 0 before the number itself
      std::string number=std::to_string(i);
      number.insert (number.begin(),4-std::to_string(i).size(),'0');
      writeInterFile = "Step-" + number + ".csv";

      std::cout << writeInterFile << std::endl;
      CsvWriter writer(writeInterFile);
      writer.write(this->getSystem());
    }
  }
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
