#ifndef Tree
#define Tree
#include"Adaptive_Huffman_Tree.h"
#include"BitIO.h"
#endif
class Encoder{
    private:
        Adaptive_Huffman_Tree* tree;
        BitWriter bitwrt;
    public:
        bool encodeFile(char* filename,char *outputname);
        void encode(char c);
};