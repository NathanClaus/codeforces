#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

struct Point2D {
  long long xx, yy;
  
  Point2D(long long x,long long y) {
    xx = x;
    yy = y;
  }

  Point2D() {
    xx = yy = 0;
  }

  long double dist(const Point2D& other) const {
    return sqrt((xx - other.xx)*(xx - other.xx) + (yy - other.yy)*(yy - other.yy));
  }

  long long dist_manhat(const Point2D& other) const {
    return abs(xx - other.xx) + abs(yy - other.yy);
  }

  long long dot_prod(Point2D other) const {
    return xx * other.xx + yy * other.yy;
  }

  Point2D operator+(Point2D other) const {
    return Point2D(xx + other.xx, yy + other.yy);
  }
  void operator+=(Point2D other) {
    xx += other.xx;
    yy += other.yy;
  }

  Point2D operator-(Point2D other) const {
    return Point2D(xx - other.xx, yy - other.yy);
  }
  void operator-=(Point2D other) {
    xx -= other.xx;
    yy -= other.yy;
  }

  Point2D operator*(long long scale) const {
    return Point2D(xx * scale, yy * scale);
  }
  void operator*=(long long scale) {
    xx *= scale;
    yy *= scale;
  }

  bool operator==(Point2D other) const {
    if(xx == other.xx && yy == other.yy) return true;
    else return false;
  }
  bool operator!=(Point2D other) const {
    if(xx == other.xx && yy == other.yy) return true;
    else return false;
  }
};

int main(int argc, char** argv) {

  long long radius, ax, ay, bx, by;
  cin >> radius >> ax >> ay >> bx >> by;
  double dist = Point2D(ax, ay).dist(Point2D(bx, by));
  long long num = (long long)ceil(dist / (2.0 * radius));

  cout << num << endl;
  
  return 0;
}