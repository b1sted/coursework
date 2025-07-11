/*
 * SPDX-FileCopyrightText: Copyright (c) 2025 Nikita Mandrykin. All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <string.h>

#include "response_dictionary.h"

const KeywordMapping RESPONSE_DICTIONARY[] = {
    // Утвердительные ответы
    {"да",   RESPONSE_AFFIRMATIVE},
    {"Да",   RESPONSE_AFFIRMATIVE},
    {"дА",   RESPONSE_AFFIRMATIVE},
    {"ДА",   RESPONSE_AFFIRMATIVE},

    // Отрицательные ответы
    {"нет",  RESPONSE_NEGATIVE},
    {"Нет",  RESPONSE_NEGATIVE},
    {"нЕт",  RESPONSE_NEGATIVE},
    {"неТ",  RESPONSE_NEGATIVE},
    {"НЕт",  RESPONSE_NEGATIVE},
    {"нЕТ",  RESPONSE_NEGATIVE},
    {"НЕТ",  RESPONSE_NEGATIVE}
};

const int DICTIONARY_SIZE = sizeof(RESPONSE_DICTIONARY) / sizeof(RESPONSE_DICTIONARY[0]);

ResponseType get_response_type_by_keyword(const char *input) {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        if (strcmp(input, RESPONSE_DICTIONARY[i].keyword_text) == 0) {
            return RESPONSE_DICTIONARY[i].type;
        }
    }
    return RESPONSE_UNKNOWN;
}
