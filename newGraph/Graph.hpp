// encoding = utf-8

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <queue>
#include <limits>
#include <string>

using namespace std;

typedef struct{
    string vName;   //顶点编号
    string vData;   //顶点�?
    vector<string> adjVertex;   //邻接�?
    vector<string> Edges;       //�?
}Vertex;

typedef struct{
    int eName;  //边编�?
    string eData;   //边�?
    string from;    //起点
    string to;  //终点
}Edge;

typedef struct{
    vector<Vertex*> V;  //顶点�?
    vector<Edge*>E;     //边集
    map<string,Vertex*> VM; //顶点�? - 通过顶点编号查找顶点
    map<int,Edge*> EM;     //边图    - 通过边编号查找边
    bool isNonDirection;    //是否是无向图  true: 无向�?  false: 有向�?
}Graph;

