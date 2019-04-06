#include "runge.h"
#include <QDebug>

Runge::Runge(double r, double a, double f, double q, int n0, int c0)
{
    this->r = r;
    this->a = a;
    this->f = f;
    this->q = q;
    this->n0 = n0;
    this->c0 = c0;
}

//prey
double Runge::equationN(double n, double c)
{
    return ((r - a * c) * n);
}

//predators
double Runge::equationC(double n, double c)
{
    return ((f * a * n - q) * c);
}

QPair<QVector<long>, QVector<long>> Runge::calculate(int n, double h)
{
    QVector<long>outVectorN(n);
    QVector<long>outVectorC(n);

    outVectorN[0] = n0;
    outVectorC[0] = c0;
    qDebug() << "Predators: " << outVectorC[0] << ", Prey: " << outVectorN[0] << "\n";

    for (int i = 1; i < n; i++)
    {
        double k1_n = equationN(outVectorN[i - 1], outVectorC[i - 1]);
        double k1_c = equationC(outVectorN[i - 1], outVectorC[i - 1]);

        double k2_n = equationN(outVectorN[i - 1] + ((h * k1_n) / 2.0), outVectorC[i - 1] + ((h * k1_c)) / 2.0);
        double k2_c = equationC(outVectorN[i - 1] + ((h * k1_n) / 2.0), outVectorC[i - 1] + ((h * k1_c)) / 2.0);

        double k3_n = equationN(outVectorN[i - 1] + ((h * k2_n) / 2.0), outVectorC[i - 1] + ((h * k2_c)) / 2.0);
        double k3_c = equationC(outVectorN[i - 1] + ((h * k2_n) / 2.0), outVectorC[i - 1] + ((h * k2_c)) / 2.0);

        double k4_n = equationN(outVectorN[i - 1] + h * k3_n, outVectorC[i - 1] + h * k3_c);
        double k4_c = equationC(outVectorN[i - 1] + h * k3_n, outVectorC[i - 1] + h * k3_c);

        outVectorN[i] = static_cast<long>(outVectorN[i - 1] + (h / 6.0) * (k1_n + 2.0 * k2_n + 2.0 * k3_n + k4_n));
        outVectorC[i] = static_cast<long>(outVectorC[i - 1] + (h / 6.0) * (k1_c + 2.0 * k2_c + 2.0 * k3_c + k4_c));

        qDebug() << "Predators: " << outVectorC[i] << ", Prey: " << outVectorN[i] << "\n";
    }

    return QPair<QVector<long>, QVector<long>> (outVectorN, outVectorC);
}
