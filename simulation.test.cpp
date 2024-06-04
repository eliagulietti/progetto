#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "doctest.h"

TEST_CASE("Testing the class simulation") {
  speciesSimulation::EcosystemParameters data;

  data.numPrey = 1000;
  data.numPredator = 500;
  data.simDuration = 0.5;
  data.a = 40;
  data.b = 0.05;
  data.c = 0.05;
  data.d = 50;

  speciesSimulation::Simulation species(data);

  SUBCASE("Test evolve() method") {
    CHECK(species.evolve().numPrey == doctest::Approx(1015));
    CHECK(species.evolve().numPredator == doctest::Approx(500.375));

    CHECK(species.evolve().numPrey == doctest::Approx(1045.66));
    CHECK(species.evolve().numPredator == doctest::Approx(502.275));
  }

  SUBCASE("Test balance() method") {
    CHECK(species.getEqPoint().x == doctest::Approx(1000));
    CHECK(species.getEqPoint().y == doctest::Approx(800));
  }
}

TEST_CASE("Testing the class simulation") {
  speciesSimulation::EcosystemParameters data;

  data.numPrey = 20;
  data.numPredator = 10;
  data.simDuration = 0.01;
  data.a = 1;
  data.b = 0.01;
  data.c = 0.02;
  data.d = 1;

  speciesSimulation::Simulation species(data);

  SUBCASE("Test maxPrey() and maxPredator() methods") {
    species.history();

    CHECK(static_cast<double>(species.simSize()) == 10);

    CHECK(species.maxPrey() == doctest::Approx(20.1808));
    CHECK(species.maxPredator() == doctest::Approx(9.994));
  }

  SUBCASE("Test getData() method") {
    species.history();

    CHECK(species.getData()[0].prey == doctest::Approx(0.40036));
    CHECK(species.getData()[0].predator == doctest::Approx(0.09994));

    CHECK(species.getData()[9].prey == doctest::Approx(0.403616));
    CHECK(species.getData()[9].predator == doctest::Approx(0.0994032));
  }
}

TEST_CASE("Testing the class simulation with large values") {
  speciesSimulation::EcosystemParameters data;
  data.numPrey = 10000;
  data.numPredator = 5000;
  data.simDuration = 1;
  data.a = 100;
  data.b = 0.1;
  data.c = 0.05;
  data.d = 50;

  speciesSimulation::Simulation species(data);

  SUBCASE("Test evolve() with large values") {
    auto evolved_population = species.evolve();
    CHECK(evolved_population.numPrey == 6000);
    CHECK(evolved_population.numPredator == 7250);
  }
  
}

TEST_CASE("Testing the class simulation with large parameters") {
  speciesSimulation::EcosystemParameters data;
  data.numPrey = 10000;
  data.numPredator = 5000;
  data.simDuration = 1;
  data.a = 100;
  data.b = 0.1;
  data.c = 0.05;
  data.d = 50;

  speciesSimulation::Simulation species(data);

  SUBCASE("Test evolve() with large values") {
    auto evolved_population = species.evolve();
    CHECK(evolved_population.numPrey == 6000);
    CHECK(evolved_population.numPredator == 7250);
  }
}