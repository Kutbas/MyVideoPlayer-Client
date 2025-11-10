#include "roletableitem.h"
#include "ui_roletableitem.h"
#include "editadmindialog.h"

RoleTableItem::RoleTableItem(QWidget *parent, int seqNumber)
    : QWidget(parent), ui(new Ui::RoleTableItem)
{
    ui->setupUi(this);
    updateUI(seqNumber);

    connect(ui->editBtn, &QPushButton::clicked, this, &RoleTableItem::onEditBtnClicked);
}

RoleTableItem::~RoleTableItem()
{
    delete ui;
}

void RoleTableItem::updateUI(int seqNumber)
{
    ui->idLabel->setText(QString::number(seqNumber));
}

void RoleTableItem::onEditBtnClicked()
{
    EditAdminDialog *editAdminDlg = new EditAdminDialog(nullptr, "编辑后台用户");
    editAdminDlg->exec();
    delete editAdminDlg;
}