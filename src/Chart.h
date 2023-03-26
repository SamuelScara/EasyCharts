#ifndef CHART_H
#define CHART_H

#include <QtCharts>

#include "Model.h"
#include "ChartView.h"

class Chart {
protected:
    Model* model;
    QChart* chart;
public:
    virtual ~Chart() = default;

    /**
     * @brief Generates the selected type of chart
     * @return the pointer to the chart
     */
    virtual QChart* generateChart() = 0;

    /**
     * @brief Adds the color mapping for the chart
     */
    virtual void addColorMapping() = 0;

    /**
     * @brief Removes the color mapping of the chart
     */
    void removeColorMapping() {model->clearMapping();};

    /**
     * @brief Sets the model object
     * @param 'm' is the model of the chart
     */
    void setModel(Model* m) {model = m;};
};

#endif // CHART_H
