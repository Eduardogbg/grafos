#include <string>
#include <vector>
#include "aresta.h"
#include "simetrica.h"


class Grafo {
public:
  int qtdVertices();
  int qtdArestas();
  string rotulo(int v);
  bool haAresta(int u, int v);
  double peso(int u, int v);
  void removerAresta(int u, int v);
  
  int grau(int v);
  int* vizinhos(int v);

  void busca(int s);
  void cicloEuleriano();
  void floydWarshall(int s);
  void bellmanFord();

  Grafo copia();

  Grafo(vector<string> labels, vector<aresta> arestas);
  Grafo();

  vector<aresta> arestas;
private:
  vector<string> labels;
  Simetrica adjacencia;
};
