CC          := gcc
SRC         := ./src
BIN         := ./bin
HEADERS     := ./headers
CFLAGS      := -std=c99 -I$(HEADERS)
LDFLAGS     := -lm
EXEC        := prog
ZIP         := exercicio.zip

# List of all expected $(BIN)/*.o
ALL         := $(wildcard $(SRC)/*.c)
ALL         := $(ALL:$(SRC)/%.c=$(BIN)/%.o)


all: $(EXEC)

compile: clean all

run: all
	./$(EXEC)

clean:
	rm -f $(EXEC) $(BIN)/*.o

zip:
	rm -f $(ZIP)
	zip $(ZIP) Makefile $(HEADERS)/*.h $(SRC)/*.c

$(EXEC): $(ALL)
	$(CC) -o $(EXEC) $(BIN)/*.o $(LDFLAGS)

$(BIN)/%.o: $(SRC)/%.c $(BIN)
	$(CC) -o $@ -c $< -I $(HEADERS) $(CFLAGS) 

$(BIN):
	mkdir -p $(BIN)