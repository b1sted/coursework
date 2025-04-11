# Переменные компилятора и опций
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99

# Исходные файлы и объектные файлы
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))

# Название итогового файла и директория для бинарника
TARGET_DIR = bin
TARGET_NAME = signal_analysis
TARGET = $(TARGET_DIR)/$(TARGET_NAME)

# Правило по умолчанию: сборка TARGET
all: $(TARGET)

# Правило линковки для создания исполняемого файла в bin/
$(TARGET): $(OBJS) | $(TARGET_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Компиляция исходников в объектные файлы, объектники сохраняются в build/
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директории build, если её нет
build:
	@mkdir -p build

# Создание директории bin, если её нет
$(TARGET_DIR):
	@mkdir -p $(TARGET_DIR)

# Очистка сборки: удаляем объектные файлы и исполняемый файл/папку
clean:
	@echo "Cleaning up..." # Добавим немного информативности
	@rm -rf build $(TARGET_DIR) # Удаляем всю папку bin и build
	@echo "Done."

# Объявляем цели, которые не являются файлами
.PHONY: all clean build $(TARGET_DIR)
