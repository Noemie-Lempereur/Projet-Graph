#include <cstring>
#include "lecture.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "generator.h"

using namespace std;
float tempfactor = 0.995; //cooling ratio
int l=400; //max iter

unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //seed to generate different random values each time
default_random_engine engine(seed);


int cost(vector<vector<int>> matriceGraph, vector<int> path){ //return the cost, aka path's length
    int cost=0;
    int size=path.size();
    for (int i=1;i<size;i++){
        cost+=matriceGraph[path[i-1]-1][path[i]-1]; //-1 because the matrix stores indexes from 0 to n-1 but cities names start at 1
    }
    cost+=matriceGraph[path[size-1]-1][path[0]-1];
    return cost;
}


vector<int> randomPath(int size){ //generates a random path going through all vertices
    vector<int> path;
    for(int i=1;i<=size;i++){
        path.push_back(i);
    }
    shuffle(path.begin(), path.end(),engine);
    return path;
}

vector<int> sim_annealing(const vector<vector<int>>& matriceGraph, int size){ //return the calculated path
    vector<int> previousPath = randomPath(size); //initial solution
    vector<int> tempPath;
    float t=size;
    bool frozen=false;
    int delta;
    float prob;
    int iter=0;
    uniform_real_distribution<float> distribution(0.0, 1.0);
    while(!frozen && iter<l){
        tempPath=randomPath(size);
        delta=cost(matriceGraph,tempPath)-cost(matriceGraph,previousPath);
        if (delta <=0){ //downhill move
            previousPath=tempPath;
        }
        else{ //if delta>0, uphill move
            prob=distribution(engine);
            if(prob < exp(-delta/t)){ //we replace the solution with probability e^-delta/t
                previousPath=tempPath;
            }
        }
        t*=tempfactor;
        iter++;
        if(t<0.000000000001){  //10^-12
            frozen=true;
        }
    }
    return previousPath;
}

int main(int argc, char** argv) {
    srand (time(NULL));
    int n;
    int* arr;
    double time = 0;
    struct timespec start;
    struct timespec end;
    ofstream fileOut;
    fileOut.open("../annealing_1000_10000.txt", ios::out);

    for (int i=1; i <= 12; ++i) {
        int weight = 10000;
        n = 500;
        arr = static_cast<int *>(malloc(n * sizeof(int)));
        for(int j=0;j<n;j++){
            arr[j] = rand() % 1000;
        }

        string nameFileIn = generator(i, weight);
        vector<vector<int>> matrixGraph;
        vector<int> path;

        matrixGraph=readFile(nameFileIn);

        clock_gettime(CLOCK_MONOTONIC, &start);
        // PUT ALGO HERE !!!!!!
        path= sim_annealing(matrixGraph, i);
        clock_gettime(CLOCK_MONOTONIC, &end);

        string file = to_string(i)+"_"+ to_string(weight)+"_annealing.out";
        writeFile(cost(matrixGraph, path), path, file);

        //printf("%s\n%d\n", res.c_str(), pathWeight);
        time = (end.tv_sec - start.tv_sec)  + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("%d\n",cost(matrixGraph, path));

        //printf("%d %f\n", i,time);

        fileOut << to_string(time) << "\n";
        free(arr);
    }
    fileOut.close();
    return 0;
}
