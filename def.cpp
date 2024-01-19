#include <iostream>
// #include <memory>
#include "dec.h"
#include "conio.h"
#include "stdlib.h"
using namespace std;
/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Cell
 */
Cell::Cell(string value) : _value(value) {}
//--
string Cell::CELL_WALL = CLR::Yellow(" # ");
string Cell::CELL_TRASH = CLR::Red(" X ");
string Cell::CELL_PLAYER = CLR::Green("|||");
string Cell::CELL_SPACER = " . ";
// Get Value
string Cell::value() const
{
  return this->_value;
}
// Set Value
void Cell::setValue(string value)
{
  this->_value = value;
}
/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Canvas
 */
Canvas::Canvas(GameLevel level)
{
  this->HEIGHT = level.getCanvasHeight();

  // this->HEIGHT = level ->getCanvasHeight()[1];
  this->WIDTH = level.getCanvasWidth();
  this->PLAYER_X = level.getPlayerPosX();
  this->PLAYER_Y = level.getPlayerPosY();
  this->COLLECTABLES = level.getCollectables();
  this->TITLE = level.getTitle();

  //-- title

  this->setup_canvas();
  this->load_walls(level.getWalls());
  this->load_collectables(this->COLLECTABLES);
  // this->render();
};
// Fill Canvas Grid Area
void Canvas::setup_canvas()
{

  // Clear Console
  system("CLS");

  cout << CLR::Green("\nLOADING__");
  // cout << "\nSetting up canvas..";
  for (int x = 0; x < this->WIDTH; x++)
  {
    vector<Cell> row;
    for (int y = 0; y < this->HEIGHT; y++)
    {
      if (x == this->PLAYER_Y && y == this->PLAYER_X)
        row.push_back(Cell(Cell::CELL_PLAYER));
      else if (x == 0 || x == this->WIDTH - 1 || y == 0 || y == this->HEIGHT - 1)
        row.push_back(Cell(Cell::CELL_WALL));
      else
        row.push_back(Cell(Cell::CELL_SPACER));
    }
    this->CANVAS.push_back(row);
  }
}
// Add Collectable items
void Canvas::load_collectables(int amount)
{
  int x, y, counter = 0;
  // cout << "\nPainting Collectables..\n";

  while (counter < amount)
  {
    x = rand() % this->WIDTH;
    y = rand() % this->HEIGHT;

    // cout << endl
    //      << "x: " << x << endl
    //      << "y: " << y << endl
    //      << "@Canvas: " << CANVAS[x][y] << endl
    //      << "counter: " << counter << endl;

    if (this->CANVAS[x][y].value() == Cell::CELL_SPACER)
    {
      this->CANVAS[x][y].setValue(Cell::CELL_TRASH);
      counter++;
      continue;
    }
  }
}
// Add Walls
void Canvas::load_walls(const vector<vector<int>> &structure)
{
  int x, y;
  // cout << "\nLoading walls..\n";
  for (const auto &wall : structure)
  {
    if (!wall[0] || !wall[1])
      continue;

    x = wall[0];
    y = wall[1];

    this->CANVAS[x][y].setValue(Cell::CELL_WALL);
  }
}
// Render Canvas
void Canvas::render()
{
  // get coordinated from position
  this->game_headers();
  // cout << CLR::Yellow("*****************************************") << endl;
  // cout << CLR::Yellow("*****************************************") << endl;
  // cout << CLR::Yellow(">>>>") << endl;
  for (int y = 0; y < this->COLLECTABLES - this->COLLECTED; y++)
  {
    if (y >= this->WIDTH + 2 && y % (this->WIDTH + 2) == 0)
      cout << endl;
    cout << CLR::Green(">> ");
  }
  cout << endl
       << endl;

  // Border
  for (int y = 0; y < this->WIDTH + 2; y++)
    cout << "***";
  cout << endl;
  // Canvas
  for (int x = 0; x < this->WIDTH; x++)
  {
    cout << "** ";
    for (int y = 0; y < this->HEIGHT; y++)
    {
      cout << CANVAS[x][y].value();
    }
    cout << " **\n";
  }
  // Border
  for (int y = 0; y < this->WIDTH + 2; y++)
    cout << "***";
  cout << endl;

  // cout << CLR::Yellow(">>>") << endl;
  // cout << CLR::Yellow(">>>>> >>>> >>> >> >") << endl;
  // cout << CLR::Yellow("*****************************************") << endl;
  // cout << CLR::Yellow("*****************************************") << endl;

  this->game_footer();
}
// Game Play Header
void Canvas::game_headers()
{
  cout << "\n     " + CLR::Green("       >> " + this->TITLE, true) + "        \n";
  cout << "*****************************************" << endl;
  cout << "*           " + CLR::Green("<< GAME PLAY >>", true) + "             *\n";
  // cout << "*                                       * \n";

  // cout << "* ------------------------------------- *\n";
  // cout << "*      " + CLR::Blue("UP") + " <> " + CLR::Blue("DOWN") + " <> " + CLR::Blue("LEFT") + " <> " + CLR::Blue("RIGHT") + "      *" << endl;
  cout << "* ------------------------------------- *\n";
  cout << "*      " + CLR::Yellow("Collected") + ": [" << this->COLLECTED << "], " + CLR::Yellow("Left") + ": [" << this->COLLECTABLES - this->COLLECTED << "]        * \n";
  // cout << "* ------------------------------------- *\n";
  // cout << "*                                       * \n";
  // cout << "* [Q > Exit, P > Pause, S > Save, R Restart] *\n";
  cout << "*****************************************\n"
       << endl;
}
void Canvas::game_footer()
{
  cout << "----------------------------------------------\n";
  cout << "| [Q > Exit, P > Pause, S > Save, R Restart] |\n";
  cout << "----------------------------------------------\n\n";
}

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Player
 */
