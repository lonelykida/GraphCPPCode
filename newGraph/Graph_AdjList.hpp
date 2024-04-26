//encoding = gbk
//Adjacency List of Graph
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


typedef struct eset{     //边表结构
    string VertexName;  //顶点名
    int weight;         //顶点表中对应顶点到该顶点的边的权值
    struct eset* next;  //下一个边顶点
}ESet;

typedef struct{     //顶点表结构
    string VertexName;  //顶点名
    ESet*first;     //第一个边表结点
    int count;      //记录边数
}VSet;

typedef struct{     //图结构
    int vertexNum;  //顶点数
    vector<VSet*> adjList;       //邻接表
    vector<string> vertexName;  //记录所有顶点的名称
    map<string,int> vertex2NumMap;  //顶点名称到顶点编号的映射
    map<int,string> num2VertexMap;  //顶点编号到顶点名称的映射
    bool isDirected;//是否是有向图  false:无向图  true:有向图
}Graph;

//1.初始化图结构 - 传入顶点数vNum(默认0)
Graph* initGraph(int vNum = 0){
    Graph* G = new Graph;   //1.初始化图结构及对应信息
    if(!vNum){
        cout<<"Input the number of vertex in Graph:"<<endl;
        cin>>G->vertexNum;
    }else G->vertexNum = vNum;
    cout<<"Is this grah is directed?(0/1):"<<endl;
    cin>>G->isDirected;
    //2.记录所有顶点的信息
    for(int i = 0;i < G->vertexNum;i++){
        VSet*V = new VSet;
        V->count = 0;
        V->first = nullptr;
        cout<<"Input the name of the vertex v"<<i+1<<":"<<endl;
        cin>>V->VertexName;
        G->adjList.push_back(V);
        G->vertexName.push_back(V->VertexName);
        G->vertex2NumMap[V->VertexName] = i;
        G->num2VertexMap[i] = V->VertexName;
        //a.记录顶点之间的关系
        string anotherV;
        do{
            cout<<"Input the name of the adjacent vertex of v"<<i+1<<":(input # to end)"<<endl;
            cin>>anotherV;
            if(anotherV == "#")break;
            ESet*E = new ESet;  //新建ESet
            E->VertexName = anotherV;
            cout<<"Input the weight of the edge between v"<<i+1<<" and v"<<anotherV<<":"<<endl;
            cin>>E->weight;
            E->next = nullptr;
            //b.将ESet插入到顶点V的边表中
            if(!V->first)V->first = E;
            else {
                ESet*temp = V->first;
                while(temp->next)temp = temp->next;
                temp->next = E;
            }
            V->count++;
        }while(1);
    }
    return G;
}

//2.图G存在，销毁图G
void destroyGraph(Graph*G){
    if(!G)return;
    for(VSet* v:G->adjList){    //对每个顶点表，删除跟随的边表
        ESet*e = v->first;
        while(e->next){
            ESet*temp = e->next;
            delete e->next;
            e->next = temp;
        }
        delete e;   //最后删除顶点表
    }
    delete G;
}

//3.顶点v存在，返回顶点v的第一个邻接点，否则返回NULL
ESet* firstAdjVertex(Graph*G,string v){
    if(G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return nullptr;
    int i = G->vertex2NumMap[v];
    return G->adjList[i]->first;
}

//4.顶点v存在，返回顶点v邻接点w的下一个邻接点，否则返回NULL
ESet* nextAdjVertex(Graph*G,string v,string w){
    if(G->vertex2NumMap.find(v) == G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return nullptr;
    auto V = G->adjList[G->vertex2NumMap[v]];
    auto E = V->first;
    while(E){
        if(E->VertexName == w)return E;
        E = E->next;
    }
    return nullptr;
}

//5.新增顶点v->w的路径
bool insertArc(Graph*G,string v,string w){
    if(G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return false;
    //查找边v->w是否已存在，若已存在，则直接返回
    ESet*e = G->adjList[G->vertex2NumMap[v]]->first;
    while(e){
        if(e->VertexName == w)return true;
        e = e->next;
    }
    if(G->vertex2NumMap.find(w) == G->vertex2NumMap.end()){
        VSet*V = new VSet;  //若w是新结点，则新增
        V->count = 0;
        V->VertexName = w;
        V->first = NULL;
        G->adjList.push_back(V);
        G->vertex2NumMap[V->VertexName] = G->vertexNum;
        G->num2VertexMap[G->vertexNum] = V->VertexName;
        G->vertexName.push_back(w);
        G->vertexNum++;
    }
    ESet*e = new ESet;
    e->VertexName = w;
    cout<<"Please input the weight of the v to w:"<<endl;
    cin>>e->weight;
    e->next = nullptr;
    if(!G->adjList[G->vertex2NumMap[v]]->first)G->adjList[G->vertex2NumMap[v]]->first = e;
    else{
        ESet*temp = G->adjList[G->vertex2NumMap[v]]->first;
        while(temp->next)temp = temp->next;
        temp->next = e;
    }
    G->adjList[G->vertex2NumMap[v]]->count++;
    if(!G->isDirected)insertArc(G,w,v); //若是无向图，则再反向加一下
    return true;
}

//6.删除顶点v及其相关的路径
bool deleteArc(Graph*G,string v){
    
}

