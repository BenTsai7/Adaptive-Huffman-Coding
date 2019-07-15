#ifndef Tree
#define Tree
#include"Adaptive_Huffman_Tree.h"
#include"BitIO.h"
#endif
class Decoder{
    private:
        Adaptive_Huffman_Tree* tree;
        BitReader bitrd;
    public:
        bool decodeFile(char* filename,char *outputname);
        char decode();
};