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
    long long n, cardboard;
    cin >> n >> cardboard;
    vector<long long> sides(n, 0);
    for(int idx = 0; idx < n; idx++) {
      cin >> sides[idx];
    }
    long long binary_min = 0, binary_max = sqrt(cardboard) + 1;
    long long correct = -1;
    while(binary_max > binary_min) {
      long long binary_mid = (binary_max + binary_min) / 2.0;
      long long cnt = 0;
      for(long long side : sides) {
        cnt += (side + 2*binary_mid) * (side + 2*binary_mid);
        if(cnt > cardboard) break;
      }
      if(cnt == cardboard) {
        correct = binary_mid;
        break;
      }
      else if(cnt < cardboard) {
        binary_min = binary_mid + 1;
      }
      else {
        binary_max = binary_mid;
      }
    }
    cout << correct << endl;
  }

  return 0;
}