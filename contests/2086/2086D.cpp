#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

const int MAXSUM = 5e5 / 2 + 1;
const int MAXN = 26;
const int MOD = 998244353;

long long modInverse(long long a, long long m) {
    long long m0 = m;
    long long y = 0, x = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

// Function to calculate nCr % mod
map<pair<long long, long long>, long long> memoNCR;
long long nCr(long long n, long long r, long long mod) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;  // Take advantage of symmetry
    if(memoNCR.find(make_pair(n, r)) != memoNCR.end()) return memoNCR[make_pair(n, r)];
    long long num = 1, den = 1;
    for (long long i = 0; i < r; i++) {
        num = (num * (n - i)) % mod;
        den = (den * (i + 1)) % mod;
    }
    long long ans = (num * modInverse(den, mod)) % mod;
    memoNCR[make_pair(n, r)] = ans;
    return ans;
}



// long long rec(int idx, long long in_sum, long long out_sum) {
//   long long & ans = memo[idx][in_sum];
//   if(ans != -1) return ans;
//   if(in_sum == 0 && out_sum == 0) {
//     return ans = 1;
//   }
//   if(idx == 26) return ans = 0;
//   ans = 0;
//   if(counts[idx] == 0) {
//     return ans = rec(idx + 1, in_sum, out_sum);
//   }
//   if(in_sum >= counts[idx]) {
//     long long base = nCr(in_sum, counts[idx], MOD);
//     ans += base * rec(idx + 1, in_sum - counts[idx], out_sum) % MOD;
//     ans %= MOD;
//   }
//   if(out_sum >= counts[idx]) {
//     long long base = nCr(out_sum, counts[idx], MOD);
//     ans += base * rec(idx + 1, in_sum, out_sum - counts[idx]) % MOD;
//     ans %= MOD;
//   }
//   //cout << "( " << idx << "," << in_sum << ", " << out_sum << ") :" << ans << endl;
//   return ans;
// }


int main(int argc, char** argv) {

  int NUM_TESTS = 0;
  cin >> NUM_TESTS;
  for(int test_idx = 0; test_idx < NUM_TESTS; test_idx++) {
    long long total_sum = 0;
    vector<long long> counts(26, 0);
    for(int idx = 0; idx < 26; idx++) {
      cin >> counts[idx];
      total_sum += counts[idx];
    }
    sort(counts.begin(), counts.end());
    reverse(counts.begin(), counts.end());

    long long half_sum = total_sum / 2;
    long long left = total_sum - half_sum;

    long long running_sum = 0;
    long long splits[2][MAXSUM + 1];
    memset(splits, 0, sizeof(splits));
    splits[0][half_sum] = 1;
    set<long long> valid;
    valid.insert(half_sum);
    for(int idx = 0; idx < 26; idx++) {
      set<long long> next_valid;
      if(counts[idx] == 0) break;
      for(long long prev_sum : valid) {
        if(splits[0][prev_sum] == 0) continue;

        if(counts[idx] <= prev_sum) {
          long long in_half = nCr(prev_sum, counts[idx], MOD);
          long long increment = (splits[0][prev_sum] * in_half) % MOD;
          splits[1][prev_sum - counts[idx]] += increment;
          splits[1][prev_sum - counts[idx]] %= MOD;
          next_valid.insert(prev_sum - counts[idx]);
        }

        long long out_sum = total_sum - prev_sum - running_sum;
        if(counts[idx] <= out_sum) {
          long long out_half = nCr(out_sum, counts[idx], MOD);
          long long increment = (splits[0][prev_sum] * out_half) % MOD;

          splits[1][prev_sum] = (splits[1][prev_sum] + increment) % MOD;
          next_valid.insert(prev_sum);
        }
      }
      memcpy(splits[0], splits[1], sizeof(splits[1]));
      memset(splits[1], 0, sizeof(splits[1]));
      running_sum += counts[idx];
      valid = next_valid;
    }
    cout << splits[0][0] << endl;
    //cout << rec(0, half_sum, left) << endl;
  }

  return 0;
}