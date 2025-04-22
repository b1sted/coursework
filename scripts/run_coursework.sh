#!/bin/bash

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

#==============================================================================
#
#   КУРСОВАЯ РАБОТА ПО АНАЛИЗУ СИГНАЛА
#   Скрипт для управления файлами и программами курсовой работы
#
#==============================================================================

# ===== НАСТРОЙКИ И ПУТИ =====
# Пути к файлам
C_PROGRAM="./bin/signal_analysis"        # Программа анализа сигнала
COURSEWORK_REPORT="./docs/coursework_report.doc"  # Пояснительная записка
WXMAXIMA_PLOT_SCRIPT="./wxmaxima/plot_data.wxmx"  # Скрипт с графиками
CONTROL_CALC_FILE="./wxmaxima/control_calculations.wxmx"  # Контрольный расчет

# Команды запуска программ
WXMAXIMA_COMMAND="flatpak run io.github.wxmaxima_developers.wxMaxima"
LIBREOFFICE_COMMAND="libreoffice"


# ===== ОБРАБОТКА СИГНАЛОВ И ЗАВЕРШЕНИЯ =====
# Функция для обработки прерываний пользователем (Ctrl+C)
handle_interrupt() {
    echo
    echo "Программа прервана пользователем (Ctrl+C). Завершение работы."
    exit 1
}

# Устанавливаем обработчик для сигналов прерывания
trap handle_interrupt SIGINT SIGTERM


