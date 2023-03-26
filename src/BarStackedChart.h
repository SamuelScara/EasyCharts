#ifndef BARSTACKEDCHART_H
#define BARSTACKEDCHART_H

#include "BarAbs.h"

class BarStackedChart : public BarAbs {
private:
    QStackedBarSeries* series;
public:
    ~BarStackedChart() = default;

    /**
     * @brief Generates the Bar Stacked Chart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // BARSTACKEDCHART_H
