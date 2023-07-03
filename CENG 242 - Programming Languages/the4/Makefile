OP_OBJS=$(patsubst %,obj/%.o,nullary unary binary expr core type)
OBJS=$(patsubst %,obj/%.o,overload) ${OP_OBJS}

CPP=g++

# for debugging
# CFLAGS+=-g
CFLAGS+=-I./include -Wall -Wpedantic -Werror -std=c++11

all: bin/4ut0d1ff

bin/4ut0d1ff: src/main.cpp ${OBJS} | bin
	$(CPP) $(CFLAGS) -o $@ $^

${OP_OBJS}: obj/%.o: src/%.cpp include/%.h | obj
	$(CPP) $(CFLAGS) -c -o $@ $<

obj/overload.o: obj/%.o: src/%.cpp | obj
	$(CPP) $(CFLAGS) -c -o $@ $<

clear:
	rm -rf obj

obj bin:
	@mkdir -p $@
