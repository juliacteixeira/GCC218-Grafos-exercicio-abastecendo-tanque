#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAXN = 1000;
const int MAXE = 10000;

vector<pair<int, int>> adj[MAXN]; // lista de adjacência do grafo
int combustivel[MAXN]; // custo para abastecer uma unidade de combustível em cada cidade

int dijkstra(int vOrigem, int vFinal, int Q) {
    // inicializa matriz que armazenaas distancias entre o vOrigem e a cada vértice do grafo
    // considerando cada possível quantidade de combustivel disponível para compra em cada cidade
    // O valor dist[i][j] representa a distância mínima de s até i, com j unidades de combustível disponíveis.
    int dist[MAXN][Q+1];
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j <= Q; j++) {
            dist[i][j] = INT_MAX;
        }
    }
   // inicializa a distância de s até si mesmo com zero e adiciona um par (0, (s, 0)) à fila de prioridade pq. 
   //O segundo elemento do par é outro par com os valores vOrigem e 0, representando o vértice atual e a quantidade de combustível disponível atualmente.
    dist[vOrigem][0] = 0;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    pq.push(make_pair(0, make_pair(vOrigem, 0)));

    // algoritmo de Dijkstra
    // O loop principal executa enquanto houver vértices na fila de prioridade. 
    // O vértice u e a quantidade de combustível f são extraídos do topo da fila pq. 
    // Para cada vértice v adjacentes a u busca a quantidade i de combustível que o viajante pode comprar em v, até no máximo Q-f unidades. 
    // e calcula a nova quantidade de combustível (novaQtdCombustivel) que o viajante teria em v e também calcula o novo custo (novoCusto) da viagem de u a v 
    // com a quantidade de combustível, levando em conta o custo (combustivel[u]) para abastecer em u e o peso (distancia) da aresta entre u e v. 
    // Depois verifica se a nova distância é menor que a distância anterior dist[v.first][novaQtdCombustivel] para o vértice v com a quantidade de combustível disponível. 
    // Se sim, a nova distância é atualizada na matriz dist, e um novo par (novaDistancia, (v.first, novaQtdCombustivel)) é adicionado à fila de prioridade pq.
    while (!pq.empty()) {
        int u = pq.top().second.first;  //vertice u é excluido 
        int f = pq.top().second.second;
        pq.pop();
        for (auto v : adj[u]) {
            int distancia = v.second;
            for (int i = 0; i <= Q-f; i++) {
                int novaQtdCombustivel = f + i;
                int novoCusto = dist[u][f] + i*combustivel[u]*distancia;
                if (novaQtdCombustivel <= Q && novoCusto < dist[v.first][novaQtdCombustivel]) {
                    dist[v.first][novaQtdCombustivel] = novoCusto;
                    pq.push(make_pair(novoCusto, make_pair(v.first, novaQtdCombustivel)));
                }
            }
        }
    }

    // Retorna o menor custo para chegar na cidade de destino
    //considerando todas as possibilidades de quantidade de combustível
    int ans = INT_MAX;
    for (int i = 0; i <= Q; i++) {
        ans = min(ans, dist[vFinal][i]);
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
        cin >> combustivel[i];
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