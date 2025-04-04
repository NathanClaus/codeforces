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
    long long x,y,a;
    cin >> x >> y >> a;
    long long total = x + y;
    long long mod = (a + 1) % total;
    if(mod == 0) mod = total;
    if(mod <= x) cout << "NO" << endl;
    else cout << "YES" << endl;
  }

  return 0;
}