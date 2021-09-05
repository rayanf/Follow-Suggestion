//rayan-forsat
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <list>
#include <vector>

#define SIZE 200
using namespace std;

#include "stdio.h"
#include "stdlib.h"

#define M 3

struct DataItem {
    char data[200];
    int key;
};


struct DataItem* hashArray[SIZE];
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
    return key % SIZE;
}

struct DataItem* searchHash(int key) {
    int hashIndex = hashCode(key);
    while (hashArray[hashIndex] != NULL) {
        if (hashArray[hashIndex]->key == key)
            return hashArray[hashIndex];
        ++hashIndex;
        hashIndex %= SIZE;
    }
    return NULL;
}


void insertHash(int key, char data[]) {

    struct DataItem* item = (struct DataItem*)malloc(sizeof(struct DataItem));
    strcpy(item->data, data);
    item->key = key;

    int hashIndex = hashCode(key);

    while (hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
        ++hashIndex;
        hashIndex %= SIZE;
    }
    hashArray[hashIndex] = item;
}


typedef struct _node {
	int    n; 
	int   keys[M - 1]; 
	struct _node* p[M]; 
} node;
node* root = NULL;

typedef enum KeyStatus {
	Duplicate,
	SearchFailure,
	Success,
	InsertIt,
	LessKeys,
} KeyStatus;

void insert(int key);
void DelNode(int x);
KeyStatus ins(node* r, int x, int* y, node** u);
int searchPos(int x, int* key_arr, int n);
KeyStatus del(node* r, int x);
bool search(int key);

// class  vector
// {
//     int *arr;
//     int top;
//     int capacity;

//     public:
//     vector(int size = SIZE);
//     void push_back(string);
//     int begin();
//     int end();
//     void clear();
//     int size();
// }

// vector::vector(int size){
//     arr = new int[size];
//     capacity = size;
//     back = -1;
//     // top = 0
// }

// vector::begin(){
//     return arr[0];
// }
// vector::end(){
//     return arr[-1];
// }
// vector::push_back(string name){
//     arr[back+1] = name;
//     back++;
// }
// vector::size(){
//     return back;
// }
// vector::clear(){
//     delete[] arr;
// }

class stack
{
    int *arr;
    int top;
    int capacity;
 
public:
    stack(int size = SIZE);         
    ~stack();                      
 
    void push(int);
    int pop();
    int topp();
 
    int size();
    bool isEmpty();
    bool isFull();
};
 
stack::stack(int size)
{
    arr = new int[size];
    capacity = size;
    top = -1;
}
 
stack::~stack() {
    delete[] arr;
}
 
void stack::push(int x)
{
    if (isFull())
    {
        exit(EXIT_FAILURE);
    }

    arr[++top] = x;
}
 
int stack::pop()
{
    if (isEmpty())
    {
        exit(EXIT_FAILURE);
    }
     return arr[top--];
}
 
int stack::topp()
{
    if (!isEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}
 
int stack::size() {
    return top + 1;
}
 
bool stack::isEmpty() {
    return top == -1;               
}
 
bool stack::isFull() {
    return top == capacity - 1;    
}

class Graph
{
	int V;  
	void fillOrder(int v, node* visited, stack& Stack);
	void DFSUtil(int v, node* visited);
public:
    list<int>* adj;
	Graph(int V);
	void addEdge(int v, int w);
	void printSCCs();
	Graph getTranspose();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}
list<int>* nodes = new list<int>[20];
void Graph::DFSUtil(int v, node* visited)
{
    insert(v);
    nodes->push_back(v);
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!search(*i))
			DFSUtil(*i, visited);
}

