#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QStandardItem>

#include "field.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Sudoku;
}
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();
    void SetField (int x);
    void CheckField () const;
private slots:
    void on_pb_set_field_easy_clicked();

    void on_pb_set_field_medium_clicked();

    void on_pb_set_field_hard_clicked();

    void onCellClicked(int row, int column);

private:
    void ResetField ();
    Ui::Sudoku *ui;
    Field field_{};
    QTableWidget* table_ = nullptr;
};
#endif // SUDOKU_H
