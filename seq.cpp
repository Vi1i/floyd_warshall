/*******************************************************************************
 *
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <climits>

#define INF 99999

void FloydWarshall(const std::vector<std::vector<int> > graph) {
    std::vector<std::vector<int> > dist;
    int row = 0;
    int col = 0;

    for(std::vector<std::vector<int> >::const_iterator it = graph.begin();
            it != graph.end(); ++it) {
        dist.push_back(std::vector<int>());
        for(std::vector<int>::const_iterator point = it->begin();
                point != it->end(); ++point) {
            dist[row].push_back(*point);
            col++;
        }
        row++;
        col = 0;
    }

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

int main(void) {
    std::vector<std::vector<int> > graph {
        {0,     5,      INF,    10},
        {INF,   0,      3,      INF},
        {INF,   INF,    0,      1},
        {INF,   INF,    INF,    0}
    };

    FloydWarshall(graph);
}
