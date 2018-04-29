
#include "common.h"
#include<algorithm>

class Kruskal2 {

private:
  //vector<intE> g[MAX_N];
  CNode* clusters[MAX_N];
  //int cid[MAX_N];
  //bool visited[MAX_N];
  int n;
  UnionFind *uf;

public:
  Kruskal2(int n) : n(n) {uf = new UnionFind(n);}

  CNode* run(int** adj)
  {
    long long mst = 0;
    vector<wghEdge<intE> > edge_list;
    adj_to_edge_list(adj, edge_list, n);
    sort(edge_list.begin(), edge_list.end(), Comp());
    for(int i = 0; i < n; i++)
      clusters[i] = new CNode(i);

    bool change = true;
    bool used[n];
    while(change)
    {
      change = false;
      for(int i = 0; i < n; i++)
        used[i] = false;
      for(int i = 0; i < edge_list.size(); i++)
      {
        intE u = edge_list[i].u;
        intE v = edge_list[i].v;
        intE w = edge_list[i].w;
        u = uf->find(u);
        v = uf->find(v);
        if(u != v && !used[u] && !used[v])
        {
          used[u] = true;
          used[v] = true;
          change = true;
          mst += w;
          CNode* t = new CNode();
          clusters[u]->parent = t;
          clusters[v]->parent = t;
          t->children.push_back(clusters[u]);
          t->children.push_back(clusters[v]);
          clusters[u] = t;
          uf->join(u, v);
        }
      }
    }
    
    CNode *root = new CNode();
    vector<int> cid(n);
    for(int i = 0; i < n; i++)
      cid[i] = uf->find(i);
    sort(cid.begin(), cid.end());
    vector<int>::iterator it = unique(cid.begin(), cid.end());
    cid.resize(distance(cid.begin(), it));
    for(int i = 0; i < cid.size(); i++)
      root->children.push_back(clusters[cid[i]]);
    cout << "mst = " << mst << endl;
    return root;
  }
};  