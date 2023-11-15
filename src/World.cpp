#include "World.h"
#include "filesystem"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <string>
#include <stdio.h>

World::World(int option){
  if(option == 1){ // use default map
    // read from default file 
    set_world_from_default_file();
  } else {
    // ask for file location
    print(std::cout, "Option 2 has been chosen");
    // read from file instead
     set_world_from_default_file();
  }
}

void World::set_world_from_default_file(){
  std::ifstream default_file{"../src/test.txt"};
  std::string line{};

  if(default_file.is_open()){
   while(std::getline(default_file, line)){
      world.push_back(line);
   }

    // going to have the ~ mark the user
    for(auto &val : world){
      std::replace(val.begin(), val.end(), 'o', '#'); // for walls and untouchable areas
      std::replace(val.begin(), val.end(), 'x', ' '); // for places we can walk 
    }

    // get the position of the tilde for the player
    for(int row{0}; row < world.size(); row++){
      for(int col{0}; col < world[row].size(); col++){
        if(world[row][col] == '~'){
          player.set_pos({col, row});
          player.set_new_pos({col, row});
        }
      }
    }
  } 
  else print(std::cout, "File not open");
  default_file.close();
}

void Player::movement_info(){
  // implement (w)random
  print(std::cout, "Where would you like to move? [(u)p,(d)own,(l)eft,(r)ight] and How many places\n");
  print(std::cout, "seperated by a space: ");
  input(this->current_orientation, this->move_amount);
  print(std::cout, "Orientation: ", this->current_orientation, '\n', "Amount: ", this->move_amount, '\n');
}

void Player::set_move_amount(int move){this->move_amount = move;}
int Player::get_move_amount()const{return this->move_amount;}
char Player::get_current_orientation()const{return this->current_orientation;}
void Player::set_orientation(char orientation){this->current_orientation = orientation;}

void World::draw(){ 
  for(auto &val : world){
    print(std::cout, val);
    print(std::cout, '\n');
  }
  print(std::cout, "Player pos x: ", player.get_pos().x, "Player Pos y: ", player.get_pos().y, '\n');
  bool valid_move{true};
  // ignore goofy code ill sort it later
  do{
    this->player.movement_info();
    if((this->player.get_current_orientation() == 'l') && ((this->player.get_pos().x == 0) ||
      world[this->player.get_pos().y][this->player.get_pos().x-(this->player.get_move_amount())] == '#')){
      print(std::cout, "Cannot move that direction choose a different place\n");
      valid_move = false;
    }else{
      this->player.set_new_pos({this->player.get_pos().x - this->player.get_move_amount(), this->player.get_pos().y});
    }

    if((this->player.get_current_orientation() == 'r') && 
      ((this->player.get_pos().x == world[this->player.get_pos().x].size()) ||
      (world[this->player.get_pos().y][this->player.get_pos().x + (this->player.get_move_amount())] == '#'))){
      print(std::cout, "Cannot move in that direction choose a different place\n");
      valid_move = false;
    }else{
      this->player.set_new_pos({this->player.get_pos().x + this->player.get_move_amount(), this->player.get_pos().y});
    }

    if((this->player.get_current_orientation() == 'u') && 
      ((this->player.get_pos().y == 0) ||
      (world[this->player.get_pos().y - (this->player.get_move_amount())][this->player.get_pos().x] == '#'))){
      print(std::cout, "Cannot move in that direction choose a different place\n");
      valid_move = false;
    } else{
      this->player.set_new_pos({this->player.get_pos().x, this->player.get_pos().y - this->player.get_move_amount()});
    }

    if((this->player.get_current_orientation() == 'd') && 
      ((this->player.get_pos().y == world.size()) ||
      (world[this->player.get_pos().y + (this->player.get_move_amount())][this->player.get_pos().x] == '#'))){
      print(std::cout, "Cannot move in that direction choose a different place\n");
      valid_move = false;
    }else{
      this->player.set_new_pos({this->player.get_pos().x, this->player.get_pos().y + this->player.get_move_amount()});
    }

    if(valid_move){
      this->update_world();
      system("clear");
      for(auto &val : world){
        print(std::cout, val);
        print(std::cout, '\n');
      }
    }

  }while(valid_move);
}

void World::update_world(){
    for(int row{0}; row < world.size(); row++){
      for(int col{0}; col < world[row].size(); col++){
        if(row == this->player.get_new_pos().y && col == this->player.get_new_pos().x){
          world[row][col] = '~';
        }
        if(row == this->player.get_pos().y && col == this->player.get_pos().x){
          world[row][col] = ' ';
        }
      }
    }
}

void Player::set_pos(Vec2 pos){this->pos = pos;}
Vec2 Player::get_pos()const{return this->pos;}
void Player::set_new_pos(Vec2 pos){this->new_pos = pos;}
Vec2 Player::get_new_pos()const{return this->new_pos;}
