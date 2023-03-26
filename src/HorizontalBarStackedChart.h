#ifndef HORIZONTALBARSTACKEDCHART_H
#define HORIZONTALBARSTACKEDCHART_H

#include "BarAbs.h"

class HorizontalBarStackedChart : public BarAbs {
private:
    QHorizontalStackedBarSeries* series;
public:
    ~HorizontalBarStackedChart() = default;

    /**
     * @brief Generates the Horizontal Bar Stacked Chart
     * @return the pointer to the chart
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // HORIZONTALBARSTACKEDCHART_H
