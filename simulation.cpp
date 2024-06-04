#include "simulation.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace speciesSimulation {
Simulation::Simulation(EcosystemParameters p) : par{p} {
  assert(par.numPrey > 0 && par.numPredator > 0 && par.a > 0 && par.b > 0 &&
         par.c > 0 && par.d > 0);

  eqPoint.x = par.d / par.c;
  eqPoint.y = par.a / par.b;
}

EquilibriumPoint const Simulation::getEqPoint() { return eqPoint; }

long unsigned int Simulation::simSize() const { return data.size(); }

EcosystemParameters Simulation::evolve() {
  double deltaPrey{};
  double deltaPredator{};

  deltaPrey = ((par.a - par.b * par.numPredator) * par.numPrey * dt);
  deltaPredator = ((par.c * par.numPrey - par.d) * par.numPredator * dt);

  par.numPrey += deltaPrey;
  par.numPredator += deltaPredator;

  assert(par.numPrey > 0 && par.numPredator > 0);

  return par;
}

const std::vector<SpeciesData> Simulation::getData() const { return data; }

void Simulation::history() {
  SpeciesData sd;
  for (int i = 0; i * dt != par.simDuration; ++i) {
    evolve();

    sd.prey = (par.numPrey / eqPoint.x);

    sd.predator = (par.numPredator / eqPoint.y);

    sd.H = (-par.d * log(par.numPrey) + par.c * par.numPrey +
            par.b * par.numPredator - par.a * log(par.numPredator));

    data.push_back(sd);

    if (par.numPrey < 2 || par.numPredator < 2) {
      break;
    }
  }
}

double Simulation::maxPrey() {
  return std::max_element(data.begin(), data.end(),
                          [](const SpeciesData& a, const SpeciesData& b) {
                            return a.prey < b.prey;
                          })
             ->prey *
         eqPoint.x;
}

double Simulation::maxPredator() {
  return std::max_element(data.begin(), data.end(),
                          [](const SpeciesData& a, const SpeciesData& b) {
                            return a.predator < b.predator;
                          })
             ->predator *
         eqPoint.y;
}

void Simulation::printHistory() {
  std::cout << "prede:    predatori:    H:" << "\n";
  std::for_each(data.begin(), data.end(), [&](const SpeciesData& element) {
    std::cout << element.prey * eqPoint.x << "    "
              << element.predator * eqPoint.y << "    " << element.H
              << "\n";
  });
}

void Simulation::createGraph() {
  float width = 800;
  float height = 600;
  const float numSteps = static_cast<float>(simSize());

  float coeff{};
  const float relXY = height / width;

  if (width < numSteps) {
    coeff = (numSteps - width) / width;
    width += width * coeff;
    height = width * relXY;
  }

  float xScale = width / numSteps;
  float yScale =
      height / static_cast<float>(std::max(maxPrey(), maxPredator()));

  sf::VertexArray graphPrey(sf::LineStrip,
                            static_cast<long unsigned int>(numSteps));
  sf::VertexArray graphPredator(sf::LineStrip,
                                static_cast<long unsigned int>(numSteps));
  auto i = 0ul;

  for (auto itData = data.begin(); itData < data.end(); ++itData) {
    graphPrey[i].position = sf::Vector2f(
        10 + xScale * static_cast<float>(i),
        height - yScale * static_cast<float>(itData->prey * eqPoint.x) -
            10);
    graphPrey[i].color = sf::Color::Green;

    graphPredator[i].position = sf::Vector2f(
        10 + xScale * static_cast<float>(i),
        height -
            yScale * static_cast<float>(itData->predator * eqPoint.y) -
            10);
    graphPredator[i].color = sf::Color::Red;

    ++i;
  }

  sf::VertexArray axes(sf::Lines, 4);
  axes[0].position = sf::Vector2f(10, height - 10);
  axes[1].position = sf::Vector2f(width, height - 10);
  axes[2].position = sf::Vector2f(10, 0);
  axes[3].position = sf::Vector2f(10, height - 10);

  sf::RenderWindow window =
      sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(width),
                                     static_cast<unsigned int>(height)),
                       "Population graph");

  window.setSize(sf::Vector2u(800, 600));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Black);

    window.draw(graphPrey);
    window.draw(graphPredator);
    window.draw(axes);

    window.display();
  }
}

void Simulation::createOrbit() {
  unsigned int width = 800;
  unsigned int height = 600;
  double x;
  double y;

  long unsigned int currentStep{};

  const double xScale = width / maxPrey();
  const double yScale = height / maxPredator();

  sf::VertexArray trajectory(sf::LineStrip);

  sf::RenderWindow window(sf::VideoMode(width, height), "Orbit graph");

  auto it = data.begin();

  sf::CircleShape equilibrium_point(5);
  equilibrium_point.setFillColor(sf::Color::White);
  equilibrium_point.setPosition(
      static_cast<float>(xScale * eqPoint.x),
      static_cast<float>(height - yScale * eqPoint.y));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    if (currentStep == simSize()) {
      it = data.begin();
      currentStep = 0;
      trajectory.clear();
    }

    window.clear(sf::Color::Black);

    x = it->prey * eqPoint.x;
    y = it->predator * eqPoint.y;

    trajectory.append(
        sf::Vertex(sf::Vector2f(static_cast<float>(xScale * x),
                                static_cast<float>(height - yScale * y)),
                   sf::Color::Yellow));

    window.draw(trajectory);
    window.draw(equilibrium_point);

    window.display();

    ++it;
    ++currentStep;

    sf::sleep(sf::milliseconds(5));
  }
}
}  // namespace speciesSimulation
