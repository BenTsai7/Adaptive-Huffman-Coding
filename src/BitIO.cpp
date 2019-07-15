#include"BitIO.h"
bool BitWriter::open(char* filename){
    if (ofs.is_open()) return false;
    ofs.open(filename,std::ios::out | std::ios::trunc | std::ios::binary);
    if (ofs.is_open()) return true;
    return false;
};
void BitWriter::write(std::string& s){
    bits += s;
    while(bits.size()>7){
        char byte = stringTobyte(bits);//write into vector in bytes
        charlist.push_back(byte);
        bits = bits.substr(8);
    }
};
void BitWriter::close(){
    if(!ofs.is_open()) return;
    int unused=8-bits.size();
    if(unused==8) unused=0;
    for(int i=0;i<unused;++i) {std::string zero("0");write(zero);}
    ofs.write(reinterpret_cast<char *>(&unused),sizeof(unused));
    int totalsize=charlist.size();
    for(int i=0;i<totalsize;++i){ofs.write(&charlist[i],sizeof(char));}
    ofs.close();
};
bool BitReader::open(char* filename){
    if (ifs.is_open()) return false;
    ifs.open(filename,std::ios::in | std::ios::binary);
    eof=false;
    if (ifs.is_open()) {read();return true;}
    return false;
};
void BitReader::read(){
    char byte;
    ifs.read(reinterpret_cast<char *>(&unused),sizeof(unused));
    count=0;
    curByte=0;
    curBit=0;
    ifs.read(&byte,sizeof(char));
    while(!ifs.eof()){
        charlist.push_back(byte);
        ++count;
        ifs.read(&byte,sizeof(char));
    }
    endByte=charlist.size()-1;
    endBit= 8-unused;
    this->byte = byteTostring(charlist[0]);
    ifs.close();
};
void BitReader::close(){
    if(ifs.is_open()) ifs.close();
};
char BitReader::getNext(){
    if(eof) {charlist.clear();return -1;}
    if(curByte==endByte&&curBit==endBit-1)
        eof = true;
    char c = byte[curBit];
    ++curBit;
    if(curBit==8) {curBit=0;++curByte;byte = byteTostring(charlist[curByte]);}
    return c;
};
std::string byteTostring(char byte){
    std::string s;
    for(int i=0;i<8;++i){
        if((byte&1)==1) s="1"+s;
        else s="0"+s;
        byte = byte>>1;
    }
    return s;
};
char stringTobyte(std::string& s){
    char byte = 0;
    for(int i=0;i<8;++i){
            byte = byte << 1;
            if(s[i]=='1') byte = byte | 1;
        }
    return byte;
};