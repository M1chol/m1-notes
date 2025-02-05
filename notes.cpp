#include "notes.h"
#include "./ui_notes.h"


Notes::Notes(TabletCanvas *m_canvas, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notes)
{
    ui->setupUi(this);
    canvas = m_canvas;
    setCentralWidget(m_canvas);
}

Notes::~Notes()
{
    delete ui;
}

void Notes::on_actionNew_file_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm?", "This action will clear contetns of file.",
                                  QMessageBox::Yes | QMessageBox::Cancel);
    if(reply == QMessageBox::Yes)
    {
        canvas->clear();
    }
}

void Notes::on_actionSave_triggered()
{
    actionNotImplemented();
}


void Notes::on_actionSave_As_triggered()
{
    actionNotImplemented();
}

void Notes::actionNotImplemented(){
    QMessageBox::warning(this, "Not implemented.", "This action has not been implemented yet.", QMessageBox::Ok);
}

void Notes::on_actionOpen_triggered()
{
    actionNotImplemented();
}

void Notes::on_actionOpen_Folder_triggered()
{
     actionNotImplemented();
}

