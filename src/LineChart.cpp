#include "LineChart.h"

LineChart::~LineChart() {
    for(auto it = series.begin(); it != series.end(); ++it)
        delete *it;

    series.clear();
}

QChart* LineChart::generateChart(){
    chart = new QChart();

    chart->setTitle("To move the chart click on it and use arrows, to zoom use +/-");
    chart->setAnimationOptions(QChart::NoAnimation);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QCategoryAxis* axisX = new QCategoryAxis();
    QValueAxis* axisY = new QValueAxis();

    for (u_int i = 0; i < model->getTable()->getColumnsNames().size(); i++)
        axisX->append(QString::fromStdString(model->getTable()->getColumnsNames().at(i)), i);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    series = generateSeries<QLineSeries>(axisX, axisY);

    axisY->setRange(model->getTable()->getMinValue(), model->getTable()->getMaxValue());
    axisX->setRange(0, model->getTable()->getColumnCount()-1);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    return chart;
}

void LineChart::addColorMapping(){
    setMapping(series);
}
