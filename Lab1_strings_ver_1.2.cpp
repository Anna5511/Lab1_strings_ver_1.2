#include <iostream>
#include <fstream>

const unsigned N = 100;
struct strm {
    int len;
    char A[N];
};

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, const char* str, char symbol, int len) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    file << text;
    if (len > 0 && str) {
        for (int i = 0; i < len; i++) file << str[i];
    }
    else if (str && str[0] != '\0') {
        file << str;
    }
    else {
        file << symbol;
    }
    file << std::endl;
    file.close();
}

void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    file << text << n << std::endl;
    file.close();
}

void swap(strm& a) {
    if (a.len <= 1) return;
    char temp = a.A[0];
    for (int i = 0; i < a.len - 1; i++) a.A[i] = a.A[i + 1];
    a.A[a.len - 1] = temp;
}

void process(strm& a) {
    if (a.len <= 0) return;
    int pos_count = a.len / 2 + a.len % 2;
    outp_n("Сколько раз свапаем : ", pos_count);
    outp_n("Длина свапаемой строки : ", a.len);
    for (int i = 0; i < pos_count; i++) swap(a);
    outp("Результат : ", a.A, ' ', a.len);
}

// Парсит строку и заполняет структуру
// Возвращает true если успешно, false если ошибка
bool parseLine(const std::string& line, strm& a) {
    if (line.empty()) {
        outp("Ошибка: Пустая строка (нет ограничителя)", "", ' ', 0);
        return false;
    }

    // Первый символ - ограничитель
    char stop = line[0];

    // Проверяем, не является ли первый символ переводом строки
    if (stop == '\n' || stop == '\r') {
        outp("Ошибка: Пустая строка (нет ограничителя)", "", ' ', 0);
        return false;
    }

    // Читаем число после ограничителя
    unsigned number = 0;
    int pos = 1; // позиция после ограничителя

    // Пропускаем пробелы/табы
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) {
        pos++;
    }

    // Читаем цифры
    int numStart = pos;
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9') {
        pos++;
    }

    // Проверка: есть ли цифры
    if (pos == numStart) {
        outp("Ошибка: нет числа или неверный формат", "", ' ', 0);
        return false;
    }

    // Парсим число
    std::string numStr = line.substr(numStart, pos - numStart);

    // Проверка на ведущий ноль
    if (numStr[0] == '0' && numStr.length() > 1) {
        outp("Ошибка: нет числа или неверный формат", "", ' ', 0);
        return false;
    }

    try {
        number = std::stoul(numStr);
    }
    catch (...) {
        outp("Ошибка: нет числа или неверный формат", "", ' ', 0);
        return false;
    }

    // Валидация диапазона: 1..100
    if (number < 1 || number > 100) {
        outp("Ошибка: нет числа или неверный формат", "", ' ', 0);
        return false;
    }

    outp_n("Количество символов (предполагаемо): ", number);
    outp("Ограничитель : ", "", stop, 0);

    // Читаем полезные данные до ограничителя
    unsigned i = 0;
    bool stopFound = false;

    while (pos < line.length() && i < N) {
        char c = line[pos];

        // Проверка на ограничитель
        if (c == stop) {
            stopFound = true;
            break;
        }

        a.A[i++] = c;
        pos++;

        // Достигли ожидаемого количества
        if (i == number) {
            break;
        }
    }

    // Проверка: есть ли символы
    if (i == 0) {
        outp("В строке нет символов", "", ' ', 0);
        return false;
    }

    a.len = i;

    // Сообщения согласно ТЗ
    if (!stopFound && i == N) {
        // Достигли лимита 100 без ограничителя - ок по ТЗ
    }
    else if (number > i) {
        outp("В строке символов меньше нужного, так что считали все", "", ' ', 0);
    }

    outp_n("Количество символов: ", i);
    return true;
}

bool in_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt");
    if (!file.is_open()) {
        std::ofstream out("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
        out << "Ошибка открытия входного файла" << std::endl;
        out.close();
        return true;
    }
    file.close();
    return false;
}

int main() {
    clear_File();
    setlocale(LC_ALL, "ru");
    if (in_file_check()) return 0;

    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt");
    if (!file.is_open()) return 0;

    int lineNumber = 0;
    std::string line;
    char c;

    // Читаем посимвольно, собирая строки
    while (file.get(c)) {
        if (c == '\n') {
            // Обработка собранной строки
            if (!line.empty() && line.back() == '\r') line.pop_back();

            strm string = { 0, {0} };
            memset(string.A, 0, N);

            outp_n("-------------- Номер строки: ", lineNumber);
            if (parseLine(line, string)) {
                process(string);
            }

            lineNumber++;
            line.clear(); // очищаем для следующей строки
        }
        else {
            line += c;
        }
    }

    if (!line.empty() || file.eof()) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        for (int i = 0; i < N; i++) {
            string.A[i] = '\0';
        }
        string.len = '\0';

        outp_n("-------------- Номер строки: ", lineNumber);
        if (parseLine(line, string)) {
            process(string);
        }
        lineNumber++;
    }

    file.close();
    return 0;
}