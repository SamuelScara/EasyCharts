#include "MainWindow.h"
#include "Controller.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
    mainLayout= new QVBoxLayout;
    chartsLayout= new QHBoxLayout();

    chart = new SplineChart();

    chartsLayout->setSpacing(0);
    chartsLayout->setAlignment(Qt::AlignCenter);
    chartsLayout->setContentsMargins(0,0,0,0);

    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(0,0,0,0);

    setLayout(mainLayout);
    resize(QSize(1024, 720));

    QRect screenSize= QGuiApplication::screens().first()->geometry();
    const QRect wr{{},frameSize().boundedTo(screenSize.size())};
    move(screenSize.center()-wr.center());

    addMenuBar();
    QHBoxLayout* toolBarLayout = new QHBoxLayout;
    setToolBar(toolBarLayout);
    QHBoxLayout* containerLayout=new QHBoxLayout;
    containerLayout->addLayout(toolBarLayout);
    mainLayout->addLayout(containerLayout);
    mainLayout->addLayout(chartsLayout);
}

void MainWindow::refreshTableView(){
    if(tableView==nullptr){
        tableView = new QTableView(this);
        chartsLayout->addWidget(tableView);
    }

    tableView->setModel(controller->getModel());

    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();
    tableView->setGeometry(0,30,300,300);
    tableView->setMinimumSize(640,480);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
}

void MainWindow::refreshChartView(){
    if(chartView == nullptr){
        chartView = new ChartView();
        chartsLayout->addWidget(chartView);
    }

    chart->setModel(controller->getModel());
    if(auto c = chart->generateChart())
        chartView->setChart(c);

    switch (chartView->getNameTheme()) {
        case QChart::ChartThemeLight:
            setLight(1);
            break;
        case QChart::ChartThemeBlueCerulean:
            setBlueCerulean(1);
            break;
        case QChart::ChartThemeDark :
            setDark(1);
            break;
        case QChart::ChartThemeBrownSand:
            setBrownSand(1);
            break;
        case QChart::ChartThemeBlueNcs:
            setBlueNCS(1);
            break;
        case QChart::ChartThemeHighContrast:
            setHighContrast(1);
            break;
        case QChart::ChartThemeBlueIcy:
            setBlueIcy(1);
            break;
        case QChart::ChartThemeQt:
            setQt(1);
            break;
    }

    if(colorsItem != nullptr && colorsItem->isChecked())
        chart->addColorMapping();
    else
        chart->removeColorMapping();

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640,480);
    chartView->hide();
}

void MainWindow::refreshGui(){
    refreshTableView();
    refreshChartView();
}

void MainWindow::tableChanged(){
    if(chartView->isVisible()){
        refreshGui();
        chartView->show();
    }
    else
        refreshGui();
}

u_int MainWindow::getSelectedColumn() const{
    return tableView->selectionModel()->currentIndex().column();
}

u_int MainWindow::getSelectedRow() const{
    return tableView->selectionModel()->currentIndex().row();
}

void MainWindow::setToolBar(QHBoxLayout* layout){
    insertColumnBeforeButton = new QPushButton(this);
    insertColumnAfterButton = new QPushButton(this);

    insertRowBeforeButton = new QPushButton(this);
    insertRowAfterButton = new QPushButton(this);

    deleteCurrentColumnButton = new QPushButton(this);
    deleteCurrentRowButton = new QPushButton(this);

    insertColumnAfterButton->setIcon(QIcon("://Icons/column_right.png"));
    insertColumnAfterButton->setToolTip("Insert Column After");

    insertColumnBeforeButton->setIcon(QIcon("://Icons/column_left.png"));
    insertColumnBeforeButton->setToolTip("Insert Column Before");

    insertRowAfterButton->setIcon(QIcon("://Icons/row_sotto.png"));
    insertRowAfterButton->setToolTip("Insert Row After");

    insertRowBeforeButton->setIcon(QIcon("://Icons/row_sopra.png"));
    insertRowBeforeButton->setToolTip("Insert Row Before");

    deleteCurrentColumnButton->setIcon(QIcon("://Icons/delete-column.png"));
    deleteCurrentColumnButton->setToolTip("Delete Current Column");

    deleteCurrentRowButton->setIcon(QIcon("://Icons/delete-row.png"));
    deleteCurrentRowButton->setToolTip("Delete Current Row");

    insertColumnAfterButton->setIconSize(QSize(36,36));
    insertColumnBeforeButton->setIconSize(QSize(36,36));
    insertRowAfterButton->setIconSize(QSize(36,36));
    insertRowBeforeButton->setIconSize(QSize(36,36));
    deleteCurrentColumnButton->setIconSize(QSize(36,36));
    deleteCurrentRowButton->setIconSize(QSize(36,36));

    layout->setSpacing(5);
    layout->addSpacing(50);

    layout->addWidget(insertColumnBeforeButton);
    layout->addWidget(insertColumnAfterButton);

    layout->addSpacing(50);

    layout->addWidget(insertRowBeforeButton);
    layout->addWidget(insertRowAfterButton);

    layout->addSpacing(50);

    layout->addWidget(deleteCurrentColumnButton);
    layout->addWidget(deleteCurrentRowButton);

    layout->addSpacing(50);
}

