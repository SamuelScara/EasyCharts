#include "Controller.h"

Controller::Controller(QObject* parent): QObject(parent) {}

void Controller::setModel(Model* m) {model = m;}

void Controller::setView(MainWindow* v) {view = v;}

Model* Controller::getModel() const {return model;}

void Controller::insert_Row(u_int index){
    if(view != nullptr && model != nullptr ){
        bool ok;
        QString text = QInputDialog::getText(view, tr("Enter Row Name"),
                                             tr("Label:"), QLineEdit::Normal,
                                             "Default", &ok);
        if (ok && !text.isEmpty()){
            model->addRow(index, text.toStdString());
            view->tableChanged();
        }
    }
}

void Controller::insert_Column(u_int index){
    if(view != nullptr && model != nullptr){
        bool ok;
        QString text = QInputDialog::getText(view, tr("Enter Column Name"),
                                             tr("Label:"), QLineEdit::Normal,
                                             "Default", &ok);
        if (ok && !text.isEmpty()){
            model->addColumn(index, text.toStdString());
            view->tableChanged();
        }
    }
}

void Controller::change_C_Label(u_int index){
    if(view != nullptr && model != nullptr){
        if(model->columnCount() == 0){
            QMessageBox msg;
            msg.setText("There is no coloumn to rename");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
        else{
            if(model->rowCount() == 0){
                QMessageBox msg;
                msg.setText("Create at least a row first");
                msg.exec();
                insert_Row(view->getSelectedRow());
            }
            else{
                bool ok;
                QString currentLabel = QString::fromStdString(model->getTable()->getColumnsNames()[index]);
                QString newLabel = QInputDialog::getText(view, tr("Enter New Col Name"),
                                                     tr("Label:"), QLineEdit::Normal,
                                                     currentLabel, &ok);
                if(ok && !newLabel.isEmpty()){
                    model->changeCol(index, newLabel.toStdString());
                    view->tableChanged();
                }
                else{
                    QMessageBox msg;
                    msg.setText("No changes have been applied");
                    msg.exec();
                }
            }
        }
    }
}

void Controller::change_R_Label(u_int index){
    if(view != nullptr && model != nullptr){
        if(model->rowCount() == 0){
            QMessageBox msg;
            msg.setText("There is no row to rename");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
        else{
            if(model->columnCount() == 0){
                QMessageBox msg;
                msg.setText("Create at least a column first");
                msg.exec();
                insert_Column(view->getSelectedColumn());
            }
            else{
                bool ok;
                QString currentLabel = QString::fromStdString(model->getTable()->getRowsNames()[index]);
                QString newLabel = QInputDialog::getText(view, tr("Enter New Row Name"),
                                                     tr("Label:"), QLineEdit::Normal,
                                                     currentLabel, &ok);
                if(ok && !newLabel.isEmpty()){
                    model->changeRow(index, newLabel.toStdString());
                    view->tableChanged();
                }
                else{
                    QMessageBox msg;
                    msg.setText("No changes have been applied");
                    msg.exec();
                }
            }
        }
    }  
}

void Controller::change_Selected_Row_Label(){change_R_Label(view->getSelectedRow());}

void Controller::insert_Row_Before_Selected() {insert_Row(view->getSelectedRow());}

void Controller::insert_Row_After_Selected() {insert_Row(view->getSelectedRow()+1);}

void Controller::change_Selected_Col_Label(){change_C_Label(view->getSelectedColumn());}

void Controller::insert_Column_Before_Selected() {insert_Column(view->getSelectedColumn());}

void Controller::insert_Column_After_Selected() {insert_Column(view->getSelectedColumn()+1);}

void Controller::remove_Selected_Row(){
    if(view != nullptr && model != nullptr){
        if(model->rowCount() == 0){
            QMessageBox msg;
            msg.setText("There is no row to delete");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
        else if(model->columnCount() == 0){
            model->removeRow(model->rowCount()-1);
            view->tableChanged();
        }
        else{
            u_int i = view->getSelectedRow();
            model->removeRow(i);
            view->tableChanged();
        }
    }
}

void Controller::remove_Selected_Column(){
    if(view != nullptr && model != nullptr){
        if(model->columnCount() == 0){
            QMessageBox msg;
            msg.setText("There is no column to delete");
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
        else if(model->rowCount() == 0){
            model->removeColumn(model->columnCount()-1);
            view->tableChanged();
        }
        else{
            u_int i = view->getSelectedColumn();
            model->removeColumn(i);
            view->tableChanged();
        }
    }
}

void Controller::saveXML(){
    if(view != nullptr && model != nullptr)
        model->SaveXML(QFileDialog::getSaveFileName(view, "Save File","../EasyCharts/Saved Files", "XML (*.xml)"));
}

void Controller::saveCSV(){
    if(view != nullptr && model != nullptr)
        model->SaveCSV(QFileDialog::getSaveFileName(view, "Save File","../EasyCharts/Saved Files", "CSV (*.csv)"));
}

void Controller::saveJSON(){
    if(view != nullptr && model != nullptr)
        model->saveJSON(QFileDialog::getSaveFileName(view, "Save File", "../EasyCharts/Saved Files", "JSON (*.json)"));
}

void Controller::loadFile(){
    if(view!=nullptr && model!=nullptr){
        QString path = QFileDialog::getOpenFileName(view, "Load File","../EasyCharts/Saved Files", "JSON, XML, CSV (*.json *.xml *.csv)");
        if(path.contains(".json")){
            model->LoadJSON(path);
            view->refreshGui();
        }
        else if(path.contains(".xml")){
            model->LoadXML(path);
            view->refreshGui();
        }
        else if (path.contains(".csv")){
            model->LoadCSV(path);
            view->refreshGui();
        }
    }
}

void Controller::newTable(){
    int rowN = QInputDialog::getInt(view, "Rows number", "Rows:", QLineEdit::Normal);
    int colN = QInputDialog::getInt(view, "Columns number", "Columns:", QLineEdit::Normal);
    model->createNewTable(rowN, colN);
    view->refreshGui();
}

void Controller::reset(){
    if(view && model){
        QMessageBox msg;
        msg.setText("Current data has been resetted");
        msg.exec();
        model->createNewTable();
        view->refreshGui();
    }
}
