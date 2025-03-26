#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

int main(int argc, char** argv) {

  int N, lazerx, lazery;
  cin >> N >> lazerx >> lazery;
  vector<pair<int, int>> points(N);
  for(int i = 0; i < N; i++) {
    cin >> points[i].first >> points[i].second;
  }

  int cnt_unique = 0;
  map<pair<int, int>, int> slopes;
  for(int i = 0; i < N; i++) {
    int dx = points[i].first - lazerx;
    int dy = points[i].second - lazery;
    int g = gcd(abs(dx), abs(dy));
    dx /= g;  
    dy /= g;
    if(dy < 0 || (dy == 0 && dx < 0)) {
      dx = -dx;
      dy = -dy;
    }
    if(slopes.find({dx, dy}) == slopes.end()) {
      slopes[{dx, dy}] = 1;
      cnt_unique++;
    } else {
      slopes[{dx, dy}]++;
    }
  } 

  cout << cnt_unique << endl;
  
  return 0;
}