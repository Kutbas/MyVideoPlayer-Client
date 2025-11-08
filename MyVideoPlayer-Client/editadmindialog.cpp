#include "editadmindialog.h"
#include "ui_editadmindialog.h"

EditAdminDialog::EditAdminDialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditAdminDialog)
{
    ui->setupUi(this);
}

EditAdminDialog::~EditAdminDialog()
{
    delete ui;
}
