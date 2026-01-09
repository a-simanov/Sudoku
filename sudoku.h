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

inline const int TEXT_ALIGNMENT = 5;
inline const int MINIMUM_CELL_SIZE = 452;
inline const int ROW_AND_COL_SIZE = 50;
inline const int FONT_SIZE = 30;

inline const int EASY_EMPTY_CELLS = 45;
inline const int MEDIUM_EMPTY_CELLS = 55;
inline const int HARD_EMPTY_CELLS = 60;

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();    
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

    void SetFieldParameters();
    void SetField (int x);
    void CheckField () const;
};
#endif // SUDOKU_H
