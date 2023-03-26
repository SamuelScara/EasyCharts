#include "SplineChart.h"

SplineChart::~SplineChart() {
    for(auto it = series.begin(); it != series.end(); ++it)
        delete *it;

    series.clear();
}

QChart* SplineChart::generateChart(){
    chart = new QChart();

    chart->setTitle("To move the chart click on it and use arrows, to zoom use +/-");
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QCategoryAxis* axisX = new QCategoryAxis();
    QValueAxis* axisY = new QValueAxis();

    for (int i = 0; i < model->columnCount(); i++)
        axisX->append(QString::fromStdString(model->getTable()->getColumnsNames().at(i)), i);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    series = generateSeries<QSplineSeries>(axisX, axisY);

    axisY->setRange(model->getTable()->getMinValue()*1.3, model->getTable()->getMaxValue()*1.3);
    axisX->setRange(0, model->getTable()->getColumnCount()-1);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    return chart;
}

void SplineChart::addColorMapping(){
    setMapping(series);
}
