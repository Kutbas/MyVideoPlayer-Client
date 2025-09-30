#include "modifymyselfdialog.h"
#include "ui_modifymyselfdialog.h"

ModifyMyselfDialog::ModifyMyselfDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ModifyMyselfDialog)
{
    ui->setupUi(this);
}

ModifyMyselfDialog::~ModifyMyselfDialog()
{
    delete ui;
}
