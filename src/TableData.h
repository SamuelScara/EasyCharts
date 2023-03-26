#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <vector>
#include <string>
#include <algorithm>

typedef unsigned int u_int;
using std::vector;
using std::string;

class TableData {
private:
    vector<vector<double>> table;
    vector<string> rowsNames;
    vector<string> columnsNames;
    u_int rowsCount;
    u_int columnsCount;
    void clearTable();

public:
    TableData();
    TableData(const vector<vector<double>>&, const vector<string>&, const vector<string>&);

    /**
     * @brief Gets the number of rows
     * @return number of rows of the Table Data
     */
    u_int getRowCount() const;

    /**
     * @brief Gets the number of columns
     * @return number of columns of the Table Data
     */
    u_int getColumnCount() const;

    /**
     * @brief Gets all the Rows labels
     * @return vector with all the rows labels
     */
    vector<string> getRowsNames() const;

    /**
     * @brief Gets all the Columns labels
     * @return vector with all the columns labels
     */
    vector<string> getColumnsNames() const;

    /**
     * @brief Gets the table model
     * @return vector with all the datas of the Table Data
     */
    vector<vector<double>> getTable() const;

    /**
     * @brief Gets the minimum value
     * @return value of the minimum data
     */
    double getMinValue() const;

    /**
     * @brief Gets the maximum value
     * @return value of the maximum value
     */
    double getMaxValue() const;

    /**
     * @brief Gets the sum of all the rows' datas
     * @return vector with the sum for all the rows
     */
    vector<double> getSumRows() const;

    /**
     * @brief Gets the sum of all the columns' datas
     * @return vector with the sum for all the columns
     */
    vector<double> getSumCols() const;

    /**
     * @brief Gets the max value for the columns
     * @return value of the maximum column
     */
    double maxCol() const;

    /**
     * @brief Changes the data value of the cell
     * @param 'row' position of the cell
     * @param 'column' position of the cell
     * @param 'value' double type to insert in the cell
     */
    void changeValue(const u_int row, const u_int column, double value);

    /**
     * @brief Changes the Column's label
     * @param 'column' position in the table
     * @param 'label' new label to insert in the columns header
     */
    void changeCL(const u_int column, string label);

    /**
     * @brief Changes the Row's label
     * @param 'row' position in the table
     * @param 'label' new label to insert in the rows header
     */
    void changeRL(const u_int row, string label);

    /**
     * @brief Adds a row in the table
     * @param 'rowData' vector containing the double type numbers for the new row
     * @param 'pos' row position in the table
     * @param 'label' row header for the new row
     */
    void addRow(vector<double>& rowData, const u_int pos = 0, const string& label = "");

    /**
     * @brief Adds a column in the table
     * @param 'colData' vector containing the double type numbers for the new column
     * @param 'pos' column position in the table
     * @param 'label' column header for the new column
     */
    void addColumn(vector<double>& colData, const u_int pos = 0, const string& label = "");

    /**
     * @brief Deletes a row in the selected position
     * @param 'pos' row position in the table
     */
    void deleteRow(const u_int pos);

    /**
     * @brief Deletes a column in the selected position
     * @param 'pos' column position in the table
     */
    void deleteColumn(const u_int pos);
};

#endif // TABLEDATA_H
