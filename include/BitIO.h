#include<fstream>
#include<vector>
#include<iostream>
class BitWriter{
    private:
        std::vector<char> charlist;
        std::string bits;
        std::fstream ofs;
    public:
        bool open(char* filename);
        void write(std::string& s);
        void close();
};
class BitReader{
    private:
        int unused;
        unsigned int count;
        unsigned int curByte;
        unsigned int curBit;
        unsigned int endBit;
        unsigned int endByte;
        std::fstream ifs;
        std::string byte;
        std::vector<char> charlist;
        void read();
    public:
        bool eof = false;
        bool open(char* filename);
        char getNext();
        void close();
};
std::string byteTostring(char byte);
char stringTobyte(std::string& s);