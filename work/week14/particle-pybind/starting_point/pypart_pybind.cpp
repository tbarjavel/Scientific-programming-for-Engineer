#include <functional>
#include <iostream>
#include <pybind11/pybind11.h>

#include "system_evolution.hh"
#include "csv_writer.hh"
#include "particles_factory_interface.hh"
#include "ping_pong_balls_factory.hh"
#include "material_points_factory.hh"
#include "planets_factory.hh"
#include "compute_temperature.hh"

namespace py = pybind11;

PYBIND11_MODULE(pypart, m) {

    // Bind the System class
    py::class_<System, std::shared_ptr<System>>(m, "System")
        ;

    // Bind the SystemEvolution class
    py::class_<SystemEvolution, std::shared_ptr<SystemEvolution>>(m, "SystemEvolution")
        .def("addCompute", (&SystemEvolution::addCompute))
        .def("getSystem", (&SystemEvolution::getSystem))
        .def("setNSteps", &SystemEvolution::setNSteps)
        .def("setDumpFreq", (&SystemEvolution::setDumpFreq))
        .def("evolve", (&SystemEvolution::evolve))
        ;

    // Bind the ParticlesFactoryInterface class
    py::class_<ParticlesFactoryInterface>(m, "ParticlesFactoryInterface")
        .def("getInstance", &ParticlesFactoryInterface::getInstance,
             py::return_value_policy::reference)
        .def("createSimulation", &ParticlesFactoryInterface::createSimulation,
             py::return_value_policy::reference)

        // Define read-only access to SystemEvolution attribute
        .def_property_readonly("system_evolution",
                               &ParticlesFactoryInterface::getSystemEvolution)
        ;

    // Bind the PlanetsFactory class
    py::class_<PlanetsFactory>(m, "PlanetsFactory")
        .def("getInstance", &PlanetsFactory::getInstance,
             py::return_value_policy::reference)
        .def("createSimulation", &PlanetsFactory::createSimulation,
             py::return_value_policy::reference)
        ;

    // Bind the PingPongBallsFactory class
    py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(m, "PingPongBallsFactory")
        .def("getInstance", &PingPongBallsFactory::getInstance,
             py::return_value_policy::reference)
        .def("createSimulation", &PingPongBallsFactory::createSimulation,
             py::return_value_policy::reference)
        ;

    // Bind the MaterialPointsFactory class
    py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(m, "MaterialPointsFactory")
        .def("getInstance", &MaterialPointsFactory::getInstance,
             py::return_value_policy::reference)

        // static casting for "classic" overloaded method
        .def("createSimulation",
             (SystemEvolution & (MaterialPointsFactory::*)(const std::string &, Real))
             &MaterialPointsFactory::createSimulation,
             py::return_value_policy::reference)

        // dynamic casting for "functor" overloaded method
        .def("createSimulation",
             py::overload_cast<const std::string &, Real, py::function>
             (&MaterialPointsFactory::createSimulation<py::function>),
             py::return_value_policy::reference)
        ;

    // Bind the generic Compute class with a shared pointer
    py::class_<Compute, std::shared_ptr<Compute>>(m, "Compute");

    // Bind the ComputeTemperature class with a shared pointer
    py::class_<ComputeTemperature, Compute,
               std::shared_ptr<ComputeTemperature>>(m, "ComputeTemperature")
        .def(py::init<>())  // constructor)
        .def("__repr__",  [](ComputeTemperature &ct) {
            return "ComputeTemperature(sigma = " + std::to_string(ct.getConductivity()) +
                ", L = " + std::to_string(ct.getL()) +
                ", Cm = " + std::to_string(ct.getCapacity()) +
                ", rho = " + std::to_string(ct.getDensity()) +
                ", dt = " + std::to_string(ct.getDeltat()) +
                ")";
        })
        // give read write access to private class attributes through acessors
        .def_property("conductivity", &ComputeTemperature::getConductivity,
                      &ComputeTemperature::setConductivity)
        .def_property("capacity", &ComputeTemperature::getCapacity,
                      &ComputeTemperature::setCapacity)
        .def_property("density", &ComputeTemperature::getDensity,
                      &ComputeTemperature::setDensity)
        .def_property("L", &ComputeTemperature::getL,
                      &ComputeTemperature::setL)
        .def_property("deltat", &ComputeTemperature::getDeltat,
                      &ComputeTemperature::setDeltat)
        ;

    // Bind the CsvWriter class
    py::class_<CsvWriter, std::shared_ptr<CsvWriter>>(m, "CsvWriter")
        .def(py::init<const std::string&>())  // constructor
        .def("write", &CsvWriter::write)
        ;

}
