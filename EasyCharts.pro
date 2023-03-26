QT += core gui widgets charts
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    src/BarAbs.cpp \
    src/BarChart.cpp \
    src/BarStackedChart.cpp \
    src/ChartView.cpp \
    src/Controller.cpp \
    src/HorizontalBarChart.cpp \
    src/HorizontalBarStackedChart.cpp \
    src/LineAbs.cpp \
    src/LineChart.cpp \
    src/MainWindow.cpp \
    src/Model.cpp \
    src/PieChart.cpp \
    src/ScatterChart.cpp \
    src/SplineChart.cpp \
    src/TableData.cpp \
    src/main.cpp \

HEADERS += \
    src/BarAbs.h \
    src/BarChart.h \
    src/BarStackedChart.h \
    src/Chart.h \
    src/ChartView.h \
    src/Controller.h \
    src/HorizontalBarChart.h \
    src/HorizontalBarStackedChart.h \
    src/LineAbs.h \
    src/LineChart.h \
    src/MainWindow.h \
    src/Model.h \
    src/PieChart.h \
    src/ScatterChart.h \
    src/SplineChart.h \
    src/TableData.h \

RESOURCES += \
    images.qrc \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
