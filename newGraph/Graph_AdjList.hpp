//encoding = gbk
//Adjacency List of Graph
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


typedef struct eset{     //�߱�ṹ
    string VertexName;  //������
    int weight;         //������ж�Ӧ���㵽�ö���ıߵ�Ȩֵ
    struct eset* next;  //��һ���߶���
}ESet;

typedef struct{     //�����ṹ
    string VertexName;  //������
    ESet*first;     //��һ���߱���
    int count;      //��¼����
}VSet;

typedef struct{     //ͼ�ṹ
    int vertexNum;  //������
    vector<VSet*> adjList;       //�ڽӱ�
    vector<string> vertexName;  //��¼���ж��������
    map<string,int> vertex2NumMap;  //�������Ƶ������ŵ�ӳ��
    map<int,string> num2VertexMap;  //�����ŵ��������Ƶ�ӳ��
    bool isDirected;//�Ƿ�������ͼ  false:����ͼ  true:����ͼ
}Graph;

//1.��ʼ��ͼ�ṹ - ���붥����vNum(Ĭ��0)
Graph* initGraph(int vNum = 0){
    Graph* G = new Graph;   //1.��ʼ��ͼ�ṹ����Ӧ��Ϣ
    if(!vNum){
        cout<<"Input the number of vertex in Graph:"<<endl;
        cin>>G->vertexNum;
    }else G->vertexNum = vNum;
    cout<<"Is this grah is directed?(0/1):"<<endl;
    cin>>G->isDirected;
    //2.��¼���ж������Ϣ
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
        //a.��¼����֮��Ĺ�ϵ
        string anotherV;
        do{
            cout<<"Input the name of the adjacent vertex of v"<<i+1<<":(input # to end)"<<endl;
            cin>>anotherV;
            if(anotherV == "#")break;
            ESet*E = new ESet;  //�½�ESet
            E->VertexName = anotherV;
            cout<<"Input the weight of the edge between v"<<i+1<<" and v"<<anotherV<<":"<<endl;
            cin>>E->weight;
            E->next = nullptr;
            //b.��ESet���뵽����V�ı߱���
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

//2.ͼG���ڣ�����ͼG
void destroyGraph(Graph*G){
    if(!G)return;
    for(VSet* v:G->adjList){    //��ÿ�������ɾ������ı߱�
        ESet*e = v->first;
        while(e->next){
            ESet*temp = e->next;
            delete e->next;
            e->next = temp;
        }
        delete e;   //���ɾ�������
    }
    delete G;
}

//3.����v���ڣ����ض���v�ĵ�һ���ڽӵ㣬���򷵻�NULL
ESet* firstAdjVertex(Graph*G,string v){
    if(G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return nullptr;
    int i = G->vertex2NumMap[v];
    return G->adjList[i]->first;
}

//4.����v���ڣ����ض���v�ڽӵ�w����һ���ڽӵ㣬���򷵻�NULL
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

//5.��������v->w��·��
bool insertArc(Graph*G,string v,string w){
    if(G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return false;
    //���ұ�v->w�Ƿ��Ѵ��ڣ����Ѵ��ڣ���ֱ�ӷ���
    ESet*e = G->adjList[G->vertex2NumMap[v]]->first;
    while(e){
        if(e->VertexName == w)return true;
        e = e->next;
    }
    if(G->vertex2NumMap.find(w) == G->vertex2NumMap.end()){
        VSet*V = new VSet;  //��w���½�㣬������
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
    if(!G->isDirected)insertArc(G,w,v); //��������ͼ�����ٷ����һ��
    return true;
}

//6.ɾ������v������ص�·��
bool deleteArc(Graph*G,string v){
    
}

