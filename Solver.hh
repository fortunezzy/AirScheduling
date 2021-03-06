#include <iostream>
#include <istream>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

struct flight {
    int orig, dest, start, end;
    flight (int o, int d, int s, int e) : orig(o), dest(d), start(s), end(e) {}
};

struct Edge {
    // from u, to v, with capacity c, flow f
    int u, v, c, f;
    Edge(int u, int v, int c, int f) : u(u), v(v), c(c), f(f) {}
    int flow(int w) { return u == w ? f : (-f); }
    int cap(int w) { return u == w ? (c - f) : f; }
    int to(int w) { return u == w ? v : u; }
    void add(int w, int nf) { f += (u == w ? nf : (-nf)); }
};

typedef vector<Edge> VE;

class Solver {
    public:
        enum Algorithm {
            EdmondsKarp,
            Dinic
        };

        enum Version {
          V1,
          V2
        };

        Solver();
        void read();
        void read(istream &is);
        VVI solve(Algorithm a, Version version);

    private: 
        static const int INF;
        static int add_edge(VVI & graph, VE & edges, int u, int v, int cap);

        // Dinics algorithm
        bool bfs(int s, int t, VI & distance, const VVI & adj, const VE & edges);
        int dfs (int u, int t, int fval, const VI & distance, const VVI & adj, VE & edges, VI & index);
        int dinic(int s, int t, VVI & adj, VE & edges);
        vector<flight> _flights;

        // Edmond Karp's algorithm
        int edmond_karp(int s, int t, VVI & graph, VE & edges);

        // Get results, flights of each pilot
        VVI get_results(int k, int s_ini, int t_ini, int num_flights, VVI &adj, VE &edges);
};
