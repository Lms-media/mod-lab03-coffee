// Copyright 2022 UNN-IASR
#include "Automata.h"

#include <chrono>
#include <iostream>
#include <thread>

Automata::Automata() {
  menu.push_back(menuItem{"Espresso", 15});
  menu.push_back(menuItem{"Americano", 20});
  menu.push_back(menuItem{"Cappuccino", 35});
  menu.push_back(menuItem{"Latte", 50});
  menu.push_back(menuItem{"Macchiato", 65});
}

Automata::Automata(std::vector<menuItem> customMenu) : menu{menu} {}

void Automata::on() {
  if (state == STATES::OFF) state = STATES::WAIT;
}

void Automata::off() {
  if (state != STATES::OFF) {
    state = STATES::OFF;
    cash = 0;
  }
}

void Automata::coin(double amount) {
  if (state == STATES::WAIT || state == STATES::ACCEPT) {
    singleCash += amount;
    state = STATES::ACCEPT;
  }
}

std::vector<menuItem> Automata::getMenu() const { return menu; }

STATES Automata::getState(std::ostream& stream) const {
  switch (state) {
    case STATES::OFF:
      stream << "OFF" << std::endl;
      break;
    case STATES::WAIT:
      stream << "WAIT" << std::endl;
      break;
    case STATES::ACCEPT:
      stream << "ACCEPT" << std::endl;
      break;
    case STATES::CHECK:
      stream << "CHECK" << std::endl;
      break;
    case STATES::COOK:
      stream << "COOK" << std::endl;
      break;
    default:
      stream << "UNKNOWN" << std::endl;
      break;
  }
  return state;
}

std::pair<CHOISE_STATES, double> Automata::choice(size_t drinkIndex) {
  if (state == STATES::ACCEPT) {
    if (drinkIndex >= 0 && drinkIndex < menu.size()) {
      state = STATES::CHECK;
      if (check(drinkIndex)) {
        cash += menu[drinkIndex].price;
        singleCash -= menu[drinkIndex].price;
        double toReturn = singleCash;
        cook();
        return std::pair(CHOISE_STATES::OK, toReturn);
      } else
        return std::pair(CHOISE_STATES::NOT_ENOUGHT_MONEY, cancel());
    } else
      return std::pair(CHOISE_STATES::INVALID_ITEM, cancel());
  }
  return std::pair(CHOISE_STATES::INACCESSIBLE, 0);
}

bool Automata::check(size_t drinkIndex) {
  if (state == STATES::CHECK) return singleCash >= menu[drinkIndex].price;
  return false;
}

double Automata::cancel() {
  if (state != STATES::OFF) {
    double toReturn = singleCash;
    singleCash = 0;
    state = STATES::WAIT;
    return toReturn;
  }
  return 0;
}

void Automata::cook() {
  if (state == STATES::CHECK) {
    state = STATES::COOK;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    finish();
  }
}

void Automata::finish() {
  if (state == STATES::COOK) {
    singleCash = 0;
    state = STATES::WAIT;
  }
}