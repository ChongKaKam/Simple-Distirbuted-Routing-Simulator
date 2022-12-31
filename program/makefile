# makefile
# basic configuration
target = simulator
SRC_DIRS = algorithm core main
INC_DIRS = algorithm core main
BUILD_DIR = $(addprefix ./build/, $(INC_DIRS))

# Find all the C++ files we want to compile
SRCS = $(shell find $(SRC_DIRS) -name '*.cc')
OBJS = $(patsubst %.cc, build/%.o, $(SRCS))
# -Ixxx
INC_FLAGS = $(addprefix -I, $(INC_DIRS))

define make-goal
$(1): $(patsubst build/%.o, ./%.cc, $(1))
	@$(CXX) $(INC_FLAGS) -c -g $$< -o $$@
endef

# set the phony target
.PHONY: all checkdirs clean run

all: checkdirs build/$(target)

build/$(target): $(OBJS)
	@$(CXX) $(OBJS) -o $@
	
$(foreach obj, $(OBJS), $(eval $(call make-goal, $(obj))))

checkdirs:
	@$(foreach bdir, $(BUILD_DIR), $(shell mkdir -p $(bdir)))

run: all
	@./build/$(target)

clean:
	@rm -r ./build
