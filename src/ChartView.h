#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>

class ChartView : public QChartView {
private:
    QChart::ChartTheme nameTheme;

    /**
     * @brief Sets an action when you press a key of your keyboard
     * @param 'event' is a keyboard button pressed
     */
    void keyPressEvent(QKeyEvent *event);
public:

    /**
     * @brief Gets the name of the theme
     * @return ChartTheme applied to the chart
     */
    QChart::ChartTheme getNameTheme() const;

    /**
     * @brief Sets the name for the theme
     * @param 'theme' is the ChartTheme to be applied
     */
    void setNameTheme(QChart::ChartTheme theme = QChart::ChartThemeLight);
};

#endif
