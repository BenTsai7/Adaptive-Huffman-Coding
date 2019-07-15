#include"Decoder.h"
bool Decoder::decodeFile(char* filename,char *outputname){
    bool res=bitrd.open(filename);
    if(!res) return false;
    std::ofstream ofs;
    ofs.open(outputname,std::ios::trunc | std::ios::out);
    if(!ofs.is_open()) return false;
    tree = new Adaptive_Huffman_Tree;
    while(true){
        char c=decode();
        if(c==-1) break;
        ofs<<c;
        tree->updateTree(c);
    }
    return true;
};
char Decoder::decode(){
    char ans = -1;
    Node* node = tree->getRoot();
    bool NEW=false;
    while(true){
        if(node->left==NULL&&node->right==NULL){
            if(node==tree->getRoot()) bitrd.getNext();
            if(node->data == -1) NEW=true;
            else ans = node->data;
            break; 
        }
        char c = bitrd.getNext();
        if(c==-1) return ans;
        if(c=='1')
            node=node->right;
        if(c=='0')
            node=node->left;
    }
    if(NEW){ //use default code
        ans=0;
        for(int i=0;i<8;++i){
            ans = ans << 1;
            if(bitrd.getNext()=='1')
                ans = ans | 1;
        }
    }
    return ans;
};