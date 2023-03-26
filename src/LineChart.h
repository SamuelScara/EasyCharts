#ifndef LINECHART_H
#define LINECHART_H

#include "LineAbs.h"

class LineChart : public LineAbs {
private:
    vector<QLineSeries*> series;
public:
    ~LineChart();

    /**
     * @brief Generates the Line Chart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // LINECHART_H
