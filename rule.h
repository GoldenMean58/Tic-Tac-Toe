#ifndef RULE_H
#define RULE_H
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
using std::cin;
using std::cout;
using std::endl;
int success_count(int grid[3][3], int player);
void fill_empty(int map[3][3], int player, int ret[3][3]);
int scheduler(int where);
void clean_tree(struct DecisionTree *);
int get_best_move(struct DecisionTree *);
void print_tree(struct DecisionTree *);
void output_map(int map[3][3]);
extern int map[3][3];
extern int now_player;
struct DecisionTree {
  int grid[3][3];
  int value;
  struct DecisionTree *next;
  struct DecisionTree *children;
};
struct DecisionTree *ai(int grid[3][3], int player, int depth);
int minimax(struct DecisionTree *node, int depth, bool maximizing_player);
struct DecisionTree *generate_decision_tree(int grid[3][3], int player,
                                            int depth);
void set_node_value(struct DecisionTree *node, int player);
#endif
