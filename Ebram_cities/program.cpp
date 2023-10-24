//inputing relevent libraries and files

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "D:\FALL 2023\applied DS\assignment 3\program\Ebram_cities\BinaryTree.cpp"
#include "D:\FALL 2023\applied DS\assignment 3\program\Ebram_cities\stackt.cpp"
#include "D:\FALL 2023\applied DS\assignment 3\program\Ebram_cities\Queuet.cpp"

using namespace std;

// This function takes the data of the city and preprocesses it in a form of a vector

vector<string> tokenizer(string x){

vector<string> tokens;

string token = "";
x+=' ';
int len = x.length();

for(int i = 0; i<len; i++){
    if((x[i] != ' ')){
        token += x[i];
    }
    else{
        tokens.push_back(token);
        token = "";
    }
}
tokens.erase(tokens.begin());

vector <string> returned_token;
if(tokens.size() > 4){

string pushed = "";

for(int i = 0; i < tokens.size(); i++){
    if ((tokens[i][0] >= 48) && (tokens[i][0] <= 57) || (tokens[i][0] == 32)){
        returned_token.push_back(tokens[i]);
    }
    else {
        pushed += tokens[i];
        pushed += ' ';
        if (i == (tokens.size()-1)){returned_token.push_back(pushed); break;}
        if (((tokens[i+1][0] >= 48) && (tokens[i+1][0] <= 57)) || (tokens[i+1][0] == 32)){
                    returned_token.push_back(pushed);
                    pushed = "";
        }
    }
}
}
else {returned_token = tokens;}

for(int i = 1; i < returned_token.size(); i++){
    returned_token[i]+=' ';
}
return returned_token;
}

// this function prints the vector
void print_vec(vector <string> v1){
    for (int i =0; i<v1.size(); i++){
    cout << "Token " << i << v1[i] << ' ';
    if (i == v1.size()-1){cout << endl;}
}
}
//This function converts the vector to a string. It will be helpful in the insertion process 
string from_vec_string(vector <string> V) {
string res = "";
for(int i = 0; i < V.size();i++){
    res += V[i];
}
return res;
}
//This function extracts the digits from a string. It will be helpful in the process of computing the distance.
vector <int> digits_extractor(string C){
char last = C[C.length()-1];
vector <string> digs;
string DS = "";

for(int i = 0; i < C.length(); i++){
    if(digs.size()>2){break;}
    if (((C[i] >= 48) && (C[i] <= 57)) && ((C[i+1] >= 48) && (C[i+1] <= 57))){
    DS+= C[i];}
    else if (((C[i] >= 48) && (C[i] <= 57)) && !((C[i+1] >= 48) && (C[i+1] <= 57))){
        DS+= C[i];
        digs.push_back(DS);
        DS = "";
    }
    }
vector <int> res;
int stoi_digit;
for(int i = 0; i < digs.size(); i++){
    stoi_digit = stoi(digs[i]);
    if (last == 'S' || last == 'W'){res.push_back(stoi_digit*-1);}
    else {res.push_back(stoi_digit);}
}
return res;
}

// This function tokenizes in a different way for the use in computing the distance.
vector<string> specialized_tokenizer(string x){

vector<string> tokens;

string token = "";
x+=' ';
int len = x.length();

for(int i = 0; i<len; i++){
    if((x[i] != ' ')){
        token += x[i];
    }
    else{
        tokens.push_back(token);
        token = "";
    }
}
return tokens;
}
//This function computes the distance
double Compute_distance(string c1 , string c2){

vector <string> tokens_1 = specialized_tokenizer(c1); 
vector <string> tokens_2 = specialized_tokenizer(c2);


vector <vector<int>> integers_of_direction_1;
vector <vector<int>> integers_of_direction_2;

integers_of_direction_1.push_back(digits_extractor(tokens_1[0]));
integers_of_direction_1.push_back(digits_extractor(tokens_1[1]));
integers_of_direction_2.push_back(digits_extractor(tokens_2[0]));
integers_of_direction_2.push_back(digits_extractor(tokens_2[1]));

char direction_1 = c1[c1.length()-1];
char direction_2 = c2[c2.length()-1];

vector <double> rad_1_2;
for (int i = 0; i <integers_of_direction_1.size(); i++){
    rad_1_2.push_back(((integers_of_direction_1[i][0]+(integers_of_direction_1[i][1]/60.0))*M_PI)/180);
}

for (int i = 0; i <integers_of_direction_2.size(); i++){
    rad_1_2.push_back(((integers_of_direction_2[i][0]+(integers_of_direction_2[i][1]/60.0))*M_PI)/180);
}
double phi_1 = rad_1_2[0];
double phi_2 = rad_1_2[2];
double lambda_1 = rad_1_2[1];
double lambda_2 = rad_1_2[3];
const double R = 6371.137;
double a = pow((phi_2-phi_1)/2, 2) + cos(phi_1)*cos(phi_2)*pow((lambda_2-lambda_1)/2,2); 
double c = 2 * atan(2* (sqrt(a),sqrt(1-a)));
double distance = R * c;
return distance;
}

int main(){
//First of all I have to check if this is the first run or not, so I will see if the file of the dictionry saved to the memory is empty or not.
ifstream I;
I.open("D:\\FALL 2023\\applied DS\\assignment 3\\program\\Dictionary_of_cities.txt");
char t;

vector <string> x;
vector<vector<string>> vec_of_vecs; 
binaryTree <string, string> dict;
string loop_key;
int cnter = 0;
ifstream r;
string in;

r.open("D:\\FALL 2023\\applied DS\\assignment 3\\program\\datatxt.txt");

int counter = 0;

while(getline(r,in)){
if(in == "No. City Latitude Longitude Country"){continue;}
x = tokenizer(in);

counter++;
loop_key = x[0];
vec_of_vecs.push_back(x);
x.erase(x.begin());
dict.insert(loop_key , from_vec_string(x));
}
string cty,lat,lng,count; 

char h = 'y';
int n;

// pritning the menu
cout << "\nWelcome in the super city dictionary!!!!\n";

while(h == 'y'){
cout << "==================== Menu ================== \n1. Add a new city\n2. Compute the distance between two cities\n3. Print all cities\n";
cin >> n;
if(n == 1){
if (h != 'y'){break;}
cout << "write the name of the city ";
cin >> cty;
cout << "Now, enter the latitude in the form of (number + (degree) + number + (minutes))+ direction as letter. Example (12degree46minutesS) ";
cin>>lat;
cout << "Now, enter the longitude in the form of (number + (degree) + number + (minutes))+ direction as letter. Example (12degree46minutesS) ";
cin>>lng;
cout << "Now, enter the country ";
cin>>count;
dict.insert(cty, (lat+ ' ' + lng + ' ' + count));
}
else if(n == 2){
cout << "write the name of the first city ";
cin >> cty;
cout << "write the name of the second city ";
cin >> lat;
cout << Compute_distance(dict.search(cty),dict.search(lat)) << endl;
}
else if(n==3){
    dict.levelorder();
}
}
dict.preorder();
}