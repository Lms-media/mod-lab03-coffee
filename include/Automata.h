// Copyright 2022 UNN-IASR
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <utility>
#include <vector>

enum class STATES { OFF, WAIT, ACCEPT, CHECK, COOK };
enum class CHOISE_STATES { OK, INVALID_ITEM, NOT_ENOUGHT_MONEY, INACCESSIBLE };

struct menuItem {
  std::string name;
  double price;
};

class Automata {
 private:
  double cash = 0;
  double singleCash = 0;
  std::vector<menuItem> menu;
  STATES state = STATES::OFF;

  bool check(size_t drinkIndex);
  void cook();
  void finish();

 public:
  Automata();
  Automata(std::vector<menuItem> customMenu);

  void on();
  void off();
  void coin(double amount);
  std::vector<menuItem> getMenu() const;
  STATES getState(std::ostream& stream) const;
  std::pair<CHOISE_STATES, double> choice(size_t drinkIndex);
  double cancel();
};

#endif
