#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAXN = 1000;
const int MAXE = 10000;

vector<pair<int, int>> adj[MAXN]; // lista de adjacência do grafo
int c[MAXN]; // custo para abastecer uma unidade de combustível em cada cidade

int dijkstra(int s, int t, int Q) {
    // inicialização
    int dist[MAXN][Q+1];
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j <= Q; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    dist[s][0] = 0;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push(make_pair(0, make_pair(s, 0)));

    // algoritmo de Dijkstra
    while (!pq.empty()) {
        int u = pq.top().second.first;
        int f = pq.top().second.second;
        pq.pop();
        for (auto v : adj[u]) {
            int w = v.second;
            for (int i = 0; i <= Q-f; i++) {
                int nf = f + i;
                int nd = dist[u][f] + i*c[u]*w;
                if (nf <= Q && nd < dist[v.first][nf]) {
                    dist[v.first][nf] = nd;
                    pq.push(make_pair(nd, make_pair(v.first, nf)));
                }
            }
        }
    }

    // retorno da resposta
    int ans = INT_MAX;
    for (int i = 0; i <= Q; i++) {
        ans = min(ans, dist[t][i]);
    }
    if (ans == INT_MAX) {
        return -1;
    } else {
        return ans;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    for (int i = 0; i < V; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    int T;
    cin >> T;
    while (T--) {
        int Q, s, t;
        cin >> Q >> s >> t;
        int ans = dijkstra(s, t, Q); //chama dijkstra passando a cidade origem e destino e o combustível máximo que o viajante pode comprar
        if (ans == -1) {
            cout << "sem solucao" << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}