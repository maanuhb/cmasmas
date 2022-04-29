enum category {ARRAY,MATRIX,SINGLE_LINKED_LIST,DOUBLE_LINKED_LIST,BINARY_SEARCH_TREE,GRAPH};

typedef struct Data{
    int n;
    int m;
    Data(){}
} Data;

template <typename type>
struct Node{
    type data;
};

template <typename type>
struct NodeSL: Node<type>{
    type data;
    NodeSL<type>* next;
};

template <typename type>
struct NodeDL: Node<type>{
    type data;
    NodeDL<type>* prev;
    NodeDL<type>* next;
};

template <typename type>
struct NodeT: Node<type>{
    type data;
    NodeT<type>* parent;
    NodeT<type>* left;
    NodeT<type>* right;
};

template <typename type>
struct NodeG: Node<type>{
    bool entry;
    int id;
    type data;
    NodeSL<NodeG<type>*>* connections;
    NodeG<type>* next;
};

#include "DS.h"

#include "dynamics/DSSL.h"
#include "dynamics/DSG.h"

template <typename type>
class SDDS{
private:
    static Data ref;

    static void insert_aux(insertable<type>* var, type value){
        var->insert(value);
    }

    static void insert_pos_aux(positionable<type>* var, int n, type value){
        var->insert(n, value);
    }

    static void extract_aux(positionable<type>* var, int pos, type* res){
        *res = var->extract(pos);
    }

    static void extension_aux(measurable* var, int* n){
        *n = var->extension();
    }

    static void reverse_aux(reversible* var){
        var->reverse();
    }
    static void extractNode(DS<type>* G, int id, NodeG<type>** node){
        NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();
        while(graph != NULL){
            if(graph->id == id) break;
            graph = graph->next;
        }
        *node = graph;
    }

    static void insert_connections(DS<type>* G, int id, NodeSL<NodeG<type>*>* C){
        NodeG<type>* graph = (NodeG<type>*) ( (DSG<type>*) G )->getRoot();
        while(graph != NULL){
            if(graph->id == id){
                graph->connections = C;
                break;
            }
            graph = graph->next;
        }
    }

public:
    static void destroy(DS<type>* var){
        var->destroy();
    }
    static void search(DS<type>* var, type value, bool* res){
        *res = var->search(value);
    }
    static void count(DS<type>* var, type value, int* res){
        *res = var->count(value);
    }
    static void show(DS<type>* var, bool verbose){
        var->show(verbose);
    }


    static void create(DS<type>** var, category cat){
        switch(cat){
            case SINGLE_LINKED_LIST: {
                DSSL<type>* SL = new DSSL<type>();
                SL->create();
                *var = SL;
                break;
            }
            case GRAPH: {
                DSG<type>* G = new DSG<type>();
                G->create();
                *var = G;
                break;
            }
        }
    }


    static void extension(DS<type>* var, int* n){
        category cat = var->getCategory();
        switch(cat){
            case SINGLE_LINKED_LIST: {
                extension_aux( ((DSSL<type>*) var), n);
                break;
            }
            case GRAPH: {
                extension_aux( ((DSG<type>*) var), n);
                break;
            }
        }
    }

    static void insert(DS<type>* var, type value){
        category cat = var->getCategory();
        switch(cat){
            case SINGLE_LINKED_LIST: {
                insert_aux( ((DSSL<type>*) var), value);
                break;
            }
        }
    }
    static void insert(DS<type>* var, int n, type value){
        category cat = var->getCategory();
        switch(cat){
            case SINGLE_LINKED_LIST: {
                insert_pos_aux( ((DSSL<type>*) var), n, value);
                break;
            }
            case GRAPH: {
                insert_pos_aux( ((DSG<type>*) var), n, value);
                break;
            }
        }
    }

    static void extract(DS<type>* var, int pos, type* res){
        category cat = var->getCategory();
        switch(cat){

            case SINGLE_LINKED_LIST: {
                extract_aux( ((DSSL<type>*) var), pos, res);
                break;
            }
            case GRAPH: {
                extract_aux( ((DSG<type>*) var), pos, res);
                break;
            }
        }
    }

    static void reverse(DS<type>* var){
        category cat = var->getCategory();
        switch(cat){
            case SINGLE_LINKED_LIST: {
                reverse_aux( ((DSSL<type>*) var) );
                break;
            }
        }
    }
    static void define_connections(DS<type>* G, int id, DS<int>* C){
        DSSL<NodeG<int>*>* graph_nodes = new DSSL<NodeG<int>*>();
        NodeG<int>* temp;
        DSSL<int>* L = (DSSL<int>*) C;
        for(int i= 0; i < L->extension(); i++){
            extractNode(G,L->extract(i),&temp);
            graph_nodes->insert(temp);
        }
        insert_connections(G,id, (NodeSL<NodeG<int>*>*) graph_nodes->getRoot());
        delete graph_nodes;
    }
    static void create_copy(DS<type>* original, DS<type>** clone){
        switch(original->getCategory()){

            case SINGLE_LINKED_LIST: {
                *clone = new DSSL<type>();
                ((DSSL<type>*) *clone)->create();
                NodeSL<type>* SL = (NodeSL<type>*) ((DSSL<type>*) original)->getRoot();
                while(SL != NULL){
                    insert_aux( ((DSSL<type>*) *clone), SL->data);
                    SL = SL->next;
                }
                reverse_aux( ((DSSL<type>*) *clone) );
                break;
            }

            case GRAPH: {
                *clone = new DSG<type>();
                ((DSG<type>*) *clone)->create();
                NodeG<type>* G = (NodeG<type>*) ((DSG<type>*) original)->getRoot();
                while(G != NULL){
                    insert_pos_aux( ((DSG<type>*) *clone), G->id, G->data);
                    NodeSL<NodeG<type>*>* O = G->connections;
                    DSSL<NodeG<type>*>* L = new DSSL<NodeG<type>*>();
                    L->create();
                    while(O != NULL){
                        L->insert(O->data);
                        O = O->next;
                    }
                    L->reverse();
                    insert_connections(*clone,G->id,(NodeSL<NodeG<type>*>* ) L->getRoot());
                    G = G->next;
                    delete L;
                }
                break;
            }
        }
    }


};
