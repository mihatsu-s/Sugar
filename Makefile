CC := g++ -Wall -Wextra -std=c++17 -I include

SRC_DIR := include/Sugar
SRC_SUF := .hpp
TEST_DIR := test
TEST_SRC_SUF := .cpp
TEST_BIN_SUF := .out

.PHONY: new test clean

new/%:
	# generate source file
	mkdir -p $(dir $(SRC_DIR)/$(patsubst new/%,%,$@))
	echo "#pragma once" > $(SRC_DIR)/$(patsubst new/%,%,$@)$(SRC_SUF)

	# generate test file
	mkdir -p $(dir $(TEST_DIR)/$(patsubst new/%,%,$@))
	echo "#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN\n#include \"$(dir $(shell echo $(patsubst new/%,%,$@) | sed -e "s/[^/]*\//..\//g"))doctest.h\"\n\n#include <Sugar/$(patsubst new/%,%,$@)$(SRC_SUF)>" > $(TEST_DIR)/$(patsubst new/%,%,$@)$(TEST_SRC_SUF)

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

$(TEST_DIR)/%$(TEST_SRC_SUF): ;