Graph Graph::getTranspose()
{
	Graph g(V);
	for (int v = 0; v < V; v++)
	{
		list<int>::iterator i;
		for (i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			g.adj[*i].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); 
}

void Graph::fillOrder(int v, node* visited, stack& Stack) 
{
	
    insert(v);
	list<int>::iterator i;
   
    for (i = adj[v].begin(); i != (adj[v].end()); ++i)
        if (!search(*i))
            fillOrder(*i, visited, Stack);
    
	Stack.push(v); 
}

void Graph::printSCCs()
{
	stack Stack(200);

	for (int i = 0; i < V; i++)
		if (search(i) == false)
			fillOrder(i, root, Stack); 

	Graph gr = getTranspose();

    for (int i = 0; i < V; i++)
        DelNode(i);
    
	while (Stack.isEmpty() == false) 
	{

		int v = Stack.topp(); 
		Stack.pop();  
		if (search(v) == 0)
		{
			gr.DFSUtil(v, root);
            nodes->push_back(-2);
		}
	}
}
void findStartPoint(string str,string* listt,int i)
{
    string word = "";
    for (auto x : str) 
    {
        if (x == ':')
        {
            listt[i] = word;
        }
        else {
            word = word + x;
        }
    }
}

void findEndPoint(string str,string* listt,int i)
{
    string word = "";
    for (auto x : str) 
    {
        if (x == ':')
        {
            word = "";
        }
        else {
            word = word + x;
        }
    }
    listt[i] = word;
}
void seperatendpoints(string str,string* endlist)
{
    string word = "";
    int i = 0;
    for (auto x : str) 
    {
        if (x == ' ')
        {
            endlist[i] = word;
            i += 1;
            word = "";
        }
        else {
            word = word + x;
        }
    } 
    endlist[i] = word; 
    endlist[i+1] = "end";
}
bool mycomp(string a, string b){
	return a<b;
}
vector<string> alphabaticallySort(vector<string> a){
	int n=a.size();
	
	sort(a.begin(),a.end(),mycomp);
	return a;
}

int main()
{
    string a;
    getline(cin,a);
    int n = stoi(a);


    Graph g(n);

    string* startpoint = new string[n];
    string* endpoint = new string[n];
    string* data = new string[n];

    
    string input;
    for (int i=0; i<n ; i++){
        getline(cin,data[i]);
        
            }
    for (int i=0; i<n; i++){
        findStartPoint(data[i], startpoint,i);
        findEndPoint(data[i], endpoint, i);

    }
    int hashlist[n] = {};
    for (int i=0; i<n; i++){
        hashlist[i] = i;
        
        char p[startpoint[i].length()+1];

        strcpy(p, startpoint[i].c_str());

    // safe
        insertHash(hashlist[i],p);
    // wrong
    }
    // return 0;
    
    for (int i=0; i<n; i++){
        string start;
        string end; 
        string* endlist = new string[n];  
        int endnum = 0;     
        start = startpoint[i];
        seperatendpoints(endpoint[i], endlist);
        for (int j=0;j<n; j++) {
            if (endlist[j] == "end"){
                break;
            }
            else{
                endnum += 1;
            }
        }
        for (int j=0; j<endnum;j++){
            for(int k=0; k<n; k++){
                if (endlist[j] == startpoint[k]){
                    DataItem* d1 = searchHash(i);
                    DataItem* d2 = searchHash(k);
                    g.addEdge(d1->key, d2->key);
                }
            }
        }
    }
    

    vector<string> names;
	g.printSCCs();
    int size = nodes->size();
    string namesmatrix[n][n];
    vector<string> subsort;
    int r = 0;
    for (int i = 0; i < size; i++){
        int a = nodes->front();
        if (a!=-2)
        {
            names.push_back(searchHash(a)->data);
        }
        else
        {   
            names=alphabaticallySort(names);

            for (int h=0; h<names.size(); h++){
                namesmatrix[r][h] = names[h];
            }
            r = r + 1;
            subsort.push_back(names[0]);
            names.clear();
        } 
        nodes->pop_front();

    }
    subsort=alphabaticallySort(subsort);
    for(int i=0; i<subsort.size(); i++){
        for(int k=0; k<n; k++){
            if(subsort[i]==namesmatrix[k][0]){
                for (int h=0; h<n; h++){
                cout<<namesmatrix[k][h]<<" ";
                }
                
                cout<<endl;
                break;
            }
        }
    }
    // delete[] hashArray;
    delete[] startpoint;
    delete[] endpoint;
    delete[] data;
	return 0;   
}


void insert(int key) {
    node* newnode;
    int upKey;
    KeyStatus value;
    value = ins(root, key, &upKey, &newnode);
    if (value == Duplicate)
        printf("Key already available\n");
    if (value == InsertIt) {
        node* uproot = root;
        root = (node*)malloc(sizeof(node));
        root->n = 1;
        root->keys[0] = upKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
    }
}

KeyStatus ins(node* ptr, int key, int* upKey, node** newnode) {
    node* newPtr, * lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    KeyStatus value;
    if (ptr == NULL) {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    if (n < M - 1) {
        pos = searchPos(newKey, ptr->keys, n);
        for (i = n; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n; 
        return Success;
    }
    if (pos == M - 1) {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else { 
        lastKey = ptr->keys[M - 2];
        lastPtr = ptr->p[M - 1];
        for (i = M - 2; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
    }
    splitPos = (M - 1) / 2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode) = (node*)malloc(sizeof(node));
    ptr->n = splitPos; 
    (*newnode)->n = M - 1 - splitPos;
    for (i = 0; i < (*newnode)->n; i++) {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if (i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}



bool search(int key) {
    int pos, i, n;
    node* ptr = root;
   
    while (ptr!=NULL) {
        n = ptr->n;
        pos = searchPos(key, ptr->keys, n);
        if (pos < n && key == ptr->keys[pos])
            return true;
        ptr = ptr->p[pos];
    }
    return false;
}

int searchPos(int key, int* key_arr, int n) {
    int pos = 0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}

void DelNode(int key) {
    node* uproot;
    KeyStatus value;
    value = del(root, key);
    switch (value) {
    case SearchFailure:
        printf("Key %d is not available\n", key);
        break;
    case LessKeys:
        uproot = root;
        root = root->p[0];
        free(uproot);
        break;
    default:
        return;
    }
}

KeyStatus del(node* ptr, int key) {
    int pos, i, pivot, n, min;
    int* key_arr;
    KeyStatus value;
    node** p, * lptr, * rptr;

    if (ptr == NULL)
        return SearchFailure;
    
    n = ptr->n;
    key_arr = ptr->keys;
    p = ptr->p;
    min = (M - 1) / 2;

                                      
    pos = searchPos(key, key_arr, n);
    
    if (p[0] == NULL) {
        if (pos == n || key < key_arr[pos])
            return SearchFailure;
        for (i = pos + 1; i < n; i++)
        {
            key_arr[i - 1] = key_arr[i];
            p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
    }   

     
    if (pos < n && key == key_arr[pos]) {
        node* qp = p[pos], * qp1;
        int nkey;
        while (1) {
            nkey = qp->n;
            qp1 = qp->p[nkey];
            if (qp1 == NULL)
                break;
            qp = qp1;
        }
        key_arr[pos] = qp->keys[nkey - 1];
        qp->keys[nkey - 1] = key;
    }
    value = del(p[pos], key);
    if (value != LessKeys)
        return value;

    if (pos > 0 && p[pos - 1]->n > min) {
        pivot = pos - 1; 
        lptr = p[pivot];
        rptr = p[pos];

        rptr->p[rptr->n + 1] = rptr->p[rptr->n];
        for (i = rptr->n; i > 0; i--) {
            rptr->keys[i] = rptr->keys[i - 1];
            rptr->p[i] = rptr->p[i - 1];
        }
        rptr->n++;
        rptr->keys[0] = key_arr[pivot];
        rptr->p[0] = lptr->p[lptr->n];
        key_arr[pivot] = lptr->keys[--lptr->n];
        return Success;
    }
    if (pos < n && p[pos + 1]->n > min) {
        pivot = pos; 
        lptr = p[pivot];
        rptr = p[pivot + 1];
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        key_arr[pivot] = rptr->keys[0];
        lptr->n++;
        rptr->n--;
        for (i = 0; i < rptr->n; i++) {
            rptr->keys[i] = rptr->keys[i + 1];
            rptr->p[i] = rptr->p[i + 1];
        }
        rptr->p[rptr->n] = rptr->p[rptr->n + 1];
        return Success;
    }

    if (pos == n)
        pivot = pos - 1;
    else
        pivot = pos;

    lptr = p[pivot];
    rptr = p[pivot + 1];
    
    lptr->keys[lptr->n] = key_arr[pivot];
    lptr->p[lptr->n + 1] = rptr->p[0];
    for (i = 0; i < rptr->n; i++) {
        lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
        lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
    }
    lptr->n = lptr->n + rptr->n + 1;
    free(rptr); 
    for (i = pos + 1; i < n; i++) {
        key_arr[i - 1] = key_arr[i];
        p[i] = p[i + 1];
    }
    return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}
