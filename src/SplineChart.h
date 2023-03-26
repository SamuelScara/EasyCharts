#ifndef SPLINECHART_H
#define SPLINECHART_H

#include "LineAbs.h"

class SplineChart : public LineAbs {
private:
    vector<QSplineSeries*> series;
public:
    ~SplineChart();

    /**
     * @brief Generates the Spline CHart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // SPLINECHART_H
