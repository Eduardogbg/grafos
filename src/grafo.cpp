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
  return this->grauTotal;
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
  --this->grauTotal;
}

int Grafo::grau(int v) {
  int grau = 0;

  for (auto u = 1ul; u <= labels.size(); ++u) {
    grau += this->haAresta(u, v);
  }

  return grau;
};
vector<int> Grafo::vizinhos(int v) {
  vector<int> vizinhos;

  for (auto u = 1ul; u <= labels.size(); ++u) {
    if (this->haAresta(u, v)) {
      vizinhos.push_back(u);
    }
  }

  return vizinhos;
}

Grafo::Grafo(vector<string> labels, vector<aresta> arestas) {
  this->labels = labels;
  this->arestas = arestas;
  this->grauTotal = arestas.size();

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
  this->grauTotal = arestas.size();

  Simetrica adjacencia(arestas);
  this->adjacencia = adjacencia;
}

Grafo::Grafo(){};

void Grafo::busca(int s) {
  queue<int> proximaLinha;
  queue<int> linhaAtual;

  Grafo g(*this);
  map<int, bool> visitados;

  int linha = 0;
  proximaLinha.push(s);

  do {
    linhaAtual.swap(proximaLinha);
    proximaLinha = {};

    cout << linha++ << ": ";
    bool primeiro = true;

    do {
      int v = linhaAtual.front();
      if (!primeiro) {
        cout << ", ";
      } else {
        primeiro = false;
      }
      cout << v;

      auto vizinhos = this->vizinhos(v);
      for (auto vizinho: vizinhos) {
        if (visitados[vizinho]) {
          continue;
        }

        proximaLinha.push(vizinho);
        visitados[vizinho] = true;
      }

      linhaAtual.pop();
    } while (!linhaAtual.empty());
    cout << endl;

  } while (!proximaLinha.empty());
  
  return;
}

void Grafo::cicloEuleriano() {
  auto ordem = this->qtdVertices();
  for (int i = 1; i <= ordem; ++i) {
    if (this->grau(i) % 2 != 0) {
      cout << '0' << endl;
      return;
    }
  }
  cout << '1' << endl;

  vector<int> ciclo;
  ciclo.reserve(this->qtdArestas() + 1);

  Grafo g(*this);
  int v = 1;
  ciclo.push_back(v);

  do {
    auto vizinhos = g.vizinhos(v);
    auto size = vizinhos.size();

    for (auto i = 0ul; i < size; ++i) {
      auto vizinho = vizinhos[i];

      if (g.grau(vizinho) > 2 || i == size - 1) {
        ciclo.push_back(vizinho);
        g.removerAresta(vizinho, v);
        v = vizinho;
        break;
      }
    }
  } while (g.qtdArestas() > 0);

  for (auto i = 0ul; i < ciclo.size(); ++i) {
    if (i != 0) {
      cout << ',';
    }
    cout << ciclo[i];
  }
  cout << endl;

  return;
}

void Grafo::bellmanFord(int s) {
  auto ordem = this->qtdVertices();
  double distAtual[ordem + 1];
  double distAnterior[ordem + 1];
  int antecessor[ordem + 1];
  auto infinity = numeric_limits<double>::infinity();

  for (auto v = 1; v <= ordem; ++v) {
    distAnterior[v] = (v == s) ? 0 : infinity;
    distAtual[v] = distAnterior[v];
  }

  for (auto n = 1; n <= ordem - 1; ++n) {
    for (auto a : this->arestas) {
      int u, v;
      double w;
      tie(u, v, w) = a;

      auto s = distAnterior[u] + w;
      if (s < distAnterior[v]) {
        distAtual[v] = s;
        antecessor[v] = u;
      }

      auto t = distAnterior[v] + w;
      if (t < distAnterior[u]) {
        distAtual[u] = t;
        antecessor[u] = v;
      }
    }

    if (n != ordem - 1) {
      for (auto v = 1; v <= ordem; ++v) {
        distAnterior[v] = distAtual[v];
      }
    }
  }

  for (auto a : arestas) {
    int u, v;
    double w;
    tie(u, v, w) = a;

    if (w < abs(distAtual[v] - distAtual[u])) {
      cout << "Grafo tem ciclo negativo" << endl;
      return;
    }
  }
  
  for (auto v = 1; v <= ordem; ++v) {
    cout << v << ": ";

    if (distAtual[v] == infinity) {
      cout << "Não há caminho" << endl;
      continue;
    }

    vector<int> caminho;
    caminho.push_back(v);
    if (v != s) {
      while (caminho.back() != s) {
        caminho.push_back(antecessor[caminho.back()]);
      }
    }

    cout << caminho[0];
    for (auto i = 1ul; i < caminho.size(); ++i) {
      cout << ", " << caminho[i];
    }
    cout << "; d=" << distAtual[v] << endl;
  }
}

void Grafo::floydWarshall() {
  int ordem = this->qtdVertices();
  Simetrica dist(this->arestas, numeric_limits<double>::infinity());

  for (int v = 1; v <= ordem; ++v) {
    dist.set(v, v, 0);
  }

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

int main(int argc, char* argv[]) {
  string path = "exemplos/" + (string) argv[1];
  Grafo grafo(path);

  cout << "Ciclo Euleriano" << endl;
  grafo.cicloEuleriano();
  cout << endl << "Busca" << endl;
  grafo.busca(6);
  cout << endl << "Bellman-Ford" << endl;
  grafo.bellmanFord(6);
  cout << endl << "Floyd-Warshall" << endl;
  grafo.floydWarshall();

  return 0;
}
