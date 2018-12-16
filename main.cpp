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
struct Line
{
    double A;
    double B;
    double C;
};

bool operator==(const Point &point1, const Point &point2) {
    return (&point1.x == &point2.x && &point1.y == &point2.y);
}

bool Collinear(double A1, double A2, double B1, double B2) {
    return A1 / A2 == B1 / B2;

    //Возвращает true, если прямые параллельны, или false, если нет
}
bool Overlap(double A1, double A2, double B1, double B2, double C1, double C2) {
    return A1 / A2 == B1 / B2 && B1 / B2 == C1 / C2;

    //Возвращает true, если прямые совпадают, или false, если нет
}
double Distance_point(Point *array_N, Point *array_peresechenya) {
    double Distance;
    Distance = sqrt(pow((array_peresechenya)->x - (array_N)->x, 2) + pow((array_peresechenya)->y - (array_N)->y, 2));

    return Distance;

    //Возвращает расстояние между точками
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

double peresechenya(Point *array, Line *array_line, Point *array_intersection, int tochek) {
    //-------------------------------------------------------------------------------------------Поиск точек пересечения
    fstream g;
    double x11 = 0, x12 = 0, y11 = 0, y12 = 0, A1 = 0, A2 = 0, B1 = 0, B2 = 0, C1 = 0, C2 = 0, X = 0, Y = 0;
    int count_line = 0;

    if (tochek == 3) {
        if(A2/A1 == B2/B1 == C2/C1) {
            //Надо дописать
            cout << "Бесконечное количество точек пересечения" << endl;
            return 0;
        }
    }
    if (tochek > 3) {
        int count = 1;
        for (int m1 = 0; m1 <= tochek - 2; m1++) {
            for (int m2 = count; m2 <= tochek - 1; m2++) {
                x11 = (array + m1)->x;
                y11 = (array + m1)->y;
                x12 = (array + m2)->x;
                y12 = (array + m2)->y;
                A1 = y11 - y12;
                B1 = x12 - x11;
                C1 = x11*y12 - x12*y11;
                (array_line + count_line)->A = A1;
                (array_line + count_line)->B = B1;
                (array_line + count_line)->C = C1;
                count_line++;
            }
            count++;
        }
        int count2 = 0;
        int count3 = 0;
        for(int i1 = 0; i1 <= count_line - 2; i1++) {
            for (int i2 = count3; i2 <= count_line - 2; i2++) {
                A1 = (array_line + i1)->A;
                A2 = (array_line + i2 + 1)->A;
                B1 = (array_line + i1)->B;
                B2 = (array_line + i2 + 1)->B;
                C1 = (array_line + i1)->C;
                C2 = (array_line + i2 + 1)->C;
                if(Collinear(A1, A2, B1, B2)) {
                    break;
                }
                if(Overlap(A1, A2, B1, B2, C1, C2)) {
                    break;
                }
                if(A1 != 0) {
                    Y = ((C2 * A1 - C1 * A2) / (A1 * B2 - B1 * A2));
                    X = (-B1 * Y + C1) / A1;
                    Y = -Y;
                    X = -X;
                }
                (array_intersection + count2)->x = X;
                (array_intersection + count2)->y = Y;
                count2++;
            }
            count3++;
        }
    }
    return  0;
}

double Dot_score(Point *array, Point *array_intersection, int tochek, double radius) {

}

void vivod_v_file(Point *array, Point *array_intersection, Line *array_line, int tochek, double radius, int line) {
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
    g << endl;
    g << "Найденные точки пересечения: " << endl;
    for (int i = 0; i <= line*3 - 1; i++) {
        auto item = array_intersection + i;
        g << item->x << ";" << item->y << endl;
    }
    g << endl;
    g << "Вычисленные коэффициенты прямых: " << endl;
    for (int i = 0; i <= line - 1; i++) {
        auto item = array_line + i;
        g << "A: " << item->A << ";" << "B: " << item->B << ";" << "C:" << item->C <<  endl;
    }
    g.close();
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


int main() {
    //----------------------------------------------------------!!!Не забудь изменить вывод в консоль на вывод в файл!!!
    fstream f;
    int tochek = 0, line = 0, Max_DotScore = 0;
    bool check = false;
    double radius = 0, x = 0, y = 0;

    check = proverka(); //Проверка файла
    if (check != 0)
        return 666;

    f.open("../cmake-build-debug/in.txt", ios::in);    //Открытие входного файла
    f >> tochek >> radius;
    tochek = abs(tochek);
    line = tochek*(tochek - 1)/2;
    auto *array = new Point[tochek];    //Создание массива структур для точек
    auto *array_line = new Line[line];  //Создание массива структур для прямых
    auto *array_intersection = new Point[line*3]; //Создание массива структур для точек пересечения
    vvod(array, tochek, radius);        //Заполнение массива структур
    f.close();      //Закрытие входного файла
    for (int i = 0; i <= tochek - 1; i++) {
        auto item = array + i;
        cout << item->x << ";" << item->y << endl;
    }
    peresechenya(array, array_line, array_intersection, tochek);

    cout << endl;
    for (int i = 0; i <= line*3 - 1; i++) {
        auto item = array_intersection + i;
        cout << item->x << ";" << item->y << endl;
    }
    cout << endl;
    for (int i = 0; i <= line - 1; i++) {
        auto item = array_line + i;
        cout << item->A << ";" << item->B << ";" << item->C <<  endl;
    }

    vivod_v_file(array, array_intersection, array_line, tochek, radius, line);    //Вывод в файл
    delete[] array; //Очистка памяти
    delete[] array_line;
    delete[] array_intersection;
    return 0;
}