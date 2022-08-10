#include <iostream>
#include "simulator.h"

int main() {
  std::cout << "Please enter simulation time in minutes:";
  int simTime;

  std::cin >> simTime;

  Simulator mySim(simTime);

  mySim.simulate();
}