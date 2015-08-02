#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>

#include "modelloader.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void AddModelToTable(int row, gfx::Model model);
private:
    Ui::MainWindow *ui;
    ModelLoader m_Loader;
    int m_ModelRow;
    std::vector<std::string> m_ModelNames;

private slots:
    void on_pushButton_clicked();
    void on_BakeButton_clicked();
    void on_ModelTable_cellActivated(int row, int column);
    void on_ModelTable_cellClicked(int row, int column);
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
