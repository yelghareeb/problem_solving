/*
	UVA 10511 - Councilling
	Idea: Network Flows
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1452
	
	We will build a network of 3 layers + 2 nodes for source/destination:
	  - Layer 1: one node per club. Each node will be connected to source with edge = 1
	  - Layer 2: one node per player. Each node from layer 1 will be connected with edge = 1 if player belongs to club
	  - Layer 3: one node per party. Each node from layer 2 will be connected with edge = 1 if player belongs to party
	all nodes of layer 3 will be connected to sink with edge = (clubs - 1) / 2
	Run the max flow from source to sink. If the max flow = # of clubs, then we have an answer.
	
	Author: Yosusef Elghareeb
*/

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <assert.h>
#include <cstring>
#include <algorithm>
#include <climits>
#include <sstream>

using namespace std;

typedef long long LL;
typedef vector<int> vi;
#define loop(i,n) for(int i = 0; i < n; i++)

const int N = 2 * 1e2 + 10;
const int INF = 1e9;

class Ford_Fulkerson {
  // Pass an adjacency matrix to this class
  vector<vi> residual;
  vector<vi> network;
  vi path, vis;
  map<pair<int, int>, int > edges;
  int get_path(int src, int sink, int min_cost = INT_MAX) {
    path.push_back(src);
    if (src == sink) {
      return min_cost;
    }
    int res = 0;
    vis[src] = 1;
    for (int j = 0; j < residual.size(); j++) {
      if (vis[j] || residual[src][j] <= 0) continue;
      res = get_path(j, sink, min(min_cost, residual[src][j]));
      if (res) break;
      else path.pop_back();
    }
    return res;
  }
public:
  Ford_Fulkerson(vector<vi> network) {
    this->network = network;
  }
  int get_max_flow(int src, int sink) {
    residual = network;
    int max_flow = 0, cur_flow;
    vis = vector<int>(residual.size(), 0);
    while ((cur_flow = get_path(src, sink))) {
      max_flow += cur_flow;
      for (int i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        residual[u][v] -= cur_flow;
        residual[v][u] += cur_flow;
        edges[make_pair(u, v)]++;
        edges[make_pair(v, u)]--;
      }
      vis = vector<int>(residual.size(), 0);
      path.clear();
    }
    return max_flow;
  }
  vi get_rel(int node) {
    vi res;
    for (int j = 0; j < network.size(); j++) {
      if (edges.count(make_pair(j, node)) && edges[make_pair(j, node)] > 0) res.push_back(j);
    }
    return res;
  }
};

struct Record {
  string player, party;
  vector<string> clubs;
};

int main () {
  int t;
  cin >> t;
  string line;
  loop(j, 2) getline(cin, line);
  for (int test = 0; test < t; test++) {
    if (test) cout << endl;
    map<string, int> players_id, party_id, club_id;
    map<int, string> players_of, party_of, club_of;
    int players_cnt = 0, party_cnt = 0, club_cnt = 0;
    vector<Record> records;
    while (getline(cin, line)) {
      if (line.empty()) {
        break;
      }
      istringstream is(line);
      string player, party, cl;
      set<string> sclubs;
      vector<string> clubs;
      is >> player >> party;
      while (is >> cl) sclubs.insert(cl);
      clubs = vector<string>(sclubs.begin(), sclubs.end());
      if (!players_id.count(player)) {
        players_id[player] = players_cnt++;
        players_of[players_cnt - 1] = player;
      }
      if (!party_id.count(party)) {
        party_id[party] = party_cnt++;
        party_of[party_cnt - 1] = party;
      }
      loop(j, clubs.size()) {
        if (!club_id.count(clubs[j])) {
          club_id[clubs[j]] = club_cnt++;
          club_of[club_cnt - 1] = clubs[j];
        }
      }
      Record r;
      r.player = player;
      r.party = party;
      r.clubs = clubs;
      records.push_back(r);
    }
    int all = 2 + players_cnt + club_cnt + party_cnt;
    vector<vi> network(all);
    loop(i, all) network[i] = vi(all, 0);
    for (int i = 1; i <= club_cnt; i++) network[0][i] = 1;
    int n1 = 1;
    int n2 = 1 + club_cnt;
    int n3 = n2 + players_cnt;
    for (int i = 0; i < records.size(); i++) {
      Record& rec = records[i];
      int p_id = players_id[rec.player];
      int par_id = party_id[rec.party];
      for (int j = 0; j < rec.clubs.size(); j++) {
        int c_id = club_id[rec.clubs[j]];
        network[c_id + n1][p_id + n2]++;
        assert(network[c_id + n1][p_id + n2] == 1);
      }
      network[p_id + n2][n3 + par_id]++;
      assert(network[p_id + n2][n3 + par_id] == 1);
    }
    for (int i = 0; i < party_cnt; i++) network[n3 + i][all - 1] = (club_cnt - 1) / 2;
    Ford_Fulkerson ford(network);
    int flow = ford.get_max_flow(0, all - 1);
    if (flow == club_cnt) {
      for (int i = 0; i < players_cnt; i++) {
        vi club = ford.get_rel(i + n2);
        if (club.empty()) continue;
        assert(club.size() == 1);
        cout << players_of[i] << " " << club_of[club[0] - 1] << endl;
      }
    }
    else {
      cout << "Impossible." << endl;
    }
  }
  return 0;
}
