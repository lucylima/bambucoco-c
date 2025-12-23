CC = gcc

COMMON_FLAGS = -Wall -Wextra -std=c11 -pedantic

DEBUG_FLAGS = -g 

PROD_FLAGS = -O3 -DNDEBUG

SRCS = main.c ./lib/interface.c ./lib/bambucoco.c
OBJS = $(SRCS:.c=.o)

TARGET_DEV = main
TARGET_PROD = bambucoco

INSTALL_DIR = ./

.PHONY: all clean install release uninstall

all: CFLAGS = $(COMMON_FLAGS) $(DEBUG_FLAGS)
all: $(TARGET_DEV)

release: clean $(TARGET_PROD)

$(TARGET_DEV): $(OBJS)
	@echo "🔨 Linkando versão de DESENVOLVIMENTO (com ASan)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET_DEV)

$(TARGET_PROD): $(OBJS)
	@echo "🚀 Linkando versão de PRODUÇÃO (Otimizada)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET_PROD) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: release
	@echo "📦 Instalando $(TARGET_PROD) em $(INSTALL_DIR)..."
	@echo "✅ Instalação concluída."

uninstall:
	@echo "🗑️ Removendo $(TARGET_PROD)..."
	@sudo rm -f $(INSTALL_DIR)/$(TARGET_PROD)

clean:
	@echo "🧹 Limpando binários e objetos..."
	rm -f $(OBJS) $(TARGET_DEV) $(TARGET_PROD)