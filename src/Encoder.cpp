#include"Encoder.h"
bool Encoder::encodeFile(char* filename,char *outputname){
    bool res=bitwrt.open(outputname);
    if(!res) return false;
    tree = new Adaptive_Huffman_Tree;
    std::ifstream ifs(filename,std::ios::in);
    if(!ifs.is_open()) return false;
    char c;
    ifs.get(c);
    while(!ifs.eof()){
        encode(c);
        tree->updateTree(c);
        ifs.get(c);
    }
    tree->printTree();
    delete tree;
    ifs.close();
    bitwrt.close();
    return true;
};
void Encoder::encode(char c){
    std::string s=tree->getCode(c);
    if(s.compare("")==0){ //use default code
        std::string NEW =tree->getCode(-1);
        bitwrt.write(NEW);
        int ascii = c;
        for(int i=0;i<8;++i){
            int bit = ascii % 2;
            if(bit) s="1"+s;
            else s = "0"+s;
            ascii /= 2;
        }
    }
    bitwrt.write(s);
};