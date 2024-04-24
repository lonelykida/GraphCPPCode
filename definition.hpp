//encoding :GBK
#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int numEdge = 0;    //count of edges

//1.define vertex
typedef struct {
    string title;   //vertex name
    string data;       //vertex data
    vector<string> adjVertexs;   //adjacent vertex edges set
    vector<int> Edges;   //edges set of vertex
}Vertex;

//2.define edge
typedef struct{
    int num;        //edge name
    int weight;     //edge weight
    string from;    //edge from vertex
    string to;      //edge to vertex
}Edge;

//3.Graph
typedef struct{
    vector<Vertex*> vertexs; //vertex set
    vector<Edge*> edges;     //edge set
    map<string,Vertex*> vertexMap;   //vertex map - vertex name -> vertex
    map<int,Edge*> edgeMap;          //edge map - edge name -> edge
}Graph;

