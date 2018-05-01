import sys
def edgesToCSR(input_path, output_path):
  adj = {}
  counters = {}
  offset = 0
  mx = 0
  edges = 0
  with open(input_path, "r") as f:
    lines = f.readlines()
    for l in lines:
      line = l.split()
      u = int(line[0])
      v = int(line[1])
      mx = max(mx, max(u+1, v+1));
      if u not in adj:
        adj[u] = {}
        counters[u] = 0
      adj[u][v] = 1
      counters[u] += 1
      edges+=1
  with open(output_path, "w") as f:
    f.write("asdfds\n");
    f.write(str(mx) + "\n")
    f.write(str(edges) + "\n")
    for i in range(0, mx):
      f.write(str(offset) + "\n")
      if i in counters:
        offset += counters[i]
    for i in range(mx):
      if i in adj:
        for j in adj[i]:
          f.write(str(j) + "\n")
        
if __name__ == '__main__':
  edgesToCSR(sys.argv[1], sys.argv[2])
