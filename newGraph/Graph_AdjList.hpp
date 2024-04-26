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
    for(auto vSet:G->adjList){
        
    }
    for(int i = 0;i < G->adjList.size();i++){
        auto V = G->adjList[i];
        delete V;
    }
    delete G;
}
