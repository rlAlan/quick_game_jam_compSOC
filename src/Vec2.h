#include <iostream>

#ifndef VEC2_HPP
#define VEC2_HPP

template<typename ...T>
void print(std::ostream &out, T ...args){
	auto printArg{
		[&out](const auto &arg){out << arg;}
	};
	(printArg(args), ...);
}

template<typename ...T>
void input(T &...args){
	auto getArg{
		[](auto &arg){std::cin >> arg;}
	};
	(getArg(args), ...);
}

struct Vec2{
  int x;
  int y;
};
#endif //  VEC2_HPP
