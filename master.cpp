#include <iostream>
#include "dec.h"
using namespace std;

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Games Levels
 */
LevelMaster::LevelMaster()
{
  // Level Objects
  TestLevel testLevel;
  LevelOne LevelOne;
  LevelTwo LevelTwo;
  // Add
  this->addLevel(testLevel);
  this->addLevel(LevelOne);
  this->addLevel(LevelTwo);
}
void LevelMaster::addLevel(GameLevel level)
{
  this->_levels.push_back(level);
  // this->_levels.push_back(make_unique<TestLevel>());
}
GameLevel &LevelMaster::getLevelByIndex(int index)
{
  const auto num_levels = _levels.size();
  if (index < num_levels)
  {
    // return *_levels[index];
    return _levels[index];
  }
  throw std::out_of_range("Index out of range. Number of levels: " + std::to_string(num_levels));
}
vector<GameLevel> &LevelMaster::getAllLevels()
{
  return _levels;
}

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Game Levels
 * >> Test Level
 */

TestLevel::TestLevel()
{
  this->setup();
}
void TestLevel::setup()
{
  this->setTitle("Test Level");
  this->setCollectables(5);

  vector<int> dimensions{10, 10};
  this->setCanvasDimensions(dimensions);

  vector<int> player{5, 5};
  this->setPlayerPosition(player);

  vector<vector<int>> walls{
      {0, 0},
  };
  this->setWalls(walls);
}
// >> Level One;
LevelOne::LevelOne()
{
  this->setup();
}
void LevelOne::setup()
{
  this->setTitle("Level One");
  this->setCollectables(15);

  vector<int> dimensions{15, 15};
  this->setCanvasDimensions(dimensions);

  vector<int> player{13, 8};
  this->setPlayerPosition(player);

  vector<vector<int>> walls{
      {9, 1},
      {9, 2},
      {9, 3},
      {9, 4},
      {8, 4},
      {7, 4},
      {10, 4},
      {11, 4},
      {12, 4},
      {12, 5},
      // {4, 4},
      {4, 8},
      {4, 9},
      {4, 10},
      {4, 12},
      {2, 11},
      {3, 11},
      {4, 11},
      {5, 11},
      {6, 11},
      {7, 11},
      // {7, 11},
      {10, 9},
      {11, 9},
      {12, 9},
      {13, 9},
      // {13, 9},
      {10, 11},
      {10, 12},
      {10, 13},

  };
  this->setWalls(walls);
}
// >> Level One;
LevelTwo::LevelTwo()
{
  this->setup();
}
void LevelTwo::setup()
{
  this->setTitle("Level Two");
  this->setCollectables(30);

  vector<int> dimensions{15, 15};
  this->setCanvasDimensions(dimensions);

  vector<int> player{13, 13};
  this->setPlayerPosition(player);

  vector<vector<int>> walls{
      // {1, 8},
      {2, 8},
      {3, 8},
      {4, 8},
      // {5, 8},
      {6, 8},
      {7, 8},
      {8, 8},
      // {9, 8},
      {10, 8},
      {11, 8},
      {13, 8},
      // {14, 8},

      {3, 4},
      {4, 4},
      {5, 4},
      {6, 4},
      // {7, 4},
      {8, 4},
      {9, 4},
      {10, 4},
      {11, 4},
      // {12, 4},
      {13, 4},
      // >>
      {4, 1},
      // {4, 2},
      {4, 3},
      // {4, 4},
      // {4, 5},
      {4, 6},
      {4, 7},
      // {4, 8},
      {4, 9},
      {4, 10},
      // {4, 11},
      {4, 12},
      {4, 13},

      // >>
      {10, 1},
      {10, 2},
      // {10, 3},
      // {10, 4},
      {10, 5},
      // {10, 6},
      {10, 7},
      {10, 8},
      {10, 9},
      {10, 10},
      {10, 11},
      // {10, 12},
      {10, 13},
  };
  this->setWalls(walls);
}