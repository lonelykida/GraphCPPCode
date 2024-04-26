//encoding = gbk

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//图的邻接矩阵表示法
typedef struct {
    int vertexNum;  //顶点数
    vector<vector<int>> adjMatrix;
    vector<string> vertexName;  //记录所有顶点的名称
    map<string,int> vertex2NumMap;  //顶点名称到顶点编号的映射
    map<int,string> num2VertexMap;  //顶点编号到顶点名称的映射
    bool isDirected;//是否是有向图  false:无向图  true:有向图
}Graph;

//1.初始化图结构 - 传入顶点数vNum(默认0)
Graph* initGraph(int vNum = 0){
    Graph* G = new Graph;   //1.初始化图结构
    if(!vNum){
        cout<<"Please input the num of vertex in Graph:"<<endl;
        cin>>G->vertexNum;
    }else G->vertexNum = vNum;
    G->adjMatrix = vector<vector<int>>(G->vertexNum,vector<int>(G->vertexNum,-1));
    cout<<"Is this grah is directed?(0/1):"<<endl;
    cin>>G->isDirected;
    string vName;
    for(int i = 0;i < G->vertexNum;i++){    //2.记录所有顶点的信息
        G->adjMatrix[i][i] = 0; //顶点自己到自己距离是0
        vName.clear();
        cout<<"Please input the "<<"v"<<i+1<<"'s name:";
        cin>>vName;
        G->vertexName.push_back(vName);
        G->vertex2NumMap[vName] = i;
        G->num2VertexMap[i] = vName;
    }
    //3.输入每个顶点之间的关系
    string v1,v2;
    cout<<"Now to input the vertex's relation.\n";
    do{
        cout<<"Please input the first vertex name:(input # to end)";
        cin>>v1;
        if(v1 == "#") break;
        cout<<"Please input the second vertex name:";
        cin>>v2;
        int i = G->vertex2NumMap[v1];
        int j = G->vertex2NumMap[v2];
        cout<<"Please input the weight of the edge between "<<v1<<" and "<<v2<<":";
        cin>>G->adjMatrix[i][j];
        if(!G->isDirected) G->adjMatrix[j][i] = G->adjMatrix[i][j];
    }while(1);
    return G;
}

//2.图G存在，销毁图G
void destroyGraph(Graph* G){
    if(!G)return;
    delete G;
}

//3.若顶点存在，输出顶点的编号，否则输出-1
int vertexNum(Graph* G,string vName){
    if(!G || G->vertex2NumMap.find(vName) == G->vertex2NumMap.end()) return -1;
    return G->vertex2NumMap.find(vName)->second;
}

//4.顶点v存在，返回顶点v的第一个邻接点，否则返回空串
string firstAdjVertex(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return "";
    int i = G->vertex2NumMap[v];
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[i][j]!= -1 && G->adjMatrix[i][j] != 0)return G->num2VertexMap[j];
    return "";
}

//5.顶点v存在，返回顶点v邻接点w的下一个邻接点，否则返回空串
string nextAdjVertex(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return "";
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    for(int k = j+1;k < G->vertexNum;k++)
        if(G->adjMatrix[i][k]!= -1 && G->adjMatrix[i][k] != 0)return G->num2VertexMap[k];
    return "";
}

//6.新增顶点v->w的路径
bool insertArc(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    cout<<"Input the weight of the edge between "<<v<<" and "<<w<<":";
    cin>>G->adjMatrix[i][j];
    return true;
}

//7.删除顶点v及其相关的路径
bool deleteArc(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    for(int j = 0;j < G->vertexNum;j++) 
        if(!G->isDirected)G->adjMatrix[i][j] = G->adjMatrix[j][i] = -1;
        else G->adjMatrix[i][j] = -1;
    return true;
}

//8.删除顶点v到顶点w的路径
bool deleteVWArc(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v)==G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    G->adjMatrix[i][j] = G->adjMatrix[j][i] = -1;
    return true;
}

//9.DFS - 深搜
void DFS(Graph*G){
    cout<<"starting DFS\n";
    if(!G || !G->vertexNum)return;
    map<string,bool>visited;//记录是否访问过
    vector<string>path;     //访问队列
    visited[G->num2VertexMap[0]] = true;    //将第一个点标记为"访问过"
    path.push_back(G->num2VertexMap[0]);    //将第一个点放入访问队列
    int front = 0,rear = 1;
    for(int i = 0;i < G->vertexNum;i++){    //不漏掉每一个点
        if(visited.find(G->num2VertexMap[i]) == visited.end()){ //若当前点未访问过，则将其放入访问队列并标记
            path.push_back(G->num2VertexMap[i]);
            visited[G->num2VertexMap[i]] = true;
            rear++;
        }
        while(front < rear){    //当队列不空时，依次访问
            string cur = path[front++];
            cout<<cur<<' ';
            string next = firstAdjVertex(G,cur);    //找邻接点
            while(visited.find(next)!=visited.end() && next.size())next = nextAdjVertex(G,cur,next);
            if(next.size()){    //若邻接点未访问过，则进入访问
                path.push_back(next);
                rear++;
                visited[next] = true;
            }
        }
    }
    cout<<endl;
}

//10.BFS - 广搜
void BFS(Graph*G){
    if(!G || !G->vertexNum)return;
    cout<<"starting BFS\n";
    map<string,bool>visited;//访问标记
    vector<string>path;     //访问队列
    int front = 0,rear = 1;
    path.push_back(G->num2VertexMap[0]);    //第一个点放入访问队列
    visited[G->num2VertexMap[0]] = true;
    for(int i = 0;i < G->vertexNum;i++){    //不漏掉每一个点
        if(visited.find(G->num2VertexMap[i]) == visited.end()){ //若当前点未访问过，则将其放入访问队列并标记
            path.push_back(G->num2VertexMap[i]);
            visited[G->num2VertexMap[i]] = true;
            rear++;
        }
        while(front<rear){  //当队列不空时，依次访问
            string cur = path[front++];
            cout<<cur<<" ";
            string next = firstAdjVertex(G,cur);    //找邻接点
            while(next.size()){    //若邻接点未访问过，则进入访问
                if(visited.find(next) == visited.end()){
                    path.push_back(next);
                    visited[next] = true;
                    rear++;
                }
                next = nextAdjVertex(G,cur,next);
            }
        }
    }
    cout<<endl;
}

//11.求图G顶点v的入度
int inDegree(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return -1;  //-1无此顶点
    int i = G->vertex2NumMap[v];
    int count = 0;
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[j][i] != -1 && G->adjMatrix[j][i] != 0)count++;
    return count;
}

//12.求图G顶点v的入度
int outDegree(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return -1;  //-1无此顶点
    int i = G->vertex2NumMap[v];
    int count = 0;
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[i][j] != -1 && G->adjMatrix[i][j] != 0)count++;
    return count;
}