void MainWindow::addMenuBar(){
    menu=new QMenuBar();

    //Action+Shortcuts
    QAction* saveFile = new QAction(QIcon("://Icons/save.png"),"Save JSON",this);
    saveFile->setShortcut(QKeySequence::Save);
    QAction* newChart = new QAction(QIcon("://Icons/new.png"),"New",this);
    newChart->setShortcut(QKeySequence::New);
    QAction* openFile = new QAction(QIcon("://Icons/open.png"),"Open",this);
    openFile->setShortcut(QKeySequence::Open);
    QAction* exitProgram = new QAction(QIcon("://Icons/close.png"),"Exit",this);
    exitProgram->setShortcut(QKeySequence::Close);
    QAction* insertColumn = new QAction(QIcon("://Icons/column.png"),"Add column before",this);
    insertColumn->setShortcut(QKeySequence(tr("CTRL+K")));
    QAction* insertRow = new QAction(QIcon("://Icons/row.png"),"Add row before",this);
    insertRow->setShortcut(QKeySequence(tr("CTRL+R")));
    QAction* insertRowAfter = new QAction(QIcon("://Icons/row.png"),"Add row after",this);
    insertRowAfter->setShortcut(QKeySequence(tr("CTRL+Alt+R")));
    QAction* insertColumnAfter = new QAction(QIcon("://Icons/column.png"),"Add column after",this);
    insertColumnAfter->setShortcut(QKeySequence(tr("CTRL+Alt+K")));
    QAction* changeRow = new QAction(QIcon("://Icons/edit_row.png"),"Change selected row label", this);
    changeRow->setShortcut(QKeySequence(tr("CTRL+Shift+R")));
    QAction* changeCol = new QAction(QIcon("://Icons/edit_col.png"),"Change selected column label", this);
    changeCol->setShortcut(QKeySequence(tr("CTRL+Shift+K")));
    QAction* deleteColumn = new QAction(QIcon("://Icons/delete-column-wb.png"),"Delete selected column",this);
    deleteColumn->setShortcut(QKeySequence(tr("Alt+K")));
    QAction* deleteRow = new QAction(QIcon("://Icons/delete-row-wb.png"),"Delete selected row",this);
    deleteRow->setShortcut(QKeySequence(tr("Alt+R")));

    //File
    file=new QMenu("&File",menu);
    menu->addMenu(file);

    file->addAction(newChart);
    file->addAction(openFile);
    file->addSeparator();
    file->addAction(new QAction(QIcon("://Icons/save.png"),"Save XML",file));
    file->addAction(new QAction(QIcon("://Icons/save.png"),"Save CSV",file));
    file->addAction(saveFile);
    file->addAction(new QAction(QIcon("://Icons/image.png"),"Save Image",file));
    file->addSeparator();
    file->addAction(new QAction("Reset data", file));
    file->addAction(exitProgram);

    //Edit
    edit=new QMenu("&Edit",menu);
    menu->addMenu(edit);

    edit->addAction(insertRow);
    edit->addAction(insertRowAfter);
    edit->addSeparator();
    edit->addAction(insertColumn);
    edit->addAction(insertColumnAfter);
    edit->addSeparator();
    edit->addAction(deleteColumn);
    edit->addAction(deleteRow);
    edit->addSeparator();
    edit->addAction(changeCol);
    edit->addAction(changeRow);

    //Graphs
    graphs=new QMenu("&Graphs",menu);
    menu->addMenu(graphs);

    vector<QAction*>items=vector<QAction*>();

    QAction* item1=new QAction("Pie chart");
    item1->setIcon(QIcon("://Icons/pie.png"));
    items.push_back(item1);
    QAction* item2=new QAction("Donut chart");
    item2->setIcon(QIcon("://Icons/donut.png"));
    items.push_back(item2);

    QAction* item3=new QAction("Bar chart");
    item3->setIcon(QIcon("://Icons/bar.png"));
    items.push_back(item3);
    QAction* item4=new QAction("Horizontal Bar chart");
    item4->setIcon(QIcon("://Icons/h_bar.png"));
    items.push_back(item4);

    QAction* item5=new QAction("StackedBar chart");
    item5->setIcon(QIcon("://Icons/stkbar.png"));
    items.push_back(item5);
    QAction* item6=new QAction("Horizontal Stacked Bar chart");
    item6->setIcon(QIcon("://Icons/h_stkbar.png"));
    items.push_back(item6);

    QAction* item7=new QAction("Spline chart");
    item7->setIcon(QIcon("://Icons/spline.png"));
    items.push_back(item7);
    QAction* item8=new QAction("Line chart");
    item8->setIcon(QIcon("://Icons/line.png"));
    items.push_back(item8);

    QAction* item9=new QAction("Scatter chart");
    item9->setIcon(QIcon("://Icons/scatter.png"));
    items.push_back(item9);

    QActionGroup* viewGroup= new QActionGroup(this);
    viewGroup->setExclusive(true);

    for (auto &item : items){
        item->setCheckable(true);
        graphs->addAction(item);
        viewGroup->addAction(item);
    }

    //Themes
    theme = new QMenu("&Themes", menu);
    menu->addMenu(theme);

    QAction* light = new QAction("Light");
    light->setCheckable(true);
    light->setChecked(true);
    QAction* blueCerulean = new QAction("Blue Cerulean");
    blueCerulean->setCheckable(true);
    QAction* dark = new QAction("Dark");
    dark->setCheckable(true);
    QAction* brownSand = new QAction("Brown Sand");
    brownSand->setCheckable(true);
    QAction* blueNCS = new QAction("Blue NCS");
    blueNCS->setCheckable(true);
    QAction* highContrast = new QAction("High Contrast");
    highContrast->setCheckable(true);
    QAction* blueIcy = new QAction("Blue Icy");
    blueIcy->setCheckable(true);
    QAction* qtDef = new QAction("Qt Default");
    qtDef->setCheckable(true);

    QActionGroup* themesGroup = new QActionGroup(this);
    themesGroup->setExclusive(true);
    themesGroup->addAction(light);
    themesGroup->addAction(blueCerulean);
    themesGroup->addAction(dark);
    themesGroup->addAction(brownSand);
    themesGroup->addAction(blueNCS);
    themesGroup->addAction(highContrast);
    themesGroup->addAction(blueIcy);
    themesGroup->addAction(qtDef);

    theme->addAction(light);
    theme->addAction(blueCerulean);
    theme->addAction(dark);
    theme->addAction(brownSand);
    theme->addAction(blueNCS);
    theme->addAction(highContrast);
    theme->addAction(blueIcy);
    theme->addAction(qtDef);

    //settings
    settings = new QMenu("&Settings", menu);
    menu->addMenu(settings);

    colorsItem=new QAction("Show table colors");
    colorsItem->setCheckable(true);
    settings->addAction(colorsItem);
    colorsItem->setChecked(true);

    manageTable=new QAction("Hide table");
    manageTable->setCheckable(true);
    settings->addAction(manageTable);
    manageTable->setChecked(false);

    manageChart=new QAction("Hide chart");
    manageChart->setCheckable(true);
    settings->addAction(manageChart);
    manageChart->setChecked(false);

    //Others
    others=new QMenu("&Others",menu);
    others->addAction(new QAction("Credits",menu));
    others->addAction(new QAction("Help", menu));

    menu->addMenu(others);
    mainLayout->addWidget(menu);
}

