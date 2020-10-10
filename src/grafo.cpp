#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <limits>
#include "simetrica.h"
#include "grafo.h"

using namespace std;


int Grafo::qtdVertices() {
  return this->labels.size();
}
int Grafo::qtdArestas() {
  return this->arestas.size();
}
string Grafo::rotulo(int v) {
  return this->labels[v - 1];
}
bool Grafo::haAresta(int u, int v) {
  return this->adjacencia.get(u, v) != 0;
}
double Grafo::peso(int u, int v) {
  return this->adjacencia.get(u, v);
}
void Grafo::removerAresta(int u, int v) {
  this->adjacencia.set(u, v, 0);
}

int Grafo::grau(int v) {
  int grau = 0;

  for (int u = 1; u <= adjacencia.size(); ++u) {
    if (this->haAresta(u, v)) {
      ++grau;
    }
  }

  return grau;
};
vector<int> Grafo::vizinhos(int v) {
  vector<int> vizinhos;

  for (int u = 1; u <= adjacencia.size(); ++u) {
    if (this->haAresta(u, v)) {
      vizinhos.push_back(u);
    }
  }

  return vizinhos;
}

Grafo::Grafo(vector<string> labels, vector<aresta> arestas) {
  this->labels = labels;
  this->arestas = arestas;

  Simetrica adjacencia(arestas);
  this->adjacencia = adjacencia;
};

Grafo::Grafo(string path) {
  ifstream infile(path);
  string line;

  getline(infile, line);
  istringstream firstLine(line);
  int ordem;
  firstLine >> line >> ordem; // use line to discard "*vertices"
  vector<string> labels;

  for (int i = 1; i <= ordem; ++i) {
    getline(infile, line);
    istringstream iss(line);

    int v;
    string label;
    iss >> v >> label;
    labels.push_back(label);
  }

  getline(infile, line);
  vector<aresta> arestas;

  while (getline(infile, line)) {
    istringstream iss(line);

    int u, v;
    double w;
    iss >> u >> v >> w;
    arestas.push_back({u, v, w});
  }

  this->labels = labels;
  this->arestas = arestas;

  Simetrica adjacencia(arestas);
  this->adjacencia = adjacencia;
}

Grafo::Grafo(){};

void Grafo::busca(int s) {
  queue<int> fila;

  Grafo g(*this);
  map<int, bool> visitados;

  int linha = 0;
  auto v = s;
  do {
    auto vizinhos = this->vizinhos(v);
    
    cout << ++linha << ": ";
    bool primeiro = true;
    for (auto vizinho: vizinhos) {
      if (visitados[vizinho]) {
        continue;
      }

      fila.push(vizinho);
      
      if (!primeiro) {
        cout << ", ";
      } else {
        primeiro = false;
      }

      cout << vizinho;
    }
    cout << endl;

    visitados[v] = true;
    while (visitados[fila.front()]) {
      fila.pop();
    }
    v = fila.front();
  } while (!fila.empty());
  
  return;
}

void Grafo::cicloEuleriano() {
  auto ordem = this->qtdVertices();
  for (auto i = 0; i < ordem; ++i) {
    if (this->grau(i) % 2 != 0) {
      cout << '0' << endl;
      return;
    }
  }
  cout << '1' << endl;

  vector<int> ciclo;
  Grafo g(*this);
  int v = 0;

  do {
    auto vizinhos = g.vizinhos(v);

    auto size = sizeof(vizinhos);
    for (unsigned long i = 0; i < size; ++i) {
      auto vizinho = vizinhos[i];

      if (g.grau(vizinho) > 2 || i == size - 1) {
        ciclo.push_back(vizinho);
        g.removerAresta(vizinho, v);
        v = vizinho;
        break;
      }
    }
  } while (g.qtdArestas() > 0);

  for (unsigned long i = 0; i < ciclo.size(); ++i) {
    if (i != 0) {
      cout << ',';
    }
    cout << ciclo[i];
  }
  cout << endl;
}

void Grafo::bellmanFord(int s) {
  auto ordem = this->qtdVertices();
  double dist[ordem];
  int antecessor[ordem];
  auto infinity = numeric_limits<double>::infinity();

  for (auto v = 0; v < ordem; ++v) {
    dist[v] = (v == s) ? 0 : infinity;
  }

  for (auto n = 0; n < ordem - 1; ++n) {
    for (auto a : this->arestas) {
      int u, v;
      double w;
      tie(u, v, w) = a;

      auto s = dist[u] + w;
      if (s < dist[v]) {
        dist[v] = s;
        antecessor[v] = u;
      }

      auto t = dist[v] + w;
      if (t < dist[u]) {
        dist[u] = t;
        antecessor[u] = v;
      }
    }
  }

  for (auto a : arestas) {
    int u, v;
    double w;
    tie(u, v, w) = a;

    if (w < abs(dist[v] - dist[u])) {
      cout << "Grafo tem ciclo negativo";
      return;
    }
  }

  for (auto v = 0; v < ordem; ++v) {
    cout << s << "; ";

    if (dist[v] == infinity) {
      cout << "Não há caminho" << endl;
      continue;
    }

    auto u = s;

    cout << u;
    while (u != v) {
      u = antecessor[u];
      cout << "," << u;
    }
    cout << "; d=" << dist[v] << endl;
  }
}

void Grafo::floydWarshall() {
  int ordem = this->qtdVertices();
  Simetrica dist(this->arestas);

  cout << "Floyd Warshall " << ordem << endl;

  for (int k = 1; k <= ordem; ++k) {
    for (int u = 1; u <= ordem; ++u) {
      for (int v = 1; v <= ordem; ++v) {
        auto t = dist.get(u, k) + dist.get(k, v);

        if (dist.get(u, v) > t) {
          dist.set(u, v, t);
        }
      }
    }
  }

  for (int v = 1; v <= ordem; ++v) {
    cout << v << ":";

    cout << dist.get(1, v);
    for (int u = 2; u <= ordem; ++u) {
      cout << "," << dist.get(u, v);
    }
    cout << endl;
  }
}

int main() {
  string path = "exemplos/adjnoun.net";
  Grafo grafo(path);

  grafo.busca(100);

  return 0;
}
