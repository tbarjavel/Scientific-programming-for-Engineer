#ifndef __MATERIAL_POINT__HH__
#define __MATERIAL_POINT__HH__

/* -------------------------------------------------------------------------- */
#include "particle.hh"

//! Class for MaterialPoint
/**
This class is meant to be used as the fundamental entity 
(i.e. a grid point) to compute the spatio-temporal 
evolution of heat on a 2D grid. To this effect, 
the class inherits from the Particle class and 
defines two additional real number attributes:
 temperature and heat rate, to be used to solve the heat equation.

*/
class MaterialPoint : public Particle {
  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */

public:

  void printself(std::ostream& stream) const override;
  void initself(std::istream& sstr) override;

  Real & getTemperature(){return temperature;};
  Real & getHeatRate(){return heat_rate;};
  Real & getHeatDistribution(){return heat_distribution;};
  
private:
  Real temperature;
  Real heat_rate;
  Real heat_distribution;
};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINT__HH__
