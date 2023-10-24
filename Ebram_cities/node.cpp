#include "node.h"
#include <iostream>
#include <string>
using namespace std;

template <class x>
treeNode<x>::treeNode(string k, vector <string> dta){
key = k;
data = dta;
leftT = NULL;
rightT = NULL;
};