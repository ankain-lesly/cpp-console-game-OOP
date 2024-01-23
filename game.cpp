#include <iostream>
#include "dec.h"

/**
 * CPP Console Game
 * @author Lesly Chuo <leeleslyank@gmail.com>
 * @package null >> HND 2024 >> CPP Exercises
 * @c Mr Mbiethieu
 *
 * Create a console game in cpp capable of collecting items in a room, keeping track of counts and levels
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