#Running on Windows 10, Mingw-32
CXX = g++
CXXFLAGS = -std=c++11 -g
HEADER_DIR = include
SRC_DIR = src
MAIN = ./bin/main
Encoder = Encoder.o
Adaptive_Huffman_Tree = Adaptive_Huffman_Tree.o
MAINO = main.o
BITIO = BitIO.o
Decoder = Decoder.o
$(MAIN) : $(Adaptive_Huffman_Tree) $(MAINO) $(Encoder) $(BITIO) $(Decoder)
	$(CXX) $(CXXFLAGS) -I $(HEADER_DIR) $^ -o $@
	del /f /s /q *.o
$(Encoder) : $(SRC_DIR)/Encoder.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(Adaptive_Huffman_Tree) : $(SRC_DIR)/Adaptive_Huffman_Tree.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(BITIO) : $(SRC_DIR)/BitIO.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(MAINO) : $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
$(Decoder) : $(SRC_DIR)/Decoder.cpp
	$(CXX) $(CXXFLAGS) -c $^ -I $(HEADER_DIR) -o $@
clean:
	del /s /q *.o
	del /s /q bin