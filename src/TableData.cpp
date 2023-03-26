#include "TableData.h"

TableData::TableData() : table(vector<vector<double>>()), rowsNames(vector<string>()), columnsNames( vector<string>()), rowsCount(0), columnsCount(0) {}

TableData::TableData(const vector<vector<double>>& tab, const vector<string>& rowsHeader, const vector<string>& columnsHeader)
                        : table(tab), rowsNames(rowsHeader), columnsNames(columnsHeader), rowsCount(rowsNames.size()), columnsCount(columnsNames.size()) {}

u_int TableData::getRowCount() const {return rowsCount;}

u_int TableData::getColumnCount() const {return columnsCount;}

vector<string> TableData::getRowsNames() const {return rowsNames;}

vector<string> TableData::getColumnsNames() const {return columnsNames;}

vector<vector<double>> TableData::getTable() const {return table;}

double TableData::getMinValue() const {
    double min = 0;
    for(unsigned long i = 0; i < table.size(); i++){
        for(unsigned long j = 0; j < table[i].size(); j++){
            if (table[i][j] < min)
                min = table[i][j];
        }
    }
    return min;
}

double TableData::getMaxValue() const {
    double max = 0;
    for(unsigned long i = 0; i < table.size(); i++){
        for(unsigned long j = 0; j < table[i].size(); j++){
            if (table[i][j] > max)
                max = table[i][j];
        }
    }
    return max;
}

vector<double> TableData::getSumRows() const {
    vector<double> vec;
    for(u_int i = 0; i < getRowCount(); ++i){
        double sum = 0.0;
        for(u_int j = 0; j < getColumnCount(); ++j)
            sum += table[i][j];
        vec.push_back(sum);
    }
    return vec;
}

vector<double> TableData::getSumCols() const {
    vector<double> vec;
    for(u_int i = 0; i < getColumnCount(); ++i){
        double sum = 0.0;
        for(u_int j = 0; j < getRowCount(); ++j)
            sum += table[j][i];
        vec.push_back(sum);
    }
    return vec;
}

double TableData::maxCol() const {
    vector<double> vec = getSumCols();
    double max = __DBL_MIN__;
    for(u_int i = 0; i < vec.size(); ++i){
        if(vec[i] > max)
            max = vec[i];
    }
    return max;
}

void TableData::changeValue(const u_int row, const u_int col, double val) {table[row][col] = val;}

void TableData::changeCL(const u_int index,  string newLabel){columnsNames.at(index) = newLabel;}

void TableData::changeRL(const u_int index,  string newLabel){rowsNames.at(index) = newLabel;}

void TableData::addRow(vector<double>& row, u_int pos, const string& rowName) {
    if (row.size() == columnsCount){
        if (rowsCount > pos){
            rowsNames.insert(rowsNames.begin() + pos, rowName);
            table.insert(table.begin() + pos, row);
        }
        else {
            rowsNames.push_back(rowName);
            table.push_back(row);
        }
        ++rowsCount;
    }
}

void TableData::addColumn(vector<double>& col, u_int pos, const string& columnName) {
    if (col.size() == rowsCount){
        if (columnsCount > pos){
            for (u_int i = 0; rowsCount > i; ++i)
                (table)[i].insert((table)[i].begin() + pos, col[i]);
            columnsNames.insert(columnsNames.begin() + pos, columnName);
        }
        else {
            for (u_int i = 0; rowsCount > i; ++i)
                table[i].push_back(col[i]);
            columnsNames.push_back(columnName);
        }
        ++columnsCount;
    }
}

void TableData::deleteRow(const u_int pos) {
    if (rowsCount > pos){
        if(rowsCount == 1)
            clearTable();

        else {
            rowsNames.erase(rowsNames.begin() + pos);
            table.erase(table.begin() + pos);
            --rowsCount;
        }
    }
}

void TableData::deleteColumn(const u_int pos) {
    if (columnsCount > pos){
        if(columnsCount == 1)
            clearTable();

        else {
            columnsNames.erase(columnsNames.begin() + pos);
            for (u_int i = 0; rowsCount > i; ++i)
                table[i].erase(table[i].begin() + pos);
            --columnsCount;
        }
    }
}

void TableData::clearTable() {
    rowsCount = 0;
    columnsCount = 0;

    table.clear();
    rowsNames.clear();
    columnsNames.clear();
}
