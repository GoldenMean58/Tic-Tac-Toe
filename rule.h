#ifndef RULE_H
#define RULE_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
using std::cin;
using std::cout;
using std::endl;
int success_count(int grid[3][3], int player);
void fill_empty(int map[3][3], int player, int ret[3][3]);
int scheduler(int where);
extern int map[3][3];
extern int now_player;

#endif
