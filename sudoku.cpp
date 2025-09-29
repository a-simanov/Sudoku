#include "sudoku.h"
#include "ui_sudoku.h"

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
    ui->tableWidget->setMinimumHeight(550);
    ui->tableWidget->setMinimumWidth(550);
    ui->tableWidget->setRowCount(9);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setFont(QFont("Arial", 30));
    field_.GenerateField(x);
    std::vector<std::vector<int>> vec = field_.GetField();
    if (vec.size() == 0) {
        throw std::logic_error("Vector empty");
    }
    for (size_t i = 0 ; i < 9; ++i) {
        for (size_t j = 0 ; j < 9; ++j) {
            if (vec[i][j] == 0) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(0));
            } else {
                QString val = QString::number(vec[i][j]);
                QTableWidgetItem* cell = new QTableWidgetItem(val);
                try {
                    ui->tableWidget->setItem(i, j, cell);
                } catch (std::exception& e) {
                    std::cout << e.what();
                }
                //cell->setFlags(cell->flags() & ~Qt::ItemIsEditable);
            }
            ui->tableWidget->setColumnWidth(j, 50);
        }
        ui->tableWidget->setRowHeight(i, 50);
    }
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
        ui->tableWidget->clear();
        field_.ResetField_();
        std::cout << e.what();
    }

}


void Sudoku::on_pb_set_field_medium_clicked()
{
    try {
        SetField(81 - 25);
        SetScore(25);
    } catch (std::logic_error& e) {
        ui->tableWidget->clear();
        field_.ResetField_();
        std::cout << e.what();
    }
}


void Sudoku::on_pb_set_field_hard_clicked()
{
    try {
        SetField(81 - 20);
        SetScore(20);
    } catch (std::logic_error& e) {
        ui->tableWidget->clear();
        field_.ResetField_();
        std::cout << e.what();
    }
}

void Sudoku::on_tableWidget_cellChanged(int row, int column)
{
    int  val = ui->tableWidget->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        ui->tableWidget->item(row, column)->setBackground(QBrush("red"));
    } else {
        ui->tableWidget->item(row, column)->setBackground(QBrush(""));
    }
    if (CheckScore()) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                ui->tableWidget->item(i, j)->setBackground(QBrush("green"));
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
    int  val = ui->tableWidget->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        ui->tableWidget->item(row, column)->setBackground(QBrush("red"));
    } else {
        ui->tableWidget->item(row, column)->setBackground(QBrush(""));
    }
    if (CheckScore()) {
        for (size_t i = 0; i < 9; ++i) {
            for (size_t j = 0; j < 9; ++j) {
                ui->tableWidget->item(i, j)->setBackground(QBrush("green"));
            }
        }
    }
    if (val) {
        SetScore(1);
    } else {
        SetScore(-1);
    }
}

