#include<string>
#include<queue>
#include<unordered_map>
#include<iostream>
struct Node{ //Huffman Tree Node
	char data;//if data==-1,it 's a node for New
	int weight;
	Node* left;
	Node* right;
    Node* parent;
	Node(){left=NULL;right=NULL;parent=NULL;data=-1;weight=0;}
    Node(Node* parent,char c,int weight){left=NULL;right=NULL;this->parent=parent;this->data=c;this->weight=weight;}
};
class Adaptive_Huffman_Tree{
    private:
        Node* root;
        Node* newNode;//new nodes insert at newNode;
        std::unordered_map<char,Node*> hashmap;//speed up query
        void recursiveDelete(Node* node);
        Node* getSwapableNode(Node* node);
        Node* findNode(char c);//find nodes stored in hash map
        void swap(Node* n1,Node *n2);
        void updateNode(Node* node);
        bool inSameTree(Node* root,Node* node);
        void insert(char c);
    public:
        Adaptive_Huffman_Tree();
        ~Adaptive_Huffman_Tree();
        std::string getCode(char c);
        bool ifExist(char c);//check if a char is in the tree
        void updateTree(char c);
        void printTree();
        Node* getRoot(){return root;}
};