#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int vvod(int stolbec, int stroka, double **ptrarr, int w);
int proverka(int w);

int main() {
    int prover = 0, stroka = 0, stolbec = 0, w = 0;
    prover = proverka(w);
    if (prover != 0) {
        return 666;
    }

    return 0;
}

int proverka(int w) {
    fstream f;

    f.open("../cmake-build-debug/in.txt", ios::in);
    if (f.bad() != 0) {
        cout << "Что-то пошло не так" << endl;
        return 666;
    }
//    else {
//        f >> stroka >> stolbec;
//        auto **ptrarr = new double *[stroka];
//        for (int i = 0; i <= stolbec - 1; i++)
//            ptrarr[i] = new double[stolbec];
//        if (stolbec <= 0 || stroka <= 0) {
//            cout << "\nКоличество элементов не может быть нулевым или отрицательным!" << endl;
//            return 666;
//        }
//        f.close();
//    }
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