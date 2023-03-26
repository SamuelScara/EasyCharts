#include "PieChart.h"

PieChart::PieChart(double hs) : series(new QPieSeries()), holeSize(hs) {};

QChart* PieChart::generateChart(){
        chart = new QChart();

        chart->setTitle("Every single slice in the chart represents the sum of the values stored in one row");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->setVisible(false);

        series = generateSeries();

        series->setLabelsVisible(true);
        series->setLabelsPosition(QPieSlice::LabelOutside);

        for(const auto& slice : series->slices()) {
            QString x = slice->label() + " " + QString("%1%").arg(100*slice->percentage(), 0, 'f', 1);
            slice->setLabel(x);
        }

        series->setPieSize(0.65);
        series->setHoleSize(holeSize);
        chart->addSeries(series);

        return chart;
}

void PieChart::addColorMapping(){
    model->clearMapping();
    QString seriesColorHex = "";
    QList<QPieSlice *> slices = series->slices();

    for(int i = 0; i <  model->rowCount(); ++i) {
        seriesColorHex = "#" + QString::number(slices.at(i)->brush().color().rgb(), 16).right(6).toUpper();
        for(int j = 0; j < model->columnCount(); ++j)
            model->addMapping(seriesColorHex, QRect(j, i, 1, 1));
    }
}

QPieSeries* PieChart::generateSeries() const {
    QPieSeries* series = new QPieSeries(chart);

    for (u_int i = 0; i < model->getTable()->getRowCount(); ++i) {
        auto val = model->getTable()->getSumRows();
        QPieSlice* slice = series->append(QString::fromStdString(model->getTable()->getRowsNames().at(i)), val[i]);
        slice->setLabelVisible();
    }

    return series;
}
