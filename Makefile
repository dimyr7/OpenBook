OBJS = account.o entry.o journal.o ledger.o transaction.o amount.o
MAINOBJS = main.o
OBJPATH = ./build

CC = clang++
CFLAGS = -c -g -O0 -Wall -Werror -Wc++11-extensions -std=c++11 -I include -I libs
LINKER = clang++
LFLAGS = -o

ifdef DEBUG
	CFLAGS += -DDEBUG
else
	CFLAGS += -DNDEBUG
endif



SRCDIR = src/
BUILDDIR = build/

TARGET = bin/openbook
TESTER = bin/tester

SRCEXT = cpp
INC = -I include
all: $(TARGET)

autoschedule: $(TARGET)

test:
	@echo "test runs"
run: $(TARGET)
	@./bin/openbook

valgrind: $(TARGET)
	@valgrind ./bin/openbook

full: $(TARGET)
	@valgrind --leak-check=full --track-origins=yes ./bin/openbook > c.out

# Linking the openbook executible
$(TARGET): $(addprefix $(BUILDDIR), $(MAINOBJS) $(OBJS))
	@echo " Building OpenBook"
	$(LINKER) $(addprefix $(BUILDDIR), $(MAINOBJS) $(OBJS))  $(INC) $(LIBS) $(LFLAGS) $(TARGET)

$(BUILDDIR)tester.o: $(TESTDIR)Tester.cpp
	$(CC) $(CFLAGS) $(TESTDIR)Tester.cpp -o $(BUILDDIR)Tester.o

# Compiling main.o **DONE
$(BUILDDIR)main.o: $(SRCDIR)Main.cpp $(addprefix $(BUILDDIR), account.o)
	$(CC) $(CFLAGS) $(SRCDIR)Main.cpp -o $(BUILDDIR)main.o


# Compiling account.o
$(BUILDDIR)account.o: $(SRCDIR)Account.cpp $(addprefix $(BUILDDIR), amount.o)
	$(CC) $(CFLAGS) $(SRCDIR)Account.cpp -o $(BUILDDIR)account.o

# Compiling entry.o
$(BUILDDIR)entry.o: $(SRCDIR)Entry.cpp $(addprefix $(BUILDDIR), account.o)
	$(CC) $(CFLAGS) $(SRCDIR)Entry.cpp -o $(BUILDDIR)entry.o

# Compiling journal.o
$(BUILDDIR)journal.o: $(SRCDIR)Journal.cpp $(addprefix $(BUILDDIR), ledger.o)
	$(CC) $(CFLAGS) $(SRCDIR)Journal.cpp -o $(BUILDDIR)journal.o

# Compiling ledger.o
$(BUILDDIR)ledger.o: $(SRCDIR)Ledger.cpp
	$(CC) $(CFLAGS) $(SRCDIR)Ledger.cpp -o $(BUILDDIR)ledger.o

$(BUILDDIR)amount.o: $(SRCDIR)Amount.cpp include/Define.hpp
	$(CC) $(CFLAGS) $(SRCDIR)Amount.cpp -o $(BUILDDIR)amount.o


clean:
	-rm -f build/*.o bin/openbook
