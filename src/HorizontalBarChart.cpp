#include "HorizontalBarChart.h"

QChart* HorizontalBarChart::generateChart(){
    chart = new QChart();

    chart->setTitle("To move the chart click on it and use arrows, to zoom use +/-");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QBarCategoryAxis* axisY = new QBarCategoryAxis();
    QValueAxis *axisX = new QValueAxis();

    for (u_int i = 0; i < model->getTable()->getColumnsNames().size(); ++i)
        axisY->append(QString::fromStdString(model->getTable()->getColumnsNames().at(i)));

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series = generateSeries<QHorizontalBarSeries>();

    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    return chart;
}

void HorizontalBarChart::addColorMapping(){
    setMapping(series);
}
