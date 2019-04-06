#include "model.h"
#include "math.h"
#include <QDebug>
#include <QValueAxis>
#include "runge.h"

Model::Model()
{

}

Model::Model(
            QChart *chart,
            QDoubleSpinBox *r,
            QDoubleSpinBox *t,
            QDoubleSpinBox *f,
            QDoubleSpinBox *q,
            QDoubleSpinBox *a,
            QSpinBox *n0,
            QSpinBox *c0,
            QValueAxis *axisX,
            QValueAxis *axisY
        )
{
    this->ctx = chart;
    this->r = r;
    this->t = t;
    this->f = f;
    this->q = q;
    this->a = a;
    this->n0 = n0;
    this->c0 = c0;
    this->axisX = axisX;
    this->axisY = axisY;
}

void Model::simulationBegin()
{
    auto values = simulate();

    auto popN = values.first;
    auto popC = values.second;

    ctx->removeAllSeries();

    seriesN = new QSplineSeries();
    seriesC = new QSplineSeries();
    seriesN->setName("Популяция жертв");
    seriesC->setName("Популяция хищников");

    float second = 0.f;
    float fl_t = t->text().toFloat();

    for (int i = 0; i < popN.size(); i++)
    {
        seriesN->append(static_cast<qreal>(second), static_cast<qreal>(popN[i]));
        seriesC->append(static_cast<qreal>(second), static_cast<qreal>(popC[i]));
        second += 1.f;
    }

    ctx->addSeries(seriesN);
    ctx->addSeries(seriesC);

    seriesN->attachAxis(axisX);
    seriesN->attachAxis(axisY);

    seriesC->attachAxis(axisX);
    seriesC->attachAxis(axisY);
}

void Model::showPhase()
{
    auto values = simulate();

    auto popN = values.first;
    auto popC = values.second;

    ctx->removeAllSeries();

    seriesN = new QSplineSeries();
    seriesC = new QSplineSeries();
    seriesN->setName("Популяция жертв");
    seriesC->setName("Популяция хищников");

    float second = 0.f;
    float fl_t = t->text().toFloat();

    for (int i = 0; i < popN.size(); i++)
    {
        seriesN->append(static_cast<qreal>(popN[i]), static_cast<qreal>(popC[i]));
        second += 1.f;
    }

    ctx->addSeries(seriesN);
    ctx->addSeries(seriesC);

    seriesN->attachAxis(axisX);
    seriesN->attachAxis(axisY);

    seriesC->attachAxis(axisX);
    seriesC->attachAxis(axisY);
}

QPair<QVector<long>, QVector<long>> Model::simulate()
{
    Runge runge(r->value(), a->value(), f->value(), q->value(), n0->value(), c0->value());

    return runge.calculate(300, t->value());
}
