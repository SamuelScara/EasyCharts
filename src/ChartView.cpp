#include "ChartView.h"

void ChartView::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Plus:
            chart()->zoomIn();
            break;
        case Qt::Key_Minus:
            chart()->zoomOut();
            break;
        case Qt::Key_Left:
            chart()->scroll(-10, 0);
            break;
        case Qt::Key_Right:
            chart()->scroll(10, 0);
            break;
        case Qt::Key_Up:
            chart()->scroll(0, 10);
            break;
        case Qt::Key_Down:
            chart()->scroll(0, -10);
            break;

        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}

QChart::ChartTheme ChartView::getNameTheme() const {return nameTheme;}

void ChartView::setNameTheme(QChart::ChartTheme theme) {nameTheme = theme;}
