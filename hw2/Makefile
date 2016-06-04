BIN_DIR = bin
CXX = g++
CXXFLAG = -g -Wall

all: $(BIN_DIR)/llisttest $(BIN_DIR)/alisttest

LListTest: $(BIN_DIR)/llisttest

AListTest: $(BIN_DIR)/alisttest

StackTest: $(BIN_DIR)/stacktest

$(BIN_DIR)/llisttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/llistint.o llisttest.cpp 
	$(CXX) $(CXXFLAG) $(BIN_DIR)/llistint.o llisttest.cpp -o $(BIN_DIR)/llisttest

$(BIN_DIR)/alisttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/alistint.o alisttest.cpp
	$(CXX) $(CXXFLAG) $(BIN_DIR)/alistint.o alisttest.cpp -o $(BIN_DIR)/alisttest

$(BIN_DIR)/stacktest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/stackint.o stacktest.cpp $(BIN_DIR)/llistint.o
	$(CXX) $(CXXFLAG) $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o stacktest.cpp -o $(BIN_DIR)/stacktest

$(BIN_DIR)/laundry: $(BIN_DIR)/.dirstamp $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o laundry.cpp
	$(CXX) $(CXXFLAG) $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o laundry.cpp -o $(BIN_DIR)/laundry

$(BIN_DIR)/llistint.o: $(BIN_DIR)/.dirstamp src/llistint.cpp lib/llistint.h
	$(CXX) $(CXXFLAG) -c src/llistint.cpp -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/alistint.o: $(BIN_DIR)/.dirstamp src/alistint.cpp lib/alistint.h
	$(CXX) $(CXXFLAG) -c src/alistint.cpp -o $(BIN_DIR)/alistint.o

$(BIN_DIR)/stackint.o: $(BIN_DIR)/.dirstamp src/stackint.cpp lib/stackint.h 
	$(CXX) $(CXXFLAG) -c src/stackint.cpp -o $(BIN_DIR)/stackint.o


$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean: 
	rm -rf $(BIN_DIR)