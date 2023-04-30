import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from functools import partial
from typing import List, Tuple

class Edge:
    def __init__(self, v, u, capacity, flow):
        self.v = v
        self.u = u
        self.capacity = capacity
        self.flow = flow

def add_edge(v: int, u: int, capacity: int, graph: List[List[Edge]]):
    e1 = Edge(v, u, capacity, 0)
    e2 = Edge(u, v, 0, 0)
    graph[v].append(e1)
    graph[u].append(e2)

def bfs(graph: List[List[Edge]], parent: List[int], s: int, t: int) -> bool:
    n = len(graph)
    visited = [False] * n
    q = [s]
    visited[s] = True
    parent[s] = -1
    while q:
        u = q.pop(0)
        visited[u] = True
        for e in graph[u]:
            v = e.u
            if not visited[v] and e.capacity > e.flow:
                visited[v] = True
                parent[v] = u
                q.append(v)
    return visited[t]

def augment(graph: List[List[Edge]], parent: List[int], s: int, t: int) -> int:
    n = len(graph)
    min_flow = float('inf')
    v = t
    while v != s:
        u = parent[v]
        for e in graph[u]:
            if e.u == v:
                min_flow = min(min_flow, e.capacity - e.flow)
                break
        v = u
    v = t
    while v != s:
        u = parent[v]
        for e in graph[u]:
            if e.u == v:
                e.flow += min_flow
                break
        for e in graph[v]:
            if e.u == u:
                e.flow -= min_flow
                break
        v = u
    return min_flow

def ford_fulkerson(graph: List[List[Edge]], s: int, t: int) -> int:
    n = len(graph)
    parent = [0] * n
    max_flow = 0
    while bfs(graph, parent, s, t):
        flow = augment(graph, parent, s, t)
        max_flow += flow
    return max_flow

def read_graph_from_file(filepath: str) -> Tuple[int, int, int, int, List[List[Edge]]]:
    with open(filepath) as f:
        n, m, s, t = map(int, f.readline().split())
        graph = [[] for _ in range(n)]
        for _ in range(m):
            u, v, c = map(int, f.readline().split())
            add_edge(u, v, c, graph)
        return n, m, s, t, graph

class App:
    def __init__(self, master):
        self.master = master
        self.filepath = ""
        self.n, self.m, self.s, self.t = 0, 0, 0, 0
        self.graph = []
        master.title("Ford-Fulkerson Algorithm")
        master.geometry("500x400")
        self.choose_file_btn = tk.Button(master, text="Choose File", command=self.choose_file)
        self.choose_file_btn.pack(pady=10)
        self.max_flow_lbl = tk.Label(master, text="")
        self.max_flow_lbl.pack(pady=10)
        self.run_algorithm_btn = tk.Button(master, text="Run Algorithm", command=self.run_algorithm)
        self.run_algorithm_btn.pack(pady=10)
        self.quit_btn = tk.Button(master, text="Quit", command=master.quit)
        self.quit_btn.pack(pady=10)

    def choose_file(self):
        self.filepath = filedialog.askopenfilename()
        if self.filepath:
            self.n, self.m, self.s, self.t, self.graph = read_graph_from_file(self.filepath)
            self.max_flow_lbl.config(text=f"Max Flow: {ford_fulkerson(self.graph, self.s, self.t)}")
    
    def run_algorithm(self):
        if self.filepath:
            self.max_flow_lbl.config(text=f"Max Flow: {ford_fulkerson(self.graph, self.s, self.t)}")
        else:
            messagebox.showerror("Error", "Please choose a file first!")

root = tk.Tk()
app = App(root)
root.mainloop()
