#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QTextStream>
#include <QtXml>
#include <iostream>
#include <fstream>
#include <QColor>

#include "TableData.h"

typedef unsigned int u_int;
using std::vector;
using std::string;


class Model : public QAbstractTableModel
{
    Q_OBJECT
private:
    TableData* table;
    QHash<QString, QRect> m_mapping;
public:
    Model(QObject *parent = nullptr);
    ~Model();

    /**
     * @brief Returns the Table with all the datas
     * @return TableData pointer
     */
    TableData* getTable();

    /**
     * @brief Gets the number of rows
     * @param 'parent'
     * @return number of rows
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief Gets the number of columns
     * @param 'parent'
     * @return number of columns
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief Gets the selected data
     * @param 'index' index of the model
     * @param 'role' indicates the role
     * @return value of the data
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /**
     * @brief Sets the data of the selected cell
     * @param 'index' index of the model
     * @param 'value' value of the data
     * @param 'role' indicates the role
     * @return true if the data has been setted
     */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    /**
     * @brief flags
     * @param 'index' index of the model
     * @return flag if data is editable
     */
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @brief Gives the header of column and row of the selected data
     * @param 'section' indicates the section
     * @param 'orientation' indicates the orientation for the header
     * @param 'role' indicates the role
     * @return 'QVariant' containing the header data based on orientation
     */
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    /**
     * @brief Sets the mapping for the selected data cell
     * @param 'color' indicates the color for the mapping
     * @param 'area' indiates the area where the mapping will be applied
     */
    void addMapping(QString color, QRect area);

    /**
     * @brief Clears the mapping for the selected cell
     */
    void clearMapping();

    /**
     * @brief Adds a row in the table
     * @param 'index' indicates the index of the row
     * @param 'label' indicates the label of the row
     */
    void addRow(u_int index, string label);

    /**
     * @brief Adds a column in the table
     * @param 'index' indicates the index of the column
     * @param 'label' indicates the label of the column
     */
    void addColumn(u_int index, string label);

    /**
     * @brief Changes the selected Column lable
     * @param 'index' indicates the index of the column that we want to change its label
     * @param 'newLabel' sets the new label for the column
     */
    void changeCol(u_int index, string newLabel);

    /**
     * @brief Changes the selected Row label
     * @param 'index' indicates the index of the column we want to change its label
     * @param 'newLabel' sets the new label for the row
     */
    void changeRow(u_int index, string newLabel);

    /**
     * @brief Removes the selected Row
     * @param 'index' indicates the index of the row we want to remove
     */
    void removeRow(u_int index);

    /**
     * @brief Removes the selected Column
     * @param 'index' indicate the index of the column we want to remove
     */
    void removeColumn(u_int index);

    /**
     * @brief Creates a new Table model
     * @param 'rowN' number of rows we want to create for the new table
     * @param 'colN' number of columns we want to create for the new table
     */
    void createNewTable(u_int rowN = 0, u_int colN = 0);

    /**
     * @brief Saves the model into a .CSV file
     * @param 'path' where the CSV file will be saved
     */
    void SaveCSV(QString path) const;

    /**
     * @brief Loads a .CSV model
     * @param 'path' from where the CSV file will be loaded
     */
    void LoadCSV(const QString& path);

    /**
     * @brief Saves the model into a .XML file
     * @param 'path' where the XML file will be saved
     */
    void SaveXML(QString path) const;

    /**
     * @brief Loads a .XML model
     * @param 'path' from where the XML file will be loaded
     */
    void LoadXML(const QString& path);

    /**
     * @brief Saves the model into a .JSON file
     * @param 'path' where the JSON file will be saved
     */
    void saveJSON(QString path) const;

    /**
     * @brief Loads a .JSON model
     * @param 'path' from where the JSON file will be loaded
     */
    void LoadJSON(const QString& path);

};

#endif // MODEL_H
