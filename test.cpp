#include "rule.h"
#include <assert.h>

int main(void) {
  srand(static_cast<unsigned int>(time(nullptr)));
  // success_count test
  {
    int map1[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map2[3][3] = {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}};
    int map3[3][3] = {{1, 1, 0}, {1, 0, 0}, {1, 0, 0}};
    int map4[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int map5[3][3] = {{1, 1, 1}, {1, 0, 0}, {1, 0, 0}};
    int map6[3][3] = {{1, 1, 1}, {1, 1, 0}, {1, 1, 0}};
    int map7[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int map8[3][3] = {{0, 0, 1}, {0, 1, 0}, {1, 0, 0}};
    int map9[3][3] = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};
    assert(success_count(map1, 1) == 0);
    assert(success_count(map2, 1) == 1);
    assert(success_count(map3, 1) == 1);
    assert(success_count(map4, 1) == 8);
    assert(success_count(map5, 1) == 2);
    assert(success_count(map6, 1) == 4);
    assert(success_count(map7, 1) == 1);
    assert(success_count(map8, 1) == 1);
    assert(success_count(map9, 1) == 2);
  }
  // fill_empty test
  {
    int buf1[3][3] = {{0}};
    int buf2[3][3] = {{0}};
    int buf3[3][3] = {{0}};
    int buf4[3][3] = {{0}};
    int buf5[3][3] = {{0}};
    int buf6[3][3] = {{0}};
    int buf7[3][3] = {{0}};
    int buf8[3][3] = {{0}};
    int buf9[3][3] = {{0}};
    int map1[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map2[3][3] = {{1, 1, 1}, {2, 0, 0}, {0, 0, 0}};
    int map3[3][3] = {{1, 1, 2}, {1, 2, 0}, {1, 2, 0}};
    int map4[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int map5[3][3] = {{1, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    int map6[3][3] = {{1, 1, 1}, {1, 1, 2}, {1, 1, 2}};
    int map7[3][3] = {{1, 0, 2}, {0, 1, 0}, {2, 2, 1}};
    int map8[3][3] = {{0, 2, 1}, {0, 1, 0}, {1, 0, 0}};
    int map9[3][3] = {{1, 2, 1}, {0, 1, 0}, {1, 0, 1}};
    fill_empty(map1, 1, buf1);
    fill_empty(map2, 1, buf2);
    fill_empty(map3, 1, buf3);
    fill_empty(map4, 1, buf4);
    fill_empty(map5, 1, buf5);
    fill_empty(map6, 1, buf6);
    fill_empty(map7, 1, buf7);
    fill_empty(map8, 1, buf8);
    fill_empty(map9, 1, buf9);
    assert(success_count(buf1, 1) == 8);
    assert(success_count(buf2, 1) == 6);
    assert(success_count(buf3, 1) == 1);
    assert(success_count(buf4, 1) == 8);
    assert(success_count(buf5, 1) == 4);
    assert(success_count(buf6, 1) == 4);
    assert(success_count(buf7, 1) == 2);
    assert(success_count(buf8, 1) == 6);
    assert(success_count(buf9, 1) == 6);
  }
  // ai test
  {
    int map1[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map2[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map3[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map4[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map5[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map6[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map7[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map8[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int map9[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    auto t = ai(map1, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map2, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map3, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map4, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map5, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map6, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map7, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map8, 1, 2);
    assert(get_best_move(t) == 4);
    t = ai(map9, 1, 2);
    assert(get_best_move(t) == 4);
  }
  while (1) {
    if (now_player == 1) {
      cout << "Player " << now_player << endl;
      cout << "x: ";
      int x;
      cin >> x;
      cout << "y: ";
      int y;
      cin >> y;
      int where = (x - 1) * 3 + (y - 1);
      int ret = scheduler(where);
      if (ret != 0) {
        cout << "That place is not empty!" << endl;
      }
    } else {
      cout << "Player " << now_player << endl;
      auto t = ai(map, now_player, 2);
      print_tree(t);
      scheduler(get_best_move(t));
    }
    output_map(map);
  }
}
