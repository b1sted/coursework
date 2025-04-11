#!/bin/bash

# Константы для путей к файлам и командам
C_PROGRAM="./bin/signal_analysis"
COURSEWORK_REPORT="./docs/coursework_report.doc"
WXMAXIMA_PLOT_SCRIPT="./wxmaxima/plot_data.wxmx"
CONTROL_CALC_FILE="./wxmaxima/control_calculations.wxmx"
WXMAXIMA_COMMAND="flatpak run io.github.wxmaxima_developers.wxMaxima"
LIBREOFFICE_COMMAND="libreoffice"

# --- Функции Обработки ---

# Функция для обработки прерываний (Ctrl+C) и Завершения (Ctrl+D на пустой строке)
# Ctrl+D во время read -p обрабатывается отдельно проверкой статуса read
handle_interrupt() {
    echo
    echo "Получен сигнал прерывания (Ctrl+C). Выход из программы."
    exit 1 # Выход с кодом ошибки для прерывания
}

# Назначаем обработчик для сигналов прерывания
trap handle_interrupt SIGINT SIGTERM

# Функция для проверки наличия программ и файлов
check_dependencies() {
    local missing_deps=()
    local dep_type="" # Для указания типа зависимости (программа/файл)

    # Проверка наличия flatpak wxMaxima
    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        missing_deps+=("wxMaxima (flatpak)")
        dep_type="программа"
    fi
    # Проверка наличия libreoffice
    if ! command -v "$LIBREOFFICE_COMMAND" &>/dev/null; then
        missing_deps+=("libreoffice")
        dep_type="программа"
    fi

    # Проверка наличия файлов проекта
    if [ ! -f "$C_PROGRAM" ]; then
        missing_deps+=("$C_PROGRAM")
        dep_type="файл"
    fi
    if [ ! -f "$WXMAXIMA_PLOT_SCRIPT" ]; then
        missing_deps+=("$WXMAXIMA_PLOT_SCRIPT")
        dep_type="файл"
    fi
    # Проверка наличия файла контрольного расчета
    if [ ! -f "$CONTROL_CALC_FILE" ]; then
        missing_deps+=("$CONTROL_CALC_FILE")
        dep_type="файл"
    fi
    if [ ! -f "$COURSEWORK_REPORT" ]; then
        missing_deps+=("$COURSEWORK_REPORT")
        dep_type="файл"
    fi

    # Если есть отсутствующие зависимости, выводим сообщение
    if [ ${#missing_deps[@]} -ne 0 ]; then
        echo "ВНИМАНИЕ: Следующие зависимости отсутствуют:"
        for dep in "${missing_deps[@]}"; do
             # Определяем тип для вывода (немного упрощенно)
             [[ "$dep" == *"flatpak"* || "$dep" == "libreoffice" ]] && dep_type="программа" || dep_type="файл"
             echo " - $dep_type: $dep"
        done
        echo
        echo "Некоторые функции могут работать некорректно или быть недоступны."
        echo "Убедитесь, что программы установлены, а файлы находятся в текущем каталоге."
        echo
        # Пауза для пользователя, с обработкой Ctrl+D
        if ! read -p "Нажмите Enter, чтобы продолжить (или Ctrl+C для выхода)..."; then
            echo; echo "Обнаружен EOF (Ctrl+D). Выход."; exit 0; # Обработка Ctrl+D здесь
        fi
    fi
}

# Функция для паузы и возврата в меню (с обработкой Ctrl+D)
pause_for_menu() {
    echo
    if ! read -p "Нажмите Enter, чтобы вернуться в меню..."; then
         echo; echo "Обнаружен EOF (Ctrl+D). Выход."; exit 0; # Обработка Ctrl+D
    fi
}

# --- Функции Меню ---

# 1. Запуск C-программы
run_analysis_program() {
    if [ ! -f "$C_PROGRAM" ]; then
        echo "Ошибка: Программа анализа ($C_PROGRAM) не найдена!"
        pause_for_menu
        return 1
    fi

    # Проверяем права на выполнение и устанавливаем при необходимости
    if [ ! -x "$C_PROGRAM" ]; then
        echo "Установка прав на выполнение для $C_PROGRAM..."
        chmod +x "$C_PROGRAM"
        if [ $? -ne 0 ]; then
             echo "Ошибка: Не удалось установить права на выполнение для $C_PROGRAM."
             pause_for_menu
             return 1
        fi
    fi

    echo "Запуск программы анализа сигнала..."
    "$C_PROGRAM" # Запускаем программу
    echo "Программа анализа завершила работу."
    pause_for_menu
}

# 2. Построение графиков в Wxmaxima
build_graphs() {
    if [ ! -f "$WXMAXIMA_PLOT_SCRIPT" ]; then
        echo "Ошибка: Скрипт построения графиков ($WXMAXIMA_PLOT_SCRIPT) не найден!"
        pause_for_menu
        return 1
    fi

    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        echo "Ошибка: Программа wxMaxima (flatpak) не установлена!"
        echo "Для установки выполните: flatpak install flathub io.github.wxmaxima_developers.wxMaxima"
        pause_for_menu
        return 1
    fi

    echo "Запуск Wxmaxima для построения графиков ($WXMAXIMA_PLOT_SCRIPT)..."
    # Запускаем Wxmaxima в *фоновом* режиме, чтобы не блокировать скрипт
    $WXMAXIMA_COMMAND "$WXMAXIMA_PLOT_SCRIPT" &
    echo "Команда Wxmaxima отправлена в фоновый режим."
    # Нет необходимости в паузе здесь, меню отобразится сразу
}

# 3. Открытие файла контрольного расчета в Wxmaxima
open_control_calculation() {
    if [ ! -f "$CONTROL_CALC_FILE" ]; then
        echo "Ошибка: Файл контрольного расчета ($CONTROL_CALC_FILE) не найден!"
        pause_for_menu
        return 1
    fi

    if ! flatpak list | grep -q "io.github.wxmaxima_developers.wxMaxima"; then
        echo "Ошибка: Программа wxMaxima (flatpak) не установлена!"
        echo "Для установки выполните: flatpak install flathub io.github.wxmaxima_developers.wxMaxima"
        pause_for_menu
        return 1
    fi

    echo "Открытие контрольного расчета ($CONTROL_CALC_FILE) в Wxmaxima..."
    # Запускаем Wxmaxima в *фоновом* режиме
    $WXMAXIMA_COMMAND "$CONTROL_CALC_FILE" &
    echo "Команда Wxmaxima отправлена в фоновый режим."
    # Нет необходимости в паузе здесь
}


# 4. Открытие пояснительной записки (отчета)
open_report() {
    if [ ! -f "$COURSEWORK_REPORT" ]; then
        echo "Ошибка: Пояснительная записка ($COURSEWORK_REPORT) не найдена!"
        pause_for_menu
        return 1
    fi

    if ! command -v "$LIBREOFFICE_COMMAND" &>/dev/null; then
        echo "Ошибка: Программа '$LIBREOFFICE_COMMAND' не найдена!"
        pause_for_menu
        return 1
    fi

    echo "Открытие пояснительной записки ($COURSEWORK_REPORT)..."
    # Запускаем LibreOffice в фоновом режиме
    "$LIBREOFFICE_COMMAND" "$COURSEWORK_REPORT" &
     echo "Команда '$LIBREOFFICE_COMMAND' отправлена в фоновый режим."
    # Нет необходимости в паузе здесь
}

# --- Основная Логика ---

# Функция для отображения меню и обработки выбора
show_menu() {
    clear
    echo "========================================================="
    echo "           КУРСОВАЯ РАБОТА ПО АНАЛИЗУ СИГНАЛА"
    echo "========================================================="
    echo
    echo "1. Запустить программу расчета (${C_PROGRAM##*/})"
    echo "2. Построить графики в Wxmaxima (${WXMAXIMA_PLOT_SCRIPT##*/})"
    echo "3. Открыть контрольный расчет в Wxmaxima (${CONTROL_CALC_FILE##*/})" # Новый пункт
    echo "4. Открыть пояснительную записку (${COURSEWORK_REPORT##*/})"        # Обновленный номер
    echo "5. Выход"                                                          # Обновленный номер
    echo
    echo "Hint: Ctrl+C для прерывания в любой момент"
    echo

    local choice
    # Используем read с проверкой на EOF (Ctrl+D)
    if ! read -p "Выберите действие [1-5]: " choice; then
        echo; echo "Обнаружен EOF (Ctrl+D). Выход."; exit 0; # Обработка Ctrl+D в главном меню
    fi

    # Обработка выбора пользователя
    case $choice in
        1) run_analysis_program ;;
        2) build_graphs ;;
        3) open_control_calculation ;; # Вызов новой функции
        4) open_report ;;             # Вызов функции с обновленным номером
        5)                            # Выход с обновленным номером
           echo "Выход из программы. До свидания!"
           exit 0
           ;;
        *)
           echo "Неверный выбор. Пожалуйста, выберите опцию от 1 до 5."
           pause_for_menu # Пауза перед повторным показом меню
           ;;
    esac
}

# --- Старт Скрипта ---

# 1. Проверяем зависимости при запуске
check_dependencies

# 2. Основной цикл программы - показывать меню до выбора выхода
while true; do
    show_menu
done
