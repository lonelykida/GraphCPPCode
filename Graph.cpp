//encoding :GBK
#include "definition.hpp"

//1.init Graph
Graph* initGraph(void){
    Graph* G = new Graph;
    return G?G:NULL;
}

//2.input Graph information
void inputGraph(Graph* G){
    do{
        string node1,node2;
        cout<<"now input two nodes that are connected to each other:(Enter # to end input)"<<endl;
        cout<<"node1:";     //(1)input two nodes : node1 and node2
        cin>>node1;
        if(node1 == "#")break;
        cout<<"node2:";
        cin>>node2;
        int w = 0;
        cout<<"input the weight of the edge between these two nodes:";
        cin>>w;
        Vertex*v1,*v2;
        if(G->vertexMap.find(node1)==G->vertexMap.end())v1 = new Vertex;    //(2)get vertex
        else v1 = G->vertexMap[node1];
        if(G->vertexMap.find(node2)==G->vertexMap.end())v2 = new Vertex;
        else v2 = G->vertexMap[node2];
        if(G->vertexMap.find(node1)!=G->vertexMap.end() 
        && G->vertexMap.find(node2)!=G->vertexMap.end()){   //(3)node1 and node2 has been existed
            bool flag = false;
            //check the edge between these two nodes is existed or not
            for(int i = 0;i < v1->adjVertexs.size();i++)
                if(v1->adjVertexs[i] == node2){flag = true;break;}
            if(flag)continue;   //continue to add next two nodes and the edge between them
        }
        Edge*e = new Edge;  //(4)create new edge
        v1->title = node1;  //(5)renew information about the edge and the vertex
        v2->title = node2;
        v1->data = node1;
        v2->data = node2;
        v1->adjVertexs.push_back(node2);    //add node2 to v1's adjacent vertex
        e->num = numEdge++;
        e->from = node1;
        e->to = node2;
        e->weight = w;
        v1->Edges.push_back(e->num);
        v2->Edges.push_back(e->num);
        if(G->vertexMap.find(node1)==G->vertexMap.end()){   //(6)add vertex to Graph
            G->vertexs.push_back(v1);
            G->edges.push_back(e);
            G->vertexMap[node1] = v1;
            G->edgeMap[e->num] = e;//edge is no in the vertex's edges
        }
        if(G->vertexMap.find(node2)==G->vertexMap.end()){
            G->vertexs.push_back(v2);
            if(G->edgeMap.find(e->num)==G->edgeMap.end()) {
                G->edges.push_back(e);
                G->edgeMap[e->num] = e;
            }
            G->vertexMap[node2] = v2;
        }
        cout<<"These two nodes has been add to the Graph successfully!"<<endl;
    }while(1);
    cout<<"end with INPUT."<<endl;
}

//3.Find vertex 'vex' in Graph G and then return the vertex's pointer or NULL if not found
Vertex* getVertex(Graph*G,string vex){
    if(!G || G->vertexMap.find(vex) == G->vertexMap.end())return NULL;
    return G->vertexMap.find(vex)->second;
}

//4.put a value to vertex 'vex' in graph G
bool putVertexValue(Graph*G,string vex,string value){
    if(!G || G->vertexMap.find(vex) == G->vertexMap.end())return false;
    G->vertexMap[vex]->data = value;
    return true;
}

//5.Find the 1st adjacent vertex of 'vex' in graph G,or NULL if not found
Vertex* firstAdjVertex(Graph*G,string vex){
    if(!G || G->vertexMap.find(vex)==G->vertexMap.end())return NULL;
    return G->vertexMap[G->vertexMap[vex]->adjVertexs[0]];
}

//6.Find the next adjacent vertex of 'w' in 'vex' in graph G or NULL if 'w' is the last one
Vertex* nextAdjVertex(Graph*G,string vex,string w){
    if(!G || G->vertexMap.find(vex) == G->vertexMap.end() 
    || G->vertexMap[vex]->adjVertexs[G->vertexMap[vex]->adjVertexs.size()-1] == w)return NULL;
    for(int i = 0;i < G->vertexMap[vex]->adjVertexs.size();i++)
        if(G->vertexMap[vex]->adjVertexs[i] == w)return G->vertexMap[G->vertexMap[vex]->adjVertexs[i+1]];
    return NULL;    
}

//7.delete the vertex and the edges connected with it
bool delVertex(Graph*G,string vex){
    //do not find the vertex
    if(!G || G->vertexMap.find(vex) == G->vertexMap.end())return false;
    Vertex*curv = G->vertexMap[vex];    //get current edge vex
    while(curv->Edges.size()){
        Edge*cure = G->edges[curv->Edges[0]];   //get 1st edge of vex
        //find the another vertex of edge cure
        string anotherVexName = (cure->from == vex)?cure->to:cure->from;
        Vertex*anotherVex = G->vertexMap[anotherVexName];
        //delete the edge between vex and anotherVex
        anotherVex->Edges.erase(find(anotherVex->Edges.begin(),anotherVex->Edges.end(),cure->num));
        anotherVex->adjVertexs.erase(find(anotherVex->adjVertexs.begin(),anotherVex->adjVertexs.end(),vex));
        //delete the adjacent vertex of anotherVex
        if(cure->from == anotherVexName)anotherVex->adjVertexs.erase(find(anotherVex->adjVertexs.begin(),anotherVex->adjVertexs.end(),cure->to));
        G->edges.erase(find(G->edges.begin(),G->edges.end(),cure));
        G->edgeMap.erase(cure->num);
        curv->Edges.erase(curv->Edges.begin());
        delete cure;
    }
    delete curv;
    return true;
}

