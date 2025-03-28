#include <bits/stdc++.h>
#include <ranges>
using namespace std;

typedef vector < string > vs;
typedef vector <int> vi;
#define FOREACH(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define deb(x) cout << #x << ": " << x << endl;
#define debv(x) cout << #x << ": "; for(int i = 0; i < (x).size(); i++) cout << x[i] << ' '; cout << endl;

ostream& operator<<(ostream& os, const pair<int,int>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

vs csv_split(string a, string delim=",") {
  vs ret;
  string cr = "";
  for(int i = 0; i < a.size(); i++)
  {
    if(delim.find(a[i])==string::npos) cr += a[i];
    else if(a[i] == '\n') break;
    else { ret.push_back(cr); cr = ""; }
  }
  ret.push_back(cr);
  return ret;
}

vs strsp(string a, string delim=" ") {
  vs ret;
  string cr = "";
  for(int i = 0; i < a.size(); i++)
  {
    if(delim.find(a[i])==string::npos) cr += a[i];
    else { if(cr.size()) ret.push_back(cr); cr = ""; }
  }
  if(cr.size()) ret.push_back(cr);
  return ret;
}

vs grp_in_read(string sep=" ", string group_sep="\n") {
  vs ret;
  string current_group = "", line = "";
  while(std::getline(cin, line)) {
    if(line.size() == 0 || line == group_sep) {
      ret.push_back(current_group);
      current_group = "";
    }
    else {
      if(current_group.size() > 0) {
        current_group += sep + line;
      }
      else {
        current_group = line;
      }
    }
  }
  if(current_group.size() > 0) ret.push_back(current_group);
  return ret;
}

vector<long long> extract_numbers(string line, string delim=" ") {
  vs words = strsp(line, delim);
  vector<long long> ret;
  long long temp;
  for(string s: words) {
    if(stringstream(s) >> temp)
      ret.push_back(temp);
  }
  return ret;
}



vi extract_ints(string line, string delim=" ") {
  vs words = strsp(line, delim);
  vi ret;
  int temp;
  for(string s: words) {
    if(stringstream(s) >> temp)
      ret.push_back(temp);
  }
  return ret;
}

vector<long long> extract_lls(string line, string delim=" ") {
  vs words = strsp(line, delim);
  vector<long long> ret;
  long long temp;
  for(string s: words) {
    if(stringstream(s) >> temp)
      ret.push_back(temp);
  }
  return ret;
}

template<typename T> vector<T> extract_tokens(string line, string delim=" ") {
  vs words = strsp(line, delim);
  vector<T> ret;
  T temp;
  for(string s: words) {
    if(stringstream(s) >> temp)
      ret.push_back(temp);
  }
  return ret;
}

int string_to_num(string word) {
  int temp = -1;
  if(stringstream(word) >> temp)
    return temp;
  else {
    cout << "Error converting string to num: " << word << "\n";
    return temp;
  }
}

vi extract_all_ints(string delim=" ") {
  vi ret;
  string line = "";
  while(std::getline(cin, line)) {
    vi line_ints = extract_ints(line, delim);
    ret.insert(ret.end(), line_ints.begin(), line_ints.end());
  }
  return ret;
}

vector< vi > extract_int_lines(string delim = " ") {
  vector< vi > ret;
  string line = "";
  while(std::getline(cin, line)) {
    vi line_ints = extract_ints(line, delim);
    ret.push_back( line_ints );
  }
  return ret;
}

vector< string > extract_string_lines(string delim = " ") {
  vector< string > ret;
  string line = "";
  while(std::getline(cin, line)) {
    ret.push_back( line );
  }
  return ret;
}

vector< vector< long long>  > extract_ll_lines(string delim = " ") {
  vector< vector< long long> > ret;
  string line = "";
  while(std::getline(cin, line)) {
    vector<long long> line_ints = extract_lls(line, delim);
    ret.push_back( line_ints );
  }
  return ret;
}

template<typename T> vector< vector<T> > extract_token_lines(string delim = " ") {
  vector< vector< T> > ret;
  string line = "";
  while(std::getline(cin, line)) {
    vector<T> line_ints = extract_tokens<T>(line, delim);
    ret.push_back( line_ints );
  }
  return ret;
}

vs extract_atoms(string line, string delim=" ") {
  vs atoms = strsp(line, delim);
  return atoms;
}

vs extract_all_atoms(string delim=" ") {
  vs ret;
  string line = "";
  while(std::getline(cin, line)) {
    
    vs line_atoms = extract_atoms(line, delim);
    ret.insert(ret.end(), line_atoms.begin(), line_atoms.end());
  }
  return ret;
}

vs extract_words(string line, string delim=" ") {
  vs words = strsp(line, delim);
  vs ret;
  int temp;
  for(string s: words) {
    if(stringstream(s) >> temp)
      temp = 0;
    else
      ret.push_back(s);
  }
  return ret;
}

vs extract_all_words(string delim=" ") {
  vs ret;
  string line = "";
  while(std::getline(cin, line)) {
    vs line_words = extract_words(line, delim);
    ret.insert(ret.end(), line_words.begin(), line_words.end());
  }
  return ret;
}

inline bool is_set_bit(long long N, int bit) {
  return (N&(1LL<<bit)) > 0 ? true : false;
}

inline int bitcount(long long N) {
  return N > 0 ? 1+bitcount(N&(N-1)) : 0;
}

int bit_string_to_num(string bits)
{
  int ret = 0;
  for(int idx = 0; idx < bits.size(); idx++)
    ret = 2*ret + (bits[idx] - '0');
  return ret;
}

vi bit_strings_to_nums(vs bit_strings)
{
  vi ret;
  for(int idx = 0; idx < bit_strings.size(); idx++)
  {
    ret.push_back(bit_string_to_num(bit_strings[idx]));
  }
  return ret;
}

template <typename T, typename Pred>
auto Filter(const std::vector<T>& vec, Pred p) {
    std::vector<T> out;
    for (auto&& elem : vec)
        if (p(elem))
            out.push_back(elem);
    return out;
}

template<typename T>
void write_answer_AOC(T answer) {
  ofstream fout("./aoc.out");
  fout << answer << endl;
}


namespace Geometry {
  struct Point3D {
    long long xx, yy, zz;
    
    Point3D(long long x,long long y,long long z) {
      xx = x;
      yy = y;
      zz = z;
    }

    Point3D() {
      xx = yy = zz = 0;
    }

    long double dist(const Point3D& other) const {
      return sqrt((xx - other.xx)*(xx - other.xx) + (yy - other.yy)*(yy - other.yy) + (zz - other.zz)*(zz - other.zz));
    }

    long long dist_manhat(const Point3D& other) const {
      return abs(xx - other.xx) + abs(yy - other.yy) + abs(zz - other.zz);
    }

    long long dot_prod(Point3D other) const {
      return xx * other.xx + yy * other.yy + zz * other.zz;
    }

    Point3D operator+(Point3D other) const {
      return Point3D(xx + other.xx, yy + other.yy, zz + other.zz);
    }
    void operator+=(Point3D other) {
      xx += other.xx;
      yy += other.yy;
      zz += other.zz;
    }

    Point3D operator-(Point3D other) const {
      return Point3D(xx - other.xx, yy - other.yy, zz - other.zz);
    }
    void operator-=(Point3D other) {
      xx -= other.xx;
      yy -= other.yy;
      zz -= other.zz;
    }

    Point3D operator*(long long scale) const {
      return Point3D(xx * scale, yy * scale, zz * scale);
    }
    void operator*=(long long scale) {
      xx *= scale;
      yy *= scale;
      zz *= scale;
    }

    bool operator==(Point3D other) const {
      if(xx == other.xx && yy == other.yy && zz == other.zz) return true;
      else return false;
    }
    bool operator!=(Point3D other) const {
      if(xx == other.xx && yy == other.yy && zz == other.zz) return true;
      else return false;
    }
  };

  ostream& operator<<(ostream& os, const Point3D& p) {
    return os << "(" << p.xx << ", " << p.yy << ", " << p.zz << ")";
  }

  

  struct Point2D {
    long double xx, yy;

    Point2D(long double x,long double y) {
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

    Point2D rotate_about_point_radians(const Point2D& point, long double angle) {
      if(xx == point.xx && yy == point.yy) return *this;

      long double current_angle = atan2(yy - point.yy, xx - point.xx);
      long double radius = dist(point);
      long double cos_theta = cos(angle + current_angle);
      long double sin_theta = sin(angle + current_angle);
      long double new_x = point.xx + radius * cos_theta;
      long double new_y = point.yy + radius * sin_theta;
      return Point2D(new_x, new_y);
    }
  };

  ostream& operator<<(ostream& os, const Point2D& p) {
    return os << "(" << p.xx << ", " << p.yy << ")";
  }


  /**
   * Rotates a square bitmask 90 degrees clockwise.
   * 
   * The function interprets the bitmask as a square grid of size x size,
   * where each bit represents a cell in the grid. It then rotates this grid
   * 90 degrees clockwise and returns the resulting bitmask.
   * 
   * @param mask The original bitmask to rotate
   * @param size The side length of the square grid
   * @return The rotated bitmask
   */
  long long rotate_bitmask(long long mask, int size) {
    long long rotated_mask = 0;
    for(long long r = 0; r < size; r++) {
      for(long long c = 0; c < size; c++) {
        int bit = r*size+c;
        int rotated_bit = (c)*size + (size-1-r);
        if( is_set_bit(mask, bit) ) rotated_mask += (1LL<<rotated_bit);
      }
    }
    return rotated_mask;
  }

  long long flip_vert_bitmask(long long mask, int size) {
    long long flipped_mask = 0;
    for(long long r = 0; r < size; r++) {
      for(long long c = 0; c < size; c++) {
        int bit = r*size+c;
        int flipped_bit = (size-1-r)*size+c;;
        if( is_set_bit(mask, bit) ) flipped_mask += (1LL<<flipped_bit);
      }
    }
    return flipped_mask;
  }

  long long flip_horz_bitmask(long long mask, int size) {
    long long flipped_mask = 0;
    for(long long r = 0; r < size; r++) {
      for(long long c = 0; c < size; c++) {
        int bit = r*size+c;
        int flipped_bit = r*size+(size-1-c);
        if( is_set_bit(mask, bit) ) flipped_mask += (1LL<<flipped_bit);
      }
    }
    return flipped_mask;
  }
}

struct EdgeGraph {
  const int EGINF = 1e9;
  int num_nodes;
  map<int, vector<pair<int, int> > > edge_map;
  map<pair<int,int>, int> cost_map;
  EdgeGraph() {
    num_nodes = 0;
  }

  EdgeGraph(int N) {
    num_nodes = N;
  }

  EdgeGraph(vector<pair<int,int> > init_edges, int same_cost=1, bool bidirectional=true, bool overwrite=true) {
    int min_node = EGINF, max_node = 0;
    for (int i = 0; i < init_edges.size(); ++i) {
      max_node = max(max_node, max(init_edges[i].first, init_edges[i].second));
      min_node = min(min_node, min(init_edges[i].first, init_edges[i].second));
    }
    if(min_node < 0) {
      deb("ERROR CONSTRUCTING EdgeGraph");
      return;
    }
    num_nodes = max_node;
    for (int i = 0; i < init_edges.size(); ++i)
    {
      int start_node = init_edges[i].first, end_node = init_edges[i].second;
      add_edge(start_node, end_node, same_cost, bidirectional, overwrite);
    }
  }

  EdgeGraph(vector<std::tuple<int,int, int> > init_edges_with_cost, bool bidirectional=true, bool overwrite=true) {
    int min_node = EGINF, max_node = 0;
    for (int i = 0; i < init_edges_with_cost.size(); ++i) {
      max_node = max(max_node, max(std::get<0>(init_edges_with_cost[i]), std::get<1>(init_edges_with_cost[i])));
      min_node = min(min_node, min(std::get<0>(init_edges_with_cost[i]), std::get<1>(init_edges_with_cost[i])));
    }
    if(min_node < 0) {
      deb("ERROR CONSTRUCTING EdgeGraph");
      return;
    }
    num_nodes = max_node;
    for (int i = 0; i < init_edges_with_cost.size(); ++i)
    {
      int start_node = std::get<0>(init_edges_with_cost[i]);
      int end_node = std::get<1>(init_edges_with_cost[i]);
      int cost = std::get<2>(init_edges_with_cost[i]);
      add_edge(start_node, end_node, cost, bidirectional, overwrite);
    }
  }

  void add_edge(int start_node, int end_node, int cost=1, bool bidirectional=true, bool overwrite=true) {
    if(start_node >= num_nodes || end_node >= num_nodes) {
      num_nodes = max(start_node, end_node) + 1;
    }

    pair<int,int> cost_map_key = make_pair(start_node, end_node);
    if(edge_map.find(start_node) == edge_map.end()) {
      edge_map[start_node] = vector<pair<int,int> >(1, make_pair(end_node, cost));
      cost_map[cost_map_key] = cost;
    }
    else {
      if(cost_map.find(cost_map_key) != cost_map.end()) {
        if(!overwrite) return;
        for(int jdx = 0; jdx < edge_map[start_node].size(); jdx++) {
          if(edge_map[start_node][jdx].first == end_node) {
            edge_map[start_node][jdx].second = cost;
          }
        }
        cost_map[cost_map_key] = cost;
      }
      else {
        edge_map[start_node].push_back(make_pair(end_node, cost));
        cost_map[cost_map_key] = cost;
      }
    }
    if(bidirectional) {
      add_edge(end_node, start_node, cost, false, overwrite);
    }
  }

  int get_dist(int start_node, int end_node) {
    if(start_node < 0 || end_node < 0 || start_node >= num_nodes || end_node >= num_nodes) return -1;
    if(start_node == end_node) return 0;

    int graph_dist[num_nodes];
    for(int idx = 0; idx < num_nodes; idx++) {
      graph_dist[idx] = EGINF;
    }
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
    graph_dist[start_node] = 0;
    pq.push(make_pair(0, start_node));

    pair<int,int> qfront;
    int cnode, ccost, nnode, ncost;
    while(pq.empty() == false) {
      qfront = pq.top();
      ccost = qfront.first;
      cnode = qfront.second;
      pq.pop();
      if(graph_dist[cnode] < ccost) continue;
      if(cnode == end_node) return ccost;

      for(int idx = 0; idx < edge_map[cnode].size(); ++idx) {
        nnode = edge_map[cnode][idx].first;
        ncost = ccost + edge_map[cnode][idx].second;
        if(graph_dist[nnode] > ncost) {
          graph_dist[nnode] = ncost;
          pq.push(make_pair(ncost, nnode));
        }
      }
    }
      
    return -1;
  }

  vector<int> get_dists(int start_node) {
    
    vector<int> graph_dist(num_nodes, EGINF);
    if(start_node < 0 || start_node >= num_nodes) return graph_dist;

    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
    graph_dist[start_node] = 0;
    pq.push(make_pair(0, start_node));

    pair<int,int> qfront;
    int cnode, ccost, nnode, ncost;
    while(pq.empty() == false) {
      qfront = pq.top();
      ccost = qfront.first;
      cnode = qfront.second;
      pq.pop();
      if(graph_dist[cnode] < ccost) continue;

      for(int idx = 0; idx < edge_map[cnode].size(); ++idx) {
        nnode = edge_map[cnode][idx].first;
        ncost = ccost + edge_map[cnode][idx].second;
        if(graph_dist[nnode] > ncost) {
          graph_dist[nnode] = ncost;
          pq.push(make_pair(ncost, nnode));
        }
      }
    }
      
    return graph_dist;
  }
};


namespace Maps {

  const int deltay[] = {-1, 0, 1, 0};
  const int deltax[] = {0, 1, 0, -1};
  const string deltachars = "NESW";

  bool inbounds(int r, int c, int R, int C) {
    if(r < 0 || c < 0 || r >= R || c >= C) return false;
    else return true;
  }

  struct Grid2D {
    int rows, cols;
    vector< vector<int> > grid;

    Grid2D() {
      rows = 0, cols = 0;
    }

    Grid2D(int R, int C)
      :rows{R}, cols{C}, grid{vector< vector<int> >(R, vector<int>(C, 0))} { }

    Grid2D(const vector<string> string_grid, map<char, int> dict) {
      rows = string_grid.size();
      cols = string_grid[0].size();
      for(int idx = 0; idx < rows; idx++) {
        vector<int> grid_row(cols, 0);
        for(int jdx = 0; jdx < cols; jdx++) {
          if(dict.find(string_grid[idx][jdx]) == dict.end()) {
            cout << "ERROR parsing string grid\n";
            return;
          }
          else {
            grid_row[jdx] = dict[string_grid[idx][jdx]];
          }
        }
        grid.push_back(grid_row);
      }
    }

    vector<int>& operator[](int row) {
      return grid[row];
    }

    const vector<int>& operator[](int row) const {
      return grid[row];
    }

    void print_dimensions(ostream& os) const {
      os << "Dimensions for grid: (" << rows << ", " << cols << ")" << endl;
    }

    bool is_on_grid(int R, int C) const {
      if(R < 0 || C < 0 || R >= rows || C >= cols) return false;
      return true;
    }

    int get_total_groups(int in_group_val) const {
      if(rows == 0 || cols == 0) return 0;
      
      bool marked[rows][cols];
      memset(marked, false, sizeof(marked));
      queue<pair<int,int> > Q;
      
      int total = 0, nr, nc;
      for(int rr = 0; rr < rows; rr++) {
        for(int cc = 0; cc < cols; cc++) {
          if(marked[rr][cc] || grid[rr][cc] != in_group_val) continue;
          total += 1;
          marked[rr][cc] = true;
          Q.push(make_pair(rr,cc));

          while(Q.empty() == false) {
            pair<int,int> cpos = Q.front();
            Q.pop();
            for(int dir = 0; dir < 4; dir++) {
              nr = cpos.first + deltay[dir];
              nc = cpos.second + deltax[dir];
              
              if(is_on_grid(nr, nc) 
                && (grid[nr][nc] == in_group_val) 
                && !marked[nr][nc]) 
              {
                marked[nr][nc] = true;
                Q.push(make_pair(nr,nc));
              }
            }
          }

        }
      }
      return total;
    }


    vector<vector<int> > get_groups(int in_group_val) const {

      vector< vector<int> > groups = vector< vector<int> >(rows, vector<int>(cols, -1));
      if(rows == 0 || cols == 0) return groups;
      bool marked[rows][cols];
      memset(marked, false, sizeof(marked));
      queue<pair<int,int> > Q;
      
      int total = 0, nr, nc;
      for(int rr = 0; rr < rows; rr++) {
        for(int cc = 0; cc < rows; cc++) {
          if(marked[rr][cc] || grid[rr][cc] != in_group_val) continue;
          total += 1;
          marked[rr][cc] = true;
          groups[rr][cc] = total-1;
          Q.push(make_pair(rr,cc));

          while(Q.empty() == false) {
            pair<int,int> cpos = Q.front();
            Q.pop();
            for(int dir = 0; dir < 4; dir++) {
              nr = cpos.first + deltay[dir];
              nc = cpos.second + deltax[dir];
              
              if(is_on_grid(nr, nc) 
                && (grid[nr][nc] == in_group_val) 
                && !marked[nr][nc]) 
              {
                marked[nr][nc] = true;
                groups[nr][nc] = total - 1;
                Q.push(make_pair(nr,nc));
              }
            }
          }

        }
      }
      return groups;
    }

    int get_dist(int start_row, int start_col, int end_row, int end_col, int invalid_val) {
      if(rows == 0 || cols == 0) return -1;
      if(!is_on_grid(start_row, start_col) || !is_on_grid(end_row, end_col)) return -1;
      if(start_row == end_row && start_col == end_col) return 0;
      int grid_dist[rows][cols];
      for(int rr = 0; rr < rows; rr++) {
        for(int cc = 0; cc < cols; cc++) {
          grid_dist[rr][cc] = -1;
        }
      }
      queue<pair<int,int> > Q;
      grid_dist[start_row][start_col] = 0;
      Q.push(make_pair(start_row,start_col));
      int nr, nc;
      while(Q.empty() == false) {
        pair<int,int> cpos = Q.front();
        Q.pop();
        if(cpos.first == end_row && cpos.second == end_col) break;
        for(int dir = 0; dir < 4; dir++) {
          nr = cpos.first + deltay[dir];
          nc = cpos.second + deltax[dir];
          
          if(is_on_grid(nr, nc) 
            && (grid[nr][nc] != invalid_val) 
            && grid_dist[nr][nc] == -1) 
          {
            grid_dist[nr][nc] = grid_dist[cpos.first][cpos.second] + 1;
            Q.push(make_pair(nr,nc));
          }
        }
      }
      
      return grid_dist[end_row][end_col];
    }
  };
}

typedef vector< vector<long long> > Matrix;

Matrix make_identity_Matrix(int N) {
  Matrix ret = Matrix(N, vector<long long>(N, 0));
  for(int i = 0; i < N; ++i) {
    ret[i][i] = 1;
  }
  return ret;
}

Matrix make_zero_Matrix(int R, int C) {
  return Matrix(R, vector<long long>(C, 0));
}

void read_in_Matrix(Matrix& a) {
  for(int r = 0; r < a.size(); ++r) {
    for (int c = 0; c < a[r].size(); ++c)
    {
      cin >> a[r][c];
    }
  }
}

void print_Matrix(const Matrix& a) {
  for (int r = 0; r < a.size(); ++r) {
    for (int c = 0; c < a[r].size(); ++c)
    {
      cout << a[r][c] << " ";
    }
    cout << endl;
  }
}

Matrix multiply_Matrix(const Matrix& a, const Matrix& b, bool modded = false, long long modulus = 1) {
  if(a[0].size() != b.size()) {
    cout << "ERROR: Bad Matrix mult\n";
    return a;
  }
  int innersize = a[0].size(), retR = a.size(), retC = b[0].size();
  Matrix ret(retR, vector<long long>(retC, 0));

  for(int r = 0; r < retR; ++r) {
    for(int c = 0; c < retC; ++c) {
      for(int j = 0; j < innersize; ++j) {
        ret[r][c] += a[r][j] * b[j][c];
        if(modded) ret[r][c] %= modulus;
      }
    }
  }

  return ret;
}

Matrix exp_Matrix(const Matrix& a, long long pow, bool modded = false, long long modulus = 1) {
  long long N = a.size();
  if(a[0].size() != N) {
    cout << "ERROR: Bad Matrix mult\n";
    return a;
  }
  Matrix ret = make_identity_Matrix(N);
  Matrix expMatrix = a;
  while(pow > 0) {
    if((pow&1) > 0) ret = multiply_Matrix(ret, expMatrix, modded, modulus);
    pow = (pow >> 1);
    expMatrix = multiply_Matrix(expMatrix, expMatrix, modded, modulus);
  }

  return ret;
}