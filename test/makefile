OBJDIR_BUILD = build
OBJ = $(OBJDIR_BUILD)/storage.o

all: directory test

test: $(OBJ)
	clang++ -o $(OBJDIR_BUILD)/test $<

directory $(OBJDIR_BUILD):
	mkdir -p $(OBJDIR_BUILD)

$(OBJ): $(OBJDIR_BUILD)/%.o: %.cpp
	clang++ -I../include -std=c++14 -Wall -Wextra -c $< -o $@

clean:
	 rm -r $(OBJDIR_BUILD)
