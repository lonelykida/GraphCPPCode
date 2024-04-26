//encoding = gbk

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//ͼ���ڽӾ����ʾ��
typedef struct {
    int vertexNum;  //������
    vector<vector<int>> adjMatrix;
    vector<string> vertexName;  //��¼���ж��������
    map<string,int> vertex2NumMap;  //�������Ƶ������ŵ�ӳ��
    map<int,string> num2VertexMap;  //�����ŵ��������Ƶ�ӳ��
    bool isDirected;//�Ƿ�������ͼ  false:����ͼ  true:����ͼ
}Graph;

//1.��ʼ��ͼ�ṹ - ���붥����vNum(Ĭ��0)
Graph* initGraph(int vNum = 0){
    Graph* G = new Graph;   //1.��ʼ��ͼ�ṹ
    if(!vNum){
        cout<<"Please input the num of vertex in Graph:"<<endl;
        cin>>G->vertexNum;
    }else G->vertexNum = vNum;
    G->adjMatrix = vector<vector<int>>(G->vertexNum,vector<int>(G->vertexNum,-1));
    cout<<"Is this grah is directed?(0/1):"<<endl;
    cin>>G->isDirected;
    string vName;
    for(int i = 0;i < G->vertexNum;i++){    //2.��¼���ж������Ϣ
        G->adjMatrix[i][i] = 0; //�����Լ����Լ�������0
        vName.clear();
        cout<<"Please input the "<<"v"<<i+1<<"'s name:";
        cin>>vName;
        G->vertexName.push_back(vName);
        G->vertex2NumMap[vName] = i;
        G->num2VertexMap[i] = vName;
    }
    //3.����ÿ������֮��Ĺ�ϵ
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

//2.ͼG���ڣ�����ͼG
void destroyGraph(Graph* G){
    if(!G)return;
    delete G;
}

//3.��������ڣ��������ı�ţ��������-1
int vertexNum(Graph* G,string vName){
    if(!G || G->vertex2NumMap.find(vName) == G->vertex2NumMap.end()) return -1;
    return G->vertex2NumMap.find(vName)->second;
}

//4.����v���ڣ����ض���v�ĵ�һ���ڽӵ㣬���򷵻ؿմ�
string firstAdjVertex(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return "";
    int i = G->vertex2NumMap[v];
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[i][j]!= -1 && G->adjMatrix[i][j] != 0)return G->num2VertexMap[j];
    return "";
}

//5.����v���ڣ����ض���v�ڽӵ�w����һ���ڽӵ㣬���򷵻ؿմ�
string nextAdjVertex(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return "";
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    for(int k = j+1;k < G->vertexNum;k++)
        if(G->adjMatrix[i][k]!= -1 && G->adjMatrix[i][k] != 0)return G->num2VertexMap[k];
    return "";
}

//6.��������v->w��·��
bool insertArc(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    cout<<"Input the weight of the edge between "<<v<<" and "<<w<<":";
    cin>>G->adjMatrix[i][j];
    return true;
}

//7.ɾ������v������ص�·��
bool deleteArc(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    for(int j = 0;j < G->vertexNum;j++) 
        if(!G->isDirected)G->adjMatrix[i][j] = G->adjMatrix[j][i] = -1;
        else G->adjMatrix[i][j] = -1;
    return true;
}

//8.ɾ������v������w��·��
bool deleteVWArc(Graph*G,string v,string w){
    if(!G || G->vertex2NumMap.find(v)==G->vertex2NumMap.end() || G->vertex2NumMap.find(w) == G->vertex2NumMap.end())return false;
    int i = G->vertex2NumMap[v];
    int j = G->vertex2NumMap[w];
    G->adjMatrix[i][j] = G->adjMatrix[j][i] = -1;
    return true;
}

//9.DFS - ����
void DFS(Graph*G){
    cout<<"starting DFS\n";
    if(!G || !G->vertexNum)return;
    map<string,bool>visited;//��¼�Ƿ���ʹ�
    vector<string>path;     //���ʶ���
    visited[G->num2VertexMap[0]] = true;    //����һ������Ϊ"���ʹ�"
    path.push_back(G->num2VertexMap[0]);    //����һ���������ʶ���
    int front = 0,rear = 1;
    for(int i = 0;i < G->vertexNum;i++){    //��©��ÿһ����
        if(visited.find(G->num2VertexMap[i]) == visited.end()){ //����ǰ��δ���ʹ������������ʶ��в����
            path.push_back(G->num2VertexMap[i]);
            visited[G->num2VertexMap[i]] = true;
            rear++;
        }
        while(front < rear){    //�����в���ʱ�����η���
            string cur = path[front++];
            cout<<cur<<' ';
            string next = firstAdjVertex(G,cur);    //���ڽӵ�
            while(visited.find(next)!=visited.end() && next.size())next = nextAdjVertex(G,cur,next);
            if(next.size()){    //���ڽӵ�δ���ʹ�����������
                path.push_back(next);
                rear++;
                visited[next] = true;
            }
        }
    }
    cout<<endl;
}

//10.BFS - ����
void BFS(Graph*G){
    if(!G || !G->vertexNum)return;
    cout<<"starting BFS\n";
    map<string,bool>visited;//���ʱ��
    vector<string>path;     //���ʶ���
    int front = 0,rear = 1;
    path.push_back(G->num2VertexMap[0]);    //��һ���������ʶ���
    visited[G->num2VertexMap[0]] = true;
    for(int i = 0;i < G->vertexNum;i++){    //��©��ÿһ����
        if(visited.find(G->num2VertexMap[i]) == visited.end()){ //����ǰ��δ���ʹ������������ʶ��в����
            path.push_back(G->num2VertexMap[i]);
            visited[G->num2VertexMap[i]] = true;
            rear++;
        }
        while(front<rear){  //�����в���ʱ�����η���
            string cur = path[front++];
            cout<<cur<<" ";
            string next = firstAdjVertex(G,cur);    //���ڽӵ�
            while(next.size()){    //���ڽӵ�δ���ʹ�����������
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

//11.��ͼG����v�����
int inDegree(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return -1;  //-1�޴˶���
    int i = G->vertex2NumMap[v];
    int count = 0;
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[j][i] != -1 && G->adjMatrix[j][i] != 0)count++;
    return count;
}

//12.��ͼG����v�����
int outDegree(Graph*G,string v){
    if(!G || G->vertex2NumMap.find(v) == G->vertex2NumMap.end())return -1;  //-1�޴˶���
    int i = G->vertex2NumMap[v];
    int count = 0;
    for(int j = 0;j < G->vertexNum;j++)
        if(G->adjMatrix[i][j] != -1 && G->adjMatrix[i][j] != 0)count++;
    return count;
}