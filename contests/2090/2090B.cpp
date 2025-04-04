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
  for(int test_idx = 0; test_idx < NUM_TESTS; test_idx++) {
    int n,m;
    cin >> n >> m;
    int grid[n][m];
    for(int i = 0; i < n; i++) {
      string row;
      cin >> row;
      for(int j = 0; j < m; j++) {
        grid[i][j] = row[j] - '0';
      }
    }
    bool ans = true;
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        if(grid[i][j] == 1) {
          if(i == 0 || j == 0) continue;
          bool row_ok = true, col_ok = true;
          for(int k = 0; k < j; k++) {
            if(grid[i][k] != 1) {
              row_ok = false;
              break;
            }
          }
          for(int k = 0; k < i; k++) {
            if(grid[k][j] != 1) {
              col_ok = false;
              break;
            }
          }
          if(row_ok == false && col_ok == false) {
            ans = false;
            break;
          }
        }
      }
    }
    if(ans) cout << "YES" << endl;
    else cout << "NO" << endl;
  }

  return 0;
}