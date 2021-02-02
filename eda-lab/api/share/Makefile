PROGRAM := eda-lab

SUB_DIRS := Analysis-EDA

API_DIR := $(abspath ../api)
export API_DIR
include $(API_DIR)/share/Makefile.template

VALGRIND_FLAGS :=--leak-check=full --error-exitcode=77

.PHONY: circuit01 circuit02 circuit01_valgrind circuit02_valgrind final

test: circuit01

circuit01: $(PROGRAM)
	cd .. && implementation/$(PROGRAM) examples/circuit01.yal CIRCUIT01 examples/library.yal

circuit02: $(PROGRAM)
	cd .. && implementation/$(PROGRAM) examples/circuit02.yal CIRCUIT02 examples/library.yal

circuit01_valgrind: $(PROGRAM)
	cd .. && valgrind $(VALGRIND_FLAGS) implementation/$(PROGRAM) examples/circuit01.yal CIRCUIT01 examples/library.yal

circuit02_valgrind: $(PROGRAM)
	cd .. && valgrind $(VALGRIND_FLAGS) implementation/$(PROGRAM) examples/circuit02.yal CIRCUIT02 examples/library.yal

#target for final hand in of code
#uses Werror additionally to make sure that no warnings are thrown by gcc, calls clean to rebuild all
#might not be safe if parallel make is used, as the order of clean and test is not guaranteed
final: CXXFLAGS += -Werror -DNDEBUG
final: clean circuit01_valgrind circuit02_valgrind


