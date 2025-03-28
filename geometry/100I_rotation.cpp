#include <bits/stdc++.h>
#include <ranges>
#include "../coding_library.h"
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

int main(int argc, char** argv) {

  long double angle_degrees, x, y;
  cin >> angle_degrees >> x >> y;
  long double angle_radians = angle_degrees * M_PI / 180.0;
  Geometry::Point2D point(x, y);
  Geometry::Point2D rotated_point = point.rotate_about_point_radians(Geometry::Point2D(0.0, 0.0), angle_radians);
  cout << fixed << setprecision(4) << rotated_point.xx << " " << rotated_point.yy << endl;

  return 0;
}