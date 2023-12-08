CC = gcc
CFLAGS = -Wall -Wextra -pthread

# --------------------------------- Server -------------------------------------

SERVER_SRCDIR = TCP_Server/src
SERVER_BUILDDIR = TCP_Server/build
SERVER_BINDIR = TCP_Server/bin
SERVER_LOGDIR = TCP_Server/logs
SERVER_DATA = TCP_Server/data

# List of source files in src directory and its subdirectories
SERVER_SRC = $(shell find $(SERVER_SRCDIR) -name "*.c")

# List of files .o in build directory
SERVER_OBJ = $(patsubst $(SERVER_SRCDIR)/%.c, $(SERVER_BUILDDIR)/%.o, $(SERVER_SRC))

# Executable name
SERVER_TARGET = server

# --------------------------------- Client -------------------------------------

CLI_SRCDIR = TCP_Client/src
CLI_BUILDDIR = TCP_Client/build
CLI_BINDIR = TCP_Client/bin
CLI_LOGDIR = TCP_Client/logs

# List of source files in src directory and its subdirectories
CLI_SRC = $(shell find $(CLI_SRCDIR) -name "*.c")

# List of files .o in build directory
CLI_OBJ = $(patsubst $(CLI_SRCDIR)/%.c, $(CLI_BUILDDIR)/%.o, $(CLI_SRC))

# Executable name
CLI_TARGET = client

# --------------------------------- Define command -------------------------------------
all: $(SERVER_TARGET) $(CLI_TARGET)

$(SERVER_TARGET): $(SERVER_OBJ)
	@mkdir -p $(SERVER_BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(SERVER_BUILDDIR)/%.o: $(SERVER_SRCDIR)/%.c
	@mkdir -p $(dir $@)  # create folder if not exist
	$(CC) $(CFLAGS) -c $< -o $@

$(CLI_TARGET): $(CLI_OBJ)
	@mkdir -p $(CLI_BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(CLI_BUILDDIR)/%.o: $(CLI_SRCDIR)/%.c
	@mkdir -p $(dir $@)  # create folder if not exist
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(SERVER_BUILDDIR) $(SERVER_BINDIR) $(CLI_BUILDDIR) $(CLI_BINDIR) ${SERVER_TARGET} ${CLI_TARGET} ${SERVER_DATA}/*

run_server: 
	./$(SERVER_TARGET)

run_cli:
	./$(CLI_TARGET)
