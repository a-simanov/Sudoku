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

void Sudoku::SetFieldParameters() {
    table_ = new QTableWidget(this);
    table_->setMinimumHeight(MINIMUM_CELL_SIZE);
    table_->setMinimumWidth(MINIMUM_CELL_SIZE);
    table_->setRowCount(NUMBER_CELLS_IN_LINE);
    table_->setColumnCount(NUMBER_CELLS_IN_LINE);
    table_->setFont(QFont("Arial", FONT_SIZE));
    table_->verticalHeader()->setVisible(false);
    table_->horizontalHeader()->setVisible(false);
    ui->verticalLayout->addWidget(table_, 1, Qt::Alignment(Qt::AlignCenter));
}

void Sudoku::SetField (int x) {
    SetFieldParameters();
    field_.GenerateField(x);
    std::vector<std::vector<int>> vec = field_.GetField();
    if (vec.size() == 0) {
        throw std::logic_error("Vector empty");
    }
    for (size_t i = 0 ; i < NUMBER_CELLS_IN_LINE; ++i) {
        table_->setRowHeight(i, ROW_AND_COL_SIZE);
        for (size_t j = 0 ; j < NUMBER_CELLS_IN_LINE; ++j) {
            table_->setColumnWidth(j, ROW_AND_COL_SIZE);
            if (vec[i][j] == 0) {
                table_->setItem(i, j, new QTableWidgetItem(0));
            } else {
                QString val = QString::number(vec[i][j]);
                QTableWidgetItem* cell = new QTableWidgetItem();
                cell->setText(val);
                table_->setItem(i, j, cell);
                cell->setFlags(cell->flags() & ~Qt::ItemIsEditable);
                cell->setBackground(QBrush(Qt::lightGray));
                cell->setTextAlignment(TEXT_ALIGNMENT);
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
    SetField(EASY_EMPTY_CELLS);
}


void Sudoku::on_pb_set_field_medium_clicked()
{
    ResetField ();
    SetField(MEDIUM_EMPTY_CELLS);
}


void Sudoku::on_pb_set_field_hard_clicked()
{
    ResetField ();
    SetField(HARD_EMPTY_CELLS);
}

void Sudoku::onCellClicked(int row, int column) {
    int  val = table_->item(row, column)->text().toInt();
    field_.SetNum(row, column, val);
    if (field_.CheckCorrectSquare(row, column, val) || field_.CheckLine(row, column, val)){
        table_->item(row, column)->setBackground(QBrush("red"));
    } else {
        table_->item(row, column)->setBackground(QBrush());
    }
};



