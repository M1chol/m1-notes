#ifndef NOTES_H
#define NOTES_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPushButton>

#include "tabletcanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Notes;
}
QT_END_NAMESPACE

class Notes : public QMainWindow
{
    Q_OBJECT

public:
    Notes(TabletCanvas *m_canvas, QWidget *parent = nullptr);
    ~Notes();

protected:

private slots:
    void on_actionNew_file_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionOpen_triggered();

    void actionNotImplemented();

    void on_actionOpen_Folder_triggered();

private:
    Ui::Notes *ui;
    TabletCanvas *canvas;
};
#endif // NOTES_H
