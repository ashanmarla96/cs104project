BIN_DIR = bin
CXX = g++
CXXFLAG = -g -Wall
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/lliststrtest $(BIN_DIR)/settest 

LListStrTest: $(BIN_DIR)/lliststrtest

SetTest: $(BIN_DIR)/settest

$(BIN_DIR)/lliststrtest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/lliststr.o lliststrtest.cpp 
	$(CXX) $(CXXFLAG) $(BIN_DIR)/lliststr.o lliststrtest.cpp -o $(BIN_DIR)/lliststrtest

$(BIN_DIR)/lliststr.o: $(BIN_DIR)/.dirstamp src/lliststr.cpp lib/lliststr.h
	$(CXX) $(CXXFLAG) -c src/lliststr.cpp -o $(BIN_DIR)/lliststr.o


$(BIN_DIR)/settest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/lliststr.o $(BIN_DIR)/setstr.o settest.cpp
	$(CXX) $(CXXFLAG) $(BIN_DIR)/lliststr.o $(BIN_DIR)/setstr.o settest.cpp $(GTEST_LL) -o $(BIN_DIR)/settest

$(BIN_DIR)/setstr.o: $(BIN_DIR)/.dirstamp src/setstr.cpp lib/setstr.h
	$(CXX) $(CXXFLAG) -c src/setstr.cpp -o $(BIN_DIR)/setstr.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean: 
	rm -rf $(BIN_DIR)
