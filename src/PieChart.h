#ifndef PIECHART_H
#define PIECHART_H

#include "Chart.h"

class PieChart : public Chart {
private:
    QPieSeries* series;
    double holeSize;
public:
    PieChart(double = 0.0);
    ~PieChart() = default;

    /**
     * @brief Generates the Pie Chart
     * @return QChart pointer
     */
    QChart* generateChart() override;

    /**
     * @brief Adds the color mapping for the chart
     */
    void addColorMapping() override;

    /**
     * @brief generates the series
     * @return generated series for pie chart
     */
    QPieSeries* generateSeries() const;
};

#endif // PIECHART_H
