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

struct DecisionTree *ai(int grid[3][3], int player, int depth) {
  if (depth < 0)
    return nullptr;
  struct DecisionTree *dt = new struct DecisionTree();
  dt->children = nullptr;
  dt->next = nullptr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      dt->grid[i][j] = grid[i][j];
    }
  }
  // {{1, 2, 1}, {0, 1, 0}, {1, 0, 1}}
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (dt->grid[i][j] == 0) {
        int tmp = dt->grid[i][j];
        dt->grid[i][j] = player;
        player = player == 1 ? 2 : 1;
        struct DecisionTree *new_tree = ai(dt->grid, player, depth - 1);
        dt->grid[i][j] = tmp;
        if (new_tree == nullptr) {
          int filled_grid1[3][3];
          fill_empty(dt->grid, player, filled_grid1);
          int value = success_count(filled_grid1, player);
          int filled_grid2[3][3];
          player = player == 1 ? 2 : 1;
          fill_empty(dt->grid, player, filled_grid2);
          dt->value = success_count(filled_grid2, player) - value;
          player = player == 1 ? 2 : 1;
        }
        player = player == 1 ? 2 : 1;
        if (dt->children == nullptr)
          dt->children = new_tree;
        else {
          struct DecisionTree *last_ele = dt->children;
          while (last_ele->next != nullptr)
            last_ele = last_ele->next;
          last_ele->next = new_tree;
        }
      }
    }
  }
  struct DecisionTree *p = dt->children;
  int min_value = INT_MAX;
  while (p) {
    if (p->value <= min_value) {
      dt->value = p->value;
      min_value = p->value;
    }
    p = p->next;
  }
  return dt;
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
