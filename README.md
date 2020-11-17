# 2048_oop

## Intro

This is our final project of OOP class ---- 2048 AI graphical.

## Version history

### v1.6

Simplify print board:
   1. Create a new head → BoardPrint.h
   2. framework.cpp → game::print() 

### v1.5

We have termial game now!

### v1.4

split main.cpp to 3 function:  
  
​    1. main.cpp → Game.out:
​        Let user play 2048 Game.
​    2. train.cpp → Train.out:  
​       Let user train 2048 AI.
​       Usage: ./Train.out <train-round>
​    3. replay.cpp → Replay.out:
​       Replay hightest score round when Training AI.
