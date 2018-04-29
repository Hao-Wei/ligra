import sys
def edgesToCSR(input_path, output_path, num_nodes):
  adj = {}
  counters = {}
  offset = 0
  with open(input_path, "r") as f:
    lines = f.readlines()
    for l in lines:
      line = l.split()
      u = int(line[0])
      v = int(line[1])
      if u not in adj:
        adj[u] = {}
        counters[u] = 0
      adj[u][v] = 1
      counters[u] += 1
  with open(output_path, "w") as f:
    for i in range(0, num_nodes):
      f.write(str(offset) + "\n")
      if i in counters:
        offset += counters[i]
    for i in adj:
      for j in adj[i]:
        f.write(str(j) + "\n")
        
if __name__ == '__main__':
  edgesToCSR(sys.argv[1], sys.argv[2], int(sys.argv[3]))