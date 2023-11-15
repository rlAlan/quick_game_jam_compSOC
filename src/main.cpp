#include <iostream>
#include "World.h"

void print_options(){
  print(std::cout, "Choose an Option:\n\t1.Use Default Map\n\t2.Load from file\n\t");
}

int main(){
  print_options();

//  World world{1};
//  world.test_file();
  int value{};
  input(value);
  World world{value};
  world.draw();
	return 0;
}
