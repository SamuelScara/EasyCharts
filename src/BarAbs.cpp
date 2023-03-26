#include "BarAbs.h"

template <class T>
T* BarAbs::generateSeries() const {
    T* series = new T();

    for(short i = 0; i < model->rowCount(); ++i){
        QBarSet* set = new QBarSet(QString::fromStdString(model->getTable()->getRowsNames().at(i)));
        for(short j = 0; j < model->columnCount(); ++j)
            set->append(model->getTable()->getTable()[i][j]);

        series->append(set);
    }
    return series;
}

template QBarSeries* BarAbs::generateSeries<QBarSeries>() const;
template QHorizontalBarSeries* BarAbs::generateSeries<QHorizontalBarSeries>() const;
template QStackedBarSeries* BarAbs::generateSeries<QStackedBarSeries>() const;
template QHorizontalStackedBarSeries* BarAbs::generateSeries<QHorizontalStackedBarSeries>() const;


template <class T>
void BarAbs::setMapping(T* series) {
    model->clearMapping();
    QString seriesColorHex = "";
    QList<QBarSet *> barsets = series->barSets();
    for(int i = 0; i < series->count(); ++i) {
        for (int j = 0; j < barsets.count(); ++j) {
            seriesColorHex = "#" + QString::number(barsets.at(i)->brush().color().rgb(), 16).right(6).toUpper();
            model->addMapping(seriesColorHex, QRect(j, i, barsets.at(i)->count(), 1));
        }
    }
}

template void BarAbs::setMapping<QBarSeries>(QBarSeries*);
template void BarAbs::setMapping<QStackedBarSeries>(QStackedBarSeries*);
template void BarAbs::setMapping<QHorizontalBarSeries>(QHorizontalBarSeries*);
template void BarAbs::setMapping<QHorizontalStackedBarSeries>(QHorizontalStackedBarSeries*);
