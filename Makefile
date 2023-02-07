test/%.out: test/%.cpp include/Sugar/%.hpp
	g++ -Wall -Wextra -std=c++17 -I include -o $@ $<

test/%: test/%.out
	$<
