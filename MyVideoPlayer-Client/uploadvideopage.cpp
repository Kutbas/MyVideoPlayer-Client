#include "uploadvideopage.h"
#include "ui_uploadvideopage.h"
#include "videoplayer.h"
#include "util.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);

    connect(ui->commitBtn, &QPushButton::clicked, this, &UploadVideoPage::onCommitBtnClicked);
    connect(ui->videoTittle, &QLineEdit::textChanged, this, &UploadVideoPage::onLineEditTextChanged);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &UploadVideoPage::onPlainEditTextChanged);
}

UploadVideoPage::~UploadVideoPage()
{
    delete ui;
}

void UploadVideoPage::onCommitBtnClicked()
{
    // 将页面中的视频信息上传到服务器

    // 切换回我的页面
    emit switchMyselfPage(MyPage);
}

void UploadVideoPage::onLineEditTextChanged(const QString &text)
{
    // LOG() << text;
    // 先从 wordLeft 中获取最大的输入字数
    QString wordLeftText = ui->wordLeft->text();
    int linePos = wordLeftText.indexOf('/');
    int maxCount = wordLeftText.mid(linePos + 1).toInt();

    // 检测 text 中的字数是否超过最大值，如果没有，将 text 的长度和最大字数拼接起来
    int wordCount = text.length();
    if (wordCount <= maxCount)
    {
        ui->wordLeft->setText(QString::number(wordCount) + "/" + QString::number(maxCount));
    }
    else
    {
        LOG() << "视频标题不能超过80个字符！";
        ui->videoTittle->setText(text.mid(0, 80));
    }
}

void UploadVideoPage::onPlainEditTextChanged()
{
    // 获取 QPlainTextEdit 中的文本
    QString text = ui->plainTextEdit->toPlainText();
    int wordCount = text.length();

    // 获取最大字数
    QString wordLeftText = ui->briefLeftWord->text();
    int linePos = wordLeftText.indexOf('/');
    int maxCount = wordLeftText.mid(linePos + 1).toInt();

    if (wordCount <= maxCount)
    {
        ui->briefLeftWord->setText(QString::number(wordCount) + "/" + QString::number(maxCount));
    }
    else
    {
        LOG() << "视频简介超过了规定字符！";
        ui->plainTextEdit->setPlainText(text.mid(0, maxCount));

        // 设置滚动条一直在底部
        // textCursor：设置当前光标的位置
        // movePosition：移动光标的位置，QTextCursor::End 移动到文本末尾；QTextCursor::MoveAnchor 光标的位置是固定的，不会创建选区
        QTextCursor textCursor = ui->plainTextEdit->textCursor();
        textCursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        ui->plainTextEdit->setTextCursor(textCursor);
    }
}
