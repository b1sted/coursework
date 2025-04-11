# Переменные компилятора и опций
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -std=c99

# Исходные файлы и объектные файлы
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))

# Название итогового файла и директория для бинарника
TARGET = bin/signal_analysis

# Правило по умолчанию: сборка TARGET
all: $(TARGET)

# Правило линковки для создания исполняемого файла в bin/
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Компиляция исходников в объектные файлы, объектники сохраняются в build/
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

# Создание директории build, если её нет
build:
	mkdir -p build

# Очистка сборки: удаляем объектные файлы и исполняемый файл
clean:
	rm -rf build $(TARGET)

.PHONY: all clean
