CC = gcc
CFLAGS = -Iinclude 
LDFLAGS = -lm

SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/filters.c \
       $(SRC_DIR)/image.c \
       $(SRC_DIR)/stack.c \
       $(SRC_DIR)/lodepng.c \
       $(SRC_DIR)/components.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: BigTask

# Линковка
BigTask: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o BigTask

# Компиляция
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Создание папки build
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Очистка
clean:
	rm -rf $(BUILD_DIR) BigTask
