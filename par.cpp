/*******************************************************************************
 *
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <climits>
#include <omp.h>

#define INF 99999
#define MAX_WEIGHT 20

std::vector<std::vector<int> > graph;

void FloydWarshall() {
    std::vector<std::vector<int> > dist(graph);

    for(unsigned int i = 0; i < dist.size(); i++){
        for(unsigned int j = 0; j < dist.size(); j++){
            for(unsigned int k = 0; k < dist.size(); k++){
                if(dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(std::vector<std::vector<int> >::const_iterator it = dist.begin();
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

void gen_adj_matrix(int size, int connectivity) {
    std::cout << "Generating..." << std::endl;
    int i;
    int j;

    // generate random size x size adjacency matrix of requested connectivity
    // uses "infinity" to indicate non-adjacent nodes   
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
    std::cout << "Done!" << std::endl;
}

int main(void) {
    //std::vector<std::vector<int> > graph(gen_adj_matrix(20, 10));
    //std::vector<std::vector<int> > graph {
    //        {0,         5,          INF,    10},
    //        {INF,   0,          3,          INF},
    //        {INF,   INF,    0,          1},
    //        {INF,   INF,    INF,    0}
    //};

    gen_adj_matrix(1000, 5);
    FloydWarshall();
}
