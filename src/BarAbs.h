#ifndef BARABS_H
#define BARABS_H

#include <QChart>

#include "Chart.h"

class BarAbs : public Chart {
protected:
    template <class T>
    /**
     * @brief generates the series
     * @return generated series for bar type charts
     */
    T* generateSeries() const;

    template <class T>
    /**
     * @brief Sets the mapping for the bars
     * @param 'series' has to be a barseries type
     */
    void setMapping(T* series);
};

#endif // BARABS_H