void MainWindow::setTableView(){
    if(tableView!=nullptr)
        layout()->removeWidget(tableView);
    else
        tableView= new QTableView();
    tableView->setModel(controller->getModel());
    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();
    tableView->setGeometry(0,30,300,300);
    tableView->setStyleSheet("QHeaderView::section {background-color:lightblue}");
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout()->addWidget(tableView);
}

void MainWindow::setController(Controller* c){
    controller=c;

    refreshGui();

    //buttons
    connect(insertColumnBeforeButton, SIGNAL(clicked()), controller, SLOT(insert_Column_Before_Selected()));
    connect(insertColumnAfterButton,SIGNAL(clicked()),controller,SLOT(insert_Column_After_Selected()));

    connect(insertRowAfterButton,SIGNAL(clicked()),controller,SLOT(insert_Row_After_Selected()));
    connect(insertRowBeforeButton,SIGNAL(clicked()),controller,SLOT(insert_Row_Before_Selected()));

    connect(deleteCurrentColumnButton,SIGNAL(clicked()),controller,SLOT(remove_Selected_Column()));
    connect(deleteCurrentRowButton,SIGNAL(clicked()),controller,SLOT(remove_Selected_Row()));

    //file
    connect(file->actions().at(0),SIGNAL(triggered()),controller,SLOT(newTable()));
    connect(file->actions().at(1),SIGNAL(triggered()),controller,SLOT(loadFile()));

    connect(file->actions().at(3),SIGNAL(triggered()),controller,SLOT(saveXML()));
    connect(file->actions().at(4),SIGNAL(triggered()),controller,SLOT(saveCSV()));
    connect(file->actions().at(5),SIGNAL(triggered()),controller,SLOT(saveJSON()));
    connect(file->actions().at(6),SIGNAL(triggered()),this,SLOT(getGraphImage()));

    connect(file->actions().at(8),SIGNAL(triggered()),controller,SLOT(reset()));
    connect(file->actions().at(9),SIGNAL(triggered()),this,SLOT(close()));

    //edit
    connect(edit->actions().at(0),SIGNAL(triggered()),controller,SLOT(insert_Row_Before_Selected()));
    connect(edit->actions().at(1),SIGNAL(triggered()),controller,SLOT(insert_Row_After_Selected()));

    connect(edit->actions().at(3),SIGNAL(triggered()),controller,SLOT(insert_Column_Before_Selected()));
    connect(edit->actions().at(4),SIGNAL(triggered()),controller,SLOT(insert_Column_After_Selected()));

    connect(edit->actions().at(6),SIGNAL(triggered()),controller,SLOT(remove_Selected_Column()));
    connect(edit->actions().at(7),SIGNAL(triggered()),controller,SLOT(remove_Selected_Row()));

    connect(edit->actions().at(9),SIGNAL(triggered()),controller,SLOT(change_Selected_Col_Label()));
    connect(edit->actions().at(10),SIGNAL(triggered()),controller,SLOT(change_Selected_Row_Label()));

    //views
    connect(graphs->actions().at(0),SIGNAL(triggered()),this,SLOT(setPieChart()));
    connect(graphs->actions().at(1),SIGNAL(triggered()),this,SLOT(setDonutChart()));
    connect(graphs->actions().at(2),SIGNAL(triggered()),this,SLOT(setBarChart()));
    connect(graphs->actions().at(3),SIGNAL(triggered()),this,SLOT(setHorizontalBarChart()));
    connect(graphs->actions().at(4),SIGNAL(triggered()),this,SLOT(setStackedBarChart()));
    connect(graphs->actions().at(5),SIGNAL(triggered()),this,SLOT(setHorizontalStackedBarChart()));
    connect(graphs->actions().at(6),SIGNAL(triggered()),this,SLOT(setSplineChart()));
    connect(graphs->actions().at(7),SIGNAL(triggered()),this,SLOT(setLineChart()));
    connect(graphs->actions().at(8),SIGNAL(triggered()),this,SLOT(setScatterChart()));

    //settings
    connect(settings->actions().at(0),SIGNAL(triggered()),this,SLOT(showColors()));
    connect(settings->actions().at(1),SIGNAL(triggered()),this,SLOT(manageTableView()));
    connect(settings->actions().at(2),SIGNAL(triggered()),this,SLOT(manageChartView()));

    //themes
    connect(theme->actions().at(0),SIGNAL(triggered()),this,SLOT(setLight()));
    connect(theme->actions().at(1),SIGNAL(triggered()),this,SLOT(setBlueCerulean()));
    connect(theme->actions().at(2),SIGNAL(triggered()),this,SLOT(setDark()));
    connect(theme->actions().at(3),SIGNAL(triggered()),this,SLOT(setBrownSand()));
    connect(theme->actions().at(4),SIGNAL(triggered()),this,SLOT(setBlueNCS()));
    connect(theme->actions().at(5),SIGNAL(triggered()),this,SLOT(setHighContrast()));
    connect(theme->actions().at(6),SIGNAL(triggered()),this,SLOT(setBlueIcy()));
    connect(theme->actions().at(7),SIGNAL(triggered()),this,SLOT(setQt()));


    //others
    connect(others->actions().at(0),&QAction::triggered,[&](){
        QMessageBox msgBox;
        msgBox.setText("                                EasyCharts © "
                       "\ndeveloped by Davide Baggio and Samuel Scarabottolo\n"
                       "                                2021/2022 ");
        msgBox.exec();});

    //about
    connect(others->actions().at(1),&QAction::triggered,[&](){
        QMessageBox msgBox;
        msgBox.setText("Welcome to EasyCharts! \nThank you for downloading our totally free open source application. "
                       "Our intent is to provide users an easy and efficient experience, making everyone able to get many charts types in every scenario they wish."
                       "\n\nIf you want to know how to use the program, read the following tutorial:\n"
                       "\n1 First of all you can open an existing one project in json, xml or csv format (we provided you some examples)\n"
                       "\n2 With the respective buttons you can add rows and columns, before or after the selected cell\n"
                       "\n3 You can change the name of the columns or rows as you prefer\n"
                       "\n4 Add the datas and select the chart you want to display\n"
                       "\n5 Finally you can save or export your project!\n\n"
                       "\n Key Shortcut legend: \n"
                       "- CTRL+S: save the current project in JSON format\n"
                       "- CTRL+N: create new project\n"
                       "- CTRL+K: insert new column\n"
                       "- CTRL+R: insert new row\n"
                       "- CTRL+Alt+K: insert new column after selected\n"
                       "- CTRL+Alt+R: insert new row after selected\n"
                       "- Alt+K: delete the selected column\n"
                       "- Alt+R: delete the selected row\n"
                       "- CTRL+O: open an existing project\n"
                       "- CTRL+Shift+K: change the selected column label\n"
                       "- CTRL+Shift+R: change the selected row label\n"
                       "- CTRL+W: exit from application\n"
                       "Remember: if you want to add a column/row before or after one you need to select it and then press the button you want\n\n");
        msgBox.exec();});

    //update on edits
    connect(controller->getModel(),&QAbstractItemModel::dataChanged,[&](){tableChanged();});
}

