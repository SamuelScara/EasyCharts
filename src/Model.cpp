#include "Model.h"

Model::Model(QObject *parent) : QAbstractTableModel(parent){
    createNewTable();
}

Model::~Model(){
    delete table;
}

TableData* Model::getTable() {
    return table;
}

int Model::rowCount(const QModelIndex & /*parent*/) const{
    return table->getRowCount();
}
int Model::columnCount(const QModelIndex & /*parent*/) const{
    return table->getColumnCount();
}
QVariant Model::data(const QModelIndex &index, int role) const{
    if (role == Qt::DisplayRole){
        qreal temp = table->getTable().at(index.row()).at(index.column());
        return temp;
    }else if (role == Qt::BackgroundRole) {
        for (const QRect &rect : m_mapping) {
            if (rect.contains(index.column(), index.row()))
                return QColor(m_mapping.key(rect));
        }

        return QColor(Qt::white);
    }
    return QVariant();
}
bool Model::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role == Qt::EditRole){
        table->changeValue(index.row(),index.column(),value.toDouble());
        emit dataChanged(index, index);
    }
    return true;
}
Qt::ItemFlags Model::flags(const QModelIndex &index) const{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (Qt::Orientation::Vertical == orientation){
        if(((int)table->getRowCount()) > section)
            return QString::fromStdString(table->getRowsNames().at(section));
    } else{
        if(((int)table->getColumnCount()) > section)
            return QString::fromStdString(table->getColumnsNames().at(section));
    }
    return QString();
}
void Model::addMapping(QString color, QRect area){
    m_mapping.insertMulti(color, area);
}

void Model::clearMapping(){
    m_mapping.clear();
}

void Model::addRow(u_int i, std::string label){
    vector<double> v(table->getColumnCount(),0);
    table->addRow(v,i,label);
}
void Model::addColumn(u_int i, std::string label){
    vector<double> v(table->getRowCount(),0);
    table->addColumn(v,i,label);
}

void Model::changeCol(u_int index, string newLabel){table->changeCL(index,newLabel);}

void Model::removeColumn(u_int i){table->deleteColumn(i);}

void Model::removeRow(u_int i){table->deleteRow(i);}

void Model::createNewTable(u_int rowN, u_int colN){
    vector<vector<double>> tab(rowN, vector<double>(colN,1));
    vector<string> rowHeaders;
    vector<string> colHeaders;

    for(u_int i = 0; i < rowN; ++i)
        rowHeaders.push_back("Row " + std::to_string(i+1));

    for(u_int i = 0; i < colN; ++i)
        colHeaders.push_back("Col " + std::to_string(i+1));

    table = new TableData(tab,rowHeaders,colHeaders);
}

void Model::changeRow(u_int index, string newLabel){table->changeRL(index,newLabel);}

void Model::SaveCSV(QString path) const{
    if(!(path.contains(".csv")))
        path += ".csv";

    QFile file(path);

    if(file.open(QFile::WriteOnly | QFile::Truncate)){
        QTextStream output(&file);
        output << ";";

        for(u_int j = 0; j < table->getColumnCount(); ++j)
                output << QString::fromStdString(table->getColumnsNames()[j]) << ";";

        output << '\n';

        for(u_int i = 0; i < table->getRowCount(); ++i){
            output << QString::fromStdString(table->getRowsNames()[i]) << ";";
            for(u_int j = 0; j < table->getColumnCount(); ++j)
                    output << table->getTable()[i][j] << ";";

            output << '\n';
        }
    }
    file.close();
}

void Model::LoadCSV(const QString& path) {
    QFile file(path);
    vector<vector<double>> tab;
    vector<string> rowsNames;
    vector<string> columnsNames;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QByteArray line = file.readLine();
    bool first = true;
    for (auto &c : line.split(';')){
        if(!first)
            columnsNames.push_back(c.toStdString());
        else
            first = false;
    }
    columnsNames.pop_back();

    QList<QByteArray> splitted;
    while (!file.atEnd()){
        line = file.readLine();
        splitted = line.split(';');

        if (splitted.count() > 1){
            rowsNames.push_back(splitted[0].toStdString());

            vector<double> row;
            for(int i = 1; i < splitted.count(); i++)
                row.push_back(splitted[i].toDouble());

            tab.push_back(row);
        }
    }
    delete table;
    table = new TableData(tab,rowsNames,columnsNames);
}

