#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);

    setWindowTitle("Ввод данных");
    resize(300, 150);
}

InputDialog::~InputDialog()
{
    delete ui;
}
