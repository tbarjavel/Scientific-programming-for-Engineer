cmake_minimum_required (VERSION 3.1)
project (Particles)
cmake_policy(VERSION 3.3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

################################################################
# libpart
################################################################

add_library(part
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
  material_point.cc
  system_evolution.cc
  ping_pong_balls_factory.cc
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc
  compute_temperature_boundaries.cc
  )


################################################################
# FFTW
################################################################


set(FFTW_LIBRARY_PATH CACHE PATH "library where to search FFTW")
find_library (FFTW_LIBRARY fftw3 /usr/include/ ${FFTW_LIBRARY_PATH})

option (USE_FFTW "Use FFTW library" ON)

if (USE_FFTW)
    target_link_libraries (part ${FFTW_LIBRARY})
endif (USE_FFTW)

################################################################
# Create executable
################################################################

add_executable(particles main.cc)
target_link_libraries(particles part)




################################################################
# Google test
################################################################


include(GoogleTest)
enable_testing()
find_package(GTest)
if (GTEST_FOUND)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(test_kepler test_kepler.cc)
add_executable(test_fft test_fft.cc)
add_executable(test_heat_eq test_heat_equation_fft.cc)
target_link_libraries(test_kepler part ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test_heat_eq part ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(test_fft part ${GTEST_BOTH_LIBRARIES} ${FFTW_LIBRARIES} pthread)
gtest_discover_tests(test_kepler)
gtest_discover_tests(test_fft)
gtest_discover_tests(test_heat_eq)
endif()


################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

# to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
)
add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)
