#include <iostream>
 
#include "simulation.hpp"

int main() {
  speciesSimulation::EcosystemParameters p; //deapcode
  char command;

  /*std::cout << "Insert the initial number x,y of prey and predators\n";
  std::cin >> p.numPrey >> p.numPredator;

  std::cout << "Insert the growth rate of prey and predators (positive)\n";
  std::cin >> p.a >> p.c;

  std::cout << "Insert the mortality rate of prey and predators (positive)\n";
  std::cin >> p.b >> p.d;

  std::cout << "Insert the duration of the simulation (in multiples of "
               "0.001)\n";
  std::cin >> p.time;*/

  speciesSimulation::Simulation sim(p);
  sim.history();

  std::cout << "d: data"
               "\ng: graph\no: orbit\nq: Quit \n";
  std::cin >> command;

  while (command != 'q') {
    if (command == 'd') {
      sim.printHistory();

      std::cout << "Max number of prey: " << sim.maxPrey() << "\n";
      std::cout << "Max number of predators: " << sim.maxPredator() << "\n";
      std::cout << "Equilibrium point: (" << sim.getEqPoint().x << "," << sim.getEqPoint().y << ")\n";

      std::cout << "d: data"
                   "\ng: graph\no: orbit\nq: Quit \n";
      std::cin >> command;

    } else if (command == 'g') {
      sim.createGraph();

      std::cout << "d: data"
                   "\ng: graph\no: orbit\nq: Quit \n";
      std::cin >> command;

    } else if (command == 'o') {
      sim.createOrbit();

      std::cout << "d: data"
                   "\ng: graph\no: orbite\nq: Quit \n";
      std::cin >> command;

    } else {
      std::cout << "d: data"
                   "\ng: graph\no: orbit\nq: Quit \n";
      std::cin >> command;
    }
  }
}