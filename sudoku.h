#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <iostream>
#include <QTableView>
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
    bool CheckScore() const;
    void SetScore(int s);
    int GetScore() const;
private slots:
    void on_pb_set_field_easy_clicked();

    void on_pb_set_field_medium_clicked();

    void on_pb_set_field_hard_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::Sudoku *ui;
    Field field_{};
    int score_{};
};
#endif // SUDOKU_H
