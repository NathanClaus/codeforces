#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

int main(int argc, char** argv) {
  
  int NUM_TESTS = 0;
  cin >> NUM_TESTS;
  int target_y = 1, target_x = 1;
  const int deltay[] = {-1, 0, 1, 0};
  const int deltax[] = {0, 1, 0, -1};
  map<char,int> move_map;
  move_map['D'] = 0;
  move_map['R'] = 1;
  move_map['U'] = 2;
  move_map['L'] = 3;

  for(int test_idx = 0; test_idx < NUM_TESTS; test_idx++) {
    int num_inst = 0, cy = 0, cx = 0;
    bool hit = false;
    cin >> num_inst;
    string input = "";
    cin >> input;
    for(char move : input) {
      int move_dir = move_map[move];
      cy += deltay[move_dir];
      cx += deltax[move_dir];
      if (cy == target_y && cx == target_x) {
        hit = true;
        break;
      }
    }

    if(hit) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}