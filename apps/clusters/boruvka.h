
#include "common.h"

class Boruvka {

private:

  vector<intE> g[MAX_N];
  int cid[MAX_N];
  bool visited[MAX_N];
  vector<CNode*> clusters;
  int n;

  void bfs(intE v, intE c, CNode* t)
  {
    if(visited[v]) return;
    visited[v] = 1;
    if(!clusters[cid[v]]->parent)
    {
      clusters[cid[v]]->parent = t;
      t->children.push_back(clusters[cid[v]]);
    }
    cid[v] = c;
    for(int i = 0; i < g[v].size(); i++) bfs(g[v][i], c, t);
  }

  CNode* run_boruvka_helper(vector<wghEdge<intE> > &edge_list)
  {
    long long mst = 0;
    clusters = vector<CNode*>(n);

    for(int i = 0; i < n; i++)
    {
      CNode* t = new CNode(i);
      clusters[i] = t;
      cid[i] = i;
      g[i].clear();
    }
    cerr << "begin main boruvka loop" << endl;
    while(clusters.size() > 1)
    {
      cerr << "cluster size: " << clusters.size() << endl;
      int size = clusters.size();
      intE max_e[size];
      int max[size];
      for(int i = 0; i < size; i++) max[i] = INT_MIN;
      for(int i = 0; i < edge_list.size(); i++)
      {
        intE u = edge_list[i].u;
        intE v = edge_list[i].v;
        intE w = edge_list[i].w;
        if(cid[u] == cid[v]) continue;
        if(max[cid[u]] < w)
        {
          max[cid[u]] = w;
          max_e[cid[u]] = i;
        }
        if(max[cid[v]] < w)
        {
          max[cid[v]] = w;
          max_e[cid[v]] = i;
        }
      }
      for(int i = 0; i < size; i++)
      {
        if(max[i] == INT_MIN) continue;
        intE u = edge_list[max_e[i]].u;
        intE v = edge_list[max_e[i]].v;
        intE w = edge_list[max_e[i]].w;
        if(isin(g[u], v)) continue;
        g[u].push_back(v);
        g[v].push_back(u);
        mst += w;
      }
      
      int count = 0;
      vector<CNode*> new_clusters;

      for(int i = 0; i < n; i++) visited[i] = 0;
      
      for(int i = 0; i < n; i++)
      {
        if(!visited[i])
        {
          CNode* t = new CNode();
      	new_clusters.push_back(t);
          bfs(i, count, t);        
          count++;
        }
      }
      if(clusters.size() == new_clusters.size())
      {
        CNode* root = new CNode();
        for(int i = 0; i < clusters.size(); i++)
        {
          clusters[i]->parent = root;
          root->children.push_back(clusters[i]);
          delete new_clusters[i];
        }
        return root;
      }
      clusters = new_clusters;
    }
    return clusters[0];
  }

public:
  Boruvka(int n) : n(n) {}

  CNode* run(int** adj)
  {
    vector<wghEdge<intE> > edge_list;
    adj_to_edge_list(adj, edge_list, n);
    return run_boruvka_helper(edge_list);
  }
};








