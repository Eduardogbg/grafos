#pragma once

#include <string>
#include <vector>
#include <unordered_map>
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
  vector<int> vizinhos(int v);

  void busca(int s);
  void cicloEuleriano();
  void floydWarshall();
  void bellmanFord(int s);

  Grafo copia();

  Grafo(vector<string> labels, vector<aresta> arestas);
  Grafo(string path);
  Grafo();

  vector<aresta> arestas;
private:
  vector<string> labels;
  Simetrica adjacencia;
  int grauTotal;
  unordered_map<int, int> graus;
};
