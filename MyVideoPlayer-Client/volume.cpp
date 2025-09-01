#include "volume.h"
#include "ui_volume.h"

Volume::Volume(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Volume)
{
    ui->setupUi(this);
}

Volume::~Volume()
{
    delete ui;
}
