#include "goloso.h"



int contar_aristas_isomorfismo_agregar(const Grafo& g1, const Grafo& g2,
    int v1, int v2,
    const Isomorfismo& iso) {
  int aristas = 0;
  for (unsigned int i = 0; i <= iso.size(); i++) {
    int vg1 = i < iso.size() ? iso[i].first : v1;
    int vg2 = i < iso.size() ? iso[i].second : v2;
    for (unsigned int j = 0; j <= iso.size(); j++) {
      int ug1 = j < iso.size() ? iso[j].first : v1;
      int ug2 = j < iso.size() ? iso[j].second : v2;

      if (g1.adj_matrix[vg1][ug1] && // ug1 y vg1 estan conectados.
          g2.adj_matrix[vg2][ug2]) { // ug2 y vg2 estan conectados.
        aristas++;
      }
    }
  }

  return aristas / 2; // conte todas 2 veces;
}

int mayor_adj(std::set<int>& lista, Grafo g) {
  int mejor = *(lista.begin());
  for (auto v : lista) {
    if (g.grados[v] > g.grados[mejor]) {
      mejor = v;
    }
  }
  return mejor;
}


MCS goloso(
    Grafo g1, std::set<int> vertices1,
    Grafo g2, std::set<int> vertices2) {

  MCS solucion;
  solucion.aristas = 0;

  int vertice1 = mayor_adj(vertices1, g1);
  int vertice2 = mayor_adj(vertices2, g2);

  solucion.isomorfismo.push_back(make_pair(vertice1, vertice2));

  vertices1.erase(vertice1);
  vertices2.erase(vertice2);

  while ( vertices1.size() != 0){
    pair<int, int> par_mayor_deg = make_pair(
        *(vertices1.begin()),
        *(vertices2.begin()));
  	for (const int u : vertices1) {
      for (const int v : vertices2) {
        Isomorfismo nuevo_iso = solucion.isomorfismo;
        nuevo_iso.push_back(make_pair(u, v));
        int aristas = contar_aristas_isomorfismo_agregar(g1, g2, u, v,
            solucion.isomorfismo);
        if ( aristas > solucion.aristas){
          solucion.aristas = aristas;
          par_mayor_deg = make_pair(u,v);
        }
      }
  	}
  	solucion.isomorfismo.push_back(par_mayor_deg);
  	vertices1.erase(par_mayor_deg.first);
  	vertices2.erase(par_mayor_deg.second);
  }

  return solucion;
}


// MCS goloso(
//     Grafo g1, std::vector<int> &vertices1, 
//     Grafo g2, std::vector<int> &vertices2) {
// 
//   sort_adj(vertices1, g1);
//   sort_adj(vertices2, g2);
// 
//   MCS solucion;
// 
//   for (unsigned int i = 0; i < vertices1.size(); i++) {
//     solucion.isomorfismo.push_back(std::make_pair(vertices1[i], vertices2[i]));
//   }
// 
//   int aristas = contar_aristas_isomorfismo(g1, g2, solucion.isomorfismo);
//   solucion.aristas = aristas;
// 
//   return solucion;
// }



