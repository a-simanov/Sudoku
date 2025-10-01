#include "sudoku.h"
#include "ui_sudoku.h"

#include <QDebug>
#include <qheaderview.h>

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
    table_->setMinimumHeight(452);
    table_->setMinimumWidth(452);
    table_->setRowCount(9);
    table_->setColumnCount(9);
    table_->setFont(QFont("Arial", 30));
    table_->verticalHeader()->setVisible(false);
    table_->horizontalHeader()->setVisible(false);
    ui->verticalLayout->addWidget(table_, 1, Qt::Alignment(Qt::AlignCenter));
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

void Sudoku::ResetField () {
    if (table_ != nullptr) {
        table_->clear();
        delete table_;
        table_ = nullptr;
    }
}

void Sudoku::on_pb_set_field_easy_clicked()
{
    ResetField ();
    SetField(45);
}


void Sudoku::on_pb_set_field_medium_clicked()
{
    ResetField ();
    SetField(55);
}


void Sudoku::on_pb_set_field_hard_clicked()
{
    ResetField ();
    SetField(60);
}

void Sudoku::onCellClicked(int row, int column) {
    int  val = table_->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        table_->item(row, column)->setBackground(QBrush("red"));
    } else {
        table_->item(row, column)->setBackground(QBrush(""));
    }
};



