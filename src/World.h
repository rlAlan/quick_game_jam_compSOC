#include <iostream>
#include <array>
#include <vector>
#include "Vec2.h"

#ifndef WORLD_HPP
#define WORLD_HPP

class Player{
public:
  void movement_info();
  char get_current_orientation()const;
  void set_orientation(char orientation);
  void set_move_amount(int move);
  int get_move_amount()const;
  void set_pos(Vec2 pos);
  Vec2 get_pos()const;

  void set_new_pos(Vec2 pos);
  Vec2 get_new_pos()const;
private:
  Vec2 pos;
  Vec2 new_pos;
  char current_orientation;
  int move_amount;
  std::vector<char> inventory;
};


class World{
public:
  World(int option);
  void set_world_from_default_file();
  void draw();
private:
  void update_world();
  std::vector<std::string> world;
  Player player;
};
#endif // WORLD_HPP
