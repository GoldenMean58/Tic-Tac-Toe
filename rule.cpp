#include "rule.h"
int map[3][3] = {{0}};
int now_player = 1;
int success_count(int grid[3][3], int player) {
  int result = 0;
  for (int i = 0; i < 3; ++i) {
    if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player)
      result++;
  }
  for (int i = 0; i < 3; ++i) {
    if (grid[0][i] == player && grid[1][i] == player && grid[2][i] == player)
      result++;
  }
  if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
    result++;
  if (grid[2][0] == player && grid[1][1] == player && grid[0][2] == player)
    result++;
  return result;
}

struct DecisionTree *generate_decision_tree(int grid[3][3], int player,
                                            int depth) {
  if (depth == 0)
    return nullptr;
  struct DecisionTree *result = new struct DecisionTree();
  result->children = nullptr;
  result->next = nullptr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      result->grid[i][j] = grid[i][j];
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (result->grid[i][j] == 0) {
        result->grid[i][j] = player;
        player = player == 1 ? 2 : 1;
        if (result->children) {
          struct DecisionTree *p = result->children;
          while (p->next) {
            p = p->next;
          }
          p->next = generate_decision_tree(result->grid, player, depth - 1);
        } else
          result->children =
              generate_decision_tree(result->grid, player, depth - 1);
        result->grid[i][j] = 0;
        player = player == 1 ? 2 : 1;
      }
    }
  }
  if (!result->children) {
    set_node_value(result, player);
  }
  return result;
}

struct DecisionTree *ai(int grid[3][3], int player, int depth) {
  struct DecisionTree *t = generate_decision_tree(grid, player, depth);
  minimax(t, depth, true);
  return t;
}

void set_node_value(struct DecisionTree *node, int player) {
  if (node) {
    int ret1[3][3];
    int ret2[3][3];
    int value1, value2;
    fill_empty(node->grid, player, ret1);
    value1 = success_count(ret1, player);
    player = player == 1 ? 2 : 1;
    fill_empty(node->grid, player, ret2);
    value2 = success_count(ret2, player);
    node->value = value1 - value2;
  }
}

int minimax(struct DecisionTree *node, int depth, bool maximizing_player) {
  if (depth == 0 || node->children == nullptr) {
    return node->value;
  }
  int best_value;
  if (maximizing_player) {
    best_value = INT_MIN;
    struct DecisionTree *child = node->children;
    while (child) {
      int value = minimax(child, depth - 1, !maximizing_player);
      child->value = value;
      if (value >= best_value)
        best_value = value;
      child = child->next;
    }
    return best_value;
  } else {
    best_value = INT_MAX;
    struct DecisionTree *child = node->children;
    while (child) {
      int value = minimax(child, depth - 1, !maximizing_player);
      child->value = value;
      if (value <= best_value)
        best_value = value;
      child = child->next;
    }
  }
  return best_value;
}

int scheduler(int where) {
  int x = where / 3;
  int y = where % 3;
  if (map[x][y] == 0) {
    map[x][y] = now_player;
    int suc_count = success_count(map, now_player);
    if (suc_count != 0) {
      return now_player;
    } else {
      if (now_player == 1)
        now_player = 2;
      else
        now_player = 1;
    }
    return 0;
  }
  return -1;
}

void fill_empty(int map[3][3], int player, int ret[3][3]) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ret[i][j] = map[i][j];
      if (map[i][j] != player) {
        ret[i][j] = (map[i][j] == 0) ? player : 0;
      }
    }
  }
}

void clean_tree(struct DecisionTree *t) {
  if (!t)
    return;
  clean_tree(t->children);
  clean_tree(t->next);
  delete t;
}

int get_best_move(struct DecisionTree *t) {
  DecisionTree *child = t->children;
  DecisionTree *max_subtree = nullptr;
  int max_value = INT_MIN;
  while (child) {
    if (child->value >= max_value) {
      max_value = child->value;
      max_subtree = child;
    }
    child = child->next;
  }
  int best_move = -1;
  if (max_subtree == nullptr)
    return 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (max_subtree->grid[i][j] != t->grid[i][j]) {
        best_move = i * 3 + j;
        break;
      }
    }
    if (best_move != -1)
      break;
  }
  clean_tree(t);
  return best_move;
}

void output_map(int map[3][3]) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
}

void print_tree(struct DecisionTree *t) {
  if (!t)
    return;
  output_map(t->grid);
  cout << t->value << endl;
  cout << endl;
  print_tree(t->children);
  cout << endl;
  print_tree(t->next);
  cout << endl;
  cout << endl;
}
