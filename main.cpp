#include <iostream>
#include <fstream>
#include <cmath>
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

bool Collinear(double A1, double A2, double B1, double B2) {
    return A1 / A2 == B1 / B2;

    //Возвращает true, если прямые параллельны, или false, если нет
}

bool Intersecting(double A1, double A2, double B1, double B2, double C1, double C2) {
    return A1 / A2 == B1 / B2 && B1 / B2 == C1 / C2;

    //Возвращает true, если прямые совпадают, или false, если нет
}

double Distance_point(Point *array_N, Point *array_peresechenya) {
    double Distance;
    Distance = sqrt(pow((array_peresechenya)->x - (array_N)->x, 2) + pow((array_peresechenya)->y - (array_N)->y, 2));

    return Distance;

    //Возвращает расстояние между точками
}

int proverka();
void vivod_v_file(Point *array, int tochek, double radius);
double vvod(Point *array, int tochek, double radius);
double peresechenya(Point *array, int tochek);
//Point sort(Point *array, int tochek);

int main() {
    //------------------------------------------------------------------------------------------------------------------!!!Не забудь изменить вывод в консоль на вывод в файл!!!
    fstream f;
    int tochek = 0;
    bool check = false;
    double radius = 0, x = 0, y = 0;

    check = proverka(); //Проверка файла
    if (check != 0)
        return 666;

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> tochek >> radius;
    tochek = abs(tochek);
    auto *array = new Point[tochek];    //Создание массива структур
    vvod(array, tochek, radius);        //Заполнение массива структур
    for (int i = 0; i <= tochek - 1; i++) {
        auto item = array + i;
        cout << item->x << ";" << item->y << endl;
    }
    peresechenya(array, tochek);

    vivod_v_file(array, tochek, radius);    //Вывод в файл
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
    double x11 = 0, x12 = 0, y11 = 0, y12 = 0, x22 = 0, y22 = 0,  A1 = 0, A2 = 0, B1 = 0, B2 = 0, C1 = 0, C2 = 0, X = 0, Y = 0;
    int count_line = 0, count_line2 = 0;

    if (tochek == 3) {
        if(A2/A1 == B2/B1 == C2/C1) {
            cout << "Бесконечное количество точек пересечения" << endl;
            return 0;
        }
    }
    if (tochek > 3) {
        count_line = tochek * (tochek - 1) / 2;
        count_line2 = tochek - 2;
        for (int i = 0; i <= count_line - 1; i++) {
            //Создание первой прямой
            y11 = (array + i)->y;
            y12 = (array + (i+1))->y;
            x11 = (array + i)->x;
            x12 = (array + (i+1))->x;

            A1 = y11 - y12;
            B1 = x12 - x11;
            C1 = x11*y12 - x12*y11;
            for (int j = 0; j <= count_line - 1; j++) {
                //Создание следующих прямых
                y22 = (array + j + 2)->y;
                x22 = (array + j + 2)->x;

                A2 = y11 - y22;
                B2 = x22 - x11;
                C2 = x11*y22 - x22*y11;
                if (A1/A2 == B1/B2 == C1/C2) {
                    //Проверка совпадения прямых
                    break;
                }
                if (A1/A2 == B1/B2) {
                    //Проверка параллельности прямых
                    break;
                }
                //Нахождение координаты точки пересечения
                Y = (C2*A1 - C1*A2)/(B1*A2 - A1*B2);
                X = (-B2*Y - C2)/A2;
            }
            //count_line2--;
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
    for(int i = 0; i <= tochek - 1; i++) {
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
            cout << "Маловато точек. Нужно минимум три уникальные точки" << endl;
            return 666;
        }
        if (tochek < 0 && (abs(tochek) >= 3))
            cout << "\nВы ввели отрицательное число точек. Я буду считать, что минус вы поставили по ошибке" << endl;
    }
    f.close();
    return 0;
}