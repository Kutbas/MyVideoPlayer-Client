#include "playspeed.h"
#include "ui_playspeed.h"
#include "util.h"

PlaySpeed::PlaySpeed(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlaySpeed)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->speed20, &QPushButton::clicked, this, &PlaySpeed::onPlay20SpeedClicked);
    connect(ui->speed15, &QPushButton::clicked, this, &PlaySpeed::onPlay15SpeedClicked);
    connect(ui->speed10, &QPushButton::clicked, this, &PlaySpeed::onPlay10SpeedClicked);
    connect(ui->speed05, &QPushButton::clicked, this, &PlaySpeed::onPlay05SpeedClicked);
}

PlaySpeed::~PlaySpeed()
{
    delete ui;
}

void PlaySpeed::onPlay20SpeedClicked()
{
    LOG() << "2.0";
}

void PlaySpeed::onPlay15SpeedClicked()
{
    LOG() << "1.5";
}

void PlaySpeed::onPlay10SpeedClicked()
{
    LOG() << "1.0";
}

void PlaySpeed::onPlay05SpeedClicked()
{
    LOG() << "0.5";
}