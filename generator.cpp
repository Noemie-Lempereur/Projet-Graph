//
// Created by guill on 11/05/2022.
//

#include "generator.h"

using namespace std;

string generator (int n, int w) {
    string file= "../instances/" + to_string(n) + "_" + to_string(w) + ".in";
    string file_instance = to_string(n)+"_"+to_string(w)+".in";

    ifstream existFile;
    existFile.open(file);
    if (existFile) {
    } else {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        uniform_int_distribution<int> distribution(0, w);
        default_random_engine engine(seed);
        ofstream fileOut;

        fileOut.open(file, ios::out);

        fileOut<<to_string(n)+"\n";
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if (j!=i) {
                    fileOut << to_string(distribution(engine));
                }
                else{
                    fileOut << to_string(0);
                }
                if (j!=n-1) {
                    fileOut << " ";
                }
            }
            fileOut<<"\n";
        }
        fileOut.close();
    }
    return file_instance;
}