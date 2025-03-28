#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

int deltax[] = {1, 0, -1, 0};
int deltay[] = {0, 1, 0, -1};

bool check_right_triangle(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
  // create vectors and check if the triangle is degenerate 
  pair<int, int> ab = {b.first - a.first, b.second - a.second};
  if(ab.first == 0 && ab.second == 0) {
    return false;
  }
  pair<int, int> ac = {c.first - a.first, c.second - a.second};
  if(ac.first == 0 && ac.second == 0) {
    return false;
  }
  pair<int, int> bc = {c.first - b.first, c.second - b.second};
  if(bc.first == 0 && bc.second == 0) {
    return false;
  }

  if(ab.first * ac.first + ab.second * ac.second == 0) {
    return true;
  }
  if(ac.first * bc.first + ac.second * bc.second == 0) {
    return true;
  }
  if(bc.first * ab.first + bc.second * ab.second == 0) {
    return true;
  }
  return false;
}

int main(int argc, char** argv) {

  vector<pair<int, int>> points(3);
  for(int i = 0; i < 3; i++) {
    cin >> points[i].first >> points[i].second;
  }

  if(check_right_triangle(points[0], points[1], points[2])) {
    cout << "RIGHT" << endl;
    return 0;
  } else {
     for(int i = 0; i < 3; i++) {
      for(int dir = 0; dir < 4; dir++) {
        points[i].first += deltax[dir];
        points[i].second += deltay[dir];
        if(check_right_triangle(points[0], points[1], points[2])) {
          cout << "ALMOST" << endl;
          return 0;
        }
        points[i].first -= deltax[dir];
        points[i].second -= deltay[dir];
      }
     }
  }

  cout << "NEITHER" << endl;
  return 0;
}