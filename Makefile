MKDIR			:= mkdir -p --

INCLUDE			:= ./include
SRC				:= ./src
SRCS			:= $(wildcard $(SRC)/*.c)
BIN				:= ./bin
OUT				:= $(BIN)/libutf8encoder.a
SO_OUT			:= $(BIN)/libutf8encoder.so

OBJ				:= ./obj
OBJS    		:= $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
SO_OBJ			:= ./soobj
SO_OBJS    		:= $(patsubst $(SRC)/%.c,$(SO_OBJ)/%.o,$(SRCS))

TESTSRC			:= ./tests
TESTSRCS		:= $(wildcard $(TESTSRC)/*.c)
TESTOUT			:= $(BIN)/test
SOTESTOUT		:= $(BIN)/sotest

WARNINGS		:= -Wall -Wextra -Wfloat-equal -Wundef
ERRORS			:= -Werror=implicit-int -Werror=implicit-function-declaration
CFLAGS 		    := $(WARNINGS) $(ERRORS) -std=c99

DEBUGCFLAGS		:= -g3
RELEASECFLAGS	:= -O3
SO_C_FLAGS		:= -fPIC
SO_LD_FLAGS 	:= -shared

.PHONY: static shared test sharedtest clean

$(OBJ)/%.o: $(SRC)/%.c
	$(MKDIR) $(OBJ)
	$(CC) $(CFLAGS) $(RELEASECFLAGS) -I$(INCLUDE) -c $^ -o $@

$(OUT): $(OBJS)
	$(MKDIR) $(BIN)
	ar rcvs $@ $^

static: $(OUT)

$(SO_OBJ)/%.o: $(SRC)/%.c
	$(MKDIR) $(SO_OBJ)
	$(CC) $(SO_CFLAGS) $(RELEASECFLAGS) -I$(INCLUDE) $^ -o $@

$(SO_OUT): $(SO_OBJS)
	mkdir -p -- $(BIN)
	$(CC) $(SO_LD_FLAGS) -o $@

shared: $(SO_OUT)

$(TESTOUT): $(OUT) $(TESTSRCS)
	$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(TESTSRCS) -L$(BIN) -lutf8encoder -I$(INCLUDE) -o $@

$(SOTESTOUT): $(SO_OUT) $(TESTSRCS)
	$(MKDIR) $(BIN)
	$(CC) $(CFLAGS) $(DEBUGCFLAGS) $(TESTSRCS) -L$(BIN) -lutf8encoder -I$(INCLUDE) -o $@

test: $(TESTOUT)

sharedtest: $(SOTESTOUT)

clean:
	rm -Rf -- $(BIN) $(OBJ) $(SO_OBJ)
