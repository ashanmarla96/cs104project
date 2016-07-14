CXX = g++
CFLAGS = -g -Wall
BIN_DIR = bin

all: sat_sol

sat_sol: $(BIN_DIR)/sat_sol

$(BIN_DIR)/sat_sol: $(BIN_DIR)/.dirstamp satsolver.cpp bst.h rbbst.h
	$(CXX) $(CFLAGS) satsolver.cpp bst.h rbbst.h -o $(BIN_DIR)/sat_sol

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $@


.PHONY: clean

clean:
	rm -rf $(BIN_DIR) 