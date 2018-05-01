
#include "common.h"
#include<algorithm>

class Boruvka3 {

private:

  vector<CNode*> clusters;
  UnionFind *uf;
  int n;

  CNode* run_boruvka_helper(vector<wghEdge<intE> > &edge_list)
  {
    long long mst = 0;
    clusters = vector<CNode*>(n);

    for(int i = 0; i < n; i++)
      clusters[i] = new CNode(i);
    cerr << "begin main boruvka loop" << endl;
    bool change = true;
    while(change)
    {
      change = false;
      //intE max_e[n];
      //int max[n];
      pair<int, intE> max[n];
      for(int i = 0; i < n; i++) max[i].first = INT_MIN;
      for(int i = 0; i < edge_list.size(); i++)
      {
        intE u = edge_list[i].u;
        intE v = edge_list[i].v;
        intE w = edge_list[i].w;
        u = uf->find(u);
        v = uf->find(v);
        if(u == v) continue;
        if(max[u].first < w)
        {
          max[u].first = w;
          max[u].second = i;
        }
        if(max[v].first < w)
        {
          max[v].first = w;
          max[v].second = i;
        }
      }
      sort(max, max+n);
      for(int i = n-1; i >= 0; i--)
      {
        if(max[i].first == INT_MIN) break;
        int j = max[i].second;
        intE u = edge_list[j].u;
        intE v = edge_list[j].v;
        intE w = edge_list[j].w;
        u = uf->find(u);
        v = uf->find(v);
        if(u != v)
        {
          mst += w;
          change = true;
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

public:
  Boruvka3(int n) : n(n) {uf = new UnionFind(n);}

  CNode* run(int** adj)
  {
    vector<wghEdge<intE> > edge_list;
    adj_to_edge_list(adj, edge_list, n);
    return run_boruvka_helper(edge_list);
  }
};








