#ifndef SCATTERCHART_H
#define SCATTERCHART_H

#include "Chart.h"

class ScatterChart : public Chart {
private:
    vector<QScatterSeries*> series;
public:
    ~ScatterChart();

    /**
     * @brief Generates the Scatter Chart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;
};

#endif // SCATTERCHART_H
