#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

typedef pair<int,pair<int,int>> seat;

seat make_seat(int a, int b, int c) {
  return make_pair(a, make_pair(b, c));
}


int main(int argc, char** argv) {

  int NUM_TESTS = 0;
  cin >> NUM_TESTS;
  for(int test_idx = 0; test_idx < NUM_TESTS; test_idx++) {
    int N;
    cin >> N;
    vi A(N);
    for(int i = 0; i < N; i++) {
      cin >> A[i];
    }
    //cout << "Case #" << test_idx + 1 << ":" << endl;
    priority_queue<seat, vector<seat>, greater<seat> > first_seat;
    priority_queue<seat, vector<seat>, greater<seat> > other_seats;
    for(int start_ycoord = 1; ; start_ycoord += 3) {
      if(first_seat.size() >= N) break;
      int ycoord = start_ycoord;
      for(int xcoord = 1; ycoord > 0; ) {
        first_seat.push(make_seat(ycoord + xcoord, xcoord, ycoord));
        ycoord -= 3; 
        xcoord += 3;
      }
    }
    for(int character : A) {
      if(character == 0 || other_seats.size() == 0) {
        seat s = first_seat.top();
        int ycoord = s.second.first, xcoord = s.second.second;
        cout << ycoord << " " << xcoord << endl;
        other_seats.push(make_seat(ycoord + xcoord + 1, xcoord, ycoord + 1));
        other_seats.push(make_seat(ycoord + xcoord + 1, xcoord + 1, ycoord));
        other_seats.push(make_seat(ycoord + xcoord + 4, xcoord + 1, ycoord + 1));
        first_seat.pop();
      }
      else {
        seat empty_table = first_seat.top();
        seat best_full = other_seats.top();
        if(best_full < empty_table) {
          cout << best_full.second.first << " " << best_full.second.second << endl;
          other_seats.pop();
        }
        else {
          int ycoord = empty_table.second.first, xcoord = empty_table.second.second;
          cout << ycoord << " " << xcoord << endl;
          other_seats.push(make_seat(ycoord + xcoord + 1, xcoord, ycoord + 1));
          other_seats.push(make_seat(ycoord + xcoord + 1, xcoord + 1, ycoord));
          other_seats.push(make_seat(ycoord + xcoord + 4, xcoord + 1, ycoord + 1));
          first_seat.pop();
        }
      }
    }
    
  }

  return 0;
}