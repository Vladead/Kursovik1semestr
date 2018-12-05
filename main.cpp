#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int vvod(int stolbec, int stroka, double **ptrarr, int w);
int proverka();

int main() {
    fstream f;
    int prover = 0, tochek = 0;
    double radius = 0;
    prover = proverka();
    if (prover != 0)
        return 666;

    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> tochek >> radius;
    tochek = abs(tochek);


    auto **ptrarr = new double *[tochek];
    for (int i = 0; i <= tochek - 1; i++)
        ptrarr[i] = new double[2];

    f.close();
    delete[] ptrarr;
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
int vvod(int stolbec, int stroka, double **ptrarr, int w) {
    fstream f;
    char s;
    f.open("../cmake-build-debug/in.txt", ios::in);
    f >> stroka >> stolbec;
    if (stolbec > 0 && stroka > 0) {
        for (int i = 0; i <= stroka - 1; i++) {
            for(int j = 0; j <= stolbec - 1; j ++) {
                f >> w;
                if (f.eof() && (i <= stroka - 1)) {
                    cout << "Не хватило строк " << endl;
                    return 666;
                }
                ptrarr[i][j] = w;
                if (j == stolbec - 1) {
                    f.unsetf(ios::skipws);
                    while(true) {
                        f >> s;
                        if (s == '\n') {
                            f.setf(ios::skipws);
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i <= stroka - 1; i++) {
            for (int j = 0; j <= stolbec - 1; j++) {
                cout << setw(2) << ptrarr[i][j];
            }
            cout << "\n";
        }
    }
    f.close();
    return 0;
}