#pragma once
#include<iostream>
#include<vector>
#include "date.h"
#include "matrix.h"


template<typename T>
class Graph {
private:
    std::vector<std::vector<std::pair<T, int> > > graph;
    std::vector<bool> isExistVertex;

    int countOfVertex;
    int countOfEdges;
public:
    Graph() {
        this->countOfVertex=0;
        this->countOfEdges=0;
    }

    int getVertex() const {
        return countOfVertex;
    }
    int getEdges() const {
        return countOfEdges;
    }

    void chooseVertex() {
        for (int i = 0; i < graph.size(); i++)
            if (isExistVertex[i])
                std::cout << "[" << i << "] ";
        std::cout << std::endl;
    }

    void addVertex() {
        std::vector<std::pair<T, int> >  new_vertex;
        graph.push_back(new_vertex);
        graph[countOfVertex].clear();
        isExistVertex.push_back(true);
        countOfVertex++;
    }

    void deletedVertex(int index) {
        if (index<0 || isExistVertex[index] == false || index>countOfVertex) {
            std::cout << "Wrong input"<<std::endl;
            return;
        }


        int countOfEdges = graph[index].size();
        int numberAdjacentVertes;

        for (int i = 0; i < countOfEdges; i++) {
            numberAdjacentVertes = graph[index][i].second;
            for (int j = 0; j < graph[numberAdjacentVertes].size(); j++) {
                if (graph[numberAdjacentVertes][j].second == index) {
                    graph[numberAdjacentVertes].erase(graph[numberAdjacentVertes].begin() + j);
                    break;
                }
            }
        }

        isExistVertex[index] = false;
        countOfVertex--;
        countOfEdges -= countOfEdges;
    }


    void addEdge(int first_vertex, int second_vertex, T weight) {
        if (!isExistVertex[first_vertex] || !isExistVertex[second_vertex]) {
            std::cout << "Wrong input vertex!" << std::endl;
            return;
        }

        bool flag = false;
        for (int i = 0; i < graph[first_vertex].size() && !flag; i++) {
            if (graph[first_vertex][i].second == second_vertex)
                flag = true;
        }

        if (flag) {
            std::cout << "This edge is exist" << std::endl;
            return;
        }

        graph[first_vertex].push_back({ weight, second_vertex });
        graph[second_vertex].push_back({ weight, first_vertex });
        countOfEdges++;
    }

    void deletedEdge(int first_vertex, int second_vertex) {
        if (!isExistVertex[first_vertex] || !isExistVertex[second_vertex]) {
            std::cout << "Wrong input indexex!" << std::endl;
            return;
        }

        bool flag = false;
        for (int i = 0; i < graph[first_vertex].size() && !flag; i++) {
            if (graph[first_vertex][i].second == second_vertex) {
                graph[first_vertex].erase(graph[first_vertex].begin() + i);
                flag = true;
            }
        }
        if (!flag) {
            std::cout << "This edge isn`t exist" << std::endl;
            return;
        }

        for (int j = 0; j < graph[second_vertex].size(); j++) {
            if (graph[second_vertex][j].second == second_vertex) {
                graph[second_vertex].erase(graph[second_vertex].begin() + j);
                break;
            }
        }

        countOfEdges--;
    }


    void MST_Kruskala() {
        Graph mst;
        for (int i = 0; i < countOfVertex; i++)
            mst.addVertex();

        std::vector<std::pair<T, std::pair<int, int> >> allEdges = sortedEdges();

        std::vector<int> tree_id(countOfVertex);
        for (int i = 0; i < countOfVertex; ++i)
            tree_id[i] = i;

        for (int i = 0; i < countOfEdges; ++i) {
            int firstVertex = allEdges[i].second.first, secondVertex = allEdges[i].second.second;
            if (tree_id[firstVertex] != tree_id[secondVertex]) {
                T newWeight = allEdges[i].first;
                mst.addEdge(firstVertex, secondVertex, newWeight);
                int old_id = tree_id[secondVertex], new_id = tree_id[firstVertex];
                for (int j = 0; j < countOfVertex; ++j)
                    if (tree_id[j] == old_id)
                        tree_id[j] = new_id;
            }
        }
        std::cout << mst;

    }

    std::vector<std::pair<T, std::pair<int, int>>> sortedEdges() {
        std::vector< std::pair<T, std::pair<int, int>>> edges;
        int arrayOfEdges[countOfVertex][countOfVertex];
        for (int i = 0; i < countOfVertex; i++)
            for (int j = 0; j < countOfVertex; j++)
                arrayOfEdges[i][j] = 0;

        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                if (arrayOfEdges[i][graph[i][j].second])
                    continue;
                else {
                    arrayOfEdges[i][graph[i][j].second] = arrayOfEdges[graph[i][j].second][i] = 1;
                    edges.push_back({ graph[i][j].first,{i,graph[i][j].second} });
                }
            }
        }
        sort(edges.begin(), edges.end());
        return edges;
    }


    friend std::ostream& operator<<(std::ostream& output, const Graph<T>& current_graph) {
        for (int i = 0; i < current_graph.graph.size(); i++) {
            if (current_graph.isExistVertex[i]) {
                std::cout << "Vertex " << i << std::endl;
                for (int j = 0; j < current_graph.graph[i].size(); j++) {
                    std::cout << "Adjective vertex ->" << current_graph.graph[i][j].second
                        << " weight = " << current_graph.graph[i][j].first << std::endl;
                }
            }
        }
        std::cout << "Count of edges= " << current_graph.countOfEdges << std::endl;
        std::cout << "Count of vertexes= " << current_graph.countOfVertex << std::endl;
        return output;
    }
};


