#ifndef RUNGE_H
#define RUNGE_H

#include <QVector>
#include <QPair>

class Runge
{
public:
    Runge(double r, double a, double f, double q, int n0, int c0);
    QPair<QVector<long>, QVector<long>>calculate(int n, double h);

private:
    double r, a, f, q;
    int n0, c0;

    double equationN(double n, double c);
    double equationC(double n, double c);

};

#endif // RUNGE_H
