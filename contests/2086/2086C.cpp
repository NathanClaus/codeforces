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
    int A[N], spot[N + 1];
    for(int i = 0; i < N; i++) {
      cin >> A[i];
      spot[A[i]] = i;
    }
    int d[N];
    for(int idx = 0; idx < N; idx++) {
      cin >> d[idx];
    }
    int replaced[N];
    memset(replaced, 0, sizeof(replaced));
    int answers[N];
    int rolling_answer = 0;
    for(int idx = 0; idx < N; idx++) {
      int perm_spot = d[idx] - 1;
      while(true) {
        if(replaced[perm_spot] == 1) break;
        replaced[perm_spot] = 1;
        rolling_answer++;
        //deb(A[perm_spot]);
        perm_spot = spot[A[A[perm_spot]-1]];
      }
      answers[idx] = rolling_answer;
    }
    for(int idx = 0; idx < N; idx++) {
      cout << answers[idx] << ' ';
    }
    cout << endl;
  }

  return 0;
}