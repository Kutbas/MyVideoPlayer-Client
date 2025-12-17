#include "uploadvideopage.h"
#include "ui_uploadvideopage.h"
#include "videoplayer.h"
#include "util.h"
#include <QFileDialog>
#include "./model/datacenter.h"

UploadVideoPage::UploadVideoPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::UploadVideoPage)
{
    ui->setupUi(this);

    // 获取所有分类数据
    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTagPtr = dataCenter->getKindAndTagClassPtr();
    ui->kinds->addItems(kindAndTagPtr->getAllKinds());
    ui->kinds->setCurrentIndex(-1);

    connect(ui->commitBtn, &QPushButton::clicked, this, &UploadVideoPage::onCommitBtnClicked);
    connect(ui->videoTittle, &QLineEdit::textChanged, this, &UploadVideoPage::onLineEditTextChanged);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &UploadVideoPage::onPlainEditTextChanged);
    connect(ui->changeButton, &QPushButton::clicked, this, &UploadVideoPage::onChangeButtonClicked);
    connect(ui->kinds, &QComboBox::currentTextChanged, this, &UploadVideoPage::onUpdateTags);
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

void UploadVideoPage::onChangeButtonClicked()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, "选择视频封面", "", "Images (*.jpg *.png)");
    if (fileName.isEmpty())
    {
        LOG() << "取消选择视频封面";
        return;
    }

    QPixmap pixmap(fileName);
    pixmap = pixmap.scaled(ui->imageLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->imageLabel->setPixmap(pixmap);
}

void UploadVideoPage::onUpdateTags(const QString &kind)
{
    addTagsByKind(kind);
}

void UploadVideoPage::addTagsByKind(const QString &kind)
{
    // 添加之前先清空之前的标签
    QList<QPushButton *> tagBtnList = ui->tagWidget->findChildren<QPushButton *>();

    for (auto tagBtn : tagBtnList)
    {
        // 删除标签按钮，提交按钮不能删除--
        ui->tagLayout->removeWidget(tagBtn);
        delete tagBtn;
    }

    // 将添加的弹簧删除掉
    // 弹簧本来是最后⼀个控件，当layoyut中的按钮删除之后，弹簧就变成第0个控件了
    QLayoutItem *spaceItem = ui->tagLayout->itemAt(ui->tagLayout->count() - 1);
    ui->tagLayout->removeItem(spaceItem);

    if (kind.isEmpty())
        return;

    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTagPtr = dataCenter->getKindAndTagClassPtr();
    auto tags = kindAndTagPtr->getTagsByKind(kind).keys();

    // 添加标签按钮到layout中
    for (auto &tag : tags)
    {
        QPushButton *tagBtn = new QPushButton(ui->tagWidget);
        tagBtn->setFixedSize(98, 49);
        tagBtn->setText(tag);
        tagBtn->setCheckable(true); // 设置按钮的状态为选中和未选中两种状态

        // QPushButton::checked 当前按钮被选中
        tagBtn->setStyleSheet("QPushButton{"
                              "border : 1px solid #3ECEFE;"
                              "border-radius : 4px;"
                              "color : #3ECEFE;"
                              "font-family : 微软雅黑;"
                              "font-size : 16px;"
                              "background-color : #FFFFFF;}"
                              "QPushButton:checked{"
                              "background-color : #3ECEFE;"
                              "color : #FFFFFF;}"
                              "QPushButton:unchecked{"
                              "background-color : #FFFFFF;"
                              "color : #3ECEFE;}");

        ui->tagLayout->addWidget(tagBtn);
    }

    // 在tagLayout最后放一个空白间距，将按钮挤到左侧
    ui->tagLayout->insertSpacing(tags.size(), ui->tagContent->width() - (98 + 20) * tags.size());
    ui->tagLayout->setSpacing(20);
}