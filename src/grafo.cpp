#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>
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
  return this->labels[v];
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

  for (int u = 0; u < adjacencia.size(); ++u) {
    if (this->haAresta(u, v)) {
      ++grau;
    }
  }

  return grau;
};
int *Grafo::vizinhos(int v) {
  vector<int> vizinhos;

  for (auto u = 0; u < adjacencia.size(); ++u) {
    if (this->haAresta(u, v)) {
      vizinhos.push_back(u);
    }
  }

  return &vizinhos[0];
}

Grafo Grafo::copia() {
  return Grafo(this->labels, this->arestas);
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
  firstLine >> ordem;
  vector<string> labels;

  for (auto i = 0; i < ordem; ++i) {
    getline(infile, line);
    istringstream iss(line);

    int v;
    iss >> v >> labels[i];
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

  int linha = 0;
  auto v = s;
  do {
    auto vizinhos = this->vizinhos(v);

    cout << linha << ": ";
    for (unsigned long i = 0; i < sizeof(vizinhos); ++i) {
      fila.push(i);

      if (i != 0) {
        cout << ", ";
      }
      cout << i;
    }
    cout << endl;

    fila.pop();
    v = fila.front();
  } while (!fila.empty());
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
  auto g = this->copia();
  int v = 0;

  do {
    auto vizinhos = g.vizinhos(v);

    auto size = sizeof(vizinhos);
    for (unsigned long i = 0; i < size; ++i) {
      if (g.grau(i) > 2 || i == size - 1) {
        ciclo.push_back(i);
        g.removerAresta(i, v);
        v = i;
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

void Grafo::floydWarshall()
{
  int ordem = this->qtdVertices();
  Simetrica dist(this->arestas);

  for (auto k = 0; k < ordem; ++k) {
    for (auto u = 0; u < ordem; ++u) {
      for (auto v = 0; v < ordem; ++v) {
        auto t = dist.get(u, k) + dist.get(k, v);

        if (dist.get(u, v) > t) {
          dist.set(u, v, t);
        }
      }
    }
  }

  for (auto v = 0; v < ordem; ++v) {
    cout << v << ":";

    cout << dist.get(0, v);
    for (auto u = 1; u < ordem; ++u) {
      cout << "," << dist.get(u, v);
    }
    cout << endl;
  }
}

int main() {
  string path = "exemplos/adjnoun.net";
  Grafo grafo(path);

  cout << "asdasd" << get<0>(grafo.arestas[0]);

  return 0;
}
