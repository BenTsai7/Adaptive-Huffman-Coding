#include"Adaptive_Huffman_Tree.h"
Adaptive_Huffman_Tree::Adaptive_Huffman_Tree(){
    root = new Node;
    newNode = root;
    hashmap.insert(std::make_pair(-1,newNode));
};
Adaptive_Huffman_Tree::~Adaptive_Huffman_Tree(){
    recursiveDelete(root);
};
Node* Adaptive_Huffman_Tree::findNode(char c){
    auto iter = hashmap.find(c);
    if(iter==hashmap.end()) return NULL;
    return iter->second;
}
bool Adaptive_Huffman_Tree::ifExist(char c){
    return hashmap.find(c)!=hashmap.end();
}
void Adaptive_Huffman_Tree::recursiveDelete(Node* node){
    if(node->left) recursiveDelete(node->left);
	if(node->right) recursiveDelete(node->right);
	delete node;
};
void Adaptive_Huffman_Tree::updateTree(char c){
    Node* node = findNode(c);
    if(node==NULL) insert(c);
    updateNode(node);
};
void Adaptive_Huffman_Tree::updateNode(Node* node){
    if(node==NULL) return;
    Node* swapNode = getSwapableNode(node);
    if(swapNode!=NULL){
        swap(node,swapNode);
    }
    ++node->weight;
    if(node->parent) updateNode(node->parent);
}
void Adaptive_Huffman_Tree::swap(Node* n1,Node *n2){
    Node* tmp=n1->parent;
    bool n1left = (n1->parent)->left==n1;
    bool n2left = (n2->parent)->left==n2;
    if(n1left){
        n1->parent->left=n2;
    }
    else{
        n1->parent->right=n2;
    }
    if(n2left){
        n2->parent->left=n1;
    }
    else{
        n2->parent->right=n1;
    }
    n1->parent=n2->parent;
    n2->parent=tmp;
};
void Adaptive_Huffman_Tree::insert(char c){
    newNode->left=new Node;
    newNode->right=new Node(newNode,c,1);
    newNode->left->parent = newNode;
    hashmap.insert(std::make_pair(c,newNode->right));//insert it into hash map
    newNode=newNode->left;
    newNode->data=-1;
    auto iter = hashmap.find(-1);
    iter->second=newNode;
    Node* tmp = newNode->parent;
    while(tmp){
        tmp->weight+=1;
        tmp = tmp->parent;
    }
};
Node* Adaptive_Huffman_Tree::getSwapableNode(Node* node){
    std::queue<Node*> q;
    std::queue<Node*> swapnodes;
    q.push(root);
    while(!q.empty()){
        Node* tmp= q.front();
        q.pop();
        if(tmp==node) break;
        swapnodes.push(tmp);
        if(tmp->right) q.push(tmp->right);
        if(tmp->left) q.push(tmp->left);
    }
    while(!swapnodes.empty()){
        Node* tmp = swapnodes.front();
        swapnodes.pop();
        if(tmp->weight==node->weight&&(!inSameTree(tmp,node))) return tmp;
    }
    return NULL;
};
std::string Adaptive_Huffman_Tree::getCode(char c){
    Node* node=findNode(c);
    std::string code ="";
    if (c==-1&&node==root) return "0";
    if(node==NULL) return code;
    while(node->parent!=NULL){
        Node* tmp = node->parent;
        if(tmp->left==node) code = "0"+code;
        else code = "1"+code;
        node = tmp;
    }
    return code;
};
void Adaptive_Huffman_Tree::printTree(){
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* tmp= q.front();
        q.pop();
        if(tmp->left==NULL && tmp->right==NULL){
            if(tmp->data==-1) std::cout<<"NEW";
            else std::cout<<tmp->data;
            std::cout<<" : "<<tmp->weight<<" code:"<<getCode(tmp->data)<<std::endl;
            continue;
        }
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
    }
    std::cout<<"-------------------------------------"<<std::endl;
}
bool Adaptive_Huffman_Tree::inSameTree(Node* root,Node* node){
    while(node!=NULL){
        if(node==root) return true;
        node = node->parent;
    }
    return false;
}