# ===== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ =====
# Проверка наличия необходимых программ и файлов
check_dependencies() {
    local missing_deps=()
    
    # Проверка программ
    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        missing_deps+=("wxMaxima (flatpak) - программа")
    fi
    
    if ! command -v "$LIBREOFFICE_COMMAND" &>/dev/null; then
        missing_deps+=("LibreOffice - программа")
    fi

    # Проверка файлов проекта
    if [ ! -f "$C_PROGRAM" ]; then
        missing_deps+=("$C_PROGRAM - файл программы")
    fi
    
    if [ ! -f "$WXMAXIMA_PLOT_SCRIPT" ]; then
        missing_deps+=("$WXMAXIMA_PLOT_SCRIPT - файл графиков")
    fi
    
    if [ ! -f "$CONTROL_CALC_FILE" ]; then
        missing_deps+=("$CONTROL_CALC_FILE - файл контрольного расчета")
    fi
    
    if [ ! -f "$COURSEWORK_REPORT" ]; then
        missing_deps+=("$COURSEWORK_REPORT - файл отчета")
    fi

    # Вывод сообщений, если есть отсутствующие компоненты
    if [ ${#missing_deps[@]} -ne 0 ]; then
        clear
        echo "+-------------------------------------------------------+"
        echo "|                                                       |"
        echo "|           ВНИМАНИЕ: ПРОВЕРКА СИСТЕМЫ                  |"
        echo "|                                                       |"
        echo "+-------------------------------------------------------+"
        echo "| Отсутствуют следующие зависимости:                    |"
        for dep in "${missing_deps[@]}"; do
             # Вычисляем длину строки для правильного выравнивания
             local line="   * $dep"
             local padding=$((55 - ${#line}))
             local spaces=$(printf "%${padding}s" "")
             echo "|$line$spaces|"
        done
        echo "|                                                       |"
        echo "| Некоторые функции программы могут быть недоступны.    |"
        echo "| Рекомендуется установить отсутствующие программы      |"
        echo "| и проверить наличие всех файлов проекта.              |"
        echo "|                                                       |"
        echo "+-------------------------------------------------------+"
        echo

        # Ожидание ввода с обработкой Ctrl+D
        if ! read -p "Нажмите Enter для продолжения (или Ctrl+C для выхода)... "; then
            echo
            echo "Обнаружен сигнал EOF (Ctrl+D). Выход из программы."
            exit 0
        fi
    fi
}

# Пауза и ожидание нажатия Enter для возврата в меню
pause_for_menu() {
    echo
    if ! read -p "Нажмите Enter для возврата в меню... "; then
        echo
        echo "Обнаружен сигнал EOF (Ctrl+D). Выход из программы."
        exit 0
    fi
}


# ===== ФУНКЦИИ ГЛАВНОГО МЕНЮ =====
# 1. Запуск программы анализа сигнала
run_analysis_program() {
    if [ ! -f "$C_PROGRAM" ]; then
        echo "ОШИБКА: Программа анализа ($C_PROGRAM) не найдена!"
        pause_for_menu
        return 1
    fi

    # Проверка и установка прав на выполнение
    if [ ! -x "$C_PROGRAM" ]; then
        echo "Установка прав на выполнение для $C_PROGRAM..."
        chmod +x "$C_PROGRAM"
        if [ $? -ne 0 ]; then
             echo "ОШИБКА: Не удалось установить права на выполнение!"
             pause_for_menu
             return 1
        fi
    fi

    echo
    echo "Запуск программы анализа сигнала..."
    echo

    "$C_PROGRAM"
    
    echo
    echo "Программа анализа завершила работу."
    
    pause_for_menu
}


# 2. Построение графиков в WxMaxima
build_graphs() {
    if [ ! -f "$WXMAXIMA_PLOT_SCRIPT" ]; then
        echo "ОШИБКА: Скрипт построения графиков ($WXMAXIMA_PLOT_SCRIPT) не найден!"
        pause_for_menu
        return 1
    fi

    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        echo "ОШИБКА: Программа wxMaxima не установлена!"
        echo "Для установки выполните: flatpak install flathub io.github.wxmaxima_developers.wxMaxima"
        pause_for_menu
        return 1
    fi

    echo
    echo "Запуск WxMaxima для построения графиков..."
    $WXMAXIMA_COMMAND "$WXMAXIMA_PLOT_SCRIPT" &
    echo "Программа запущена в фоновом режиме."
    
    pause_for_menu
}


# 3. Открытие файла контрольного расчета
open_control_calculation() {
    if [ ! -f "$CONTROL_CALC_FILE" ]; then
        echo "ОШИБКА: Файл контрольного расчета ($CONTROL_CALC_FILE) не найден!"
        pause_for_menu
        return 1
    fi

    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        echo "ОШИБКА: Программа wxMaxima не установлена!"
        echo "Для установки выполните: flatpak install flathub io.github.wxmaxima_developers.wxMaxima"
        pause_for_menu
        return 1
    fi

    echo
    echo "Открытие контрольного расчета в WxMaxima..."
    $WXMAXIMA_COMMAND "$CONTROL_CALC_FILE" &
    echo "Программа запущена в фоновом режиме."
    
    pause_for_menu
}


# 4. Открытие пояснительной записки
open_report() {
    if [ ! -f "$COURSEWORK_REPORT" ]; then
        echo "ОШИБКА: Пояснительная записка ($COURSEWORK_REPORT) не найдена!"
        pause_for_menu
        return 1
    fi

    if ! command -v "$LIBREOFFICE_COMMAND" &>/dev/null; then
        echo "ОШИБКА: Программа LibreOffice не найдена!"
        pause_for_menu
        return 1
    fi

    echo
    echo "Открытие пояснительной записки..."
    "$LIBREOFFICE_COMMAND" "$COURSEWORK_REPORT" &
    echo "Программа запущена в фоновом режиме."
    
    pause_for_menu
}


# ===== ГЛАВНОЕ МЕНЮ =====
# Отображение меню и обработка выбора пользователя
show_menu() {
    clear
    echo "+-------------------------------------------------------+"
    echo "|                                                       |"
    echo "|           КУРСОВАЯ РАБОТА ПО АНАЛИЗУ СИГНАЛА          |"
    echo "|                                                       |"
    echo "+-------------------------------------------------------+"
    echo "|                                                       |"
    echo "| 1. Запустить программу расчета                        |"
    echo "| 2. Построить графики в WxMaxima                       |"
    echo "| 3. Открыть контрольный расчет                         |"
    echo "| 4. Открыть пояснительную записку                      |"
    echo "| 5. Завершить работу                                   |"
    echo "|                                                       |"
    echo "| Подсказка: Ctrl+C для экстренного выхода из программы |"
    echo "|                                                       |"
    echo "+-------------------------------------------------------+"
    echo

    local choice
    # Чтение выбора пользователя с обработкой Ctrl+D
    if ! read -p "Выберите действие [1-5]: " choice; then
        echo
        echo "Обнаружен сигнал EOF (Ctrl+D). Выход из программы."
        exit 0
    fi

    # Обработка выбора
    case $choice in
        1) run_analysis_program ;;
        2) build_graphs ;;
        3) open_control_calculation ;;
        4) open_report ;;
        5) 
           echo
           echo "Выход из программы. До свидания!"
           exit 0
           ;;
        *)
           echo "ПРЕДУПРЕЖДЕНИЕ: Неверный выбор. Пожалуйста, выберите опцию от 1 до 5."
           pause_for_menu
           ;;
    esac
}

# ===== ЗАПУСК ПРОГРАММЫ =====
# Проверка зависимостей при старте
check_dependencies

# Основной цикл - показывать меню до выхода
while true; do
    show_menu
done
