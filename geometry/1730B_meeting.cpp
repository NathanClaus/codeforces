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
    int N;
    cin >> N;
    vector<long double> positions(N), times(N);
    for(int i = 0; i < N; i++) {
      cin >> positions[i];
    }
    long double min_time = 0, max_time = 1e11;
    for(int i = 0; i < N; i++) {
      cin >> times[i];
      min_time = max(min_time, times[i] - 1e-10);
    }
    long double mid_time, min_left, max_right, next_left, next_right;
    while( (max_time - min_time) > 1e-8 ) {
      mid_time = (min_time + max_time) / 2;
      min_left = -1e11, max_right = 1e11;
      for(int i = 0; i < positions.size(); i++) {
        next_left = positions[i] - mid_time + times[i];
        next_right = positions[i] + mid_time - times[i];
        min_left = max(min_left, next_left);
        max_right = min(max_right, next_right);
        if(min_left > max_right) {
          break;
        }
      }
      if(min_left <= max_right) {
        max_time = mid_time;
      } else {
        min_time = mid_time;
      }
    }
    min_left = -1e11, max_right = 1e11;
    for(int i = 0; i < positions.size(); i++) {
      next_left = positions[i] - max_time + times[i];
      next_right = positions[i] + max_time - times[i];
      min_left = max(min_left, next_left);
      max_right = min(max_right, next_right);
    }
    cout << std::setprecision(9) << (min_left + max_right) / 2 << endl;
  }

  return 0;
}