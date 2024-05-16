#ifndef __MATERIAL_POINTS_FACTORY__HH__
#define __MATERIAL_POINTS_FACTORY__HH__

/* -------------------------------------------------------------------------- */
#include "particles_factory_interface.hh"
#include "material_point.hh"
/* -------------------------------------------------------------------------- */


//! Factory for material points
/**
This class is meant to be used as the interface through which the user can initialize a collection of M
aterialPoint objects and then run a simulation to compute the spatio-temporal evolution of temperature across these points. 
To this effect, it inherits from the generic ParticlesFactoryInterface and redefines the createParticle and createSimulation
 methods in the specific context of material points (e.g. making sure that number of points is square at initialization).
*/
class MaterialPointsFactory : public ParticlesFactoryInterface {
  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
private:
  MaterialPointsFactory() = default;

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  SystemEvolution& createSimulation(const std::string& fname,
				    Real timestep) override;

  std::unique_ptr<Particle> createParticle() override;

  static ParticlesFactoryInterface& getInstance();
};

/* -------------------------------------------------------------------------- */
#endif  //__MATERIAL_POINTS_FACTORY__HH__
