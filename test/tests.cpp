// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>

#include "Automata.h"

TEST(task1, test1) {
  Automata* automata = new Automata();
  automata->on();
  automata->coin(20);
  STATES result = automata->getState(std::cout);
  ASSERT_EQ(STATES::ACCEPT, result);
  CHOISE_STATES cookResult = automata->choice(2).first;
  ASSERT_EQ(CHOISE_STATES::NOT_ENOUGHT_MONEY, cookResult);
  cookResult = automata->choice(0).first;
  ASSERT_EQ(CHOISE_STATES::INACCESSIBLE, cookResult);
}