# Evolution Simulator

A C++ evolution simulation built with Raylib that models entities with different traits competing for survival.

## Features
- Object-oriented design with separate classes for different character types
- Two character types: 
  - Vision-based seekers that move randomly until food is within range, then seek it
  - Random movers with an eating range but no vision
- Hybrid characters with beneficial traits from both types
- Random movement algorithm inspired by *The Nature of Code*
- After each round, characters with the least food are eliminated

## Technologies
- C++
- Raylib

## Notes
The simulation demonstrates how simple traits can evolve and combine over generations through random hybridization and selection.
