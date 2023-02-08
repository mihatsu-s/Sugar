CC := g++ -Wall -Wextra -std=c++17 -I include

SRC_DIR := include/Sugar
SRC_SUF := .hpp
TEST_DIR := test
TEST_SRC_SUF := .cpp
TEST_BIN_SUF := .exe

.PHONY: new test clean

new/%:
	mkdir -p $(dir $(SRC_DIR)/$(patsubst new/%,%,$@))
	touch $(SRC_DIR)/$(patsubst new/%,%,$@)$(SRC_SUF)
	mkdir -p $(dir $(TEST_DIR)/$(patsubst new/%,%,$@))
	touch $(TEST_DIR)/$(patsubst new/%,%,$@)$(TEST_SRC_SUF)

test: $(patsubst %$(TEST_SRC_SUF), %,                   \
		$(wildcard $(TEST_DIR)/*$(TEST_SRC_SUF))        \
		$(wildcard $(TEST_DIR)/*/*$(TEST_SRC_SUF))      \
		$(wildcard $(TEST_DIR)/*/*/*$(TEST_SRC_SUF))    \
		$(wildcard $(TEST_DIR)/*/*/*/*$(TEST_SRC_SUF))  \
	  )

test/%: $(TEST_DIR)/%$(TEST_BIN_SUF)
	$<

clean: 
	rm -f $(TEST_DIR)/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*/*$(TEST_BIN_SUF)
	rm -f $(TEST_DIR)/*/*/*/*$(TEST_BIN_SUF)

$(TEST_DIR)/%$(TEST_BIN_SUF): $(TEST_DIR)/%$(TEST_SRC_SUF) $(SRC_DIR)/%$(SRC_SUF)
	$(CC) $< -o $@ 
