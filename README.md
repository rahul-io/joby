# Joby Aviation eVTOL Simulator

## System Requirements
* CMake: >=3.24.0
* C++20 compatible compiler (e.g. g++ >=11)

## Project Setup

Configure the project, then compile:
<pre>
<strong>joby$ cmake -S . -B build</strong>
-- The CXX compiler identification is GNU 11.1.0
...
-- Build files have been written to: .../joby/build

<strong>joby$ cmake --build build</strong>
...
[ 23%] Built target simulator
...
[ 35%] Built target run_sim
...
[ 47%] Built target gtest
...
[ 58%] Built target gtest_main
...
[ 76%] Built target eVTOLSimTests
...
[ 88%] Built target gmock
...
[100%] Built target gmock_main
</pre>

## Running the Simulator
To run the simulator, call the executable in `build/main_app/run_sim`:

<pre>
<strong>joby$ build/main_app/run_sim</strong>
Starting simulation...
0 minutes
1 minutes
...
180 minutes
Simulation complete!

     Company Name     Number of Vehicles     Average Flight Time     Average Charging Time     Average Charger Wait Time     Max Faults     Total Passenger Travel Distance
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            Alpha                      4         109.996 minutes                 9 minutes               61.0261 minutes              2                       3519.86 miles
             Beta                      5         54.7946 minutes           5.35394 minutes               119.871 minutes              1                       2283.11 miles
          Charlie                      3              75 minutes           72.2492 minutes               31.7598 minutes              0                          1800 miles
            Delta                      3         113.853 minutes              24.8 minutes               41.3525 minutes              1                       1024.67 miles
             Echo                      5         91.9542 minutes              14.4 minutes               73.2135 minutes              4                       459.771 miles
</pre>

## Running Unit Tests

<pre>
<strong>joby$ cmake --build build --target test</strong>
Running tests...
Test project /home/rahul/repos/joby/build
    Start 1: VehicleTest.testFly
1/4 Test #1: VehicleTest.testFly ..............   Passed   10.00 sec
    Start 2: VehicleTest.testCharge
2/4 Test #2: VehicleTest.testCharge ...........   Passed   12.01 sec
    Start 3: SimulatorTest.StartsAtZero
3/4 Test #3: SimulatorTest.StartsAtZero .......   Passed    0.00 sec
    Start 4: SimulatorTest.ValidSimulation
4/4 Test #4: SimulatorTest.ValidSimulation ...........   Passed   180.02 sec

100% tests passed, 0 tests failed out of 4

Total Test time (real) =  22.01 sec
</pre>

## Initial Assumptions
The following assumptions were taken before starting development.
1. Vehicles always charge to full.
2. Vehicles always travel with a full load of passengers.

## Project Structure
![UML][uml.png]

## Fault Probability Calculation
To check for faults every second, I had to convert the probability of fault per hour to a probability per second. Since a fault with given probability $p_{hour}$ is a Bernoulli random variable, we can find $p_{minute}$ with the following: $$p_{minute} = 1 - (1 - p_{hour})^\frac{1}{60}$$