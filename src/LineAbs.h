#ifndef LINEABS_H
#define LINEABS_H

#include <QChart>
#include <vector>
#include <string>

#include "Chart.h"

class LineAbs : public Chart {
protected:
    template <class T>
    /**
     * @brief generates the series
     * @return generated series for line type charts
     */
    vector<T*> generateSeries(QCategoryAxis*&, QValueAxis*&) const;

    template <class T>

    /**
     * @brief Sets the mapping for the chart
     */
    void setMapping(vector<T*>);
};

#endif // LINEABS_H
