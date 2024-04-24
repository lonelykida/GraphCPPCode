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
}
