#include <iostream>
#include "dec.h"

int main()
{
  // srand(time(nullptr));
  // start();

  LevelMaster master;

  Game game(master);
  game.start();

  // GameLevel level = master.getLevelByIndex(2);
  // game.runLevel(level);

  return 0;
}