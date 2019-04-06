#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QVector>
#include <QPair>

#include <QtCharts/QChartView>
#include <QSlider>
#include <QSpinBox>
#include <QValueAxis>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>

QT_CHARTS_USE_NAMESPACE

class Model : public QObject
{
    Q_OBJECT
public:
    Model();
    Model(
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
            );

public slots:
    void simulationBegin();
    void showPhase();

private:
    QDoubleSpinBox *r, *f, *q, *a, *t;
    QSpinBox *n0, *c0;

    QPair<QVector<long>, QVector<long>> simulate();
    QChart *ctx;
    QSplineSeries *seriesN;
    QSplineSeries *seriesC;
    QValueAxis *axisX, *axisY;
};

#endif // MODEL_H
