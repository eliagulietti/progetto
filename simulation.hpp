#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace speciesSimulation {

struct EcosystemParameters {
  double numPrey = 100;
  double numPredator = 20;
  double simDuration = 10;
  double a = 0.5;
  double b = 0.001;
  double c = 0.005;
  double d = 3;
};

struct EquilibriumPoint {
  double x;
  double y;
};

struct SpeciesData {
  double prey;
  double predator;
  double H;
};

class Simulation {
  std::vector<SpeciesData> data;

  EcosystemParameters par;
  EquilibriumPoint eqPoint;

  double const dt = 0.001;

 public:
  Simulation(EcosystemParameters p);

  EquilibriumPoint const getEqPoint();

  long unsigned int simSize() const;

  EcosystemParameters evolve();

  const std::vector<SpeciesData> getData() const;

  void history();

  double maxPrey(); 
  double maxPredator();

  void printHistory();

  void createGraph();

  void createOrbit();
};
}  // namespace speciesSimulation

#endif