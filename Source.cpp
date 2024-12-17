#include <iostream>
#include <stack>
using namespace std;

struct Vertex {
    int value;             
    Vertex* next;          
    struct Edge* edges;    
    bool visited;         
};

struct Edge {
    Vertex* connectedVertex;            
    Edge* next;            
};

class Graph {
    Vertex* head; 

public:
    Graph() : head(nullptr) {} 

    void insertVertex(int value);       
    void deleteVertex(int value);       
    void insertEdge(int from, int to);  
    void deleteEdge(int from, int to);  
    void AdjacentVertex(int value);    
    bool isEmpty();                     
    Vertex* findVertex(int value);      
    void DFS(int startValue);           
    void resetVisited();                
    void displayGraph();              
};

void Graph::insertVertex(int value) {
    if (findVertex(value)) {
        cout << "Vertex " << value << " already exists!\n";
        return;
    }

    Vertex* newVertex = new Vertex();
    newVertex->value = value;
    newVertex->next = nullptr;
    newVertex->edges = nullptr;
    newVertex->visited=false;

    //if head dosen't exist make the new vertex head
    if (!head) {
        head = newVertex;
    }
    else { //else if head exists traverse to the last vertex and insert new vertex as its next
        Vertex* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newVertex;
    }
    cout << "Vertex " << value << " added successfully.\n";
}


void Graph::deleteVertex(int value) {
    Vertex* current = head;
    Vertex* prev = nullptr;

    while (current && current->value != value) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Vertex " << value << " not found.\n";
        return;
    }

    // once vertext is found remove edges connected to this vertex
    Vertex* temp = head;
    while (temp) {
        deleteEdge(temp->value, value);
        temp = temp->next;
    }

    // After deleting edges delete the vertex itself
    if (prev) {
        prev->next = current->next;
    }
    else {
        head = current->next;
    }
    delete current;
    cout << "Vertex " << value << " deleted successfully.\n";
}

void Graph::insertEdge(int source, int destination) {
    Vertex* sourceVertex = findVertex(source);
    Vertex* destinationVertex = findVertex(destination);

    if (!sourceVertex || !destinationVertex) {
        cout << "One or both vertices not found!\n";
        return;
    }

    // Add edge from 'sourceVertex' to 'destinationVertex'
    Edge* newEdge = new Edge{ destinationVertex, nullptr };
    if (!sourceVertex->edges) {
        sourceVertex->edges = newEdge;
    }
    else {
        Edge* temp = sourceVertex->edges;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEdge;
    }

    cout << "Edge added between " << source << " and " << destination << ".\n";
}

void Graph::deleteEdge(int source, int destination) {
    Vertex* sourceVertex = findVertex(source);

    if (!sourceVertex) {
        cout << "Vertex " << source << " not found.\n";
        return;
    }

    Edge* current = sourceVertex->edges;
    Edge* prev = nullptr;

    while (current && current->connectedVertex->value != destination) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        cout << "Edge between " << source << " and " << destination << " not found.\n";
        return;
    }

    if (prev) {
        prev->next = current->next;
    }
    else {
        sourceVertex->edges = current->next;
    }
    delete current;
    cout << "Edge between " << source << " and " << destination << " deleted successfully.\n";
}

void Graph::AdjacentVertex(int value) {
    Vertex* vertex = findVertex(value);

    if (!vertex) {
        cout << "Vertex " << value << " not found.\n";
        return;
    }

    cout << "Adjacent vertices of " << value << ": ";
    Edge* edge = vertex->edges;
    while (edge) {
        cout << edge->connectedVertex->value << " ";
        edge = edge->next;
    }
    cout << endl;
}

bool Graph::isEmpty() {
    return head == nullptr;
}

Vertex* Graph::findVertex(int value) {
    Vertex* temp = head;
    while (temp) {
        if (temp->value == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void Graph::DFS(int startValue) {
    Vertex* startVertex = findVertex(startValue);       //find starting vertex in graph
    if (!startVertex) {
        cout << "Starting vertex not found!\n";
        return;
    }

    stack<Vertex*> s;       //then initialize stack with all unvisited vertices for traversal
    s.push(startVertex);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        Vertex* current = s.top(); //pop stack for processing
        s.pop();

        if (!current->visited) {
            cout << current->value << " ";
            current->visited = true; //Visit each vertex and mark it as visited

            Edge* edgeTemp = current->edges;
            while (edgeTemp) {
                if (!edgeTemp->connectedVertex->visited) {
                    s.push(edgeTemp->connectedVertex);
                }
                edgeTemp = edgeTemp->next;
            }
        }
    }
    cout << endl;

    resetVisited(); // Reset the visited status for next search
}

void Graph::resetVisited() {
    Vertex* temp = head;
    while (temp) {
        temp->visited = false;
        temp = temp->next;
    }
}

void Graph::displayGraph() {
    Vertex* temp = head;
    cout << "Graph adjacency list:\n";
    while (temp) {
        cout << temp->value << ": ";
        Edge* edgeTemp = temp->edges;
        while (edgeTemp) {
            cout << edgeTemp->connectedVertex->value << " ";
            edgeTemp = edgeTemp->next;
        }
        cout << endl;
        temp = temp->next;
    }
}


int getValidInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
    return value;
}

int main() {
    Graph g;
    int choice, value, source, destination, startValue;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Vertex\n";
        cout << "2. Delete Vertex\n";
        cout << "3. Insert Edge\n";
        cout << "4. Delete Edge\n";
        cout << "5. Display Adjacent Vertices\n";
        cout << "6. Check if Graph is Empty\n";
        cout << "7. Display Graph\n";
        cout << "8. Perform DFS\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidInt();

        switch (choice) {
        case 1:
            cout << "Enter vertex value: ";
            value = getValidInt();
            g.insertVertex(value);
            break;
        case 2:
            cout << "Enter vertex value to delete: ";
            value = getValidInt();
            g.deleteVertex(value);
            break;
        case 3:
            cout << "Enter source vertex of edge: \n";
            source = getValidInt();
            cout << "Enter destination vertex of edge: \n";
            destination = getValidInt();
            g.insertEdge(source, destination);
            break;
        case 4:
            cout << "Enter source vertex of edge you want to delete: ";
            source = getValidInt();
            cout << "Enter destination vertex of edge you want to delete: ";
            destination = getValidInt();
            g.deleteEdge(source, destination);
            break;
        case 5:
            cout << "Enter vertex to find adjacent vertices: ";
            value = getValidInt();
            g.AdjacentVertex(value);
            break;
        case 6:
            cout << (g.isEmpty() ? "Graph is empty." : "Graph is not empty.") << endl;
            break;
        case 7:
            g.displayGraph();
            break;

        case 8:
            cout << "Enter starting vertex for DFS: ";
            startValue = getValidInt();
            g.DFS(startValue);
            break;

        case 9:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
