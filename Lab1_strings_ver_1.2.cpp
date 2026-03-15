#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm { char mark; char A[N + 1]; };

/// <summary>
/// Функция вывода в файл out.txt
/// </summary>
/// <param name="text"> - сообщение</param>
/// <param name="str"> - строка на вывод</param>
/// <param name="c"> - символ на вывод</param>
void outp(const char* text, const char* str, char c)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);

    if (str != "") {
        file << text;
        for (int i = 0; i < 100; i++) {
            if (str[i] == '\0') {
                file << std::endl;
                file.close();
                break;
            }
            file << str[i];
        }
        file << std::endl;
    }
    else {
        file << text << c << str << std::endl;
    }

    file.close();
}

/// <summary>
/// Перемещает символы в строке
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="len"> - изначальная позиция маркера </param>
void swap(strm& a, int len)
{
    char temp = a.A[0];
    for (int i = 0; i < len; i++) {
        a.A[i] = a.A[i + 1];
    }
    a.A[len] = temp;
}

/// <summary>
/// Ищет изначальную позицию маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>
int poisk_pos(strm& a) {
    int o_pos = 0;

    while (a.A[o_pos] != '\0')
    {
        if (a.A[o_pos] == a.mark) {
            return o_pos;
        }
        o_pos++;
    }
}

/// <summary>
/// Основная работа программы - перемещение символов в строке
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="o_pos"> - old marker position (конец строки)</param>
/// <param name="n_pos"> - new marker position (середина строки)</param>
void process(strm& a, int o_pos, int n_pos)
{
    int len = o_pos;
    while (o_pos != n_pos) {
        swap(a, len);
        o_pos--;
    }
    outp("Результат : ", a.A, ' ');

}

/// <summary>
/// Функция ввода из файла
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>
bool inp(strm& a) {
    int file_num = 1;
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in2.txt", std::ios::in);
    std::ofstream out("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::out);

    char c;

    if (!file.is_open()) {
        std::cout << "Ошибка открытия входного файла";
        outp("Ошибка открытия входного файла", "", ' ');
        return false;
    }
    if (!out.is_open()) {
        outp("Ошибка открытия выходного файла", "", ' ');
        return false;
    }

    //читает построчно файл, считывает маркеты и ограничители, читает строки, если что-то не так, то выдает ошибки
    while (!(file.eof())) {
        char n = file_num + '0';
        outp("Cтрока №", "", n);


        file.get(a.mark);
        if (a.mark == '\n') {
            outp("Ошибка - пустая строка", "", ' ');
            file_num++;
            outp("----------------", "", ' ');
            continue;
        }
        //массив числа - количества считываемых из строки символов
        char num[4];

        //--------
        int j = 0;
        char temp;
        while (file.get(temp) || j < 3) {
            if (temp >= '0' && temp <= '9') {
                num[j] = temp;  // Сохраняем в массив
                j++;
            }
            else {
                file.putback(temp);  // Возвращаем нецифровой символ обратно!
                num[j] = '\0';
                break;
            }
            num[j] = '\0';
        }


        if (j == 0) {
            outp("Ошибка: нет числа", "", ' ');
            
        }

        // Проверка на ведущий ноль (кроме числа "0")
        if (num[0] == '0') {
            outp("Ошибка: неверное число (ведущий ноль)", "", ' ');
            return 0;
        }

        //// Проверка, что после числа есть строка
        //if (file.get(temp) == '\n') {
        //    std::cout << "Ошибка: нет строки после числа" << std::endl;
        //    return 0;
        //}

        // Парсинг числа вручную
        unsigned number = 0;
        for (int jj = 0; jj < j; jj++) {
            number = number * 10 + (num[jj] - '0');
        }

        // Проверка диапазона [0, 100]
        if (number > 100) {
            outp("Ошибка: число > 100", "", ' ');
            return 0;
        }

        //--------



        

        unsigned i = 0;
        bool flag = false;

        while (file.get(c)) {
            if (c == a.mark) break;
            if (c == '\n' || file.eof()) {
                file_num++;
                outp("Ошибка - в строке нет маркера", "", ' ');
                outp("----------------", "", ' ');
                flag = true;
                break;

            }
            if (i > number) {
                outp("В строке символов больше нужного", "", ' ');
                break;
            }

            a.A[i] = c;
            i++;
            if (i > N) {
                outp("Ошибка - в строке больше 100 символов", "", ' ');
                file_num++;
                outp("----------------", "", ' ');
                flag = true;
                break;
            }

        }

        //Пропускает остаток строки и переходит на следующую строчку
        if (flag) {
            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }
            continue;
        }

        if (i == 0) {
            outp("Ошибка - пустая строка", "", ' ');
            return 0;
        }
        if (i == N) {
            outp("В строке ровно 100 символов", "", ' ');
            a.A[i] = a.mark;
        }
        if (i < N) {
            a.A[i] = a.mark;
            a.A[i + 1] = '\0';
        }

        
        outp("Маркер: ", "", a.mark);
        outp("Длина считываемой строки :", num, ' ');
        outp("Строка: ", a.A, ' ');

        while (file.get(c)) {
            if (c == '\n') break;
            if (file.eof()) return true;
        }

        file_num++;


        int o_pos = poisk_pos(a);
        int n_pos = (poisk_pos(a)) / 2 + (poisk_pos(a)) % 2;
        process(a, o_pos, n_pos);

        outp("----------------", "", ' ');


    }
    out.close();
    file.close();
    return true;
}

int main() {
    setlocale(LC_ALL, "ru");
    strm file;
    if (!(inp(file))) return 0;

    return 0;
}