Player::Player() {}
// mover player
int Player::movePlayer(Canvas &canvas)
{
  // update position
  char key;
  key = getch();
  int posY = canvas.PLAYER_Y;
  int posX = canvas.PLAYER_X;
  int POSITION_Y = canvas.PLAYER_Y;
  int POSITION_X = canvas.PLAYER_X;

  // Move Actions
  if ((key == 'a' || key == 'A') || key == 75 && POSITION_X > 1)
  {
    // cout << "\nMoving left: " << POSITION_X << endl;
    POSITION_X--;
  }
  else if ((key == 'd' || key == 'D') || key == 77 && POSITION_X < canvas.WIDTH - 2)
  {
    // cout << "\nMoving right: " << POSITION_X << endl;
    POSITION_X++;
  }
  else if ((key == 'w' || key == 'W') || key == 72 && POSITION_Y > 1)
  {
    // cout << "\nMoving up: " << POSITION_Y << endl;
    POSITION_Y--;
  }
  else if ((key == 's' || key == 'S') || key == 80 && POSITION_Y < canvas.HEIGHT - 2)
  {
    // cout << "\nMoving down: " << POSITION_Y << endl;
    POSITION_Y++;
  }

  // Add Score
  if (canvas.COLLECTED >= canvas.COLLECTABLES)
    return Game::STATE_WIN; // win
  //-- TRASH Collision
  if (canvas.CANVAS[POSITION_Y][POSITION_X].value() == Cell::CELL_TRASH)
    canvas.COLLECTED++;

  // Wall Collision
  if (canvas.CANVAS[POSITION_Y][POSITION_X].value() == Cell::CELL_WALL)
  {
    POSITION_X = posX;
    POSITION_Y = posY;
  }

  // Exit
  if (key == 81 || key == 113)
    return Game::STATE_QUIT; // quit-game

  // Update CANVAS
  canvas.CANVAS[posY][posX].setValue(Cell::CELL_SPACER);
  canvas.CANVAS[POSITION_Y][POSITION_X].setValue(Cell::CELL_PLAYER);
  canvas.PLAYER_X = POSITION_X;
  canvas.PLAYER_Y = POSITION_Y;
  // game_board.get_cell(x, y) = Cell(this->symbol);
  if (POSITION_X != posX || POSITION_Y != posY)
    return Game::STATE_MOVE; // no-action
  else
    return 0; // no-action
}

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Game
 * Game Start Instructions
 */

