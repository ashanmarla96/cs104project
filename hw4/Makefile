BIN_DIR = bin
CXX = g++
CXXFLAG = -g -Wall

all: 

$(BIN_DIR)/datetime.o: $(BIN_DIR)/.dirstamp src/datetime.cpp lib/datetime.h
	$(CXX) $(CXXFLAG) -c src/datetime.cpp -o $(BIN_DIR)/datetime.o


$(BIN_DIR)/user.o: $(BIN_DIR)/.dirstamp src/user.cpp lib/user.h
	$(CXX) $(CXXFLAG) -c src/user.cpp -o $(BIN_DIR)/user.o


$(BIN_DIR)/tweet.o: $(BIN_DIR)/.dirstamp src/tweet.cpp lib/tweet.h
	$(CXX) $(CXXFLAG) -c src/tweet.cpp -o $(BIN_DIR)/tweet.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean
clean: 
	rm -rf $(BIN_DIR)