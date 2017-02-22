OBJS = account.o entry.o journal.o ledger.o transaction.o amount.o color.o
MAINOBJS = main.o
OBJPATH = ./build

CC = g++-6
CFLAGS = -c -g -O0 -Wall -Werror -std=c++11 -Iinclude -Ilibs -I/usr/local/include
LINKER = g++-6
LIBS = -L/usr/local/lib/ -lmysqlcppconn
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

#$(BUILDDIR)tester.o: $(TESTDIR)Tester.cpp
#	$(CC) $(CFLAGS) $(TESTDIR)Tester.cpp -o $(BUILDDIR)Tester.o

# Compiling main.o **DONE
$(BUILDDIR)main.o: $(SRCDIR)Main.cpp $(addprefix $(BUILDDIR), journal.o ledger.o color.o)
	$(CC) $(CFLAGS) $(SRCDIR)Main.cpp -o $(BUILDDIR)main.o

# Compiling journal.o
$(BUILDDIR)journal.o: $(SRCDIR)Journal.cpp $(addprefix $(BUILDDIR), transaction.o ledger.o color.o)
	$(CC) $(CFLAGS) $(SRCDIR)Journal.cpp -o $(BUILDDIR)journal.o

###############################################################################

# Compiling transaction.o
$(BUILDDIR)transaction.o: $(SRCDIR)Transaction.cpp $(addprefix $(BUILDDIR), entry.o)
	$(CC) $(CFLAGS) $(SRCDIR)Transaction.cpp -o $(BUILDDIR)transaction.o

# Compiling entry.o
$(BUILDDIR)entry.o: $(SRCDIR)Entry.cpp $(addprefix $(BUILDDIR), account.o amount.o)
	$(CC) $(CFLAGS) $(SRCDIR)Entry.cpp -o $(BUILDDIR)entry.o

# Compiling ledger.o
$(BUILDDIR)ledger.o: $(SRCDIR)Ledger.cpp $(addprefix $(BUILDDIR), account.o)
	$(CC) $(CFLAGS) $(SRCDIR)Ledger.cpp -o $(BUILDDIR)ledger.o

# Compiling account.o
$(BUILDDIR)account.o: $(SRCDIR)Account.cpp $(addprefix $(BUILDDIR), amount.o)
	$(CC) $(CFLAGS) $(SRCDIR)Account.cpp -o $(BUILDDIR)account.o

# Compiling amount.o
$(BUILDDIR)amount.o: $(SRCDIR)Amount.cpp
	$(CC) $(CFLAGS) $(SRCDIR)Amount.cpp -o $(BUILDDIR)amount.o

# Compiling color.o
$(BUILDDIR)color.o: $(SRCDIR)Color.cpp
	$(CC) $(CFLAGS) $(SRCDIR)Color.cpp -o $(BUILDDIR)color.o

clean:
	-rm -f build/*.o bin/openbook
