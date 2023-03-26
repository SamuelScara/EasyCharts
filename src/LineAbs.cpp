#include "LineAbs.h"

template <class T>
vector<T*> LineAbs::generateSeries(QCategoryAxis*& x, QValueAxis*& y) const {
    vector<T*> series = vector<T*>();

    for (int i = 0; i < model->rowCount(); ++i){
        T* s = new T();
        s->setName(QString::fromStdString(model->getTable()->getRowsNames().at(i)));

        for (int j = 0; j < model->columnCount(); j++)
            s->append(j, model->getTable()->getTable()[i][j]);

        chart->addSeries(s);
        series.push_back(s);

        s->attachAxis(x);
        s->attachAxis(y);
    }

    return series;
}

template vector<QLineSeries*> LineAbs::generateSeries<QLineSeries>(QCategoryAxis*&, QValueAxis*&) const;
template vector<QSplineSeries*> LineAbs::generateSeries<QSplineSeries>(QCategoryAxis*&, QValueAxis*&) const;


template<class T>
void LineAbs::setMapping(vector<T*> series) {
    model->clearMapping();
    QString seriesColorHex = "";
    for (u_int i = 0; i < series.size(); ++i) {
        for (int j = 0; j < series.at(i)->count(); ++j) {
            seriesColorHex = "#" + QString::number(series.at(i)->color().rgb(), 16).right(6).toUpper();
            model->addMapping(seriesColorHex, QRect(j, i, series.at(i)->count(), 1));
        }
    }
}

template void LineAbs::setMapping<QLineSeries>(vector<QLineSeries*>);
template void LineAbs::setMapping<QSplineSeries>(vector<QSplineSeries*>);
