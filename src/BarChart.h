#ifndef BARCHART_H
#define BARCHART_H

#include "BarAbs.h"

class BarChart : public BarAbs {
private:
    QBarSeries* series;
public:
    ~BarChart() = default;

    /**
     * @brief Generates the Bar Chart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;

};

#endif // BARCHART_H
