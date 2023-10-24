#ifndef node
#define node
#include <iostream>
#include <vector>

using namespace std;

template <class x>
class treeNode{
string key;
vector <string> data;
treeNode *leftT;
treeNode *rightT;
public: 
treeNode(string , vector<string>);
treeNode();

};

#endif
