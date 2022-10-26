

#ifndef PROJETGRAPH_LECTURE_H
#define PROJETGRAPH_LECTURE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int> > readFile(string nameFile);
void writeFile(int weight, vector<int> path, string namefile);

#endif //PROJETGRAPH_LECTURE_H
