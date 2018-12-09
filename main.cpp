#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <set>
#include <tuple>
using namespace std;

struct point
{
    point(double x, double y) : x(x), y(y) {}
    double x;
    double y;
};

struct compare {
    bool operator() (const point&lhs, const point& rhs) const {
        return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
    }
};

set<point, compare> vvod(set<point, compare> container, int a, double b);
int proverka();

int main() {
    fstream f;
    int prover = 0, tochek = 0, a = 0, b = 0, w = 0;
    double radius = 0;
    set<point, compare> vivod{};
    prover = proverka();
    if (prover != 0)
        return 666;

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> tochek >> radius;
    tochek = abs(tochek);
    vivod = vvod(vivod, tochek, radius);
    for(auto item : vivod)
    {
        cout << item.x << ";" << item.y << std::endl;
    }

    f.close();
    return 0;
}

int proverka() {
    //----------------------------------------------------Проверяет радиус, точки и сам файл
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
            cout << "Маловато точек. Нужно минимум три" << endl;
            return 666;
        }
        if (tochek < 0 && (abs(tochek) >= 3))
            cout << "\nВы ввели отрицательное число точек. Я буду считать, что минус вы поставили по ошибке" << endl;
    }
    f.close();
    return 0;
}
set<point, compare> vvod(set<point, compare> container, int a, double b) {
    fstream f;
    double schet_x = 0, schet_y = 0;

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> a >> b;
    a = abs(a);
    for (int i = 0; i <= a - 1; i++) {
        f >> schet_x >> schet_y;
        container.insert(point(schet_x, schet_y));
    }
    f.close();
    return container;
}