void MainWindow::showColors(){
    refreshGui();
    manageTableView();
    manageChartView();
}

void MainWindow::manageTableView() {
    if(manageTable->isChecked())
        tableView->hide();
    else {
        tableView->setMinimumSize(900,480);
        tableView->show();
    }
}

void MainWindow::manageChartView() {
    if(manageChart->isChecked())
        chartView->hide();
    else
        chartView->show();
}

void MainWindow::setPieChart(){
    delete chart;
    chart=new PieChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::setBarChart(){
    delete chart;
    chart=new BarChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::setHorizontalBarChart(){
    delete chart;
    chart=new HorizontalBarChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::setStackedBarChart(){
    delete chart;
    chart=new BarStackedChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::setHorizontalStackedBarChart(){
    delete chart;
    chart=new HorizontalBarStackedChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::setLineChart(){
    delete chart;
    chart=new LineChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}
void MainWindow::setSplineChart(){
    delete chart;
    chart=new SplineChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}
void MainWindow::setScatterChart(){
    delete chart;
    chart=new ScatterChart();
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}
void MainWindow::setDonutChart(){
    delete chart;
    chart=new PieChart(0.4);
    refreshGui();
    if(!manageChart->isChecked())
        chartView->show();
}

void MainWindow::styleButton(const QString& color) {
    insertColumnAfterButton->setStyleSheet("background-color: " + color);
    insertColumnBeforeButton->setStyleSheet("background-color: " + color);
    insertRowAfterButton->setStyleSheet("background-color: " + color);
    insertRowBeforeButton->setStyleSheet("background-color: " + color);
    deleteCurrentColumnButton->setStyleSheet("background-color: " + color);
    deleteCurrentRowButton->setStyleSheet("background-color: " + color);
}

void MainWindow::setTheme(QRgb win, QRgb text, QChart::ChartTheme theme, const QString& button, const QString& tabStyle, const QString& menuStyle, bool b){
    QPalette pal = window()->palette();
    pal.setColor(QPalette::Window, QRgb(win));
    pal.setColor(QPalette::WindowText, QRgb(text));
    chartView->setNameTheme(theme);
    chartView->chart()->setTheme(theme);
    window()->setPalette(pal);

    styleButton(button);
    tableView->setStyleSheet(tabStyle);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    menu->setStyleSheet(menuStyle);

    if(!b){
        if(colorsItem != nullptr && colorsItem->isChecked())
            chart->addColorMapping();
        else
            chart->removeColorMapping();
        refreshTableView();
    }
}

void MainWindow::setLight(bool b){
    setTheme(0xf0f0f0, 0x404044, QChart::ChartThemeLight, "#FFFFFF",
             "QHeaderView::section{background-color: lightblue}" "QTableView {background-color: #f0f0f0; border: none}",
             "background-color: white; color: black", b);
}

void MainWindow::setBlueCerulean(bool b){
    setTheme(0x40434a, 0xd6d6d6, QChart::ChartThemeBlueCerulean, "#056087",
             "QHeaderView::section{background-color: #09486a; color: white}" "QTableView {background-color: #40434a; border: none}",
             "background-color: #40434a; color: white", b);
}

void MainWindow::setDark(bool b){
    setTheme(0x121218, 0xd6d6d6, QChart::ChartThemeDark, "#414146",
             "QHeaderView::section{background-color: #2e303a; color: white}" "QTableView {background-color: #121218; border: none}",
             "background-color: #121218; color: white", b);
}

void MainWindow::setBrownSand(bool b){
    setTheme(0x9e8965, 0x9e8965, QChart::ChartThemeBrownSand, "#f3ece0",
             "QHeaderView::section{background-color: #f3ece0}" "QTableView {background-color: #9e8965; border: none}",
             "background-color: #9e8965; color: black", b);
}

void MainWindow::setBlueNCS(bool b){
    setTheme(0x018bba, 0x404044, QChart::ChartThemeBlueNcs, "#1db0da",
             "QHeaderView::section{background-color: lightblue}" "QTableView {background-color: #018bba; border: none}",
             "background-color: #018bba; color: black", b);
}

void MainWindow::setHighContrast(bool b){
    setTheme(0xffab03, 0x181818, QChart::ChartThemeHighContrast, "#f3ece0",
             "QHeaderView::section{background-color: #F3d9b1}" "QTableView {background-color: #ffab03; color: white; border: none}",
             "background-color: #ffab03; color: black", b);
}

void MainWindow::setBlueIcy(bool b){
    setTheme(0xcee7f0, 0x404044, QChart::ChartThemeBlueIcy, "#2fa3b4",
             "QHeaderView::section{background-color: lightblue}" "QTableView {background-color: #cee7f0; color: white; border: none}",
             "background-color: #cee7f0; color: black", b);
}

void MainWindow::setQt(bool b){
    setTheme(0xaeadac, 0x404044, QChart::ChartThemeQt, "#80c342",
             "QHeaderView::section{background-color: #B9e891}" "QTableView {background-color: #aeadac; color: white; border: none}",
             "background-color: #aeadac; color: black", b);
}

void MainWindow::getGraphImage() {
    QPixmap p = chartView->grab();
    QOpenGLWidget *glWidget  = chartView->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint())-chartView->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }
    p.save(QFileDialog::getSaveFileName(this, "Save Image","../EasyCharts/Saved Files", "PNG (*.png)"), "PNG");
}
