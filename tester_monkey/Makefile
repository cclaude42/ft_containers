INCLUDE_PATH=..

CONTAINERS =list \
	vector \
	deque \
	map \
	set \
	multimap \
	multiset \
	stack \
	priority_queue

OBJ_DIR=.objs

USER_CONTAINERS = $(foreach a, $(CONTAINERS),ft_${a})

DEPS=$(foreach c, $(USER_CONTAINERS), ${OBJ_DIR}/$c.d)

STD_CONTAINERS = $(foreach a, $(CONTAINERS),std_${a})

to_upper=$(shell echo $(1) | tr '[a-z]' '[A-Z]')

remove_ns=$(shell echo $(1) | sed 's/[^_]*_//')

all: $(CONTAINERS)

$(USER_CONTAINERS): ${OBJ_DIR}
	clang++ srcs/main.cpp -D TEST_$(call to_upper, $(call remove_ns, $@)) -MMD -MF ${OBJ_DIR}/$@.d -MT $@ -g3 -std=c++98 -I ${INCLUDE_PATH}  -D TEST_FT -o $@

$(STD_CONTAINERS):
	clang++ srcs/main.cpp -D TEST_$(call to_upper, $(call remove_ns, $@)) -std=c++98 -D TEST_STD -o $(@)

.SECONDEXPANSION:

$(CONTAINERS): ft_$$(@) std_$$(@)

${OBJ_DIR}:
	mkdir $@

clean:
	rm -f $(DEPS)

fclean: clean
	rm -rf $(USER_CONTAINERS) $(STD_CONTAINERS) $(OBJ_DIR)

re: fclean all

-include $(DEPS)