int Game::STATE_WIN = 12;
int Game::STATE_QUIT = 14;
int Game::STATE_LOOSE = 19;
int Game::STATE_MOVE = 1;
int Game::STATE_NEXT = 22;
int Game::STATE_REPLAY = 17;
Game::Game(LevelMaster master) : player(), master(master)
{
  this->current_level = 0;
  this->total_levels = this->master.getAllLevels().size();
}
void Game::start()
{
  system("CLS");
  cout << "\nListing levels..." << endl;
  int selectedLevel = this->createGameMenuList();

  if (selectedLevel >= 0)
  {
    this->current_level = selectedLevel;
    this->runLevel(this->master.getLevelByIndex(selectedLevel));
  }

  /**
   * Create interface of all levels and you select
   * on select getLevel >> runLevel
   */
  // --
}
void Game::runLevel(GameLevel level)
{
  Canvas canvas(level);
  this->intro_headers();
  // Start Game
  cout << "\n   \t SETTING UP: Canvas, walls, collectibles... ";
  cout << "\n   \t DONE.\n";
  cout << "\n >>\t Level: " << canvas.TITLE;
  cout << "\n >>\t Press [Enter] to begin:";
  cout << "\n   \t ...";
  getchar();

  bool isPlaying = true;
  int state = 0;
  int key = 0;

  while (isPlaying)
  {
    // Clear Screen
    system("CLS");

    canvas.render();
    cout << " X >>:" << canvas.PLAYER_X << endl;
    cout << " Y >>:" << canvas.PLAYER_Y << endl;
    cout << " Moves  >>:" << key << endl;
    cout << " State >>: " << state << endl;
    state = this->player.movePlayer(canvas);

    if (state == Game::STATE_MOVE)
      key++;

    if (state == Game::STATE_WIN)
      break;
    else if (state == Game::STATE_QUIT)
      break;
  }
  // Clear Screen
  system("CLS");

  if (state == Game::STATE_WIN)
    this->win_text();
  else if (state == Game::STATE_QUIT)
    this->quit_text();

  char input;
  this->end_text();
  state = 0;
  while (true)
  {
    input = getch();
    // restart
    if (input == 'r' || input == 'R')
    {
      state = 11;
      break;
    }
    // Select Levels
    else if (input == 'u' || input == 'U')
    {
      state = 22;
      break;
    }
    // Next Level
    else if (input == 'n' || input == 'N')
    {
      if (this->hasNextLevel(this->current_level))
      {
        state = 33;
        break;
      }
      else
        cout << CLR::Yellow("\n >> \tPLAYER: This was your last level");
    }
    // Exit
    else if (input == 81 || input == 113)
      break;
  }

  // restart
  if (state == 11)
    this->runLevel(level);
  // Select Levels
  else if (state == 22)
    this->start();
  // Next Level
  else if (state == 33)
  {
    this->current_level++;
    GameLevel nextLevel = this->master.getLevelByIndex(this->current_level);
    runLevel(nextLevel);
  }
}
void Game::intro_headers()
{
  cout << endl
       << endl;
  cout << CLR::Yellow("* INSTRUCTIONS [PRESS]") << "\n*\n";
  cout << "* [Q > Exit, P > Pause, S > Save, R Restart]" << endl
       << endl;
  cout << "* >> PLAY KEYS \n";
  cout << "* --------------------------------- \n";
  cout << "*  " + CLR::Blue("UP") + " <> " + CLR::Blue("DOWN") + " <> " + CLR::Blue("LEFT") + " <> " + CLR::Blue("RIGHT") + "" << endl;
  cout << "* --------------------------------- \n";
  cout << "*  " + CLR::Blue("W") + " <> " + CLR::Blue("S") + " <> " + CLR::Blue("A") + " <> " + CLR::Blue("D") + "" << endl;
  cout << "* --------------------------------- \n";
}
void Game::win_text()
{
  cout
      << endl
      << endl
      << "   \t " + CLR::Green("| >>  >>  >>  >> >>") + " \n"
      << " " + CLR::Green(">>") + "\t | " + CLR::Green("Woohuu You Won!..") + "\n"
      << "   \t " + CLR::Green("| >>  >>  >>  >> >>") + " \n"
      << endl
      << endl;
}
void Game::end_text()
{
  cout
      << endl
      << " >>\t Press [R] Play Again!"
      << endl
      << " >>\t Press [Q] Exit!"
      << endl
      << " >>\t Press [U] Select Level!"
      << endl
      << " >>\t Press [N] Next Level!"
      << endl
      << "   \t ...";
}
void Game::quit_text()
{
  cout
      << endl
      << endl
      << CLR::Red("   \t | >>\n")
      << CLR::Red(" >>\t | Exiting Game...\n")
      << CLR::Red("   \t | >>")
      << endl;
}
bool Game::hasNextLevel(int current_level)
{
  return this->current_level < this->total_levels - 1;
}
int Game::createGameMenuList()
{
  char input;
  int state = 0;
  bool isMenu = true;
  bool isSelected = false;
  vector<GameLevel> levels = this->master.getAllLevels();

  while (isMenu && !isSelected)
  {
    system("CLS");
    cout << CLR::Green("---------------------------------- ") << endl;
    cout << CLR::Green("- <<<<< ROBOT CLEANER GAME >>>>> -", true) << endl;
    cout << CLR::Green("---------------------------------- ") << "\n*\n";

    cout << "\n SELECT GAME LEVEL\n";
    cout << "\n Press " << CLR::Yellow("[Up, Down]") << " Arrow keys";
    cout << "\n To navigate list";
    cout << "\n\n";

    // Move Up
    if (input == 72 && state > 0)
      state--;
    // Move Down
    else if (input == 80 && state < levels.size() - 1)
      state++;
    //  >> Draw Menu
    for (int i = 0; i < levels.size(); i++)
    {
      if (i == state)
        cout << CLR::Green(" >>");
      else
        cout << "   ";
      cout << "\t" << levels[i].getTitle() << endl;
    }
    //  >> End Menu

    cout << "\n\n Press >>";
    cout << "\n \t" << CLR::Yellow("[K]") << " to Start level";
    cout << "\n \t" << CLR::Yellow("[Q]") << " to Exit";
    cout << "\n\n";

    input = getch();
    if (input == 'k' || input == 'K')
      isSelected = true;
    // Exit
    else if (input == 81 || input == 113)
      isMenu = false;
  }

  if (isSelected)
    return state;

  return -2;
}
/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * GameLevel
 */