void Model::SaveXML(QString path) const{
    if(!(path.contains(".xml")))
        path += ".xml";

    QDomDocument doc;
    QDomElement root = doc.createElement("Graph");
    doc.appendChild(root);

    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Text )){
        qDebug() << "Already opened or there is another issue";
        file.close();
    }

    QTextStream text(&file);

    QDomElement Cols = doc.createElement("Columns");
    Cols.setAttribute("number", QString::number(table->getColumnCount()));
    for(const auto& s : table->getColumnsNames()) {
        QDomElement child = doc.createElement("Col");
        child.setAttribute("value", QString::fromStdString(s));
        Cols.appendChild(child);
    }
    root.appendChild(Cols);


    QDomElement Rows = doc.createElement("Rows");
    Rows.setAttribute("number",QString::number(table->getRowCount()));
    for(const auto& s : table->getRowsNames()) {
        QDomElement child = doc.createElement("Row");
        child.setAttribute("value", QString::fromStdString(s));
        Rows.appendChild(child);
    }
    root.appendChild(Rows);


    QDomElement Data = doc.createElement("Data");
    for(const auto &data : table->getTable()){
        QDomElement values = doc.createElement("Row");
        for (auto d : data){
            QDomElement child = doc.createElement("Num");
            child.setAttribute("value", QString::number(d));
            values.appendChild(child);
        }
        Data.appendChild(values);
    }
    root.appendChild(Data);
    text << doc.toString();
}

void Model::LoadXML(const QString& path) {
    vector<vector<double>> tab;
    vector<string> rowsNames;
    vector<string> columnsNames;

    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly ))
       qDebug() << "The selected file is 'read only'";

    doc.setContent(&file);
    file.close();

    QDomElement root = doc.documentElement();
    QDomElement Cols = root.firstChildElement();
    QDomElement Row = Cols.nextSiblingElement();
    QDomElement Table = Row.nextSiblingElement();

    if(!Cols.isNull()){
        QDomElement ColsChild = Cols.firstChildElement();
        while(ColsChild.isNull() == false){
            columnsNames.push_back(ColsChild.attribute("value","x").toStdString());
            ColsChild = ColsChild.nextSiblingElement();
        }
    }

    if (!Row.isNull()){
        QDomElement RowChild = Row.firstChildElement();
        while(!RowChild.isNull()){
            rowsNames.push_back(RowChild.attribute("value","x").toStdString());
            RowChild = RowChild.nextSiblingElement();
        }
    }

    if (!Table.isNull()){
        QDomElement Row = Table.firstChildElement();
        while(!Row.isNull()){
            vector<double> rowVals;
            QDomElement RowElement = Row.firstChildElement();
            while (!RowElement.isNull()){
                rowVals.push_back(RowElement.attribute("value","0").toDouble());
                RowElement = RowElement.nextSiblingElement();
            }
            tab.push_back(rowVals);
            Row = Row.nextSiblingElement();
        }
    }
    delete table;
    table = new TableData(tab,rowsNames,columnsNames);
}

void Model::saveJSON(QString path) const{
    if(!(path.contains(".json")))
           path += ".json";

       QFile file(path);
       file.open(QFile::WriteOnly);
       QJsonObject json;
       QJsonArray columns;


       for(const auto& s : table->getColumnsNames())
           columns.push_back(QString::fromStdString(s));
       json.insert("Columns", columns);

       QJsonObject rows;
       auto val = table->getTable();
       auto rowNames = table->getRowsNames();
       for(u_int i = 0; i < table->getRowCount() ; ++i){
           QJsonArray rowVal;
           for(u_int j = 0; j < table->getColumnCount() ; ++j)
               rowVal.push_back(val[i][j]);
           rows.insert(QString::fromStdString(rowNames[i]), rowVal);
       }
       json.insert("Rows", rows);
       QJsonDocument doc(json);
       file.write(doc.toJson());
       file.close();
}

void Model::LoadJSON(const QString& path){
    QFile file(path);
    vector<vector<double>> data;
    vector<string> rowsNames;
    vector<string> columnsNames;

    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "The selected file is 'read only'";

    QByteArray content = file.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(content);
    QJsonObject jsonObj = jsonDoc.object();

    QJsonValue columns =  jsonObj["Columns"];
    QJsonArray colsArray = columns.toArray();
    int colCounter = 0;
    for(auto it = colsArray.begin(); it != colsArray.end(); ++it){
        ++colCounter;
        columnsNames.push_back(it->toString().toStdString());
    }

    QJsonValue rows = jsonObj["Rows"];
    QJsonObject rowsObj = rows.toObject();
    QMap<QString,QVariant> rows_map = rowsObj.toVariantMap();

    int rowCounter = 0;
    for(auto it = rows_map.begin(); it != rows_map.end(); ++it){
        rowsNames.push_back(it.key().toStdString());
        QList<QVariant> row_Array = (it.value()).toList();
        data.push_back(*(new vector<double>));

        for(auto s_it = row_Array.begin(); s_it!= row_Array.end(); ++s_it){
            QString numCheck = s_it->toString();
            numCheck.replace(" ","");
            data[rowCounter].push_back(s_it->toDouble());
        }
        ++rowCounter;
    }

    if(rowCounter < 1 || colCounter < 1)
        throw true;

    delete Model::table;
    Model::table = new TableData(data,rowsNames,columnsNames);
    file.close();
}
