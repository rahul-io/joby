#include <iostream>
#include "simulator.h"

int main() {
  /*std::cout << "Please enter simulation time in minutes: ";
  int simTime;

  std::cin >> simTime;*/

  std::cout << "Simulating...\n";

  Simulator mySim;

  mySim.simulate();
}