// >> Setters
void GameLevel::setWalls(vector<vector<int>> walls)
{
  this->_walls = walls;
}
void GameLevel::setPlayerPosition(vector<int> position)
{
  this->_player_position = position;
}
void GameLevel::setCollectables(int count)
{
  this->_collectables = count;
}
void GameLevel::setCanvasDimensions(vector<int> dimension)
{
  this->_dimensions = dimension;
}
void GameLevel::setTitle(string title)
{
  this->_title = title;
}
// >> Getters
vector<vector<int>> GameLevel::getWalls()
{
  return this->_walls;
}
vector<int> GameLevel::getPlayerPosition()
{
  return this->_player_position;
}
int GameLevel::getCollectables()
{
  return this->_collectables;
}
vector<int> GameLevel::getCanvasDimensions()
{
  return this->_dimensions;
};
string GameLevel::getTitle()
{
  return this->_title;
};
int GameLevel::getCanvasHeight()
{
  return this->_dimensions[1];
};
int GameLevel::getCanvasWidth()
{
  return this->_dimensions[0];
};
int GameLevel::getPlayerPosX()
{
  return this->_player_position[1];
};
int GameLevel::getPlayerPosY()
{
  return this->_player_position[0];
};

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Text with colors
 */
// Colors >> Red
string
CLR::Red(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[31m" + text + "\033[0m";
  else
    return "\033[31m" + text + "\033[0m";
}
// Colors >> Green
string CLR::Green(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[32m" + text + "\033[0m";
  else
    return "\033[32m" + text + "\033[0m";
}
// Colors >> Yellow
string CLR::Yellow(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[33m" + text + "\033[0m";
  else
    return "\033[33m" + text + "\033[0m";
}
// Colors >> Blue
string CLR::Blue(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[34m" + text + "\033[0m";
  else
    return "\033[34m" + text + "\033[0m";
}

/*
 * >>>>>>>>>>>>>>>>>>>>>>>
 * File Handling >> Save Game State
 */
GameFiler::GameFiler() : state("Pending DB..."){};
