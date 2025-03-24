// Copyright 2022 UNN-IASR
#include <iostream>

#include "Automata.h"

int main() {
  Automata* automata = new Automata();
  automata->on();
  for (menuItem item : automata->getMenu()) {
    std::cout << item.name << ": " << item.price << std::endl;
  }
  automata->coin(20);
  std::cout << static_cast<int>(automata->getState(std::cout)) << std::endl;
  std::cout << static_cast<int>(automata->choice(2).first) << std::endl;
  return 0;
}