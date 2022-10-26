#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include "generator.h"

using namespace std;

int minWeight = INT_MAX;
string res = "";
int numVertices;
int matriceGraph[20][20];

void readFile(string nameFile){
    fstream fileGraph;
    nameFile="../instances/"+nameFile;
    fileGraph.open(nameFile.c_str(),ios::in);
    string line;
    stringstream s;
    if(fileGraph.is_open()){
        s << fileGraph.rdbuf();
        s >> numVertices;
        for(int i=0;i<numVertices;i++){
            for(int j=0;j<numVertices;j++){
                int data;
                s >> data;
                matriceGraph[i][j] = data;
            }
        }
    }else{
        cout << "ERREUR : No file found" << endl;
    }
    fileGraph.close();
}

void writeFile(int weight, string path, string namefile){
    ofstream fileOut;
    fileOut.open(namefile.c_str());
    for(int i=0;i<path.size();i++){
        fileOut<<path[i];
    }
    fileOut<<'\n'<<weight;
}

void exactAlgo(int from, string path, int dist, int n){
    if(n < numVertices) {
        for (int i = 0; i < numVertices; i++) {
            if (matriceGraph[from][i] != 0 && !strstr(path.c_str(), to_string(i + 1).c_str())) {
                exactAlgo(i, path + " "+to_string(i + 1), dist + matriceGraph[from][i], n + 1);
            }
        }
    } else{
        dist += matriceGraph[from][0];
        if(dist < minWeight){
            minWeight = dist;
            res = path;
        }
    }
}


int main() {
    srand (time(NULL));
    int n;
    int* arr;
    double time = 0;
    struct timespec start;
    struct timespec end;

    //string tab[10] = {"10_10.in", "10_100.in", "10_1000.in", "10_10000.in", "11_1000.in", "12_1000.in"};
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
        exactAlgo(0,"1",0,1);
        //------------------------
        clock_gettime(CLOCK_MONOTONIC, &end);
        res += " 1";
        //printf("%s\n%d\n", res.c_str(), minWeight);
        //writeFile(minWeight, res.c_str(), file);
            //string file ="../instances/"+ to_string(i)+"_"+ to_string(weight)+"_exact.out";
            //writeFile(minWeight, res, file);
        printf("%d\n",minWeight);

        minWeight = INT_MAX;
        string res = "";

        time = (end.tv_sec - start.tv_sec)  + (float) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        //printf("%s time: %f seconds\n", nameFileIn.c_str(),time);
        free(arr);
    }


    return 0;
}

//
// Created by guill on 11/05/2022.
//