//8.insert the edge between 'from' and 'to','from' and 'to' must be in the Graph
bool insertEdge(Graph*G,string from,string to){
    if(!G || G->vertexMap.find(from) == G->vertexMap.end() || G->vertexMap.find(to) == G->vertexMap.end())return false;
    if(find(G->vertexMap.find(from)->second->adjVertexs.begin(),G->vertexMap.find(from)->second->adjVertexs.end(),to)
     != G->vertexMap.find(from)->second->adjVertexs.end())return true;  //edge has been existed
    Edge*e = new Edge;
    e->from = from;
    e->to = to;
    cout<<"input the weight of the edge between these two vertex:"<<endl;
    cin>>e->weight;
    e->num = numEdge++;
    G->edges.push_back(e);
    G->edgeMap[e->num] = e;
    G->vertexMap[from]->Edges.push_back(e->num);
    G->vertexMap[to]->Edges.push_back(e->num);
    G->vertexMap[from]->adjVertexs.push_back(to);
    return true;
}

//9.delete the edge between 'from' and 'to','from' and 'to' must be in the Graph
bool deleteEdge(Graph*G,string from,string to){
    if(!G || G->vertexMap.find(from) == G->vertexMap.end() || G->vertexMap.find(to) == G->vertexMap.end())return false;
    if(find(G->vertexMap[from]->adjVertexs.begin(),G->vertexMap[from]->adjVertexs.end(),to)
     == G->vertexMap[from]->adjVertexs.end())return false;  //edge has not been existed
    Vertex*vA = G->vertexMap[from],*vB = G->vertexMap[to];
    vA->adjVertexs.erase(find(vA->adjVertexs.begin(),vA->adjVertexs.end(),to));
    //find the edge of vA and vB
    for(int i = 0;i < vA->Edges.size();i++){
        Edge*cure = G->edgeMap[vA->Edges[i]];
        if(cure->from == from && cure->to == to){
            vA->Edges.erase(vA->Edges.begin()+i);
            G->edges.erase(find(G->edges.begin(),G->edges.end(),cure));
            G->edgeMap.erase(cure->num);
            delete cure;
            break;
        }
    }
    for(int i = 0;i < vB->Edges.size();i++){
        Edge*cure = G->edgeMap[vB->Edges[i]];
        if(cure->from == from && cure->to == to){
            vB->Edges.erase(vB->Edges.begin()+i);
            break;
        }
    }
    return true;
}

//10.DFS - Depth First Search
void DFS(Graph*G){
    if(!G || !G->vertexs.size())return;
    cout<<"starting DFS.\n";
    vector<Vertex*>visitedQueue;    //queue for DFS
    map<string,bool>visitedMap;     //map for visited
    visitedQueue.push_back(G->vertexs[0]);  //1st vertex input to the visited queue
    int rear = 1,front = 0;         //queue rear and front
    for(int i = 0;i < G->vertexs.size();i++){   //to make sure all vertices can be visited
        if(find(visitedQueue.begin(),visitedQueue.end(),G->vertexs[i]) == visitedQueue.end()){
            visitedQueue.push_back(G->vertexs[i]);  //push the vertex to the queue
            rear++;
        }
        while(front<rear){          //visit all vertex in the queue
            Vertex*cur = visitedQueue[front++];
            cout<<cur->title<<" ";
            visitedMap[cur->title] = true;  //renew the visited map
            for(int j = 0;j < cur->adjVertexs.size();j++)
                if(visitedMap.find(cur->adjVertexs[j]) == visitedMap.end() || !visitedMap[cur->adjVertexs[j]]){
                        visitedQueue.push_back(G->vertexMap[cur->adjVertexs[j]]);
                        rear++;
                        break;
                }
        }
    }
    cout<<endl;
}

//11.BFS - Breadth First Search
void BFS(Graph*G){
    if(!G || !G->vertexs.size())return ;
    cout<<"starting BFS.\n";
    vector<Vertex*>visitedQueue;    //queue for BFS
    map<string,bool>visitedMap;     //map for visited
    visitedQueue.push_back(G->vertexs[0]);  //1st vertex input to the visited queue
    int rear = 1,front = 0;         //queue rear and front
    for(int i = 0;i < G->vertexs.size();i++){   //to make sure all vertices can be visited
        if(find(visitedQueue.begin(),visitedQueue.end(),G->vertexs[i]) == visitedQueue.end()){
            visitedQueue.push_back(G->vertexs[i]);  //push the vertex to the queue
            rear++;
        }
        while(front<rear){
            Vertex*cur = visitedQueue[front++];
            cout<<cur->title<<" ";
            visitedMap[cur->title] = true;  //renew the visited map
            for(int j = 0;j < cur->adjVertexs.size();j++)
                if(find(visitedQueue.begin(),visitedQueue.end(),G->vertexMap[cur->adjVertexs[j]]) == visitedQueue.end()){
                    visitedQueue.push_back(G->vertexMap[cur->adjVertexs[j]]);
                    rear++;
                }
        }
    }
    cout<<endl;
}

