#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QChartView>
#include <QLineSeries>
#include <QWidget>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QScreen>
#include <QMessageBox>
#include <QtCharts>

#include <QVXYModelMapper>
#include <QTableView>
#include <QChartView>

#include "Chart.h"
#include "BarChart.h"
#include "HorizontalBarChart.h"
#include "BarStackedChart.h"
#include "HorizontalBarStackedChart.h"
#include "LineChart.h"
#include "PieChart.h"
#include "ScatterChart.h"
#include "SplineChart.h"
#include "Model.h"
#include "TableData.h"
#include "ChartView.h"

#include <vector>
using std::vector;
using QtCharts::QVXYModelMapper;
using QtCharts::QChartView;

typedef unsigned int u_int;
class Controller;
class MainWindow : public QWidget
{
    Q_OBJECT
private:
    Controller* controller;

    QVBoxLayout* mainLayout;
    QHBoxLayout* chartsLayout;
    Chart* chart;

    QMenuBar* menu;
    QMenu* file;
    QMenu* edit;
    QMenu* graphs;
    QMenu* settings;
    QMenu* theme;
    QMenu* others;
    QAction* help;

    QAction* saveChart;
    QAction* newTab;
    QAction* insertColumnKey;
    QAction* insertRowKey;
    QAction* openChart;


    QPushButton* insertRowBeforeButton;
    QPushButton* insertRowAfterButton;
    QPushButton* insertColumnBeforeButton;
    QPushButton* insertColumnAfterButton;
    QPushButton* deleteCurrentRowButton;
    QPushButton* deleteCurrentColumnButton;

    QTableView* tableView = nullptr;
    ChartView* chartView = nullptr;

    QAction* colorsItem;
    QAction* manageTable;
    QAction* manageChart;
public:
    MainWindow(QWidget* = nullptr);
    ~MainWindow() = default;

    /* ----required sets---- */

    /**
     * @brief Sets controller object
     * @param 'controller' controller object to be applied
     */
    void setController(Controller* controller);

    /**
     * @brief Sets TableView object
     */
    void setTableView();

    /**
     * @brief sets ChartView object
     */
    void setChartView();

    /* ----add grapichal interface---- */

    /**
     * @brief Sets the Menu Bar object with all the features and graphical interface
     */
    void addMenuBar();

    /**
     * @brief Sets the Tool Bar with all the buttons and features into the layout
     * @param layout for the toolBar
     */
    void setToolBar(QHBoxLayout* layout);

    /**
     * @brief Refreshes the Table View object
     */
    void refreshTableView();

    /**
     * @brief Refreshes the Chart View object
     */
    void refreshChartView();

    /**
     * @brief Refreshes the GUI
     */
    void refreshGui();

    /**
     * @brief Refreshes the table after a data change of the table
     */
    void tableChanged();

    /* ----get tableview selected cells---- */

    /**
     * @brief Returns the selected row
     * @return data values for the selected row
     */
    u_int getSelectedRow() const;

    /**
     * @brief Returns the selected column
     * @return data values for the selected column
     */
    u_int getSelectedColumn() const;

private slots:
    //set a chart tipe

    /**
      * @brief Generates an image of the graph in .PNG format
      */
     void getGraphImage();

     /**
      * @brief showColors
      */
     void showColors();

     /**
      * @brief Hides/shows the table
      */
     void manageTableView();

     /**
      * @brief Hides/shows the chart
      */
     void manageChartView();

     /**
      * @brief Generates a Pie Chart with the data provided by the user
      */
     void setPieChart();

     /**
      * @brief Generates a Donut Chart with the data provided by the user
      */
     void setDonutChart();

     /**
      * @brief Generates a Bar Chart with the data provided by the user
      */
     void setBarChart();

     /**
      * @brief  Generates an Horizontal Bar Chart with the data provided by the user
      */
     void setHorizontalBarChart();

     /**
      * @brief  Generates a Stacked Bar Chart with the data provided by the user
      */
     void setStackedBarChart();

     /**
      * @brief  Generates an Horizontal Stacked Bar Chart with the data provided by the user
      */
     void setHorizontalStackedBarChart();

     /**
      * @brief  Generates a Spline Chart with the data provided by the user
      */
     void setSplineChart();

     /**
      * @brief  Generates a Line Chart with the data provided by the user
      */
     void setLineChart();

     /**
      * @brief  Generates a Scatter Chart with the data provided by the user
      */
     void setScatterChart();

     /**
      * @brief Sets the style for the buttons
      * @param 'color' buttons color
      */
     void styleButton(const QString& color);

     /**
      * @brief Sets the theme selected by the user
      * @param 'window' color
      * @param 'text' color
      * @param 'theme' Qt theme
      * @param 'butColor' color
      * @param 'tabStyle' stylesheet for the table
      * @param 'menuStyle' stylesheet for the table
      * @param 'b' used to check if it's called while refreshing the chart view
      */
     void setTheme(QRgb window, QRgb text, QChart::ChartTheme theme, const QString& butColor, const QString& tabStyle, const QString& menuStyle, bool b);

     /**
      * @brief Sets the Light Theme
      */
     void setLight(bool = false);

     /**
      * @brief Sets the Blue Cerulean Theme
      */
     void setBlueCerulean(bool = false);

     /**
      * @brief Sets the Dark Theme
      */
     void setDark(bool = false);

     /**
      * @brief Sets the Brown Sand Theme
      */
     void setBrownSand(bool = false);

     /**
      * @brief Sets the Blue NCS Theme
      */
     void setBlueNCS(bool = false);

     /**
      * @brief Sets the High Contrast Theme
      */
     void setHighContrast(bool = false);

     /**
      * @brief Sets the Blue Icy Theme
      */
     void setBlueIcy(bool = false);

     /**
      * @brief Sets the Qt Default Theme
      */
     void setQt(bool = false);

};

#endif // MAINWINDOW_H
