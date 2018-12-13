#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <set>
#include <tuple>
using namespace std;

struct Point
{
    double x;
    double y;

    friend bool operator == (const Point& point1, const Point& point2);
};

bool operator==(const Point &point1, const Point &point2) {
    return (&point1.x == &point2.x && &point1.y == &point2.y);
}

int proverka();
void vivod_v_file(Point *array, int tochek, double radius);
double vvod(Point *array, int tochek, double radius);
//Point sort(Point *array, int tochek);

int main() {
    //------------------------------------------------------------------------------------------------------------------!!!Не забудь изменить вывод в консоль на вывод в файл!!!
    fstream f;
    int check = 0, tochek = 0;
    double radius = 0, x = 0, y = 0;

    check = proverka(); //Проверка файла
    if (check != 0)
        return 666;

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> tochek >> radius;
    tochek = abs(tochek);
    auto *array = new Point[tochek];    //Создание массива структур
    vvod(array, tochek, radius);        //Заполнение массива структур
    for (int i = 0; i < tochek - 1; i++) {
        auto item = array + i;
        cout << item->x << ";" << item->y << endl;
    }


    delete[] array; //Очистка памяти
    f.close();      //Закрытие входного файла
    return 0;
}

double vvod(Point *array, int tochek, double radius) {
    //---------------------------------------------------------------------------------Заполняет массив точками из файла
    fstream f;
    double schet_x = 0, schet_y = 0;
    Point point{};

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> tochek >> radius;
    tochek = abs(tochek);
    for (int i = 0; i <= tochek - 1; i++) {
        f >> schet_x >> schet_y;
        point.x = schet_x;
        point.y = schet_y;
        *(array + i) = point;
    }
    f.close();
    return 0;
}
//Point sort(Point *array, int tochek) {
//    int dublicatCount = 0;
//    Point temple1, Zero;
//    Zero.x = 0;
//    Zero.y = 0;
//    for (int i1 = 0; i1 <= tochek -1; ++i1) {
//        temple1 = *(array + i1);
//        for(int j1 = 0; j1 <= tochek -1; ++j1) {
//            if (temple1 == *(array + j1)) {
//                *(array + j1) = Zero;
//                dublicatCount++;
//            }
//        }
//    }
//}
double peresechenya(Point *array, int tochek) {
    //-------------------------------------------------------------------------------------------Поиск точек пересечения
    fstream g;
    double x11 = 0, x12 = 0, y11 = 0, y12 = 0, x21 = 0, x22 = 0, y21 = 0, y22 = 0,  A1 = 0, A2 = 0, B1 = 0, B2 = 0, C1 = 0, C2 = 0, X = 0, Y = 0;
    int count_line = 0, count_line2 = 0;

    if (tochek == 3) {
        if(A2/A1 == B2/B1 == C2/C1) {
            cout << "Бесконечное количество точек пересечения" << endl;
            return 0;
        }

    }
    if (tochek > 3) {
        count_line = tochek * (tochek - 1) / 2;
        count_line2 = count_line;
        for (int i = 0; i <= count_line; i++) {
            x11 = (array + i)->x;
            y11 = (array + i)->y;
            x12 = (array + i + 1)->x;
            y12 = (array + i + 1)->y;

            for (int j = 0; j <= count_line2; j++) {

            }
            count_line2--;
        }
    }
    return  0;
}
void vivod_v_file(Point *array, int tochek, double radius) {
    //------------------------------------------------------------------------------------Вывод насчитанного в программе
    fstream g;

    g.open("protocol.odt", ios::out);
    tochek = abs(tochek);
    g << "Реальное количество точек в исходном файле: " << tochek << endl;
    g << "Введенный радиус: " << radius << endl;
    g << "Уникальные точки, введенные в исходный файл: " << endl;
    for(int i = 0; i < tochek - 1; i++) {
        auto item = array + i;
        g << item->x << ";" << item->y << endl;
    }

    g.close();
}
int proverka() {
    //--------------------------------------------------------------------------------Проверяет радиус, точки и сам файл
    fstream f;
    int tochek;
    double radius = 0;
    f.open("../cmake-build-debug/in.txt", ios::in);
    if (f.bad() != 0) {
        cout << "Что-то пошло не так" << endl;
        return 666;
    }
    if (f.bad() == 0) {
        f >> tochek >> radius;
        if (radius <= 0) {
            cout << "Радиус нуль или меньше, так нельзя!" << endl;
            return 666;
        }
        if (abs(tochek) < 3) {
            cout << "Маловато точек. Нужно минимум три уникальных точек" << endl;
            return 666;
        }
        if (tochek < 0 && (abs(tochek) >= 3))
            cout << "\nВы ввели отрицательное число точек. Я буду считать, что минус вы поставили по ошибке" << endl;
    }
    f.close();
    return 0;
}