
cmake_minimum_required (VERSION 2.6)
project (Particles)

set(CMAKE_CXX_STANDARD 14)

add_executable(particles
  main.cc
  vector.cc
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc)

