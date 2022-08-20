#include <iostream>

#include "../src/simulator.h"

int main() {
  std::cout << "Starting simulation...\n";

  Simulator eVtolSim;

  Simulator::simulate();
}