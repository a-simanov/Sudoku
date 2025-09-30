#include "sudoku.h"
#include "ui_sudoku.h"

#include <QDebug>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);
}

Sudoku::~Sudoku()
{
    delete ui;
}

void Sudoku::SetField (int x) {
    table_ = new QTableWidget(this);
    table_->setMinimumHeight(500);
    table_->setMinimumWidth(500);
    table_->setRowCount(9);
    table_->setColumnCount(9);
    table_->setFont(QFont("Arial", 30));
    table_->verticalHeader()->setVisible(false);
    table_->horizontalHeader()->setVisible(false);
    field_.GenerateField(x);
    std::vector<std::vector<int>> vec = field_.GetField();
    if (vec.size() == 0) {
        throw std::logic_error("Vector empty");
    }
    for (size_t i = 0 ; i < 9; ++i) {
        table_->setRowHeight(i, 50);
        for (size_t j = 0 ; j < 9; ++j) {
            table_->setColumnWidth(j, 50);
            if (vec[i][j] == 0) {
                table_->setItem(i, j, new QTableWidgetItem(0));
            } else {
                QString val = QString::number(vec[i][j]);
                QTableWidgetItem* cell = new QTableWidgetItem();
                cell->setText(val);
                table_->setItem(i, j, cell);
                cell->setFlags(cell->flags() & ~Qt::ItemIsEditable);
            }            
        }        
    }
    table_->show();
    connect(table_, SIGNAL(cellChanged(int, int)), this, SLOT(onCellClicked(int, int)));
}



void Sudoku::SetScore(int s) {
    score_ += s;
}

int Sudoku::GetScore() const {
    return score_;
}

bool Sudoku::CheckScore() const {
    return GetScore() == 81;
}

void Sudoku::on_pb_set_field_easy_clicked()
{
    try {
        SetField(81 - 30);
        SetScore(40);
    } catch (std::logic_error& e) {
        table_->clear();
        field_.ResetField_();
    }

}


void Sudoku::on_pb_set_field_medium_clicked()
{
    try {
        SetField(81 - 25);
        SetScore(25);
    } catch (std::logic_error& e) {
        table_->clear();
        field_.ResetField_();
    }
}


void Sudoku::on_pb_set_field_hard_clicked()
{
    try {
        SetField(81 - 20);
        SetScore(20);
    } catch (std::logic_error& e) {
        table_->clear();
        field_.ResetField_();
    }
}

void Sudoku::onCellClicked(int row, int column) {
    int  val = table_->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        table_->item(row, column)->setBackground(QBrush("red"));
    } else {
        table_->item(row, column)->setBackground(QBrush(""));
    }
    if (CheckScore()) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                table_->item(i, j)->setBackground(QBrush("green"));
            }
        }
    }
    if (val) {
        SetScore(1);
    } else {
        SetScore(-1);
    }
};

void Sudoku::on_tableWidget_cellChanged(int row, int column)
{
    int  val = table_->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        table_->item(row, column)->setBackground(QBrush("red"));
    } else {
        table_->item(row, column)->setBackground(QBrush(""));
    }
    if (CheckScore()) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                table_->item(i, j)->setBackground(QBrush("green"));
            }
        }
    }
    if (val) {
        SetScore(1);
    } else {
        SetScore(-1);
    }
}


void Sudoku::on_tableWidget_cellClicked(int row, int column)
{
    int  val = table_->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        table_->item(row, column)->setBackground(QBrush("red"));
    } else {
        table_->item(row, column)->setBackground(QBrush(""));
    }
    if (CheckScore()) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                table_->item(i, j)->setBackground(QBrush("green"));
            }
        }
    }
    if (val) {
        SetScore(1);
    } else {
        SetScore(-1);
    }
}

