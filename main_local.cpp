#include "lecture.h"
#include "generator.h"

using namespace std;
int weigh(int a, int b, vector<int> path, vector<vector<int> > matriceGraph);
vector <int> initialAnswer(vector<vector<int> > matriceGraph);

int main(int argc, char** argv) {
    srand (time(NULL));
    int n;
    int* arr;
    double time = 0;
    struct timespec start;
    struct timespec end;

    for (int i = 1; i <= 12; ++i) {
        int weight = 10000;
        n = 500;
        arr = static_cast<int *>(malloc(n * sizeof(int)));
        for(int j=0;j<n;j++){
            arr[j] = rand() % 1000;
        }

        string nameFileIn = generator(i, weight);
        readFile(nameFileIn);

        clock_gettime(CLOCK_MONOTONIC, &start);
        // PUT ALGO HERE !!!!!!
        vector <vector<int> > matriceGraph;
        matriceGraph = readFile(nameFileIn);
        const int numVertices = matriceGraph.size();

        int pathWeight;
        int pathWeightTest;
        vector<int> path(1, 1);
        vector<int> pathTest(1, 1);
        for (int i = 2; i <= numVertices; i++) {
            path.push_back(i);
        }
        path=initialAnswer(matriceGraph);

        for (int i = 0; i < numVertices - 1; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (i != j && i != j + 1 && i != j - 1) {
                    pathTest = path;
                    int k = i + 1;
                    int q = j;

                    if (i < j) {
                        while (k < q) {
                            pathTest[k] = path[q];
                            pathTest[q] = path[k];
                            k++;
                            q--;
                        }
                    } else {
                        while (k > q) {
                            pathTest[k] = path[q];
                            pathTest[q] = path[k];
                            k--;
                            q++;
                        }
                    }
                    pathWeightTest = weigh(pathTest[0], pathTest[numVertices - 1], pathTest, matriceGraph) +
                                     matriceGraph[pathTest[numVertices - 1] - 1][0];
                    pathWeight = weigh(path[0], path[numVertices - 1], path, matriceGraph) +
                                 matriceGraph[path[numVertices - 1] - 1][0];
                    if (pathWeightTest < pathWeight) {
                        path = pathTest;
                    }
                }
            }
        }
        //------------------------
        clock_gettime(CLOCK_MONOTONIC, &end);
        //printf("%s\n%d\n", res.c_str(), minWeight);
        //writeFile(minWeight, res.c_str(), file);
        time = (end.tv_sec - start.tv_sec)  + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        //printf("%s time: %f seconds\n", nameFileIn.c_str(),time);
        //printf("%d %f\n", i,time);
        free(arr);

            pathWeight= weigh(path[0],path[numVertices-1],path,matriceGraph)+matriceGraph[path[numVertices-1]-1][0];
        printf("%d\n",pathWeight);
            //string file = to_string(i)+"_"+ to_string(weight)+"_local.out";
        //writeFile(pathWeight, path, file);
    }
    return 0;
}



int weigh(int a, int b, vector<int> path, vector<vector<int> > matriceGraph){
    if(a==b){
        return 0;
    }else{
        int number=0;
        while(path[number]!=a){
            number++;
        }
        return matriceGraph[a-1][path[number+1]-1] + weigh(path[number+1],b,path,matriceGraph);
    }
}

vector <int> initialAnswer(vector<vector<int> > matriceGraph){
    const int numVertices=matriceGraph.size();
    int oldVertex=0;
    int newVertex=0;
    int minWeight=0;
    int pathWeight=0;
    vector<bool> inPath (numVertices, false);
    inPath[0]= true;
    vector<int> path (1,1);
    for(int i=1;i<numVertices;i++) {
        bool firstLoop = true;
        for (int j = 1; j < numVertices; j++) {
            if (j != oldVertex and !inPath[j] and firstLoop) {
                newVertex = j;
                minWeight = matriceGraph[oldVertex][j];
                firstLoop = false;
            } else {
                if (minWeight > matriceGraph[oldVertex][j] and !inPath[j]) {
                    newVertex = j;
                    minWeight = matriceGraph[oldVertex][j];
                }
            }
        }
        oldVertex = newVertex;
        path.push_back(newVertex + 1);
        inPath[newVertex] = true;
    }
    return path;
}