/*******************************************************************************
 *
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <climits>
#include <chrono>
#include <omp.h>
#include "bigBoy.cpp"

#define INF 99999
#define MAX_WEIGHT 20

std::vector<std::vector<int>> graph;

void FloydWarshall(std::vector<std::vector<int>> * dist) {
    int size = graph.size();
    #pragma omp parallel for collapse(3)
    for(unsigned int i = 0; i < size; i++){
        for(unsigned int j = 0; j < size; j++){
            for(unsigned int k = 0; k < size; k++){
                if(graph[i][k] + graph[k][j] < graph[i][j]) {
                    (*dist)[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

void PrintGraph(std::vector<std::vector<int>> dist) {
    for(std::vector<std::vector<int>>::const_iterator it = dist.begin();
            it != dist.end(); ++it) {
        for(std::vector<int>::const_iterator point = it->begin();
                point != it->end(); ++point) {
            if(*point == INF){
                std::cout << "INF\t";
            }else{
                std::cout << *point << "\t";
            }
        }
        std::cout << std::endl;
    }
}

void GenAdjMatrix(int size, int connectivity) {
    int i;
    int j;

    srand((unsigned) time(0));
    for(i = 0; i < size; i++) {
        graph.push_back(std::vector<int>());
        for(j = 0; j < size; j++) {
            if(((rand() % size) < connectivity) && i != j) {
                graph[i].push_back(1 + (rand() % MAX_WEIGHT));
            }else{
                graph[i].push_back(INF);
            }
        }
    }
}

int main(void) {
    std::vector<std::vector<int> > local {
        {0,     5,      INF,    10}, 
        {INF,   0,      3,      INF},
        {INF,   INF,    0,      1},
        {INF,   INF,    INF,    0} 
    };
    graph = big_boy;
    //GenAdjMatrix(500, 100);
    //std::vector<std::vector<int>> * dist = new std::vector<std::vector<int>>(graph);
    std::vector<std::vector<int>> * dist = new std::vector<std::vector<int>>(big_boy);

    //PrintGraph(*dist);

    auto start = std::chrono::high_resolution_clock::now();
    FloydWarshall(dist);
    auto stop = std::chrono::high_resolution_clock::now();
    auto time = stop - start;

    std::cout << "Time : " <<
        (std::chrono::duration_cast<std::chrono::nanoseconds>(time).count())
        /1000000000.0 << "s" << std::endl;
    PrintGraph(big_boy);
}
