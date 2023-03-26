#include "BarStackedChart.h"

QChart* BarStackedChart::generateChart(){
    chart = new QChart();

    chart->setTitle("To move the chart click on it and use arrows, to zoom use +/-");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QValueAxis *axisY = new QValueAxis();

    for (u_int i = 0; i < model->getTable()->getColumnCount(); ++i)
        axisX->append(QString::fromStdString(model->getTable()->getColumnsNames().at(i)));

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series = generateSeries<QStackedBarSeries>();

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    return chart;
}


void BarStackedChart::addColorMapping(){
    setMapping(series);
}
