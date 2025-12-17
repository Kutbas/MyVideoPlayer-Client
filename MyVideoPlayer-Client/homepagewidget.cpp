#include "homepagewidget.h"
#include "ui_homepagewidget.h"
#include <QVBoxLayout>
#include "util.h"
#include "videobox.h"
#include "./model/datacenter.h"

HomePageWidget::HomePageWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::HomePageWidget)
{
    ui->setupUi(this);

    initKindAndTags();
    initRefreshAndTopBtn();
    initVideos();
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}

// 初始化分类和标签
void HomePageWidget::initKindAndTags()
{
    // 分类
    // QList<QString> kinds = {
    //     "历史",
    //     "美食",
    //     "游戏",
    //     "科技",
    //     "运动",
    //     "动物",
    //     "旅行",
    //     "电影"};
    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTagPtr = dataCenter->getKindAndTagClassPtr();
    auto kinds = kindAndTagPtr->getAllKinds();

    // 创建分类按钮
    QPushButton *kindBtn = buildSelectBtn(ui->classifys, "#3ECEFF", "分类");
    ui->classifyHLayout->addWidget(kindBtn);

    // 具体的分类按钮
    for (auto &kind : kinds)
    {
        QPushButton *kindItemBtn = buildSelectBtn(ui->classifys, "#222222", kind);
        ui->classifyHLayout->addWidget(kindItemBtn);

        // 给分类按钮绑定槽函数
        connect(kindItemBtn, &QPushButton::clicked, this, [=]
                { onKindBtnClicked(kindItemBtn); });
    }

    ui->classifyHLayout->addStretch(); // 添加水平弹簧

    ui->classifyHLayout->setSpacing(8);

    // 分类和该分类下所有标签映射
    // tags = {
    //     {"历史",
    //      {"中国史", "世界史", "历史人物", "艺术", "文化", "奇闻"}},
    //     {"美食",
    //      {"美食测评", "美食制作", "美食攻略", "美食记录", "探店", "水果", "海鲜"}},
    //     {"游戏",
    //      {"游戏攻略", "单机游戏", "电子竞技", "手机游戏", "网络游戏", "游戏赛事", "桌游棋牌"}},
    //     {"科技",
    //      {"数码", "软件应用", "智能家居", "手机", "电脑", "人工智能", "基础设施"}},
    //     {"运动",
    //      {"篮球", "足球", "乒乓球", "羽毛球", "健身", "竞技体育", "运动装备"}},
    //     {"动物",
    //      {"喵星人", "汪星人", "宠物知识", "动物资讯", "野生动物", "动物世界", "萌宠"}},
    //     {"旅行",
    //      {"旅游攻略", "旅行vlog", "自驾游", "交通", "环球旅行", "露营", "野外生存"}},
    //     {"电影",
    //      {"电影解说", "电影推荐", "电影剪辑", "搞笑", "吐槽", "悬疑", "经典"}}};
    auto tags = kindAndTagPtr->getTagsByKind(kinds[0]).keys();

    // 创建分类下的所有标签，默认情况下创建第0个分类下的标签
    // resetTags(tags[kinds[0]]);
    resetTags(tags);
}

QPushButton *HomePageWidget::buildSelectBtn(QWidget *parent, const QString &color, const QString &text)
{
    QPushButton *btn = new QPushButton(text, parent);
    btn->setStyleSheet("color:" + color + ";");
    btn->setMinimumHeight(26);
    btn->setFixedWidth(text.size() * 16 + 18 + 18);
    return btn;
}

// void HomePageWidget::resetTags(const QList<QString> &tags)
// {
//     QPushButton *tag = buildSelectBtn(ui->labels, "#3ECEFF", "标签");
//     ui->labelHLayout->addWidget(tag);

//     // 创建具体的每个标签
//     for (auto &tagText : tags)
//     {
//         QPushButton *tagItem = buildSelectBtn(ui->labels, "#666666", tagText);
//         ui->labelHLayout->addWidget(tagItem);

//         connect(tagItem, &QPushButton::clicked, this, [=]
//                 { onTagBtnClicked(tagItem); });
//     }

//     ui->labelHLayout->addStretch();

