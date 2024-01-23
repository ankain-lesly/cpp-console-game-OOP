#include <iostream>
#include "dec.h"

/**
 * CPP Console Game
 * @author Lesly Chuo <leeleslyank@gmail.com>
 *
 */

int main()
{
  // srand(time(nullptr));
  // start();

  LevelMaster master;

  // >> this
  Game game(master);
  game.start();

  // >> OR  this

  // GameLevel level = master.getLevelByIndex(2);
  // game.runLevel(level);

  return 0;
}