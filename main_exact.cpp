#include <bits/stdc++.h>

using namespace std;

int minWeight = INT_MAX;
string res = "";
int numVertices;
int matriceGraph[50][50];

void readFile(string nameFile){
    fstream fileGraph;
    nameFile="../Instances/"+nameFile+".in";
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
    namefile="../Instances/"+namefile;
    fileOut.open(namefile.c_str());
    for(int i=0;i<path.size();i++){
        if(i!=0){
            fileOut<<" ";
        }
        fileOut<<path[i];    }
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


int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "ERROR : bad argument for the name of the file" << endl;
        return 0;
    }
    string nameFileIn = argv[1];
    readFile(nameFileIn);

    exactAlgo(0,"1",0,1);
    string nameFileOut=nameFileIn+"_exact.out";
    writeFile(minWeight,res, nameFileOut);

    return 0;
}