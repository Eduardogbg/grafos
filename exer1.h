#include <vector>
#include <tuple>
#include <map>


typedef tuple<int, int, double> Aresta;

class Simetrica {
public:
  double get(int i, int j);
  void set(int i, int j, double w);
  int size();

  Simetrica(vector<Aresta> arestas);
  Simetrica();

private:
  map<int, int, double> esparsa;
  int ordem;
};

class Grafo {
public:
  int qtdVertices();
  int qtdArestas();
  string rotulo(int v);
  int grau(int v);
  int* vizinhos(int v);
  bool haAresta(int u, int v);
  double peso(int u, int v);
  void removerAresta(int u, int v);

  Grafo copia();

  Grafo(vector<string> labels, vector<Aresta> arestas);
  Grafo();

private:
  vector<string> labels;
  vector<Aresta> arestas;
  Simetrica adjacencia;
};
