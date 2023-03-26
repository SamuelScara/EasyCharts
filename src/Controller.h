#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QInputDialog>
#include <QFileDialog>
#include <QInputDialog>


#include "MainWindow.h"
#include "Model.h"

typedef unsigned int u_int;
using std::string;

class Controller : public QObject
{
    Q_OBJECT
private:
    MainWindow* view;
    Model* model;

    /**
     * @brief Inserts a row into the table
     * @param 'index' index of the row
     */
    void insert_Row(u_int index);

    /**
     * @brief Inserts a column into the table
     * @param 'index' index of the column
     */
    void insert_Column(u_int index);

    /**
     * @brief Changes the column lable
     * @param 'index' index of the column
     */
    void change_C_Label(u_int index);

    /**
     * @brief Changes the row lable
     * @param 'index' index of the row
     */
    void change_R_Label(u_int index);

public:
    explicit Controller(QObject *parent = nullptr);

    /**
     * @brief Sets the model object
     * @param 'm' is the model to be applied
     */
    void setModel(Model* m);

    /**
     * @brief Sets the view object
     * @param 'v' is the view to manipulate
     */
    void setView(MainWindow* v);

    /**
     * @brief Opens a JSON/CSV/XML file
     * @return the 'model' contained by the class
     */
    Model* getModel() const;

public slots:

    /**
     * @brief Inserts a row before the selected one
     */
    void insert_Row_Before_Selected();

    /**
     * @brief Inserts a row after the selected one
     */
    void insert_Row_After_Selected();

    /**
     * @brief Inserts a column before the selected one
     */
    void insert_Column_Before_Selected();

    /**
     * @brief Inserts a column after the selected one
     */
    void insert_Column_After_Selected();

    /**
     * @brief Removes the selected row
     */
    void remove_Selected_Row();

    /**
     * @brief Removes the selected column
     */
    void remove_Selected_Column();

    /**
     * @brief Changes the selected column label
     */
    void change_Selected_Col_Label();

    /**
     * @brief Changes the selected row label
     */
    void change_Selected_Row_Label();

    /**
     * @brief Creates new table
     */
    void newTable();

    /**
     * @brief Empties the whole program
     */
    void reset();

    /**
     * @brief Saves the current model in .XML file
     */
    void saveXML();

    /**
     * @brief Saves the current model in .JSON file
     */
    void saveJSON();

    /**
     * @brief Saves the current model in .CSV file
     */
    void saveCSV();

    /**
     * @brief Loads a JSON/CSV/XML file
     */
    void loadFile();
};

#endif // CONTROLLER_H
