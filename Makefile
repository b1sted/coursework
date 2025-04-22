# Copyright (c) 2025 Nikita Mandrykin
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
