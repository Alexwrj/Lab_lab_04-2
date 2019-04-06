/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

#include <QVector>
#include <QString>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>

#include "chart.h"
#include "chartview.h"
#include "model.h"

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Chart *chart = new Chart();
    chart->setTitle("Модель \"Хищник-жертва\"");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(5);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QWidget window;

    QLabel *lbl_Prarm_r = new QLabel("    r: ");
    QLabel *lbl_Prarm_f = new QLabel("    f: ");
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addWidget(chartView);

    const int rowNum = 5;
    QVector<QHBoxLayout*> strings(rowNum);

    for (auto &row : strings)
    {
        row = new QHBoxLayout();
        vLayout->addLayout(row);
    }

    QDoubleSpinBox *sl_RangeParam_r = new QDoubleSpinBox();
    sl_RangeParam_r->setRange(0.01, 100);
    sl_RangeParam_r->setValue(5);
    sl_RangeParam_r->setSingleStep(0.1);

    QDoubleSpinBox *sl_RangeParam_f = new QDoubleSpinBox();
    sl_RangeParam_f->setRange(0.01, 100);
    sl_RangeParam_f->setValue(0.6);
    sl_RangeParam_f->setSingleStep(0.1);

    strings[0]->addWidget(lbl_Prarm_r);
    strings[0]->addWidget(sl_RangeParam_r);
    strings[0]->addSpacing(10);
    strings[0]->addWidget(lbl_Prarm_f);
    strings[0]->addWidget(sl_RangeParam_f);
    strings[0]->addStretch(10);

    QLabel *lbl_Param_t = new QLabel("    t:  ");
    QDoubleSpinBox *sbox_Param_t = new QDoubleSpinBox();
    sbox_Param_t->setValue(0.1);
    sbox_Param_t->setSingleStep(0.001);
    sbox_Param_t->setMinimum(0.001);
    sbox_Param_t->setMaximum(10);

    strings[1]->addWidget(lbl_Param_t);
    strings[1]->addWidget(sbox_Param_t);
    strings[1]->addWidget(new QLabel(""), 8);

    QLabel *lbl_Param_q = new QLabel("    q: ");
    QLabel *lbl_Param_a = new QLabel("   a: ");
    QDoubleSpinBox *txt_Param_q = new QDoubleSpinBox();
    txt_Param_q->setRange(0.01, 100);
    txt_Param_q->setValue(2);
    txt_Param_q->setSingleStep(0.1);
    QDoubleSpinBox *txt_Param_a = new QDoubleSpinBox();
    txt_Param_a->setRange(0.01, 100);
    txt_Param_a->setValue(0.1);
    txt_Param_a->setSingleStep(0.1);

    strings[2]->addWidget(lbl_Param_q);
    strings[2]->addWidget(txt_Param_q);
    strings[2]->addSpacing(10);
    strings[2]->addWidget(lbl_Param_a);
    strings[2]->addWidget(txt_Param_a);
    strings[2]->addStretch(10);

    QLabel *lbl_Param_n0 = new QLabel("    Жертвы:  ");
    QSpinBox *sbox_Param_n0 = new QSpinBox();
    sbox_Param_n0->setValue(100);
    sbox_Param_n0->setMinimum(0);
    sbox_Param_n0->setMaximum(1000);

    QLabel *lbl_Param_c0 = new QLabel("  Хищники:  ");
    QSpinBox *sbox_Param_c0 = new QSpinBox();
    sbox_Param_c0->setValue(30);
    sbox_Param_c0->setMinimum(0);
    sbox_Param_c0->setMaximum(1000);

    strings[3]->addWidget(lbl_Param_n0);
    strings[3]->addWidget(sbox_Param_n0);
    strings[3]->addSpacing(10);
    strings[3]->addWidget(lbl_Param_c0);
    strings[3]->addWidget(sbox_Param_c0);
    strings[3]->addStretch(10);

    QPushButton *btn_BeginSimulation = new QPushButton("Начать симуляцию");
    QPushButton *btn_ShowPhase = new QPushButton("Фазовый портрет");

    strings[4]->addWidget(new QLabel("       "));
    strings[4]->addWidget(btn_BeginSimulation);
    strings[4]->addWidget(btn_ShowPhase);
    strings[4]->addStretch(10);

    Model *model = new Model(
                    chart,
                    sl_RangeParam_r,
                    sbox_Param_t,
                    sl_RangeParam_f,
                    txt_Param_q,
                    txt_Param_a,
                    sbox_Param_n0,
                    sbox_Param_c0,
                    axisX,
                    axisY
                );
    QObject::connect(btn_BeginSimulation, SIGNAL(clicked()), model, SLOT(simulationBegin()));
    QObject::connect(btn_ShowPhase, SIGNAL(clicked()), model, SLOT(showPhase()));

    window.setLayout(vLayout);
    window.grabGesture(Qt::PanGesture);
    window.grabGesture(Qt::PinchGesture);
    window.resize(800, 600);
    window.show();


    return a.exec();
}
