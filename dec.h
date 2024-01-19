#ifndef GAME_MODE_H
#define GAME_MODE_H

#include <iostream>
// #include <memory>
#include "vector"

using namespace std;

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Colors
 */
class CLR
{
public:
  // Colors >> Red
  static string Red(string text, bool bold = false);
  // Colors >> Green
  static string Green(string text, bool bold = false);
  // Colors >> Yellow
  static string Yellow(string text, bool bold = false);
  // Colors >> Blue
  static string Blue(string text, bool bold = false);
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 *Cell
 */
class Cell
{

private:
  string _value;

public:
  // Game Object
  static string CELL_WALL;
  static string CELL_TRASH;
  static string CELL_PLAYER;
  static string CELL_SPACER;
  // --
  Cell(string value);

  // Get Value
  string value() const;
  // Set Value
  void setValue(string value);
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * GameLevel
 */
class GameLevel
{
protected:
  vector<vector<int>> _walls;
  vector<int> _player_position;
  int _collectables;
  vector<int> _dimensions;
  string _title;

  virtual void setWalls(vector<vector<int>> walls);
  virtual void setPlayerPosition(vector<int> position);
  virtual void setCollectables(int count);
  virtual void setCanvasDimensions(vector<int> dimension);
  virtual void setTitle(string title);

public:
  vector<vector<int>> getWalls();
  vector<int> getPlayerPosition();
  int getCollectables();
  vector<int> getCanvasDimensions();
  string getTitle();
  // --
  int getCanvasHeight();
  int getCanvasWidth();
  int getPlayerPosX();
  int getPlayerPosY();
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Game Levels
 * >> Test Level
 */
class TestLevel : public GameLevel
{
  void setup();

public:
  TestLevel();
};
// >> Test Level
class LevelOne : public GameLevel
{
  void setup();

public:
  LevelOne();
};
// >> Test Level
class LevelTwo : public GameLevel
{
  void setup();

public:
  LevelTwo();
};
/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Canvas >> Play Area
 */
class Canvas
{
public:
  vector<vector<Cell>> CANVAS;
  // --
  Canvas(const GameLevel level);
  // --
  void setup_canvas();
  void load_walls(const vector<vector<int>> &structure);
  void load_collectables(int amount);
  // Cell &get_cell(int x, int y);
  // --
  // bool is_full();
  // bool is_empty();
  void render();
  void game_headers();
  void game_footer();
  // GETTER | SETTER | width and height

  string TITLE;
  int HEIGHT,
      WIDTH,
      PLAYER_X,
      PLAYER_Y,
      COLLECTED = 0,
      COLLECTABLES;
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Player
 */
class Player
{
  // friend class Canvas;

public:
  Player();
  /**
   * 01 = move
   * 10 = no-action
   * 14 = quit-game
   * 12 = win
   */
  int movePlayer(Canvas &canvas);
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Games Levels
 */
class LevelMaster
{
public:
  void addLevel(GameLevel level);
  GameLevel &getLevelByIndex(int index);
  // vector<unique_ptr<GameLevel>> &getAllLevels();
  vector<GameLevel> &getAllLevels();
  LevelMaster();

private:
  // vector<unique_ptr<GameLevel>> _levels;
  vector<GameLevel> _levels;
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * File Handling >> Save Game State
 */
class GameFiler
{
public:
  string state;
  GameFiler();
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Game
 */
class Game
{
public:
  // Props
  static int STATE_WIN;
  static int STATE_LOOSE;
  static int STATE_QUIT;
  static int STATE_MOVE;
  static int STATE_NEXT;
  static int STATE_REPLAY;
  //--
  // int items_collected = 0;
  // int items_total = 0;
  //--
  int current_level;
  int total_levels;
  // --
  // Canvas canvas;
  Player player;
  LevelMaster master;

  Game(LevelMaster level);
  void start();
  // Level _canvas;
  // bool has_won(const Player &player) const;
  void intro_headers();
  void game_headers();
  void win_text();
  void quit_text();
  void end_text();
  bool hasNextLevel(int current_level);
  int createGameMenuList();
  // --
  void runLevel(GameLevel level);
  /**
   * start
   * runLevel
   *  - play
   *  - end
   *  - choose next level | quite
   * finish
   * next level
   */
};

#endif

/**
 * Game
 *  > Canvas
 *  > Level
 *    - walls
 *    - player position | X | Y
 *    - collectables
 *    - dimension | width | height
 *  > Player
 */

/**
 * GameLevels
 *
 * > One
 *    - Class >> GameLevels
 *    - Add a game level into an array
 *    - accessed by index
 *
 */