CC := g++ -Wall -Wextra -std=c++17 -I include

SRC_DIR := include/Sugar
SRC_SUF := .hpp
TEST_DIR := test
TEST_SRC_SUF := .cpp
TEST_BIN_SUF := .exe

.PHONY: test clean

$(TEST_DIR)/%$(TEST_BIN_SUF): $(TEST_DIR)/%$(TEST_SRC_SUF) $(SRC_DIR)/%$(SRC_SUF)
	$(CC) $< -o $@ 

$(TEST_DIR)/%: $(TEST_DIR)/%$(TEST_BIN_SUF)
	$<

test: $(patsubst %$(TEST_SRC_SUF), %,                   \
		$(wildcard $(TEST_DIR)/*$(TEST_SRC_SUF))        \
		$(wildcard $(TEST_DIR)/*/*$(TEST_SRC_SUF))      \
		$(wildcard $(TEST_DIR)/*/*/*$(TEST_SRC_SUF))    \
		$(wildcard $(TEST_DIR)/*/*/*/*$(TEST_SRC_SUF))  \
	  )

clean: 
	rm -f $(TEST_DIR)/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*/*/*$(TEST_BIN_SUF)
