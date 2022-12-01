CC = g++
LD = g++

target = Router
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, build/%.o, $(SRC))
BUILD_PATH = $(patsubst ./%, build/%, ./)

define make-goal
$(1): $(patsubst build/%.o, ./%.cc, $(1))
	@$(CC) $(INCLUDES) -c -g $$< -o $$@
endef

.PHONY: all checkdirs test clean

all: checkdirs build/$(target)
	
build/$(target): $(OBJ)
	@$(LD) $^ -g -o $@

$(foreach bdir,$(OBJ),$(eval $(call make-goal,$(bdir))))

checkdirs: $(BUILD_PATH)

$(BUILD_PATH):
	@mkdir -p $@

run: all
	./build/$(target)

clean:
	@rm -rf $(BUILD_PATH)