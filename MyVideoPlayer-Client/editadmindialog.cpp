#include "editadmindialog.h"
#include "ui_editadmindialog.h"
#include "util.h"
#include "videoplayer.h"

EditAdminDialog::EditAdminDialog(QWidget *parent, const QString &text)
    : QDialog(parent), ui(new Ui::EditAdminDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    ui->tittleLabel->setText(text);

    // 移动窗口位置，和主界面左上角对齐
    VideoPlayer *videoPlayer = VideoPlayer::getInstance();
    this->move(videoPlayer->mapToGlobal(QPoint(0, 0)));

    // 对手机号的格式进行限制
    QRegularExpression regExp("^1\\d{10}$");
    QValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->phoneEdit->setValidator(validator);

    // 设置管理员角色
    ui->roleComboBox->addItem("平台管理员");
    ui->roleComboBox->setCurrentIndex(0);

    // 编辑字数改变
    connect(ui->commentTextEdit, &QPlainTextEdit::textChanged, this, [=]
            {
        QString text=ui->commentTextEdit->toPlainText();
        int wordCount=text.length();
        if(wordCount>10)
        {   
            wordCount = 10;
            ui->commentTextEdit->setPlainText(text.mid(0,10));
        }
        ui->wordCount->setText(QString::number(wordCount)+"/10");

        QTextCursor textCursor = ui->commentTextEdit->textCursor();
        textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->commentTextEdit->setTextCursor(textCursor); });

    connect(ui->submitBtn, &QPushButton::clicked, this, &EditAdminDialog::onSubmitBtnClicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &EditAdminDialog::onCancelBtnClicked);
}

EditAdminDialog::~EditAdminDialog()
{
    delete ui;
}

void EditAdminDialog::onSubmitBtnClicked()
{
    LOG() << ui->tittleLabel->text() << " 按钮点击";
}

void EditAdminDialog::onCancelBtnClicked()
{
    close();
}
