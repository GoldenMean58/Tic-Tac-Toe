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

int scheduler(int where) {
  int x = where / 3;
  int y = where % 3;
  if (map[x][y] == 0) {
    map[x][y] = now_player;
    int suc_count = success_count(map, now_player);
    if (suc_count != 0) {
      cout << "Winner is Player " << now_player << endl;
      exit(0);
    } else {
      if (now_player == 1)
        now_player = 2;
      else
        now_player = 1;
    }
    return 0;
  }
  return 1;
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
