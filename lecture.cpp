#include "lecture.h"


vector<vector<int> > readFile(string nameFile){
    int numVertices=0;
    fstream fileGraph;
    nameFile="../Instances/"+nameFile;
    fileGraph.open(nameFile.c_str(),ios::in);
    vector<vector<int> > matriceGraph;
    string line;
    stringstream s;
    if(fileGraph.is_open()){
        //getline(fileGraph,line);
        s << fileGraph.rdbuf();
        s >> numVertices;
        for(int i=0;i<numVertices;i++){
            vector<int> distance;
            for(int j=0;j<numVertices;j++){
                int data;
                s >> data;
                distance.push_back(data);
            }
            matriceGraph.push_back(distance);
        }
    }else{
        cout << "ERREUR : No file found" << endl;
    }
    fileGraph.close();
    return matriceGraph;
}

void writeFile(int weight, vector<int> path, string namefile){
    ofstream fileOut;
    namefile="../instances/"+namefile;
    fileOut.open(namefile.c_str());
    for(int i=0;i<path.size();i++){
        if(i!=0){
            fileOut<<" ";
        }
        fileOut<<path[i];    }
    fileOut<<'\n'<<weight;
}