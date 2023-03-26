#ifndef HORIZONTALBARCHART_H
#define HORIZONTALBARCHART_H

#include "BarAbs.h"

class HorizontalBarChart : public BarAbs {
private:
    QHorizontalBarSeries* series;
public:
    ~HorizontalBarChart() = default;

    /**
     * @brief Generates the Horizontal Bar Chart
     * @return the pointer to the chart
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // HORIZONTALBARCHART_H
