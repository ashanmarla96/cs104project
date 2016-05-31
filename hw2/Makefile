BIN_DIR = bin
CXX = g++
CXXFLAG = -g -Wall

all: $(BIN_DIR)/testAddToEmptyList

$(BIN_DIR)/testAddToEmptyList: $(BIN_DIR)/.dirstamp $(BIN_DIR)/llistint.o testAddToEmptyList.cpp 
	$(CXX) $(CXXFLAG) -c $(BIN_DIR)/llistint.o testAddToEmptyList.cpp -o $(BIN_DIR)/testAddToEmptyList

$(BIN_DIR)/llistint.o: $(BIN_DIR)/.dirstamp llistint.cpp llistint.h
	$(CXX) $(CXXFLAG) -c llistint.cpp -o $(BIN_DIR)/llistint.o




$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean: 
	rm -rf $(BIN_DIR)