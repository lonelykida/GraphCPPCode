#include "Graph.cpp"

int main(){
    Graph* G = initGraph();
    inputGraph(G);
    DFS(G);
    BFS(G);
    // int * a = new int(2);
    // int *b = new int(3);
    // cout<<"address of a = "<<a<<" and address of b = "<<b<<endl;
    // vector<int*> arr;
    // arr.push_back(a);
    // cout<<"address of arr[0] = "<<arr[0]<<endl;
    // arr.push_back(b);
    // arr.erase(arr.begin());
    // cout<<"address of a = "<<a<<" and address of b = "<<b<<endl;
    // delete a;
    
    // cout<<"address of a = "<<a<<" and address of b = "<<b<<endl;
    return 0;
}