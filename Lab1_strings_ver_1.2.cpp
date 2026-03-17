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
bool outp(const char* text, const char* str, char c)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out2.txt", std::ios::app);

    if (!file.is_open()) {
        outp("Ошибка открытия выходного файла", "", ' ');
        return false;
    }

    //Если есть строка на ввод, то читаем либо всю (101 символ), либо до ее назначенного конца
    if (str != "") {
        file << text;
        for (int i = 0; i < 101; i++) {
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
    return true;
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
/// Основная работа программы - перемещение символов в строке + вывод результата с помощью outp
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

    char c;

    if (!file.is_open()) {
        std::cout << "Ошибка открытия входного файла";
        outp("Ошибка открытия входного файла", "", ' ');
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

        //Дальше идет считывание числа - количество читаемых символов из строки
        int j = 0;
        while (file.get(c) || j < 3) {
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
            num[j] = '\0';
        }

        //не совершили j++ => не записали ничего в массив
        if (j == 0) {
            outp("Ошибка: нет числа", "", ' ');
            file_num++;
            outp("----------------", "", ' ');

            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }
            continue;
        }

        if (num[0] == '0') {
            outp("Ошибка: неверное число (ведущий ноль)", "", ' ');
            file_num++;
            outp("----------------", "", ' ');

            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }
            continue;
        }

        if (num[0] == '-') {
            outp("Ошибка: неверное число (отрицательное значение)", "", ' ');
            file_num++;
            outp("----------------", "", ' ');

            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }
            continue;
        }

        unsigned number = 0;
        for (int jj = 0; jj < j; jj++) {
            number = number * 10 + (num[jj] - '0');
        }

        //для ошибок - чтобы пропустить остаток и идти дальше
        bool flag = false;
        
        // Проверка диапазона [0, 100]
        if (number > 100) {
            outp("Ошибка: число > 100", "", ' ');            
            outp("----------------", "", ' ');
            file_num++;
            flag = true;
        }

        unsigned i = 0;

        // для ситуаций, где символов в строке меньше нужного
        bool flag2 = true;

        while (file.get(c)) {
            if (c == a.mark) break;
            if (c == '\n' || file.eof()) {
                outp("Ошибка - в строке нет маркера", "", ' ');             
                outp("----------------", "", ' ');
                file_num++;
                flag = true;
                flag2 = false;
                break;
            }
            if (i > number) {
                outp("В строке символов больше нужного", "", ' ');
                flag2 = false;
                break;
            }
            a.A[i] = c;
            i++;
            if (i > N) {
                outp("Ошибка - в строке больше 100 символов", "", ' ');
                outp("----------------", "", ' ');
                file_num++;
                flag = true;
                flag2 = false;
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
            flag2 = false;
            return 0;
        }
        if (i == N) {
            outp("В строке ровно 100 символов", "", ' ');
            flag2 = false;
            a.A[i] = a.mark;
        }
        if (i < N) {
            a.A[i] = a.mark;
            a.A[i + 1] = '\0';
        }
        if (flag2) {
            outp("В строке символов меньше нужного, так что считываем все", "", ' ');
        }

        outp("Маркер: ", "", a.mark);
        outp("Длина считываемой строки: ", num, ' ');
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
    file.close();
    return true;
}



int main() {
    setlocale(LC_ALL, "ru");
    strm file;
    if (!(inp(file))) return 0;

    return 0;
}