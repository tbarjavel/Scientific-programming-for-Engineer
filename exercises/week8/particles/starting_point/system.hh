#ifndef __SYSTEM__HH__
#define __SYSTEM__HH__

/* -------------------------------------------------------------------------- */
#include "my_types.hh"
#include "particle.hh"
#include <memory>
#include <vector>
/* -------------------------------------------------------------------------- */

//! Container for particles
class System {
  /*
   * No need for constructor/destructor with std::unique_ptr
   */

  // List of particle pointers
  using ParticleList = std::vector<std::shared_ptr<Particle>>;

  // Methods
public:
  //! Remove particle from vector
  void removeParticle(UInt particle);
  //! Get particle for specific id
  Particle& getParticle(UInt i);
  //! Add a particle to the system
  void addParticle(const std::shared_ptr<Particle>& new_particle);
  //! Get number of particles
  UInt getNbParticles();


private:
  ParticleList list_particles;
};

/* -------------------------------------------------------------------------- */
#endif  //__SYSTEM__HH__
