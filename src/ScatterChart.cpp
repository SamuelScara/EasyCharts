#include "ScatterChart.h"

ScatterChart::~ScatterChart() {
    for(auto it = series.begin(); it != series.end(); ++it)
        delete *it;

    series.clear();
}

QChart* ScatterChart::generateChart(){
    chart = new QChart();

    chart->setTitle("To move the chart click on it and use arrows, to zoom use +/-");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QCategoryAxis* axisX = new QCategoryAxis();
    QValueAxis* axisY = new QValueAxis();

    for (int i = 0; i < model->columnCount(); i++)
        axisX->append(QString::fromStdString(model->getTable()->getColumnsNames().at(i)), i);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    vector<vector<double>> data = model->getTable()->getTable();
    for (int i = 0; i < model->rowCount(); ++i){
        QScatterSeries* ser = new QScatterSeries();
        ser->setName(QString::fromStdString(model->getTable()->getRowsNames().at(i)));

        for (int j = 0; j < model->columnCount(); j++){
            ser->append(j, model->getTable()->getTable()[i][j]);
            ser->setMarkerShape(QScatterSeries::MarkerShapeCircle);
        }

        chart->addSeries(ser);
        series.push_back(ser);

        ser->attachAxis(axisX);
        ser->attachAxis(axisY);
    }

    axisY->setRange((model->getTable()->getMinValue() >= 0) ? 0 : model->getTable()->getMinValue()*1.1, model->getTable()->getMaxValue()*1.1);
    axisX->setRange(-1, model->columnCount());

    return chart;
}

void ScatterChart::addColorMapping(){
    model->clearMapping();
    QString seriesColorHex = "";
    for (u_int i = 0; i < series.size(); ++i) {
        for (int j = 0; j < series.at(i)->count(); ++j) {
            seriesColorHex = "#" + QString::number(series.at(i)->color().rgb(), 16).right(6).toUpper();
            model->addMapping(seriesColorHex, QRect(j, i, series.at(i)->count(), 1));
        }
    }
}
