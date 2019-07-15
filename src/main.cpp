#include"Encoder.h"
#include"Decoder.h"
int getFileSize(char* filename){
    std::ifstream ifs(filename);
    if(!ifs.is_open()) return 0;
    ifs.seekg(0,std::ios::end);
    int filesize = ifs.tellg();
    ifs.close();
    return filesize;
}
int main(){
    Encoder encoder;
    Decoder decoder;
    char* input = "input.txt";
    char* zip= "zip";
    char* output = "output.txt";
    encoder.encodeFile(input,zip);
    decoder.decodeFile(zip,output);
    std::cout<<"compression ratio is "<<(double)getFileSize(input)/getFileSize(zip)<<std::endl;
}