//     ui->labelHLayout->setSpacing(4);
// }
// 重置标签
void HomePageWidget::resetTags(const QList<QString> &tags)
{
    // 清空旧的 stretch，避免重复添加
    QLayoutItem *child;
    while ((child = ui->labelHLayout->takeAt(ui->labelHLayout->count() - 1)) != nullptr)
    {
        if (child->spacerItem())
        {
            delete child; // 删除旧的 stretch
            break;
        }
        else
        {
            ui->labelHLayout->insertItem(ui->labelHLayout->count(), child);
        }
    }

    // 插入“标签”按钮
    QPushButton *tag = buildSelectBtn(ui->labels, "#3ECEFF", "标签");
    ui->labelHLayout->insertWidget(0, tag);

    // 插入每个标签按钮（紧跟在前一个之后）
    int index = 1;
    for (auto &tagText : tags)
    {
        QPushButton *tagItem = buildSelectBtn(ui->labels, "#666666", tagText);
        ui->labelHLayout->insertWidget(index++, tagItem);

        connect(tagItem, &QPushButton::clicked, this, [=]
                { onTagBtnClicked(tagItem); });
    }

    // 保证始终有一个 stretch 在最后
    ui->labelHLayout->addStretch();

    ui->labelHLayout->setSpacing(4);
}

// 分类按钮点击
void HomePageWidget::onKindBtnClicked(QPushButton *clickedKindBtn)
{
    // 设置当前被点击分类按钮的高亮显示
    clickedKindBtn->setStyleSheet("background-color:#F1FDFF;"
                                  "color:#3ECEFF;");

    // 清除之前点击过的分类按钮的高亮显示
    QList<QPushButton *> kindBtns = ui->classifys->findChildren<QPushButton *>(); // 获取所有的分类按钮
    for (auto kindBtn : kindBtns)
    {
        if (kindBtn != clickedKindBtn)
        {
            kindBtn->setStyleSheet("color : #222222;");
        }
    }

    // 先删除分类布局器中之前分类按钮下的所有标签
    QList<QPushButton *> tagBtns = ui->labels->findChildren<QPushButton *>();
    for (auto tagBtn : tagBtns)
    {
        ui->labelHLayout->removeWidget(tagBtn);
        delete tagBtn;
    }
    // 重新添加当前点击分类按钮对应的所有标签
    auto dataCenter = model::DataCenter::getInstance();
    auto kindAndTagPtr = dataCenter->getKindAndTagClassPtr();
    resetTags(kindAndTagPtr->getTagsByKind(clickedKindBtn->text()).keys());
}

// 标签按钮点击
void HomePageWidget::onTagBtnClicked(QPushButton *clickedTagBtn)
{
    // 设置当前被点击标签按钮的高亮显示
    clickedTagBtn->setStyleSheet("background-color:#F1FDFF;"
                                 "color:#3ECEFF;");

    // 获取当前分类下的所有标签，并清除之前点击过的标签的高亮显示
    QList<QPushButton *> tagBtns = ui->labels->findChildren<QPushButton *>();
    for (auto &tagBtn : tagBtns)
    {
        if (tagBtn != clickedTagBtn)
        {
            tagBtn->setStyleSheet("color : #666666;");
        }
    }
}

void HomePageWidget::initRefreshAndTopBtn()
{
    // 先创建一个 QWidget
    QWidget *refreshTopWidget = new QWidget(this);
    refreshTopWidget->setFixedSize(42, 94);
    refreshTopWidget->setStyleSheet("QPushButton{border-radius : 21px;"
                                    "border : none;"
                                    "background-color : #DDDDDD;}"
                                    "QPushButton:hover{background-color : #666666;}");
    QVBoxLayout *layout = new QVBoxLayout(refreshTopWidget);

    // 创建按钮
    QPushButton *topBtn = new QPushButton(refreshTopWidget);
    topBtn->setFixedSize(42, 42);
    topBtn->setStyleSheet("border-image : url(:images/homePage/zhiding.png);");

    layout->addWidget(topBtn);

    QPushButton *refreshBtn = new QPushButton(refreshTopWidget);
    refreshBtn->setFixedSize(42, 42);
    refreshBtn->setStyleSheet("border-image : url(:images/homePage/shuaxin.png);");

    layout->addWidget(refreshBtn);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    refreshTopWidget->move(1278, 618);

    connect(topBtn, &QPushButton::clicked, this, &HomePageWidget::onTopBtnClicked);
    connect(refreshBtn, &QPushButton::clicked, this, &HomePageWidget::onRefreshBtnClicked);
}

void HomePageWidget::onTopBtnClicked()
{
    LOG() << "置顶";
}

void HomePageWidget::onRefreshBtnClicked()
{
    LOG() << "刷新";
}

void HomePageWidget::initVideos()
{
    for (int i = 0; i < 16; ++i)
    {
        VideoBox *videoBox = new VideoBox();

        // 一行显示4个视频
        ui->videoGLayout->addWidget(videoBox, i / 4, i % 4);
    }
}