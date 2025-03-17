ALLOC_TEST_FILES := $(wildcard tests/alloc/*.c)
FREE_TEST_FILES := $(wildcard tests/free/*.c)
COALESCE_TEST_FILES := $(wildcard tests/coalesce/*.c)
ALL_TEST_FILES := $(ALLOC_TEST_FILES) $(FREE_TEST_FILES) $(COALESCE_TEST_FILES)

ALLOC_TEST_TARGETS := $(patsubst tests/alloc/%.c,target/tests/alloc/%,$(ALLOC_TEST_FILES))
FREE_TEST_TARGETS := $(patsubst tests/free/%.c,target/tests/free/%,$(FREE_TEST_FILES))
COALESCE_TEST_TARGETS := $(patsubst tests/coalesce/%.c,target/tests/coalesce/%,$(COALESCE_TEST_FILES))
ALL_TEST_TARGETS := $(ALLOC_TEST_TARGETS) $(FREE_TEST_TARGETS) $(COALESCE_TEST_TARGETS)

.PHONY: build clean all test_alloc test_free test_coal memcheck

build: heap.c heap.h

./target/libheap.so: heap.c heap.h
	mkdir -p ./target
	gcc -g -c -Wall -fpic heap.c -o ./target/heap.o
	gcc -shared -Wall -o ./target/libheap.so ./target/heap.o

clean:
	rm -rf ./target/heap.o ./target/libheap.so ./target/tests/*

# Build and run all tests
test: build $(ALL_TEST_TARGETS)
	@echo "Running all tests..."
	@for test in $(ALL_TEST_TARGETS); do \
		echo "Running $$test..."; \
		$$test; \
	done

# Build and run alloc tests
test_alloc: build $(ALLOC_TEST_TARGETS)
	@echo "Running alloc tests..."
	@for test in $(ALLOC_TEST_TARGETS); do \
		echo "Running $$test..."; \
		$$test; \
	done

# Build and run free tests
test_free: build $(FREE_TEST_TARGETS)
	@echo "Running free tests..."
	@for test in $(FREE_TEST_TARGETS); do \
		echo "Running $$test..."; \
		$$test; \
	done

# Build and run coalesce tests
test_coal: build $(COALESCE_TEST_TARGETS)
	@echo "Running coalesce tests..."
	@for test in $(COALESCE_TEST_TARGETS); do \
		echo "Running $$test..."; \
		$$test; \
	done

# Rule to build each test executable
target/tests/alloc/%: tests/alloc/%.c ./target/libheap.so
	mkdir -p ./target/tests/alloc
	clang -I. -g -Wl,-rpath,./target -o $@ $< -L./target -lheap -std=gnu99

target/tests/free/%: tests/free/%.c ./target/libheap.so
	mkdir -p ./target/tests/free
	clang -I. -g -Wl,-rpath,./target -o $@ $< -L./target -lheap -std=gnu99

target/tests/coalesce/%: tests/coalesce/%.c ./target/libheap.so
	mkdir -p ./target/tests/coalesce
	clang -I. -g -Wl,-rpath,./target -o $@ $< -L./target -lheap -std=gnu99

memcheck: 
	valgrind --leak-check=yes ./test103 # or other test
	valgrind --leak-check=yes ./test213 # or other test
	valgrind --leak-check=yes ./test214_immedcoal # or other test

