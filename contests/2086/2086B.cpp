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
    long long n,k,x;
    cin >> n >> k >> x;
    long long A[n];
    long long single_sum = 0, total_sum = 0;
    for(int i = 0; i < n; i++) {
      cin >> A[i];
      single_sum += A[i];
    }
    total_sum = single_sum * k;
    long long ans = 0;
    long long needed_seqs = (x + single_sum - 1) / single_sum;
    if(needed_seqs > k) {
      cout << 0 << endl;
      continue;
    }
    ans += (k - needed_seqs) * n + 1;
    long long rolling_sum = needed_seqs * single_sum;
    for(int idx = 0; idx < n; idx++) {
      rolling_sum -= A[idx];
      if(rolling_sum >= x) {
        ans++;
      }
      else break;
    }
    cout << ans << endl;

    
  }

  return 0;
}