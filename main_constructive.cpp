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
    ofstream fileOut;
    fileOut.open("../constructive_1000_1000.txt", ios::out);

    for (int i=1; i <= 12; ++i) {
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
        vector<vector<int> > matriceGraph;
        matriceGraph=readFile(nameFileIn);
        const int numVertices=matriceGraph.size();
        int oldVertex=0;
        int newVertex=0;
        int minWeight=0;
        int pathWeight=0;
        vector<bool> inPath (numVertices, false);
        inPath[0]= true;
        vector<int> path (1,1);
        for(int i=1;i<numVertices;i++){
            bool firstLoop=true;
            for(int j=1; j<numVertices;j++){
                if(j!=oldVertex and !inPath[j] and firstLoop){
                    newVertex=j;
                    minWeight=matriceGraph[oldVertex][j];
                    firstLoop= false;
                }else{
                    if(minWeight>matriceGraph[oldVertex][j] and !inPath[j]){
                        newVertex=j;
                        minWeight=matriceGraph[oldVertex][j];
                    }
                }
            }
            pathWeight+=minWeight;
            oldVertex=newVertex;
            path.push_back(newVertex+1);
            inPath[newVertex]=true;
        }
        clock_gettime(CLOCK_MONOTONIC, &end);

        pathWeight+=matriceGraph[newVertex][0];
        string file = to_string(i)+"_"+ to_string(weight)+"_constructive.out";
        writeFile(pathWeight, path, file);

        //printf("%s\n%d\n", res.c_str(), pathWeight);
        time = (end.tv_sec - start.tv_sec)  + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        //printf("%d %f\n", i,time);
        printf("%d\n",pathWeight);

        fileOut << to_string(time) << "\n";
        free(arr);
    }
    fileOut.close();
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