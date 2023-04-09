#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Optimization
{
protected:
    /*

        Метод расчёта целевой функции, заданной в условии.

        Вариант 9.

    */
    double f(double x1, double x2)
    {
        return 99 * pow(x1, 2) + 196 * x1 * x2 + 99 * pow(x2, 2) - 95 * x1 - 9 * x2 + 91;
    }

    /*

        Метод расчёта производной целевой функции по x1

    */
    double x1_f(double x1, double x2)
    {
        return 198 * x1 + 196 * x2 - 95;
    }

    /*

        Метод расчёта производной целевой функции по x2

    */
    double x2_f(double x1, double x2)
    {
        return 198 * x2 + 196 * x1 - 9;
    }
};

/*

    Поиск по образцу

*/
class SampleSearch : Optimization
{
public:
    void algorithm(double x1_0, double x2_0, double h, double E)
    {
        int N = 1, l = 0;
        double x1_k, x2_k, _x1, _x2, y_k, _y;

        vector <double> x1(5);
        vector <double> x2(5);
        vector <double> y(5);

        x1[0] = x1_0;
        x2[0] = x2_0;
        y[0] = f(x1_0, x2_0);

        while (true)
        {
            y_k = numeric_limits<double>::max();

            x1[1] = x1[0] + h;
            x2[1] = x2[0] + h;

            x1[2] = x1[0] + h;
            x2[2] = x2[0] - h;

            x1[3] = x1[0] - h;
            x2[3] = x2[0] - h;

            x1[4] = x1[0] - h;
            x2[4] = x2[0] + h;

            for (int i = 1; i < 5; i++)
            {
                y[i] = f(x1[i], x2[i]);

                if (y[i] < y_k)
                {
                    y_k = y[i];
                    x1_k = x1[i];
                    x2_k = x2[i];
                }
            }

            N += 4;

            if (y_k < y[0])
            {
                x1[0] = x1_k;
                x2[0] = x2_k;
                y[0] = y_k;

                l++;

                continue;
            }

            if (sqrt(2) * h > E)
            {
                h /= 2;

                x1[0] = x1_k;
                x2[0] = x2_k;
                y[0] = y_k;

                l++;
            }
            else
            {
                break;
            }
        }

        _x1 = x1[0];
        _x2 = x2[0];
        _y = y[0];

        cout << "~x1: " << _x1 << "    ~x2: " << _x2 << "    ~y: " << _y << "    N: " << N << "    l: " << l << "\n";
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Метод поиска по образцу (1, 1):\n\n";

    SampleSearch* sampleSearch1 = new SampleSearch();

    for (int i = 1; i <= 5; i++)
        sampleSearch1->algorithm(1, 1, 1, pow(10, -i));

    sampleSearch1->~SampleSearch();

    delete sampleSearch1;

    cout << "\nМетод поиска по образцу (-1, -1):\n\n";

    SampleSearch* sampleSearch2 = new SampleSearch();

    for (int i = 1; i <= 5; i++)
        sampleSearch2->algorithm(-1, -1, 1, pow(10, -i));

    sampleSearch2->~SampleSearch();

    delete sampleSearch2;
}