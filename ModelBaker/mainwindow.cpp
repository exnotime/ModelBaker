#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileUtility.h"
#include <QFileDialog>
#include <QTableWidgetItem>
#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_ModelRow = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddModelToTable(int row, gfx::Model model)
{
    QTableWidgetItem* name = new QTableWidgetItem(tr(GetFilenameFromPath(model.Name).c_str()));
    QTableWidgetItem* vCount = new QTableWidgetItem(tr(patch::to_string(model.NumVertices).c_str()));
    QTableWidgetItem* iCount = new QTableWidgetItem(tr(patch::to_string(model.NumIndices).c_str()));
    std::stringstream ssout;
    ssout << m_Loader.CalcModelSize(model) / (float)(1024 * 1024); //recalc to MB
    ssout << " MB";
    QTableWidgetItem* size = new QTableWidgetItem(tr(ssout.str().c_str()));
    ui->ModelTable->insertRow(row);
    ui->ModelTable->setItem(row,0, name);
    ui->ModelTable->setItem(row,1, vCount);
    ui->ModelTable->setItem(row,2, iCount);
    ui->ModelTable->setItem(row,3, size);
}

void MainWindow::on_pushButton_clicked()
{
   QString fn = QFileDialog::getOpenFileName(this,tr("Open file..."), QDir::currentPath(),tr("Model files (*.dae *.obj);;All files (*)"));
   if(fn == "")
       return;
   if(m_Loader.LoadModel(fn.toLocal8Bit().constData())){
        static int counter = 0;

        gfx::Model& m = m_Loader.GetModel(fn.toLocal8Bit().constData());
        QString str = QString();
        str.sprintf("Model %d, VertexCount %d, IndiceCount %d",counter,m.NumVertices,m.NumIndices );

        //ui->tableWidget->listWidget->addItem(str);
        AddModelToTable(counter,m);
        counter++;

        m_ModelNames.push_back(m.Name);
        //set labels
        str.clear();
        str.sprintf("Total Vertex Count: %d", m_Loader.GetVertexCount());
        ui->vertexCountLabel->setText(str);
        str.clear();
        str.sprintf("Total Index Count: %d", m_Loader.GetIndexCount());
        ui->IndexCountLabel->setText(str);

   }
}

void MainWindow::on_BakeButton_clicked()
{
    QFileDialog* dialog = new QFileDialog();
    QString file = dialog->getSaveFileName(this,"Save file", QDir::currentPath(), "binary file (*.kbm)");
}

void MainWindow::on_ModelTable_cellActivated(int row, int column)
{


}

void MainWindow::on_ModelTable_cellClicked(int row, int column)
{
    if( m_ModelRow == row){
        return; //nothing has changed
    }

    m_ModelRow = row;
    //popluate material table
    ui->MaterialTable->clearContents();
    ui->MaterialTable->setRowCount(0);
    gfx::Model m = m_Loader.GetModel(m_ModelNames.at(row));
    for(int i = 0; i < m.MaterialCount; i++){
        gfx::Material mat = m_Loader.GetMaterial(m.MaterialOffset + i);
        QTableWidgetItem* name = new QTableWidgetItem(tr(mat.GetName().c_str()));
        QTableWidgetItem* albedo = new QTableWidgetItem(tr(mat.GetAlbedoTexture().c_str()));
        QTableWidgetItem* bump = new QTableWidgetItem(tr(mat.GetNormalTexture().c_str()));
        QTableWidgetItem* roughness = new QTableWidgetItem(tr(mat.GetRoughnessTexture().c_str()));
        QTableWidgetItem* metal = new QTableWidgetItem(tr(mat.GetMetalTexture().c_str()));
        ui->MaterialTable->insertRow(i);
        ui->MaterialTable->setItem(i,0,name);
        ui->MaterialTable->setItem(i,1,albedo);
        ui->MaterialTable->setItem(i,2,bump);
        ui->MaterialTable->setItem(i,3,roughness);
        ui->MaterialTable->setItem(i,4,metal);
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionAbout_triggered()
{
    //QMessageBox::information(this, "About", "Made by Henrik Johansson 2015");
}
