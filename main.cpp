#include <iostream>

#include "simulator.h"

int main() {
  std::cout << "Starting simulation...\n";

  Simulator eVtolSim;

  eVtolSim.simulate();
}