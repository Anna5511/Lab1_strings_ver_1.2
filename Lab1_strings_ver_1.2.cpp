#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm { int len; char A[N]; };

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, const char* str, char symbol, int len)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    if (len > 0) {
        file << text;
        for (int i = 0; i < len; i++) {
            file << str[i];
        }
        file << std::endl;
    }
    else {
        file << text << symbol << std::endl;
    }
    file.close();
}
void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    //if (n != 0) file << "-------------------" << std::endl;
    file << text << n << std::endl;
    file.close();
}

void swap(strm& a) {
    char temp = a.A[0];
    for (int i = 0; i < a.len; i++) {
        a.A[i] = a.A[i + 1];
    }
    a.A[a.len] = temp;
}

void process(strm& a) {
    int pos_count = a.len / 2 + a.len % 2;
    outp_n("Сколько раз свапаем : ", pos_count);
    outp_n("Длина свапаемой строки : ", a.len);
    outp("Строка до свапа : ", a.A, ' ', a.len);
    for (int i = 0; i < pos_count; i++) {
        swap(a);
    }
    outp("Результат : ", a.A, ' ', a.len);
}

void skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '\n') break;
    }
}

bool readLine(std::ifstream& file, strm& a) {
    char c = ' ';
    char stop;
    // Читаем ограничитель
    if (!file.get(stop)) {
        outp("Ошибка: Пустой входной файл", "", ' ', 0);
        return false;
    }
    if (stop == '\n') {
        outp("Ошибка: Пустая строка (нет ограничителя)", "", ' ', 0);
        return false;
    }

    ///////////////////////////////////
    char num[4];

    //Дальше идет считывание числа - количество читаемых символов из строки
    int j = 0;
    while (file.get(c) && j < 3) {
        if (c >= '0' && c <= '9') {
            num[j] = c;
            j++;
        }
        else if (c == '-') {
            //сохраняем в массив минус, чтобы потом его увидеть и поругаться
            num[j] = c;
            j++;
            continue;
        }
        else {
            file.putback(c);
            num[j] = '\0';
            break;
        }
        
    }

    //не совершили j++ => не записали ничего в массив
    if (j == 0) {
        outp("Ошибка: нет числа", "", ' ', 0);
        return false;
    }

    if (num[0] == '0') {
        outp("Ошибка: неверное число (ведущий ноль)", "", ' ', 0);
        return false;
    }

    if (num[0] == '-') {
        outp("Ошибка: неверное число (отрицательное значение)", "", ' ', 0);
        return false;
    }

    unsigned number = 0;
    for (int jj = 0; jj < j; jj++) {
        number = number * 10 + (num[jj] - '0');
    }

    // Проверка диапазона [0, N]
    if (number > N) {
        outp("Ошибка: число > N", "", ' ', 0);
        return 0;
    }

    //////////////////////////////////
    outp_n("Количество символов (предполагаемо): ", number);
    outp("Ограничитель : ", "", stop, 0);

    // Читаем строку до ограничителя
    unsigned i = 0;

    while (file.get(c) && c != '\n' && (!file.eof())) {

        if (c == stop) {
            skipToNextLine(file);
            outp_n("1) Количество символов: ", i);
            a.len = i;
            return true;
        }
        a.A[i] = c;
        i++;
        if (i == number) {
            outp("В строке взято только нужное количество символов", "", ' ', 0);
            a.len = number-1;
            outp_n("2) Количество символов: ", number);
            skipToNextLine(file);
            break;
        }
    }
    if (i == 0) {
        outp("В строке нет символов", "", ' ', 0);
        return false;
    }
    if (number > i){
        outp("В строке символов меньше нужного, так что считали все", "", ' ', 0);
        a.len = i;
        outp_n("3) Количество символов: ", i);
    }


    if (!file.eof()) return true;
}

bool out_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\out2.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}
bool in_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt");
    if (!file.is_open()) {
        outp("Ошибка открытия входного файла", "", ' ', 0);
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}

int main()
{
    clear_File();
    setlocale(LC_ALL, "ru");
    if (in_file_check()) return 0;
    if (out_file_check()) return 0;


    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt");
    int lineNumber = 0;

    // Основной цикл обработки
    while (!file.eof()) {
        strm string;

        for (int i = 0; i < N; i++) {
            string.A[i] = '\0';
        }
        string.len = '\0';

        outp_n("-------------- Номер строки: ", lineNumber);

        if (readLine(file, string)) process(string);
        lineNumber++;
    }

    return 0;
}