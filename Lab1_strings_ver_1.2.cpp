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

void outp(const char* text, char symbol, strm& a) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    file << text;
    if (symbol == ' ') {
        for (int i = 0; i < a.len; i++) { 
            file << a.A[i]; 
        }
    }
    else{
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

void outp_t(const char* text) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);
    file << text;
    file << std::endl;
    file.close();
}

void swap(strm& a) {
    if (a.len <= 1) return;
    char temp = a.A[0];
    for (int i = 0; i < a.len - 1; i++) {
        a.A[i] = a.A[i + 1]; 
    }
    a.A[a.len - 1] = temp;
}

void process(strm& a) {
    if (a.len <= 0) return;
    int pos_count = a.len / 2;
    outp_n("Сколько раз свапаем : ", pos_count);
    outp_n("Длина свапаемой строки : ", a.len);
    outp("Строка до свапа : ", ' ', a);
    for (int i = 0; i < pos_count; i++) swap(a);
    outp("Результат : ", ' ', a);
}

void skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c) && c != '\n');
}

bool readLine(std::ifstream& file, strm& a) {
    char c = ' ';
    char stop;
    // Читаем ограничитель
    if (!file.get(stop)) {
        outp_t("Ошибка: Пустой входной файл");
        return false;
    }
    if (stop == '\n') {
        outp_t("Ошибка: Пустая строка (нет ограничителя)");
        return false;
    }
    outp("Ограничитель : ", stop, a);
    ///////////////////////////////////
    char num[4] = { 0 };
    
    
    //Дальше идет считывание числа - количество читаемых символов из строки
    int j = 0;
    while (file.get(c) && j <= 2) {
        if (c >= '0' && c <= '9') {
            num[j] = c;
            j++;
        }
        else if (c == '-') {
            outp_t("Ошибка: неверное число (отрицательное значение)");
            skipToNextLine(file);
            return false;
        }
        else {
            file.seekg(-1, std::ios::cur);
            break;
        }
    }
    if (!(c >= '0' && c <= '9')) {
        file.seekg(-1, std::ios::cur);
    }
    //не совершили j++ => не записали ничего в массив
    if (j == 0) {
        outp_t("Ошибка: нет числа");
        skipToNextLine(file);
        return false;
    }



    if (num[0] == '0') {
        outp_t("Ошибка: неверное число (ведущий ноль)");
        skipToNextLine(file);
        return false;
    }
    unsigned number = 0;
    for (int jj = 0; jj < j; jj++) {
        number = number * 10 + (num[jj] - '0');
    }
    

    //////////////////////////////////
    outp_n("Количество символов (предполагаемо): ", number);
    

    // Проверка диапазона [0, N]
    if (number > N) {
        outp_t("Ошибка: число > N");
        skipToNextLine(file);
        return 0;
    }

    // Читаем строку до ограничителя
    unsigned i = 0;

    while (file.get(c) && c != '\n' && (!file.eof())) {
        if (c == stop) {
            a.len = i;
            outp_n("Количество символов: ", a.len);
            skipToNextLine(file);
            break;
        }
        a.A[i] = c;
        i++;
        if (i == number) {
            outp_t("В строке взято только нужное количество символов");
            a.len = number;
            outp_n("Количество символов: ", a.len);
            skipToNextLine(file);
            break;
        }
    }
    std::cout << i << " " << number << std::endl << "-------" << std::endl;
    if (i == 0) {
        outp_t("В строке нет символов");
        return false;
    }
    if (number > i) {
        outp_t("В строке символов меньше нужного, так что считали все");
        a.len = i;
    }
    


    return true;
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
        outp_t("Ошибка открытия входного файла");
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}

int main() {
    clear_File();
    setlocale(LC_ALL, "ru");
    if (in_file_check()) return 0;
    if (out_file_check()) return 0;

    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt");

    int lineNumber = 0;
    strm string;
    char c;

    while (file.peek() != EOF) {
        outp_n("-------------- Номер строки: ", lineNumber);
        if (readLine(file, string)) process(string);
        lineNumber++;
    }

    file.close();
    return 0;
}