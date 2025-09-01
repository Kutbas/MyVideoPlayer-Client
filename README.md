# 【项目】基于脚手架微服务的视频点播系统

## 首页布局

### 分类和标签处理

在实现一个带有分类与标签选择功能的界面时，我们需要解决以下几个核心问题：

1. 如何动态创建分类和标签按钮，并设置它们的样式与点击响应。
2. 如何在点击某个分类后，快速显示对应的所有标签。
3. 如何高效地管理分类与标签之间的映射关系。

**1. 分类与标签按钮的动态创建**

在界面中，**分类**和**标签**本质上都是具有点击功能的按钮。不同按钮的文本不同，而在**选中**与**未选中**状态下，它们的文本颜色和背景颜色也需要区分开。因此，我们可以封装一个方法 `buildSelectBtn(parent, text, color)`，用于创建按钮并设置样式。

**2. 分类与标签的布局设计**

根据界面逻辑，**分类按钮**通常放在一个固定的区域中，而**标签按钮**则在用户点击分类后动态显示。

比如：首页顶部是分类区域，点击“电影”后，下方会显示“经典电影”“剪辑”“吐槽”等标签。

在实现上：

- **分类是固定的**：
   因此我们可以用 `QList<QString>` 来存储所有分类。
- **标签也是固定的**：
   每个分类下的标签集合是确定的，可以用 `QList<QString>` 存储。
- **分类与标签的对应关系**：
   需要通过一个高效的数据结构进行映射，例如 `QHash<QString, QList<QString>>`。

**3. 分类与标签的映射关系**

当用户点击某个分类按钮后，我们需要**快速拿到该分类下的所有标签**。这就要求我们提前建立分类到标签的映射关系。在 C++ STL 中，有多种关联式容器可供选择：

| 容器类型             | 底层结构 | 查找效率 | 是否有序 |
| -------------------- | -------- | -------- | -------- |
| `map`                | 红黑树   | O(log n) | 有序     |
| `multimap`           | 红黑树   | O(log n) | 有序     |
| `unordered_map`      | 哈希表   | O(1)     | 无序     |
| `unordered_multimap` | 哈希表   | O(1)     | 无序     |

由于分类是唯一的，不需要考虑键重复，而且我们更关注查找效率，因此选择 **哈希表** 是最合适的。在 Qt 中，我们可以使用 **QHash**。

**4. 界面初始化方法设计**

为了让分类与标签在界面中正常显示，我们可以封装一个初始化方法：

```c++
// 初始化分类和标签
void HomePageWidget::initKindAndTags()
{
    // 分类
    QList<QString> kinds = {
        "历史",
        "美食",
        "游戏",
        "科技",
        "运动",
        "动物",
        "旅行",
        "电影"};

    // 分类和该分类下所有标签映射
    QHash<QString, QList<QString>> kindsAndTags{
        {"历史",
         {"中国史", "世界史", "历史人物", "艺术", "文化", "奇闻"}},
        {"美食",
         {"美食测评", "美食制作", "美食攻略", "美食记录", "探店", "水果", "海鲜"}},
        {"游戏",
         {"游戏攻略", "单机游戏", "电子竞技", "手机游戏", "网络游戏", "游戏赛事", "桌游棋牌"}},
        {"科技",
         {"数码", "软件应用", "智能家居", "手机", "电脑", "人工智能", "基础设施"}},
        {"运动",
         {"篮球", "足球", "乒乓球", "羽毛球", "健身", "竞技体育", "运动装备"}},
        {"动物",
         {"喵星人", "汪星人", "宠物知识", "动物资讯", "野生动物", "动物世界", "萌宠"}},
        {"旅行",
         {"旅游攻略", "旅行vlog", "自驾游", "交通", "环球旅行", "露营", "野外生存"}},
        {"电影",
         {"电影解说", "电影推荐", "电影剪辑", "搞笑", "吐槽", "悬疑", "经典"}}};
}
```

当点击分类按钮时，会调用 `initKindAndTags`，动态生成对应标签按钮。

在我们的界面中，**分类**和**标签**都是具有点击功能的按钮。

- 每个按钮上都有文本显示，不同的分类、标签对应不同的文本。
- 按钮的选中状态和未选中状态下，文本颜色和背景色不同。
- 当用户点击某个分类按钮后，需要在标签区域展示该分类对应的所有标签。

**5. 按钮创建方法**

因为分类和标签本质上都是按钮，创建按钮时需要避免重复编写代码，所以我们定义一个统一的方法：

```C++
QPushButton* buildSelectBtn(QWidget* parent, const QString& text, const QColor& color);
```

- **parent**：父组件，一般是分类区域或标签区域。
- **text**：按钮上显示的文本。
- **color**：按钮的背景色或文本颜色。
- 通过封装方法，可以统一设置样式，比如按钮在选中和未选中状态下的颜色。

> **TIPS**
>  我们的首页界面中，分类按钮会被放在一个 **分类布局容器** 中，而标签按钮会被放在 **标签布局容器** 中，两者的布局是分开的。

**6. 分类与标签的数据组织**

在 C++ STL 中，关联式容器主要分为以下几种：

|         容器         | 底层实现 | 是否有序 | 平均查找复杂度 |
| :------------------: | -------- | -------- | -------------- |
|        `map`         | 红黑树   | 有序     | O(log n)       |
|      `multimap`      | 红黑树   | 有序     | O(log n)       |
|   `unordered_map`    | 哈希表   | 无序     | O(1)           |
| `unordered_multimap` | 哈希表   | 无序     | O(1)           |

因为我们不关心分类的顺序，只需要快速查找，所以推荐使用 **unordered_map** 或 **QHash**。

在 Qt 程序中，更常用 **QHash**，它是 Qt 对哈希表的封装。

**7. 在 Qt 中动态创建分类与标签按钮**

在首页界面中，需要在分类与标签区域动态生成一系列按钮。由于分类和标签的布局不同、颜色不同，而且按钮的数量不固定，因此我们抽取了一个通用的构建函数 `buildSelectBtn`，用于创建带有特定颜色和文本的按钮。

```c++
QPushButton *HomePageWidget::buildSelectBtn(QWidget *parent, const QString &color, const QString &text)
{
    QPushButton *btn = new QPushButton(text, parent);

    // 通过样式表设置文本颜色
    btn->setStyleSheet("color:" + color + ";");

    // 设置按钮的最小高度
    btn->setMinimumHeight(16);

    // 根据文本长度动态计算按钮宽度
    // 每个字符占 16 像素，左右各留 18 像素的边距
    btn->setFixedWidth(text.size() * 16 + 18 + 18);

    return btn;
}
```

这个函数的核心是三个步骤：

1. **创建按钮**：直接使用 `QPushButton`，传入父控件和文本。
2. **设置样式**：通过 `setStyleSheet` 动态拼接颜色，让每个按钮可以有不同的前景色。
3. **计算宽度**：因为每个按钮上的文本长度不同，所以宽度也不能固定。这里根据字符串的字符数乘以字体像素宽度（16px），再加上左右各 18px 的边距。

这样就可以用同一个函数去创建分类按钮和标签按钮，而不需要为每种按钮写不同的逻辑。

**8. 分类按钮与标签按钮的区别**

在首页的 UI 中，“分类”是一个提示性标签，不需要点击交互，而每一个具体的分类按钮和标签按钮则需要响应点击事件。因此处理方式不同：

- **分类提示按钮**：只显示文字和颜色，不需要绑定槽函数。
- **具体分类和标签按钮**：在循环中动态创建，并且绑定点击信号。

例如，在初始化函数中大致是这样的逻辑：

```c++
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
            { kindItemBtn->setStyleSheet("background-color:#F1FDFF;"
                                         "color:#3ECEFF;"); });
}
```

通过这样的处理，既能保证分类提示与具体分类分开显示，又让每一个可点击的按钮都具备动态交互的能力。

在给按钮动态设置颜色时，有一个小坑需要注意：如果需要同时设置 `color`（前景色）和 `background-color`（背景色），必须在两条样式之间加上分号，否则 Qt 无法正确解析样式字符串，例如：

```c++
btn->setStyleSheet("background-color:#f1fdfd; color:#33ccee;");
```

如果忘记加分号，Qt 会直接报样式解析错误，导致颜色设置失效。

在分类按钮创建完成后，如果所有按钮紧密排列在一起，界面会显得拥挤。这时可以通过设置布局的 `spacing` 属性，给按钮之间留出一定的间距，例如：

```c++
ui->classifyHLayout->setSpacing(8);
```

这样可以让界面更加美观，也避免按钮贴得过近。

**9. 动态创建标签按钮**

当点击不同分类时，下方展示的标签列表也需要相应更新。因此，不能只在初始化时创建一次标签，而是需要根据当前选中的分类动态刷新。为此封装了一个 `resetTags` 方法：

```c++
// 重置标签
void HomePageWidget::resetTags(const QList<QString> &tags)
{
    // 创建“标签”提示按钮
    QPushButton *tag = buildSelectBtn(ui->labels, "#666666", "标签");
    ui->labelHLayout->addWidget(tag);

    // 创建具体的每个标签
    for (auto &tagText : tags)
    {
        QPushButton *tagItem = buildSelectBtn(ui->labels, "#666666", tagText);
        ui->labelHLayout->addWidget(tagItem);

        // 绑定点击事件：切换背景与文字颜色
        connect(tagItem, &QPushButton::clicked, this, [=] {
            tagItem->setStyleSheet("background-color:#F1FDFF;"
                                   "color:#3ECEFF;");
        });
    }

    // 设置标签按钮之间的间距
    ui->labelHLayout->setSpacing(4);
}
```

这个函数主要负责两件事：

1. **创建提示按钮**：在标签列表最前面添加一个不可点击的“标签”说明按钮。
2. **创建标签项**：根据传入的 `tags` 列表，动态生成每个标签按钮，并绑定点击事件。

这样，在点击不同的分类时，只需要传入对应的标签列表，就能重新渲染下方的标签按钮，实现动态联动。

**10. 分类与标签的交互逻辑**

在初始化函数 `HomePageWidget::initKindAndTags` 中，第一次进入界面时会默认展示第一个分类下的标签：

```c++
// 在初始化函数中
resetTags(kindsAndTags[kinds[0]]);
```

当用户点击其他分类时，触发槽函数重新调用 `resetTags`，即可刷新对应标签。整个过程无需手动清理旧按钮，Qt 会自动管理内存和布局。

**11. 样式优化**

在功能完成后，界面样式还需要进一步美化。主要优化点如下：

1. **去掉按钮默认边框**

   Qt 默认按钮带边框，这在本界面并不美观。可以在样式表中统一去掉：

   ```css
   QPushButton {
       border: none;
   }
   ```

通过类型选择器 `QPushButton`，让所有分类和标签按钮的边框消失。

2. **设置圆角效果**

   为了让按钮更贴合现代 UI 风格，给所有按钮加上圆角：

   ```css
   QPushButton {
       border-radius: 13px;
   }
   ```

   这里需要注意一个细节：**圆角半径不能超过按钮高度的一半**。否则裁剪效果会失效。
    之前我们设置的按钮高度是 16px，而圆角半径是 13px，导致圆角没有生效。解决方案有两种：

   - 增加按钮高度
   - 或减小圆角半径

   最后选择把按钮高度提升到 26px，圆角半径保持 13px，视觉效果刚好合适。

3. **分类与标签按钮的间距**

   分类按钮和标签按钮的间距不同。为了区分层级关系：

   ```c++
   ui->classifyHLayout->setSpacing(8); // 分类按钮之间间距
   ui->labelHLayout->setSpacing(4); // 标签按钮之间间距
   ```

   这样分类的层次更清晰，标签按钮更加紧凑。

4. 分类标题字体加粗

“分类”提示按钮需要在视觉上比普通分类更突出，因此单独设置字体加粗：

```css
QPushButton{
    font-weight: bold;
}
```

完成后的效果如下所示：

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202508282003548.png" style="width:90%;">
   			</td>
   		</tr>
           <tr><td><strong>分类与标签效果图</strong></td></tr>
   	</tbody>
   </table>
**12. 分类按钮点击逻辑优化**

前面我们已经完成了分类和标签的基本创建与显示，但在运行中发现两个问题：

1. **点击不同分类按钮时，底下的标签没有正确刷新**。
2. **之前点击过的分类或标签按钮的高亮状态没有清除**。

为了解决这个问题，我们需要在分类按钮点击事件中补充逻辑，并将相关操作封装到一个新的槽函数中。

1. 给分类按钮绑定点击槽函数:

在 `HomePageWidget::initKindAndTags` 中，为每一个分类按钮绑定槽函数 `onKindBtnClicked`，这样点击按钮时可以统一处理高亮状态和标签刷新：

```
// 给分类按钮绑定槽函数
connect(kindItemBtn, &QPushButton::clicked, this, [=] {
    onKindBtnClicked(kindItemBtn);
});
```

这一步的好处是将所有分类按钮的点击处理逻辑集中到了一个函数里，后续维护会更简单。

2. 分类按钮点击的完整逻辑:

接下来，我们实现 `onKindBtnClicked` 方法，分成三大步骤：

```c++
// 分类按钮点击事件
void HomePageWidget::onKindBtnClicked(QPushButton *clickedKindBtn)
{
    // Step 1. 设置当前点击按钮的高亮样式
    clickedKindBtn->setStyleSheet(
        "background-color:#F1FDFF;"
        "color:#3ECEFF;"
    );

    // Step 2. 清除其他分类按钮的高亮样式
    QList<QPushButton *> kindBtns = ui->classifys->findChildren<QPushButton *>();
    for (auto kindBtn : kindBtns) {
        if (kindBtn != clickedKindBtn) {
            kindBtn->setStyleSheet("color:#222222;");
        }
    }

    // Step 3. 先删除旧标签
    QList<QPushButton *> tagBtns = ui->labels->findChildren<QPushButton *>();
    for (auto tagBtn : tagBtns) {
        ui->labelHLayout->removeWidget(tagBtn);
        delete tagBtn;  // 手动释放
    }

    // Step 4. 重新添加当前分类对应的所有标签
    resetTags(tags[clickedKindBtn->text()]);
}
```

这里有一个细节需要注意：`removeWidget()` 方法只会将控件从布局器中移除，但并不会自动释放内存，因为我们的按钮是用 `new` 创建的。因此我们必须显式调用 `delete tagBtn` 来释放资源，否则会导致内存泄漏。

此外，可以看到我们在清除高亮状态和删除标签时都用到了 `findChildren<QPushButton *>()`。

原因是分类按钮和标签按钮都被动态创建并添加到了布局器中，它们没有被单独保存到列表里。使用 `findChildren` 可以直接通过父控件（这里是 `ui->classifys` 和 `ui->labels`）获取当前存在的所有按钮，非常方便。

**13. 标签按钮点击逻辑优化**

在上一部分中，我们完成了**分类按钮点击逻辑**，解决了高亮状态和标签刷新问题。
 但我们的交互还差一步：**标签按钮点击后的高亮状态处理**。

场景很简单：

- 当用户点击某个标签按钮时，这个标签应该被高亮。
- 其他标签需要恢复默认样式。
- 点击标签不会影响分类状态。

1. 给标签按钮绑定槽函数

在 `HomePageWidget::resetTags(const QList<QString> &tags)` 方法中，我们动态创建标签按钮。
 此时就可以直接绑定槽函数 `onTagBtnClicked()`，将当前标签按钮作为参数传递进去：

```
// 给标签按钮绑定槽函数
connect(tagItem, &QPushButton::clicked, this, [=] {
    onTagBtnClicked(tagItem);
});
```

**2. **标签按钮点击的完整逻辑****

标签按钮的点击处理和分类按钮类似，但更简单：

```c++
// 标签按钮点击事件
void HomePageWidget::onTagBtnClicked(QPushButton *clickedTagBtn)
{
    // Step 1. 设置当前点击标签按钮的高亮样式
    clickedTagBtn->setStyleSheet(
        "background-color:#F1FDFF;"
        "color:#3ECEFF;"
    );

    // Step 2. 清除其他标签的高亮状态
    QList<QPushButton *> tagBtns = ui->labels->findChildren<QPushButton *>();
    for (auto &tagBtn : tagBtns) {
        if (tagBtn != clickedTagBtn) {
            tagBtn->setStyleSheet("color:#666666;");
        }
    }
}
```

逻辑非常直观：

- 高亮当前点击的标签。
- 遍历所有标签按钮，恢复其他按钮的默认样式。

### 搜索框实现

在完成分类和标签的交互逻辑后，接下来我们处理首页的搜索功能。

 需求很简单：在首页顶部添加一个搜索框，用户可以输入关键词并点击搜索按钮，或者按下回车键触发搜索。

#### 为什么要自定义 QLineEdit

Qt 提供了内置的 `QLineEdit` 控件，但它只能显示一个纯文本编辑框，没办法直接在输入框内部添加左侧图标和右侧按钮。
 我们的设计目标是这样的：

```
[ 🔍 | 输入关键字...                  | 搜索按钮 ]
```

因此，我们需要自己封装一个新的控件：

- 左侧显示搜索图标
- 中间是用户输入的文本
- 右侧是一个“搜索”按钮

这就是为什么我们创建了 `SearchLineEdit` 类。

#### 创建 SearchLineEdit 类

在 Qt 项目中添加一个新类 `SearchLineEdit`，并继承 `QLineEdit`，从而保留输入框的基础功能，同时进行自定义扩展。

```c++
#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QLineEdit>

class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SearchLineEdit(QWidget *parent = nullptr);

signals:
    // 未来可以在这里添加自定义信号，比如 searchTriggered()
};

#endif // SEARCHLINEEDIT_H
```

> 继承 `QLineEdit` 的好处是，我们不需要自己实现输入功能，只需在原有基础上做 UI 扩展。

#### 在构造函数中实现自定义布局

```c++
#include "searchlineedit.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPixmap>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    // Step 1. 设置输入框大小和占位文字
    setFixedSize(320, 36);
    setPlaceholderText("请搜索你感兴趣的视频");

    // Step 2. 创建左侧搜索图标
    QLabel *searchImage = new QLabel(this);
    searchImage->setFixedSize(16, 16);
    searchImage->setPixmap(QPixmap(":/images/homePage/sousuo.png"));

    // Step 3. 创建右侧搜索按钮
    QPushButton *searchBtn = new QPushButton(this);
    searchBtn->setText("搜索");
    searchBtn->setFixedSize(62, 32);

    // Step 4. 创建水平布局器
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(searchImage);
    layout->addStretch();           // 给输入区留出空间
    layout->addWidget(searchBtn);
    layout->setContentsMargins(8, 2, 8, 2);
    layout->setSpacing(6);
}
```

#### 类型提升：把 UI 中的 QLineEdit 替换成自定义类

在 Qt Designer 中，首页上原本使用的是普通 `QLineEdit`，我们需要手动把它替换成 `SearchLineEdit`：

1. 选中首页上的搜索框 `QLineEdit`。
2. 右键 → **提升为**。
3. 类名填写 `SearchLineEdit`。
4. 勾选“全局添加”，点击确定。

这样，Qt Designer 仍然把它当作 QLineEdit 使用，但底层已经替换成了我们自定义的 `SearchLineEdit` 类。

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202508291602847.png" style="width:90%;">
   			</td>
   		</tr>
           <tr><td><strong>类型提升</strong></td></tr>
   	</tbody>
   </table>

#### 搜索框的布局优化

在上一节中，我们封装了 `SearchLineEdit` 类，让首页拥有了一个带搜索图标和按钮的输入框。不过，那时我们仅仅完成了控件的基本布局，样式和交互逻辑都还比较粗糙。这一节我们继续完善：首先调整搜索框的视觉效果，然后给按钮和回车键绑定交互逻辑，让它真正具备“搜索”功能。

最初实现时，我们把搜索图标、输入框和搜索按钮放到了同一个 `QHBoxLayout` 中，但没有添加任何“空白弹簧”，结果导致图标、按钮和文字都显得比较拥挤。老师在课上提到，解决办法其实很简单：在图标和按钮之间插入一个 **伸缩性空白区域**，类似于一个“弹簧”，它会自动把图标顶到最左边，按钮顶到最右边，输入文字则自然居中。

在代码中，只需要在 `layout->addWidget(searchImage);` 和 `layout->addWidget(searchBtn);` 之间加上一句 `layout->addStretch();` 即可完成。

**调整文字与图标的间距**

虽然添加弹簧解决了整体对齐问题，但输入框里的文字仍然显得太靠左，几乎要贴着图标。为了让视觉更舒适，我们使用 `setTextMargins` 为输入文字留出内边距：

```c++
setTextMargins(33, 0, 0, 0);
```

这里 `33` 像素是根据搜索图标宽度和预留间距测量出来的值，另外三个参数分别表示上、右、下的边距，统一设为 `0` 即可。

**为搜索框设置样式**

接下来，我们使用 **样式表（StyleSheet）** 美化搜索框的外观。老师在课堂上强调过，圆角半径不要超过控件高度的一半，否则会导致边角渲染异常。搜索框的高度是 `36px`，因此圆角半径设置为 `18px` 最合适。

```c++
setObjectName("search");
setStyleSheet(
    "#search {"
    "background-color: #FFFFFF;"
    "border-radius: 18px;"
    "border: 1px solid #3ECEFE;"
    "font-family: 微软雅黑;"
    "font-size: 14px;"
    "font-style: normal;"
    "}"
);
```

注意这里用的是 **ID 选择器** `#search`，原因是我们只想给搜索框本身设置样式，而不是影响它的子控件。如果直接写 `setStyleSheet` 不加 ID，子控件（比如 `QLabel` 和 `QPushButton`）也会继承这些样式，导致图标、按钮文字都显示异常。使用 ID 可以避免样式污染。

**搜索按钮的样式美化**

搜索按钮是搜索框视觉设计的重要部分，需要和输入框保持统一的风格。我们直接对按钮使用 `setStyleSheet` 设置圆角、背景色和字体样式：

```c++
searchBtn->setStyleSheet(
    "background-color: #3ECEFE;"
    "border-radius: 16px;"
    "font-family: 微软雅黑;"
    "font-size: 14px;"
    "color: #FFFFFF;"
    "font-style: normal;"
);
```

按钮的高度是 `32px`，因此圆角半径设置为 `16px`，刚好形成柔和的圆角矩形效果。背景颜色与搜索框的边框颜色保持一致，形成视觉统一。

**绑定搜索交互逻辑**

搜索框不仅要好看，还要能用。我们在类中新增了一个槽函数 `onSearchBtnClicked()`，用于响应点击搜索按钮或按下回车键：

```c++
SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
    // ......

    // 点击搜索按钮触发搜索
    connect(searchBtn, &QPushButton::clicked,
            this, &SearchLineEdit::onSearchBtnClicked);

    // 按下回车键同样触发搜索
    connect(this, &QLineEdit::returnPressed,
            this, &SearchLineEdit::onSearchBtnClicked);
}

void SearchLineEdit::onSearchBtnClicked()
{
    LOG() << "搜索按钮点击";
}
```

此处用到的 `LOG()` 宏来自项目中的 `util.h`，方便在控制台输出调试信息。
 通过绑定 **按钮点击信号** 和 **回车信号**，用户既可以手动点击，也可以直接敲回车完成搜索，体验更加自然。

### 刷新和置顶按钮实现

在首页视频列表的浏览过程中，当内容越来越多时，用户需要快速返回顶部或者重新加载视频数据。为了实现这两个功能，我们在首页右下角添加了两个悬浮按钮：上方是“置顶”按钮，下方是“刷新”按钮。

从交互上来说，**置顶按钮**用于快速回到页面顶部；**刷新按钮**则会重新向服务器发起请求，重新获取最新的视频列表。这两个按钮是独立的功能，但它们的布局设计是一体的，放在同一个小面板中，方便用户操作。

#### 创建按钮容器和布局

我们先在 `HomePageWidget` 中新建一个方法 `initRefreshAndTopBtn()`，在其中完成按钮容器、布局器和按钮本身的创建：

```c++
void HomePageWidget::initRefreshAndTopBtn()
{
    // 创建一个容器 QWidget，作为刷新和置顶按钮的父控件
    QWidget *refreshTopWidget = new QWidget(this);
    refreshTopWidget->setFixedSize(42, 94);

    // 使用垂直布局器，让两个按钮上下排列
    QVBoxLayout *layout = new QVBoxLayout(refreshTopWidget);

    // 创建置顶按钮
    QPushButton *topBtn = new QPushButton(refreshTopWidget);
    topBtn->setFixedSize(42, 42);
    topBtn->setStyleSheet("border: none;"
                          "border-image: url(:/images/homePage/zhiding.png);");
    layout->addWidget(topBtn);

    // 创建刷新按钮
    QPushButton *refreshBtn = new QPushButton(refreshTopWidget);
    refreshBtn->setFixedSize(42, 42);
    refreshBtn->setStyleSheet("border: none;"
                              "border-image: url(:/images/homePage/shuaxin.png);");
    layout->addWidget(refreshBtn);

    // 调整布局器的内边距和按钮之间的间距
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
}
```

从布局上看，两个按钮的大小相同，都是 `42x42`，中间留 `10px` 的空隙，整个容器高度正好是 `94px`，这样看起来非常紧凑。

#### 更新按钮容器与样式

在上一节中，我们完成了刷新和置顶按钮的基本布局。但目前按钮还有几个问题：

- 按钮是方形的，而图标是圆形，看起来不协调
- 悬浮状态没有高亮效果
- 没有绑定具体的点击逻辑

这一节我们完善这两个按钮的**样式**和**交互**，并通过信号槽绑定为后续功能预留接口。

我们在 `HomePageWidget::initRefreshAndTopBtn()` 方法中，为刷新与置顶按钮的父容器添加统一的样式，让按钮圆形化，并设置悬停高亮。

```c++
void HomePageWidget::initRefreshAndTopBtn()
{
    // 创建刷新和置顶按钮的容器 QWidget
    QWidget *refreshTopWidget = new QWidget(this);
    refreshTopWidget->setFixedSize(42, 94);

    // 给父容器内所有 QPushButton 设置统一样式
    refreshTopWidget->setStyleSheet(
        "QPushButton {"
        "    border-radius: 21px;"          // 圆角，半径=宽度/2
        "    border: none;"                 // 去掉边框
        "    background-color: #DDDDDD;"    // 默认背景色
        "}"
        "QPushButton:hover {"
        "    background-color: #666666;"    // 悬停高亮
        "}"
    );

    // 创建垂直布局器，放置两个按钮
    QVBoxLayout *layout = new QVBoxLayout(refreshTopWidget);

    // 置顶按钮
    QPushButton *topBtn = new QPushButton(refreshTopWidget);
    topBtn->setFixedSize(42, 42);
    topBtn->setStyleSheet("border-image: url(:/images/homePage/zhiding.png);");
    layout->addWidget(topBtn);

    // 刷新按钮
    QPushButton *refreshBtn = new QPushButton(refreshTopWidget);
    refreshBtn->setFixedSize(42, 42);
    refreshBtn->setStyleSheet("border-image: url(:/images/homePage/shuaxin.png);");
    layout->addWidget(refreshBtn);

    // 去掉内边距 & 设置按钮间距
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);

    // **绝对定位**：将按钮固定在首页右下角
    refreshTopWidget->move(1278, 618);

    // 绑定信号槽
    connect(topBtn, &QPushButton::clicked, this, &HomePageWidget::onTopBtnClicked);
    connect(refreshBtn, &QPushButton::clicked, this, &HomePageWidget::onRefreshBtnClicked);
}
```

**为什么使用绝对定位**

刷新与置顶按钮的功能是**悬浮**，它们应该固定在界面右下角，不随页面滚动而移动。

如果把它们放进主布局中，随着页面滚动时它们会跟着动，这显然不符合预期。因此我们不使用 `QLayout` 管理这两个按钮，而是直接调用 `move(x, y)`，将容器固定在指定坐标：

```c++
refreshTopWidget->move(1278, 618);
```

这样无论页面滚动多少，两个按钮都能保持在固定位置。

**圆形按钮与悬停高亮**

虽然按钮贴了圆形图片，但如果不设置 `border-radius`，按钮本身仍然是方的。鼠标移上去时，悬浮区域会是矩形，视觉上会很违和。

因此我们在容器的样式里统一设置：

```c++
QPushButton {
    border-radius: 21px;    /* 半径=42/2，刚好是圆形 */
    border: none;
    background-color: #DDDDDD;
}

QPushButton:hover {
    background-color: #666666;
}
```

这样不仅解决了圆角问题，还让悬浮时有高亮反馈，更符合现代 UI 设计习惯。

**点击事件与日志测试**

目前我们还没有实现回到顶部和刷新列表的逻辑，但可以先通过日志验证点击事件是否正常触发：

```c++
void HomePageWidget::onTopBtnClicked()
{
    LOG() << "置顶";
}

void HomePageWidget::onRefreshBtnClicked()
{
    LOG() << "刷新";
}
```

运行程序后点击按钮，如果控制台打印出对应日志，说明信号槽绑定成功。

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202508291727352.png" style="width:90%;">
   			</td>
   		</tr>
           <tr><td><strong>绑定效果</strong></td></tr>
   	</tbody>
   </table>


### VideoBox 布局

在完成了顶部导航、刷新与置顶按钮后，首页还缺少最核心的一块：**视频内容展示区**。
 这一块的任务是将服务器返回的视频数据，以统一且美观的方式呈现在首页。

我们会抽象出一个通用的组件——`VideoBox`，用来展示每一个视频的信息。

#### VideoBox 显示的内容

根据设计图，每一个视频卡片需要展示以下信息：

- **视频封面图 / 首帧图**
   用于直观展示视频内容，通常是用户上传的封面图，也可能是自动截取的首帧图。
- **视频基本信息**
   包括：
  - 视频播放量
  - 点赞数量
  - 视频总时长
- **视频标题**
   突出展示，帮助用户快速了解内容。
- **上传用户的信息**
   包括：
  - 用户头像
  - 用户昵称
  - 上传时间

#### VideoBox 的布局设计

VideoBox 的结构可以分为三大块，从上到下依次是：

```
┌────────────────────┐
│ 视频封面图         │  ← 上方图片区域（覆盖宽度）
│  └── 视频基本信息  │  ← 封面图右下角悬浮
├────────────────────┤
│ 视频标题           │  ← 单行或两行显示
├────────────────────┤
│ 用户头像 昵称 时间 │  ← 水平布局组织
└────────────────────┘
```

更具体的布局思路：

- **外层容器**：
   使用一个垂直布局（`QVBoxLayout`）组织三个大区域。
- **封面图区域**：
   最上方用一个 `QLabel` 显示封面图；
   封面图内部再嵌一个水平布局器，用于展示播放量、点赞量、总时长。
- **视频标题**：
   单独占据一行，文本从服务器动态填充。
- **上传用户信息**：
   用一个水平布局器，放置用户头像、昵称、上传时间。

此外，`VideoBox` 组件不仅会在首页使用，在“我的页面”里也会复用。
 但“我的页面”对视频信息的显示略有不同：

| **模块**     | **首页** | **我的页面** |
| ------------ | -------- | ------------ |
| 视频封面图   | 显示     | 显示         |
| 视频基本信息 | 显示     | **隐藏**     |
| 视频标题     | 显示     | 显示         |
| 上传用户信息 | 显示     | 显示         |
| 删除按钮     | **隐藏** | **显示**     |

> **设计思路**
>  我们在 `VideoBox` 内部把所有元素都设计好，然后根据不同场景（首页 / 我的页面）来控制某些元素的显示与隐藏。
>  这样不仅减少代码重复，还能保持统一的 UI 风格。

#### VideoBox 实现

**1. 创建VideoBox类**

首先，在 Qt Creator 中添加一个新的 **Qt Designer 界面类**，我们选择“带有 UI 的 QWidget”，这样既可以设计界面，又能在 C++ 类中控制逻辑。

我们把类命名为 **`VideoBox`**，Qt 会自动生成以下三个文件：

```
videobox.h
videobox.cpp
videobox.ui
```

接下来，我们会在 `.ui` 文件中完成布局设计。

**2. 设置 VideoBox 的整体尺寸**

根据设计图，单个视频卡片的推荐大小是：

- **宽度**：`310px`
- **高度**：`257px`

这个尺寸能在一行容纳三列 `VideoBox`，视觉上比较协调。

在 Qt Designer 中选中根部的 `VideoBox`，在属性面板中设置：

```
minimumWidth  = 310
maximumWidth  = 310
minimumHeight = 257
maximumHeight = 257
```

这样就锁定了组件的尺寸。

**3. 三段式布局：封面图、视频标题、用户信息**

根据之前的分析，`VideoBox` 从上到下分为三块：

| 区域       | 内容                        | 布局方式 | 高度 |
| ---------- | --------------------------- | -------- | ---- |
| **封面图** | 视频封面 / 视频基本信息叠加 | 垂直布局 | 自动 |
| **标题区** | 视频标题                    | 固定高度 | 42px |
| **用户区** | 用户头像、昵称、上传时间    | 水平布局 | 19px |

在 Qt Designer 中拖拽三个 `QWidget`，从上到下放入 `VideoBox`，然后在外层设置 **垂直布局**（`QVBoxLayout`），最后将 `margin` 和 `spacing` 全部设为 `0`。

为了方便调试，可以给三个区域分别设置临时背景色，例如：

```css
#coverBox { background-color: #f8d7da; }
#titleBox { background-color: #d1ecf1; }
#userBox  { background-color: #d4edda; }
```

**4. 封面图区域：叠加视频基本信息**

封面图是 VideoBox 最显眼的部分，我们会在上方的 `coverBox` 内放置一个 `QLabel`，用于展示封面图。
 此外，封面图底部还需要叠加一条视频基本信息栏，包括：

- 播放量
- 点赞数
- 总时长

**步骤**：

1. **封面图 QLabel**
   - 拖一个 `QLabel` 到 `coverBox`
   - `objectName` 命名为 `coverLabel`
   - 设置 `scaledContents = true`，保证封面图等比缩放。
2. **视频基本信息容器**
   - 在 `coverBox` 中再添加一个 `QWidget`
   - 命名为 `videoInfoBox`
   - 设置 **水平布局**（`QHBoxLayout`）
   - 把 `margin` 和 `spacing` 都设为 `0`
   - 这个容器会固定在封面图底部，稍后我们用弹簧把它压下去。
3. **添加一个垂直弹簧**
   - 在 `videoInfoBox` 上方拖拽一个 **垂直弹簧**
   - 作用是把 `videoInfoBox` 固定到底部。

**5. 视频基本信息的实现**

`videoInfoBox` 中一共有三组信息：播放量、点赞数、总时长。
 每组信息采用同样的结构：**小图标 + 数字**。

**步骤**

1. **播放量区域**
   - 拖一个 `QWidget`，命名为 `playBox`
   - 设置 **水平布局**（`QHBoxLayout`）
   - 固定宽度 `100px`
   - 在内部放置：
     - 一个 `QLabel`（图标）：`playIcon`
     - 一个 `QLabel`（数字）：`playCount`
   - 暂时填入示例文本，比如“26.1万”。
2. **点赞数区域**
   - 方法同上，命名为 `likeBox`
   - 内部有：
     - 图标：`likeIcon`
     - 数字：`likeCount`
   - 示例数据：“1226”。
3. **总时长区域**
   - 命名为 `timeBox`
   - 内部有：
     - 图标：`timeIcon`
     - 文本：`videoDuration`
   - 示例数据：“12:34”。

**临时样式**

在 `videoInfoBox` 的三组小组件里，我们可以先用不同背景色区分，方便调试：

```css
#playBox { background-color: #fff3cd; }
#likeBox { background-color: #cce5ff; }
#timeBox { background-color: #e2e3e5; }
```

**6. 视频标题区**

中间的 `titleBox` 用于展示视频标题：

- 添加一个 `QLabel`，命名为 `titleLabel`
- 属性设置：
  - **最大行数**：两行
  - **自动换行**：`true`
  - **对齐方式**：`Qt::AlignLeft | Qt::AlignTop`
- 示例文本：“北京三日自由行 Vlog｜故宫 & 长城 & 后海”

**7. 用户信息区**

最底部的 `userBox` 展示上传用户的信息，包括：

- 用户头像
- 用户昵称
- 上传时间

**步骤**

1. **用户头像**
   - 拖一个 `QLabel`，命名为 `avatarLabel`
   - 固定大小 `20x20`
   - 设置圆角显示（后续在 QSS 中处理）。
2. **用户昵称**
   - 添加 `QLabel`，命名为 `nicknameLabel`
   - 示例填“旅行家小王”。
3. **上传时间**
   - 添加 `QLabel`，命名为 `uploadTimeLabel`
   - 示例填“3天前”。
4. **水平布局**
   - 将三者放入一个 `QHBoxLayout`
   - `margin` 和 `spacing` 都设为 `0`。

**8. 布局、样式与资源绑定**

**添加视频时长显示**

视频时长位于封面图的右下角，通过一个 `QLabel` 来实现。

**步骤**

1. 拖拽一个 `QLabel` 到 `timeBox` 内。

2. 修改 `objectName` 为 **timeLabel**。

3. 设置默认文本：

   ```
   25:52
   ```

4. 调整 `timeBox` 的布局，确保时长信息在右侧靠齐。

5. 设置 `timeLabel` 的最小和最大高度，保持与图标统一。

**视频标题与自动换行**

视频标题可能很长，一行无法展示完整，因此我们需要让 `QLabel` 自动换行。

**操作步骤**

1. 拖拽一个 `QLabel` 到 `videoTitleBox`。

2. 修改 `objectName` 为 **videoTitle**。

3. 设置测试文本：

   ```
   北京旅游攻略 | 一条视频告诉你去了北京该怎么玩
   ```

4. 在右侧属性面板中，勾选 **wordWrap** 属性，让标题自动换行。

5. 设置 `videoTitleBox` 的 `minimumHeight` 和 `maximumHeight`，统一高度为 `42px`。

**添加用户信息与删除按钮**

最下方的 `userBox` 显示 **用户头像、昵称、上传时间**，并在右侧放置一个 **删除按钮**。

**用户信息布局**

1. 拖拽三个 `QLabel` 到 `userBox`：
   - **userIcon**：显示用户头像
   - **userNick**：显示用户昵称
   - **uploadTime**：显示视频上传时间
2. 设置宽高：
   - `userIcon`：`18x18`
   - `userNick` 和 `uploadTime` 自动填充剩余空间
3. 拖拽一个 **水平弹簧** 到最右侧，把用户信息挤到左边。

**删除按钮**

1. 拖拽一个 `QPushButton` 到 `userBox` 的最右侧。

2. 修改 `objectName` 为 **delVideoBtn**。

3. 去掉按钮文本，改为图标：

   ```css
   #delVideoBtn {
       border: none;
       background-color: transparent;
       background-image: url(:/images/homePage/delete.png);
       background-repeat: no-repeat;
       background-position: center;
   }
   ```

4. 统一设置按钮大小：

   ```c++
   delVideoBtn->setFixedSize(24, 24);
   ```

**为播放量、点赞量、时长绑定图标**

播放量、点赞量、视频时长都需要直观的图标。我们统一使用资源路径：

```css
#playIcon {
    image: url(:/images/homePage/play.png);
    width: 20px;
    height: 20px;
}

#likeIcon {
    image: url(:/images/homePage/like.png);
    width: 20px;
    height: 20px;
}

#timeIcon {
    image: url(:/images/homePage/time.png);
    width: 20px;
    height: 20px;
}
```

通过样式表可以避免直接在代码中频繁设置图片路径。

**样式表统一管理**

为了让 UI 更整洁，所有颜色、字体、间距统一在 `.qss` 中集中管理。

**VideoBox 样式**

```css
/* VideoBox 背景 */
#videoBox {
    background-color: #FFFFFF;
    border-radius: 8px;
}

/* 视频标题 */
#videoTitle {
    color: #333333;
    font-size: 16px;
    font-weight: bold;
    font-family: "Microsoft YaHei";
}

/* 用户昵称、上传时间 */
#userBox QLabel {
    color: #999999;
    font-size: 14px;
    font-family: "Microsoft YaHei";
}

/* 删除按钮 */
#delVideoBtn {
    border: none;
    background-color: transparent;
    background-image: url(:/images/homePage/delete.png);
    background-repeat: no-repeat;
    background-position: center;
}
#delVideoBtn:hover {
    background-color: #F5F5F5;
    border-radius: 4px;
}
```

这样，当我们以后需要修改颜色或字体时，只需要调整 `.qss` 文件。

效果图：

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202508301759932.png" style="width:60%;">
   			</td>
   		</tr>
           <tr><td><strong>VideoBox实现效果</strong></td></tr>
   	</tbody>
   </table>

#### 视频首页布局与滚动条样式优化

在完成 `VideoBox` 组件的设计之后，我们需要将其添加到首页的视频显示区域，并为右侧滚动条设置自定义样式，以提升整体观感和交互体验。

**在首页添加视频卡片**

在首页中，我们通过栅格布局（`QGridLayout`）来展示视频卡片。为了方便测试，先一次性添加 16 个 `VideoBox`：

```c++
// homepagewidget.cpp

void HomePageWidget::initVideos()
{
    for (int i = 0; i < 16; ++i)
    {
        VideoBox *videoBox = new VideoBox();
        // 一行显示 4 个视频
        ui->videoGLayout->addWidget(videoBox, i / 4, i % 4);
    }
}
```

**关键点**

- 首页中的视频以 **4 列**排布
- 行号 = `i / 4`，列号 = `i % 4`
- 这种写法非常直观，方便日后扩展，比如改为每行 5 个视频，只需要修改除数即可

在构造函数中调用 `initVideos()`，运行后即可在首页看到 16 个 `VideoBox`。

**设置视频区域背景**

视频展示区使用 `QScrollArea` 承载，因此我们先把滚动区域的背景设置为白色，让整体视觉更清爽：

```css
#videoScroll {
    border: none;
    background-color: #FFFFFF;
}
```

**自定义滚动条样式**

右侧滚动条是 `QScrollBar` 控件，我们可以通过 QSS 对其进行美化。

1. 垂直滚动条主体

   ```css
   QScrollBar:vertical {
       border: none;
       background-color: #FFFFFF;
       width: 10px;  /* 滚动条整体宽度 */
   }
   ```

   这里设置了滚动条整体的宽度为 10px，并去掉了边框。

2. 滚动条滑块（handle）

   ```css
   QScrollBar::handle:vertical {
       border: none;
       border-radius: 5px;              /* 圆角滑块 */
       background-color: #E8E8E8;       /* 浅灰色手柄 */
       min-height: 134px;               /* 限制最小高度 */
   }
   ```

   > **心得**
   >  圆角半径最好不要超过宽度或高度的一半，否则会导致显示异常。
   >  本例中宽度 10px，因此设置半径 5px 最合适。

3. 去掉上下箭头

   Qt 默认在滚动条两端会显示上下箭头，但这里我们不需要，直接隐藏：

   ```css
   QScrollBar::up-arrow:vertical,
   QScrollBar::down-arrow:vertical {
       border: none;
       width: 0px;
       height: 0px;
   }
   ```

   这样，滚动条就只剩一个干净的滑块，视觉上更加现代。

4. 右侧边距优化

   运行程序后发现滚动条和窗口右边缘距离太近，可以在外层布局中给右侧加一点 `margin`：

   ```c++
   ui->videoScroll->setContentsMargins(0, 0, 3, 0);
   ```

   经过调整，给右侧留出 3px 空隙，既不会显得太拥挤，也不会浪费过多空间。

#### VideoBox 点击播放与删除按钮控制

在上一节中，我们实现了 **首页视频区域** 的栅格布局，完成了 `VideoBox` 的批量创建与显示。
 本节主要处理两个问题：

1. **删除按钮的显示控制**
2. **视频封面与标题的点击事件处理**

**1. 删除按钮默认隐藏**

在首页中展示的视频通常不是用户本人上传的，因此不能允许删除；
 而在“我的页面”中，视频是用户本人上传的，才允许删除。

所以我们需要在 `VideoBox` 构造函数中，将删除按钮默认隐藏：

```c++
VideoBox::VideoBox(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoBox)
{
    ui->setupUi(this);

    // 删除按钮默认隐藏（仅“我的页面”显示）
    ui->delVideoBtn->hide();
}
```

如果在“我的页面”中需要显示删除按钮，可以在后续逻辑中通过 `ui->delVideoBtn->show()` 来控制。

**2. 给视频封面和标题添加点击事件**

视频封面和标题使用的是 `QLabel`，默认情况下 **不响应鼠标点击**，
 因此我们需要通过 **事件过滤器** 来拦截鼠标点击事件。

1. 安装事件过滤器

   在 `VideoBox` 构造函数中，我们已经给封面图 `imageBox` 和标题 `videoTittle` 安装了过滤器：

   ```
   ui->imageBox->installEventFilter(this);
   ui->videoTittle->installEventFilter(this);
   ```

   这样，所有发往这两个控件的事件都会先经过 `VideoBox::eventFilter()` 方法。

2. 重写 `eventFilter()`

   在 `videobox.cpp` 中实现事件拦截：

   ```c++
   bool VideoBox::eventFilter(QObject *watched, QEvent *event)
   {
       // 只处理视频封面或标题的点击事件
       if (ui->imageBox == watched || ui->videoTittle == watched) {
           // 判断事件类型是否是鼠标点击
           if (event->type() == QEvent::MouseButtonPress) {
               // TODO: 将来在这里跳转到播放页面
               LOG() << "打开播放窗口";
               return true; // 事件已处理
           }
       }
   
       // 其他事件交给父类处理
       return QObject::eventFilter(watched, event);
   }
   ```

效果演示：

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202508301912921.png" style="width:60%;">
   			</td>
   		</tr>
           <tr><td><strong>视频点击效果</strong></td></tr>
   	</tbody>
   </table>

## 播放页布局

### 播放页面布局设计：分区、控件与自定义组件

当用户在首页或“我的页面”中点击视频封面或标题时，我们会进入视频播放页面。
 播放页面的布局相对复杂，涉及弹幕、播放控制、用户信息等多个功能区。
 在这一节，我们将梳理 **播放页面的布局结构** 和 **涉及的控件设计**。

**1. 播放页面的整体结构**

从设计图来看，播放页面可以划分为 **三个主要区域**：

1. **页面标题栏**
2. **视频画面与弹幕区**
3. **播放控制与视频信息区**

整体采用 **垂直布局（QVBoxLayout）**，每个区域内部再使用水平布局或嵌套布局来安排控件。

```
┌──────────────────────────┐
│          页面标题栏       │  ← 顶部：视频标题 + 系统按钮
├──────────────────────────┤
│      视频画面 + 弹幕区    │  ← 中间：视频播放 + 三行弹幕
├──────────────────────────┤
│ 播放控制区 + 用户信息区等 │  ← 底部：播放按钮、弹幕输入、音量调节、视频信息
└──────────────────────────┘
```

**2. 页面标题栏（顶部区域）**

标题栏分为两部分：

- **左侧**：视频标题（`QLabel`）
- **右侧**：系统按钮区（最小化、最大化、关闭按钮）

通常使用 **水平布局（QHBoxLayout）** 实现。

**3. 视频画面与弹幕区（中间区域）**

中间区域主要用于显示 **视频画面** 和 **弹幕**，其中弹幕分为三行：

- **最上行弹幕**
- **中间行弹幕**
- **最低行弹幕**

视频画面部分使用自定义控件承载视频播放功能，
 弹幕层叠在视频之上，因此需要用到 **层叠布局**。

弹幕内容会从服务器动态获取，后续实现时需要处理弹幕的创建、更新和渲染。

**4. 播放控制与视频信息区（底部区域）**

底部区域是整个页面最复杂的部分，主要包含四块内容：

1. 播放进度条区

   - 使用自定义进度条控件（因为内置 `QSlider` 风格不符合需求）
   - 显示当前播放时间与总时长

2. 播放控制区

   播放控制区采用 **水平布局**，包含以下元素：

   | 控件          | 类型           | 功能           |
   | ------------- | -------------- | -------------- |
   | 播放/暂停按钮 | `QPushButton`  | 控制视频播放   |
   | 当前播放时间  | `QLabel`       | 显示当前时间   |
   | 总时长        | `QLabel`       | 显示视频总时长 |
   | 弹幕开关      | `QPushButton`  | 开启或关闭弹幕 |
   | 弹幕编辑框    | `QLineEdit`    | 输入弹幕内容   |
   | 发送弹幕按钮  | `QPushButton`  | 提交弹幕       |
   | 倍速播放      | 自定义下拉菜单 | 调整播放速度   |
   | 音量调节      | 自定义控件     | 控制视频音量   |

3. 用户信息区

   位于播放控制区下方，采用 **水平布局**，展示视频相关信息：

   - 用户头像（`QLabel` + 图片）
   - 用户昵称（`QLabel`）
   - 上传时间（`QLabel`）
   - 播放量（图标 + 数字）
   - 点赞量（图标 + 数字）

4. 视频简介区

   最后一块区域用于显示视频简介，支持自动换行。

**5. 自定义控件**

在播放页面中，以下控件需要自定义：

- **视频播放控件**：负责视频解码与渲染
- **进度条控件**：自定义样式，替换默认 `QSlider`
- **弹幕层**：用于在视频上方动态绘制弹幕
- **倍速播放弹窗**：自定义下拉窗口
- **音量调节控件**：自定义音量滑块与图标

这些自定义控件会在后续实现中逐一拆解。

### 播放页面布局实现

在前面我们分析了播放页面的布局和功能区，这一节开始正式在 **Qt Designer** 中实现页面的初步框架。
 目标是创建一个名为 **PlayerPage** 的界面，搭建出三大区域：

1. 顶部标题栏（playHead）
2. 视频显示与弹幕区（screen）
3. 播放控制与视频信息区（playControlBox）

接下来按照步骤完成。

**1. 创建 PlayerPage 设计师界面**

首先，新建一个 Qt Designer 界面文件：

- 文件类型：**QWidget**
- 命名为：`PlayerPage`
- 设置 **geometry**：宽 `1450`，高 `860`

在属性面板中确认修改后，保存到 `ui/playerpage.ui`。

**2. 搭建整体框架（三大区域）**

在 PlayerPage 中，拖拽 **三个 QWidget**，上下排列：

| 顺序 | objectName       | 说明         | 背景色             |
| ---- | ---------------- | ------------ | ------------------ |
| 1    | `playHead`       | 顶部标题栏   | `rgb(0, 0, 0)`     |
| 2    | `screen`         | 视频显示区   | `rgb(170,170,127)` |
| 3    | `playControlBox` | 底部控制区域 | `rgb(0, 0, 0)`     |

完成后，选中 **PlayerPage** → 点击 **垂直布局**。
 然后在右侧属性栏将 `Margin` 和 `Spacing` **全部设置为 0**。

接着设置高度约束：

- `playHead`：`minimumSize` 和 `maximumSize` 的 **高度**均设为 `60`
- `playControlBox`：`minimumSize` 和 `maximumSize` 的 **高度**均设为 `186`

这样，三大区域的高度结构已经固定，页面骨架完成。

**3. 顶部标题栏（playHead）**

在 `playHead` 中添加以下控件：

- **QLabel** → `objectName = videoTittle`
  - 背景色：`rgb(255,255,255)`
  - 用于显示视频标题
- **QWidget** → `objectName = sysBtnBox`
  - 背景色：`rgb(170,170,255)`
  - 系统按钮容器

完成后选中 `playHead` → 点击 **水平布局**。

再设置布局属性：

- `playHead.leftMargin = 13`
- 其他 `Margin` 和 `Spacing` = `0`
- `sysBtnBox.minimumSize.width = 112`
- `sysBtnBox.maximumSize.width = 112`

**4. 系统按钮区（sysBtnBox）**

在 `sysBtnBox` 内添加两个按钮，左右排列：

| 顺序 | objectName | 功能     |
| ---- | ---------- | -------- |
| 1    | `minBtn`   | 最小化   |
| 2    | `quitBtn`  | 关闭页面 |

再选中 `sysBtnBox` → 点击 **水平布局**。
 设置布局参数：

- `sysBtnBox.rightMargin = 31`
- 其他 `Margin = 0`
- `Spacing = 36`
- `minBtn` 和 `quitBtn` 的 `minimumSize`、`maximumSize` **统一为 (20, 20)`

最终，顶部标题栏就搭建完成。

**5. 底部播放控制区（playControlBox）**

`playControlBox` 内部由四个功能区组成，从上到下依次为：

| 顺序 | objectName          | 功能区       | 背景色             |
| ---- | ------------------- | ------------ | ------------------ |
| 1    | `videoSlider`       | 播放进度条区 | `rgb(170,255,255)` |
| 2    | `playControl`       | 播放按钮区   | `rgb(255,170,127)` |
| 3    | `videoInfoBox`      | 视频信息区   | `rgb(255,170,255)` |
| 4    | `videoIntroduceBox` | 视频简介区   | `rgb(85,170,255)`  |

完成后，选中 **playControlBox** → 点击 **垂直布局**，并将 `Margin` 和 `Spacing` **全部设置为 0**。

再设置高度：

- `videoSlider`：高度 `30`
- `playControl`：高度 `32`
- `videoInfoBox`：高度 `60`
- `videoIntroduceBox`：自适应剩余空间

#### 播放控制区实现

在完成了 **PlayerPage** 播放页面的整体框架之后，接下来我们专注于底部的 **播放控制区（playControlBox）**，为视频播放、弹幕、倍速、音量等功能预留交互入口。

**1. 布局拆分：playControl 四大子区**

在 **playControl** 区域内，我们需要左右依次放置四个功能模块：

| 模块       | objectName        | 功能                | 背景色 (示例)    |
| ---------- | ----------------- | ------------------- | ---------------- |
| 播放时间区 | `playTimeBox`     | 播放按钮 + 时间显示 | rgb(0,170,127)   |
| 弹幕输入区 | `bulletScreenBox` | 弹幕开关 + 输入框   | rgb(170,255,127) |
| 播放倍速区 | `speedBox`        | 倍速切换按钮        | rgb(170,85,127)  |
| 音量控制区 | `volumeBox`       | 静音/音量按钮       | rgb(255,85,127)  |

操作步骤：

1. 在 `playControl` 中拖拽 **4 个 QWidget**，左右依次摆放。
2. 修改 `objectName`，按上表命名。
3. 分别为每个模块设置不同背景色，便于开发阶段区分。
4. 选中 `playControl`，点击 **水平布局**。
5. 设置边距：
   - `LeftMargin = 30`
   - `RightMargin = 30`
   - 其他 `Margin` = 0
   - `Spacing` = 0

**2. playTimeBox：播放按钮 + 时间显示**

该区域主要包括播放/暂停按钮和视频播放时间。

结构：

| 控件         | objectName      | 作用                 | 最小/最大尺寸 |
| ------------ | --------------- | -------------------- | ------------- |
| 播放按钮     | `playBtn`       | 控制播放/暂停        | (26, 26)      |
| 视频时长标签 | `videoDuration` | 显示 `28:58 / 39:32` | 自适应        |

操作步骤：

1. 在 `playTimeBox` 中拖拽 **QPushButton** 和 **QLabel**，水平摆放。

2. 修改 `objectName`：

   - 播放按钮 → `playBtn`
   - 时间标签 → `videoDuration`

3. 清空 `playBtn` 的文本，后续会贴图标。

4. 将 `videoDuration` 的初始文本设置为示例：

   ```
   28:58 / 39:32
   ```

5. 选中 `playTimeBox` → **水平布局**。

6. 设置边距与间距：

   - `Margin` = 0
   - `Spacing` = 10

7. 调整 `playBtn` 的最小/最大宽高为 `(26, 26)`。

**3. bulletScreenBox：弹幕输入与开关**

该区域用于开启/关闭弹幕和输入弹幕文本。

结构：

| 控件         | objectName         | 作用         | 最小/最大尺寸 |
| ------------ | ------------------ | ------------ | ------------- |
| 弹幕开关按钮 | `bulletScreenBtn`  | 控制弹幕显示 | (26, 26)      |
| 弹幕输入框   | `bulletScreenText` | 输入弹幕内容 | 自适应        |

操作步骤：

1. 在 `bulletScreenBox` 中拖拽 **QPushButton** + **QLineEdit**，水平摆放。
2. 修改 `objectName`：
   - 弹幕开关按钮 → `bulletScreenBtn`
   - 弹幕输入框 → `bulletScreenText`
3. 清空 `bulletScreenText` 默认文本。
4. 选中 `bulletScreenBox` → **水平布局**。
5. 设置边距与间距：
   - `LeftMargin = 30`
   - 其他 `Margin` = 0
   - `Spacing = 30`
6. 调整 `bulletScreenBtn` 的最小/最大宽高为 `(26, 26)`。

**4. speedBox：倍速切换按钮**

该区域只有一个按钮，用于切换播放速度。

操作步骤：

1. 在 `speedBox` 中拖拽 **QPushButton**。
2. 修改 `objectName` 为 `speedBtn`。
3. 将按钮文本设置为 **“倍数”**。
4. 选中 `speedBox` → **水平布局**。
5. 设置边距与间距：
   - 所有 `Margin` = 0
   - `Spacing` = 0
6. 调整 `speedBtn` 的最小/最大尺寸为 `(32, 21)`。

**5. volumeBox：音量控制按钮**

最后一个区域预留静音/音量切换功能。

操作步骤：

1. 在 `volumeBox` 中拖拽 **QPushButton**。
2. 修改 `objectName` 为 `volumeBtn`。
3. 清空按钮文本，后续将贴图标。
4. 选中 `volumeBox` → **水平布局**。
5. 设置边距与间距：
   - `LeftMargin = 0`
   - `Spacing = 0`
6. 调整 `volumeBtn` 的最小/最大尺寸为 `(26, 26)`。

**6. 最终效果**

完成上述步骤后，**playControl** 区域的基本 UI 框架如下：

```
[ 播放按钮 | 时间 ]   [ 弹幕开关 | 弹幕输入框 ]   [ 倍数按钮 ]   [ 音量按钮 ]
```

功能区域已经清晰划分，尺寸和布局统一，后续会继续实现以下功能：

- 为播放按钮、音量按钮、弹幕按钮添加 **图标资源**。
- 在代码中绑定播放状态、音量调节、弹幕发送等逻辑。
- 与视频播放器内核联动，更新播放时长和弹幕状态。

#### 视频信息区与简介区实现

在完成 **播放控制区** 的布局后，接下来需要设计 **视频信息区 (videoInfoBox)** 和 **视频简介区 (videoIntroduceBox)**。
 这两部分主要用于展示视频上传者信息、播放量、点赞数以及视频的详细简介。

**1. 视频信息区 (videoInfoBox) 整体布局**

在 `videoInfoBox` 中，我们需要放置三个主要子模块，左右排列：

| 模块       | objectName   | 功能                     | 背景色(开发阶段区分) |
| ---------- | ------------ | ------------------------ | -------------------- |
| 视频信息   | `videoInfo`  | 用户头像、昵称、上传时间 | rgb(170,85,255)      |
| 播放量统计 | `playNumBox` | 播放次数                 | rgb(255,170,127)     |
| 点赞统计   | `likeNumBox` | 点赞按钮与数量           | rgb(170,170,0)       |

操作步骤：

1. 在 `videoInfoBox` 中拖拽 **3 个 QWidget**，左右依次摆放。
2. 修改 `objectName`，按上表命名。
3. 分别为三个区域设置背景色，方便调试。
4. 选中 `videoInfoBox` → **水平布局**。
5. 设置 `videoInfoBox` 的边距与间距：
   - `Margin = 0`
   - `Spacing = 0`
6. 设置子模块的宽度：
   - `videoInfo` → `minimumSize` / `maximumSize` 宽度 = **310**
   - `playNumBox` → `minimumSize` / `maximumSize` 宽度 = **114**

**2. videoInfo：用户信息模块**

该模块显示上传者头像、昵称和上传时间。

结构：

| 控件     | objectName     | 功能           | 初始文本         | 最小/最大尺寸 |
| -------- | -------------- | -------------- | ---------------- | ------------- |
| 用户头像 | `userAvatar`   | 上传者头像按钮 | 清空             | (26, 26)      |
| 用户昵称 | `userNikeName` | 上传者昵称     | “昵称名称用户名” | 宽度 126      |
| 上传时间 | `loadupTime`   | 上传时间       | “9-16 12:28:58”  | 自适应        |

操作步骤：

1. 在 `videoInfo` 中拖拽 **1 个 QPushButton** + **2 个 QLabel**，水平排列。
2. 修改 `objectName`：
   - 用户头像按钮 → `userAvatar`
   - 用户昵称 → `userNikeName`
   - 上传时间 → `loadupTime`
3. 设置初始文本：
   - `userAvatar` → 清空
   - `userNikeName` → “昵称名称用户名”
   - `loadupTime` → “9-16 12:28:58”
4. 选中 `videoInfo` → **水平布局**。
5. 调整边距与间距：
   - `LeftMargin = 30`
   - 其他 `Margin = 0`
   - `Spacing = 10`
6. 设置尺寸：
   - `userAvatar` → 最小/最大宽高 = **(26, 26)**
   - `userNikeName` → 最小/最大宽度 = **126**

**3. playNumBox：播放量统计模块**

该模块显示视频的播放量。

结构：

| 控件     | objectName     | 功能       | 初始文本 | 最小/最大尺寸 |
| -------- | -------------- | ---------- | -------- | ------------- |
| 图标标签 | `playNumImage` | 播放量图标 | 清空     | (24, 24)      |
| 播放量   | `playNum`      | 播放次数   | “26.1万” | 自适应        |

操作步骤：

1. 在 `playNumBox` 中拖拽 **2 个 QLabel**，水平摆放。
2. 修改 `objectName`：
   - 图标标签 → `playNumImage`
   - 播放量标签 → `playNum`
3. 设置初始文本：
   - `playNumImage` → 清空
   - `playNum` → “26.1万”
4. 选中 `playNumBox` → **水平布局**。
5. 设置边距与间距：
   - `LeftMargin = 35`
   - 其他 `Margin = 0`
   - `Spacing = 7`
6. 设置 `playNumImage` 的最小/最大宽高为 **(24, 24)**。

**4. likeNumBox：点赞统计模块**

该模块包含一个点赞按钮和点赞数量。

结构：

| 控件     | objectName     | 功能         | 初始文本 | 最小/最大尺寸 |
| -------- | -------------- | ------------ | -------- | ------------- |
| 点赞按钮 | `likeImageBtn` | 点赞图标按钮 | 清空     | (24, 24)      |
| 点赞数量 | `likeNum`      | 点赞数       | “1226万” | 自适应        |
| 弹簧     | QSpacerItem    | 靠右布局辅助 | —        | —             |

操作步骤：

1. 在 `likeNumBox` 中拖拽 **1 个 QPushButton** + **1 个 QLabel**，水平排列。
2. 在 `likeImageBtn` 左侧拖入一个 **水平弹簧**，让整个模块靠右。
3. 修改 `objectName`：
   - 点赞按钮 → `likeImageBtn`
   - 点赞数量 → `likeNum`
4. 设置初始文本：
   - `likeImageBtn` → 清空
   - `likeNum` → “1226万”
5. 选中 `likeNumBox` → **水平布局**。
6. 设置边距与间距：
   - `RightMargin = 30`
   - 其他 `Margin = 11`
   - `Spacing = 7`
7. 设置 `likeImageBtn` 的最小/最大宽高为 **(24, 24)**。

**5. videoIntroduceBox：视频简介模块**

该模块显示视频的详细描述。

操作步骤：

1. 在 `videoIntroduceBox` 中拖拽 **1 个 QLabel**。

2. 修改 `objectName` 为 `videoDesc`。

3. 将 `videoDesc` 的初始文本设置为示例：

   ```
   【北京旅游攻略】一条视频告诉你去了北京该怎么玩~
   ```

   （这里示例用了长文本，便于测试自动换行）

4. 选中 `videoIntroduceBox` → **水平布局**。

5. 设置边距与间距：

   - `LeftMargin = 30`
   - `RightMargin = 34`
   - `BottomMargin = 20`
   - `TopMargin = 0`
   - `Spacing = 0`

6. 勾选 `videoDesc` 的 **wordWrap** 属性，使长文本自动换行。

**6. 最终效果**

完成以上步骤后，**视频信息区 + 视频简介区** 的基本 UI 框架就搭建完成了：

```
[ 头像 | 昵称 | 上传时间 ]    [ 播放量图标 | 播放量 ]    [ 点赞按钮 | 点赞数 ]
---------------------------------------------------------------------------
视频简介：一条视频告诉你去了北京该怎么玩~
```

### 播放页面样式美化

在完成播放页面的 UI 布局后，我们需要通过 **Qt 样式表（QSS）** 来优化界面，让播放页面更符合现代视频应用的视觉风格。
 这一节我们将实现以下几件事：

- **统一字体与颜色**
- **设置播放头、控制区、视频标题等样式**
- **给按钮、图标、头像等添加图片**
- **视频信息区和简介的样式微调**

**1. 清理已有的背景颜色**

在设计 UI 时，我们之前在 Qt Designer 中给一些 `QWidget` 设置了背景颜色，但如果继续在样式表中指定样式，这些设置会冲突，导致效果不一致。

因此，在正式应用 QSS 前，**先将所有控件在 Designer 中设置的背景颜色全部清除**，保证样式统一由 QSS 控制。

**2. 播放页面 QSS 样式总览**

整理之后的 QSS 样式如下：

```css
/* 通用字体样式 */
* {
    color: #FFFFFF;                 /* 默认字体白色 */
    font-size: 16px;                /* 默认字体大小 */
    background-color: rgba(0,0,0,0);/* 背景透明，避免冲突 */
}

/* 按钮统一去除边框 */
QPushButton {
    border: none;
}

/* 播放头区域 */
#playHead {
    background-color: #000000;      /* 纯黑背景 */
}

/* 播放控制区 */
#playControlBox {
    background-color: #000000;      /* 控制区纯黑 */
}

/* 视频标题 */
#videoTittle {
    font-size: 24px;                /* 大号字体 */
}

/* 最小化按钮 */
#minBtn {
    border-image: url(":/images/PlayPage/suoxiao.png");
}

/* 关闭按钮 */
#quitBtn {
    border-image: url(":/images/PlayPage/quxiao.png");
}

/* 视频播放区域背景 */
#screen {
    background-color: rgb(0, 85, 127);
}

/* 播放/暂停按钮 */
#playBtn {
    border-image: url(":/images/PlayPage/zanting.png");
}

/* 弹幕开关按钮 */
#bulletScreenBtn {
    border-image: url(":/images/PlayPage/danmu.png");
}

/* 播放速度按钮 */
#speedBtn {
    color: #3ECEFE;                /* 高亮蓝色 */
    font-size: 16px;
}

/* 音量按钮 */
#volumeBtn {
    border-image: url(":/images/PlayPage/shnegyin.png");
}

/* 用户头像按钮 */
#userAvatar {
    border-image: url(":/images/PlayPage/touxiang.png");
}

/* 用户昵称 */
#userNikeName {
    font-size: 18px;
    font-weight: bold;             /* 加粗昵称 */
}

/* 播放量图标 */
#playNumImage {
    border-image: url(":/images/PlayPage/bofangliang.png");
}

/* 点赞按钮 */
#likeImageBtn {
    border-image: url(":/images/PlayPage/dianzan.png");
}

/* 视频描述 */
#videoDesc {
    font-size: 14px;               /* 视频简介较小字体 */
}
```

**说明：**

1. 通过 `*` 选择器统一了字体颜色和大小，避免单独为每个控件重复设置样式。默认使用 **白色字体**，并将控件背景设置为透明，防止与黑色主背景冲突；
2. **播放头** `#playHead` 和 **控制区** `#playControlBox` 都设置了 **纯黑背景**，方便突出视频内容和控制按钮。控制区的播放、弹幕、音量等按钮，全部通过 `border-image` 设置自定义图标；
3. **用户头像**：设置为圆形图片按钮；**用户昵称**：加粗并设置为 18px，视觉上更突出；**播放量 & 点赞**：通过 `border-image` 添加小图标，让 UI 更直观；
4. 视频简介 `#videoDesc` 采用 **14px 较小字体**，在 UI 中不会抢占视频标题的视觉焦点。同时启用 `wordWrap` 属性，让文字在达到容器宽度后自动换行。

通过应用上述样式，播放页面的整体视觉风格趋近于现代视频平台：

- **顶部播放头**：纯黑背景，最小化 & 关闭按钮使用定制图标
- **中部视频区域**：蓝黑背景，更好地突出视频
- **底部控制区**：播放、弹幕、音量、点赞等按钮统一风格
- **视频信息区**：头像、昵称、播放量、点赞量布局整齐
- **视频简介**：自动换行，简洁美观

### 为 VideoBox 添加播放窗口交互逻辑

在完成了 `VideoBox` 组件的布局与样式后，我们开始处理视频播放逻辑。这里的关键是让用户在点击视频封面或标题时，弹出一个无边框、模态的播放窗口，同时支持最小化和关闭操作。

**1. 在 VideoBox 中安装事件过滤器**

我们希望用户点击视频封面或标题时，自动打开播放页面。实现方法是给对应控件安装 **事件过滤器**，在捕获到鼠标点击时调用播放逻辑：

```c++
#include "videobox.h"
#include "ui_videobox.h"
#include "util.h"

VideoBox::VideoBox(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoBox)
{
    ui->setupUi(this);

    // 默认隐藏删除按钮
    ui->delVideoBtn->hide();

    // 创建播放页面
    playPage = new PlayPage();

    // 给视频封面和标题安装事件拦截器
    ui->imageBox->installEventFilter(this);
    ui->videoTittle->installEventFilter(this);
}

VideoBox::~VideoBox() {
    delete ui;
}

bool VideoBox::eventFilter(QObject *watched, QEvent *event)
{
    // 如果点击了封面或标题
    if (ui->imageBox == watched || ui->videoTittle == watched) {
        if (event->type() == QEvent::MouseButtonPress) {
            // 显示播放窗口
            onPlayClicked();
            return true;
        }
    }
    return QObject::eventFilter(watched, event);
}

void VideoBox::onPlayClicked()
{
    playPage->show();
}
```

> **关键点**
>
> - `installEventFilter()`：给控件安装事件过滤器。
> - 重写 `eventFilter()`，在鼠标点击事件触发时打开播放页面。
> - 将播放窗口封装在 `onPlayClicked()` 方法中，便于后续扩展播放逻辑。

**2. 定义 PlayPage 播放窗口**

播放页面使用单独的 `PlayPage` 类实现，并且需要满足以下要求：

- **无边框**：隐藏原生窗口标题栏；
- **模态对话框**：防止用户在播放时去操作其他页面；
- **最小化和关闭按钮**：自定义按钮控制窗口行为。

修改 `playpage.cpp`：

```c++
#include "playpage.h"
#include "ui_playpage.h"

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);

    // 去掉系统边框
    setWindowFlag(Qt::FramelessWindowHint);

    // 设置为模态对话框
    setAttribute(Qt::WA_ShowModal);

    // 绑定最小化和关闭按钮
    connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);
}

PlayPage::~PlayPage()
{
    delete ui;
}
```

> **实现思路**
>
> - `setWindowFlag(Qt::FramelessWindowHint)` 去掉窗口标题栏；
> - `setAttribute(Qt::WA_ShowModal)` 把播放页面设置为模态对话框；
> - 通过 `connect()` 连接自定义最小化与关闭按钮。

**3. 效果**

<table style="border:none;text-align:center;width:auto;margin: 0 auto; padding: 0;">
	<tbody>
   		<tr>
   			<td style="padding: 0;">
   				<img src="https://graphbed-1331926955.cos.ap-shanghai.myqcloud.com/GraphBed/202509011937588.png" style="width:90%;">
   			</td>
   		</tr>
           <tr><td><strong>播放页效果</strong></td></tr>
   	</tbody>
   </table>

### 为 PlayPage 播放窗口添加拖拽功能

在上一节中，我们去掉了播放窗口的边框，并将其设置为无边框、模态对话框。
 但是，Qt 默认的无边框窗口 **不再支持拖拽**，所以需要手动实现标题栏区域的拖拽逻辑。

**1. 功能需求分析**

当用户在播放窗口的 **标题栏区域（`playHead`）** 按住鼠标左键并移动时，我们希望整个窗口跟随鼠标移动。
 这里有几个关键点：

- 拖拽只在标题区域有效，避免误操作；
- 记录鼠标点击位置与窗口左上角的相对偏移量；
- 在鼠标移动时，通过计算 **全局鼠标位置 - 偏移量** 来移动窗口。

**2. 新增成员变量**

在 `playpage.h` 中添加一个变量，用于记录鼠标点击点与窗口左上角的相对偏移：

```c++
private:
    QPoint dragPos;  // 记录鼠标相对窗口的偏移
```

**3. 重写鼠标事件**

在 `playpage.cpp` 中，新增 `mousePressEvent` 和 `mouseMoveEvent` 两个函数：

```c++
#include <QMouseEvent>

// 鼠标按下事件
void PlayPage::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标在窗口内的位置
    QPoint point = event->position().toPoint();

    // 判断鼠标是否在标题栏（playHead）区域
    if (ui->playHead->geometry().contains(point)) {
        // 如果是鼠标左键按下，记录相对偏移
        if (event->button() == Qt::LeftButton) {
            dragPos = event->globalPosition().toPoint() - geometry().topLeft();
            return;
        }
    }

    // 如果不在标题栏，交给父类处理
    QWidget::mousePressEvent(event);
}

// 鼠标移动事件
void PlayPage::mouseMoveEvent(QMouseEvent *event)
{
    // 获取鼠标在窗口内的位置
    QPoint point = event->position().toPoint();

    // 判断鼠标是否在标题栏区域
    if (ui->playHead->geometry().contains(point)) {
        // 鼠标左键按下时才进行拖拽
        if (event->buttons() == Qt::LeftButton) {
            // 移动窗口到新位置：全局坐标 - 偏移量
            move(event->globalPosition().toPoint() - dragPos);
            return;
        }
    }

    QWidget::mouseMoveEvent(event);
}
```

**4. 拖拽逻辑原理**

1. **记录偏移**
   - 当鼠标左键在标题栏按下时，计算鼠标全局坐标与窗口左上角坐标的差值；
   - 这个偏移量在拖拽过程中保持不变。
2. **移动窗口**
   - 鼠标移动时，通过 `event->globalPosition()` 获取鼠标的全局坐标；
   - 用全局坐标减去之前保存的 `dragPos` 偏移量，计算出窗口新的左上角坐标；
   - 调用 `move()` 更新窗口位置。
3. **限制拖拽区域**
   - 拖拽逻辑只在 `playHead` 区域有效，避免误点播放按钮、进度条等控件。

### 自定义视频播放进度条 PlaySlider

在播放页面中，我们希望实现一个简洁、美观、可自定义的视频播放进度条。
 虽然 Qt 提供了 `QSlider` 和 `QProgressBar`，但它们的样式和灵活性无法满足需求，因此我们采用 **自定义进度条控件** 的方式。

**1. 功能需求**

- **展示总时长与播放进度**
   进度条需要同时展示视频的总时长和已播放时长。
- **播放进度动态变化**
   随着视频播放，已播放部分的宽度需要实时更新。
- **统一 UI 风格**
   进度条需要符合播放页面的整体黑底蓝色风格。

最终效果是：

> 一条浅色的总进度背景条（inLine）
>  上面叠加一条蓝色的已播放进度条（outLine）。

**2. 新建自定义控件 PlaySlider**

在 Qt Designer 中创建一个新的 **QWidget 设计师界面**，命名为 **PlaySlider**。
 设置主控件的属性：

- `geometry`: **宽 1450px** × **高 30px**
- `objectName`: `PlaySlider`
- `background-color`: `#000000`（黑色背景）

这将作为我们自定义进度条的容器。

**3. 添加两个 QFrame 作为进度条层**

在 **PlaySlider** 界面中，拖拽两个 `QFrame`，并设置如下属性：

| 属性         | 总时长条 inLine     | 已播放条 outLine    |
| ------------ | ------------------- | ------------------- |
| `objectName` | `inLine`            | `outLine`           |
| `geometry`   | `(0, 13, 1450, 4)`  | `(0, 13, 480, 4)`   |
| `background` | `#EBFAFF`（浅蓝）   | `#3ECEFE`（高亮蓝） |
| `frameShape` | `NoFrame`（无边框） | `NoFrame`（无边框） |

这样，**outLine** 会在 **inLine** 之上，形成进度覆盖效果。

> 注意：这里采用 **绝对布局**，不将两个 QFrame 放入布局器中。
>  如果放入水平布局器，两个进度条会左右分布，而不是上下重叠。

**4. 样式表设置**

在 `PlaySlider.ui` 中，分别设置主控件和两个进度条的样式表：

```css
/* PlaySlider 主控件 */
#PlaySlider {
    background-color: #000000; /* 黑色背景 */
}

/* 总时长进度条 */
#inLine {
    background-color: #EBFAFF; /* 浅蓝底色 */
}

/* 播放进度条 */
#outLine {
    background-color: #3ECEFE; /* 高亮蓝色 */
}
```

#### 在 PlaySlider 中实现 Seek 功能

在上一节中，我们完成了 **自定义进度条 PlaySlider** 的静态效果：

- `inLine` 表示视频总时长；
- `outLine` 表示已播放时长。

这一节要实现的核心是 **Seek 功能**：
 用户可以通过 **点击进度条** 或 **拖拽滑动** 来改变播放进度。

**1. 功能需求分析**

- 鼠标 **单击进度条** → 跳转到点击位置对应的播放进度；
- 鼠标 **按下后拖拽** → 实时更新进度条宽度，松开后确定播放进度；
- 拖动过程中需保证 **进度范围合法**（不能小于 0，也不能超过进度条宽度）。

简单来说：

> Seek 功能的核心就是通过鼠标事件捕获位置，计算新的播放进度，并更新 `outLine` 的宽度。

**2. PlaySlider 新增鼠标事件**

在 `PlaySlider` 中，我们需要重写以下三个事件：

- `mousePressEvent(QMouseEvent *event)` —— 鼠标点击
- `mouseReleaseEvent(QMouseEvent *event)` —— 鼠标释放
- `mouseMoveEvent(QMouseEvent *event)` —— 鼠标拖动

在类中还需要一个成员变量：

```c++
int playProgress;  // 当前播放进度（像素位置）
```

**3. 实现 Seek 功能**

在 `playslider.cpp` 中实现具体逻辑：

```c++
#include "playslider.h"
#include "ui_playslider.h"
#include <QMouseEvent>
#include "util.h"

PlaySlider::PlaySlider(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlaySlider)
{
    ui->setupUi(this);
    playProgress = 0;
}

PlaySlider::~PlaySlider()
{
    delete ui;
}

// 鼠标点击
void PlaySlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        playProgress = event->pos().x();
        moveSlider();
        emit progressChanged(playProgress);
        return;
    }
    QWidget::mousePressEvent(event);
}

// 鼠标释放
void PlaySlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        playProgress = event->pos().x();
        moveSlider();
        emit progressChanged(playProgress);
        return;
    }
    QWidget::mouseReleaseEvent(event);
}

// 鼠标拖拽
void PlaySlider::mouseMoveEvent(QMouseEvent *event)
{
    // 检查鼠标是否在进度条区域内
    if (!this->geometry().contains(event->pos())) {
        LOG() << event->pos();
        return;
    }

    if (event->buttons() == Qt::LeftButton) {
        playProgress = event->pos().x();

        // 防止越界
        if (playProgress < 0)
            playProgress = 0;
        int maxWidth = this->width();
        if (playProgress > maxWidth)
            playProgress = maxWidth;

        moveSlider();
        emit progressChanged(playProgress);
        return;
    }

    QWidget::mouseMoveEvent(event);
}

// 更新 outLine 宽度
void PlaySlider::moveSlider()
{
    ui->outLine->setGeometry(ui->outLine->x(),
                             ui->outLine->y(),
                             playProgress,
                             ui->outLine->height());
}
```

**4. 效果验证**

运行程序后，可以进行以下操作：

- **点击进度条**：蓝色进度条会跳到点击位置；
- **拖动进度条**：蓝色进度条会跟随鼠标实时移动；
- **边界控制**：拖到左侧时归零，拖到右侧时不会超出总宽度。

此时，虽然视频播放功能尚未接入，但进度条本身的交互已经完成。
 后续只需要在 `moveSlider()` 中发出一个 **信号（signal）**，将当前进度传递给播放器，就能真正控制视频跳转。

### 音量调节窗口实现

在播放器中，点击音量按钮后，我们希望弹出一个可交互的音量调节窗口。这个窗口的功能和播放进度条的实现思路类似，但也有一些关键的不同点：

- 播放进度条是**水平**的，而音量滑杆是**垂直**的。
- 播放进度条**一直显示**，而音量调节窗口是**弹出式**的，只有点击音量按钮时才会显示。
- 音量调节窗口的滑杆顶部有一个**圆形按钮**，可以通过拖动该按钮调整音量大小。

**1. 音量调节窗口的设计**

首先，在 Qt Designer 中创建一个新的 UI 文件，命名为 `Volume.ui`，将它设计成一个独立的弹出式小窗口。

1. 基础窗口设置

   - 创建新的 Qt Designer 界面，命名为 **Volume**。

   - 设置窗口大小：`geometry = (0, 0, 60, 164)`。

   - 这个窗口将作为音量调节的弹出界面。

2. 添加背景容器

   - 拖拽一个 `QWidget` 到 `Volume` 窗口中，命名为 **volumeBg**。

   - 选中 `Volume`，点击 **垂直布局**。

   - 将 **Margin** 和 **Spacing** 全部设置为 `0`，保证内容紧贴窗口边界。

3. 添加滑杆容器

   - 在 **volumeBg** 中拖拽一个 `QWidget`，命名为 **volumeBox**。

   - 选中 `volumeBg`，点击 **水平布局**。

   - 设置 **TopMargin** 和 **BottomMargin** 为 `7`，其他 Margin 和 Spacing 均为 `0`。

4. 添加进度条的两层框架

   - 音量显示使用两层 `QFrame` 实现，原理和播放进度条类似：

     - **inLine**：表示音量总高度
       - `objectName = inLine`
       - `geometry = (28, 5, 4, 145)`
       - 可以设置一个浅色背景，比如淡灰色。

     - **outLine**：表示当前音量大小
       - `objectName = outLine`
       - `geometry = (28, 100, 4, 50)`
       - 可以设置一个高亮颜色，比如粉色或绿色。

     + 通过调整 **outLine** 的高度，就能实现音量大小的可视化反馈。

5. 添加音量拖动按钮

   - 为了让用户能够直观地拖动调节音量，在滑杆顶部添加一个圆形按钮：

   - 拖拽一个 `QPushButton` 到 **volumeBox**，命名为 **volumeBtn**。

   - 设置几何属性：
     - `geometry = (25, 95, 10, 10)`

**2. 创建 Volume 界面**

添加一个新的 Qt Designer 界面文件，命名为 `volume.ui`：

- **geometry**：`60 x 164`
- **类名**：`Volume`
- 这个界面本质上是一个小型弹窗，后续会嵌入到播放页面中。

布局结构：

| 元素       | objectName  | 类型        | geometry / 布局                       | 说明                       |
| ---------- | ----------- | ----------- | ------------------------------------- | -------------------------- |
| 背景容器   | `volumeBg`  | QWidget     | 垂直布局，margin=0, spacing=0         | 背景底板                   |
| 内部容器   | `volumeBox` | QWidget     | 水平布局，topMargin=7，bottomMargin=7 | 放置音量条                 |
| 总音量条   | `inLine`    | QFrame      | `[(28,5), 4x145]`                     | 灰色，表示总音量范围       |
| 当前音量条 | `outLine`   | QFrame      | `[(28,100), 4x50]`                    | 蓝色，表示当前音量         |
| 拖拽按钮   | `volumeBtn` | QPushButton | `[(25,95), 10x10]`                    | 圆形按钮，表示当前音量位置 |

> 这里的 `inLine` 和 `outLine` 是两根重叠的竖直 QFrame，通过动态调整高度来反映音量大小。

**3. Volume 样式美化**

在播放器样式文件中加入以下样式：

```css
#volumeBg {
    background-color: #3D3B3B;
    border-radius: 4px;
}

QFrame {
    border-radius: 2px;
}

#inLine {
    background-color: #D8D8D8; /* 总音量 */
}

#outLine {
    background-color: #3ECEFE; /* 当前音量 */
}

#volumeBtn {
    background-color: #D8D8D8;
    border: 1px solid #979797;
    border-radius: 5px; /* 半径=5 => 圆形 */
}
```

💡 **技巧**

- `border-radius` 让控件更圆润
- `#volumeBtn` 的宽高是 `10x10`，半径设置为 `5`，按钮会显示成圆球
- `inLine` 和 `outLine` 颜色对比明显，方便区分总音量与当前音量

**4. 播放页面集成 Volume 窗口**

+ 修改 `playpage.h`

```c++
#include "volume.h"

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayPage(QWidget *parent = nullptr);
    ~PlayPage();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void onVolumeBtnClicked();

private:
    Ui::PlayPage *ui;
    QPoint dragPos;
    Volume* volume; // 音量调节窗口
};
```

+ 修改 `playpage.cpp`

```c++
#include "playpage.h"
#include "ui_playpage.h"
#include <QMouseEvent>

PlayPage::PlayPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::PlayPage)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_ShowModal);

    // 创建音量调节窗口，默认隐藏
    volume = new Volume(this);
    volume->hide();

    // 绑定按钮
    connect(ui->minBtn,   &QPushButton::clicked, this, &QWidget::showMinimized);
    connect(ui->quitBtn,  &QPushButton::clicked, this, &QWidget::close);
    connect(ui->volumeBtn,&QPushButton::clicked, this, &PlayPage::onVolumeBtnClicked);
}

PlayPage::~PlayPage()
{
    delete ui;
}

void PlayPage::onVolumeBtnClicked()
{
    // 点击音量按钮 => 显示音量调节窗口
    volume->show();
}
```







帮我把下面本节课新写的代码和老师课上的讲话结合在一起整理成博客，要注意课上的讲话是通过语音转写成文字的，所以有些转写错误的地方需要对照一下笔记的内容，此外也要避免过多的分点陈述，做好上下文衔接，不要擅自修改板书中的代码：“

板书中的内容：“

\#volumeBg{

​	background-color:#3D3B3B;

​	border-radius:4px;

}



QFrame{

​	border-radius:2px;

}



\#inLine{

​	background-color:#D8D8D8;

}



\#outLine{

​	background-color:#3ECEFE;

}



\#volumeBtn{

​	background-color:#D8D8D8;

​	border:1px solid #979797;

​	border-radius:5px;

}



// playpage.h增加新功能后的代码：

#ifndef PLAYPAGE_H
#define PLAYPAGE_H

#include <QWidget>
#include "volume.h"

namespace Ui
{
    class PlayPage;
}

class PlayPage : public QWidget
{
    Q_OBJECT

public:
    explicit PlayPage(QWidget *parent = nullptr);
    ~PlayPage();

​    void mousePressEvent(QMouseEvent *event); // 鼠标点击
​    void mouseMoveEvent(QMouseEvent *event);  // 鼠标移动

private slots:
    void onVolumeBtnClicked();

private:
    Ui::PlayPage *ui;
    QPoint dragPos;
    Volume* volume;
};

#endif // PLAYPAGE_H



// playpage.cpp增加新功能后的代码：

\#include "playpage.h"

\#include "ui_playpage.h"

\#include <QMouseEvent>

PlayPage::PlayPage(QWidget *parent)

  : QWidget(parent), ui(new Ui::PlayPage)

{

  ui->setupUi(this);

  setWindowFlag(Qt::FramelessWindowHint);

  setAttribute(Qt::WA_ShowModal);

  volume = new Volume(this);

  connect(ui->minBtn, &QPushButton::clicked, this, &QWidget::showMinimized);

  connect(ui->quitBtn, &QPushButton::clicked, this, &QWidget::close);

  connect(ui->volumeBtn, &QPushButton::clicked, this, &PlayPage::onVolumeBtnClicked);

}

PlayPage::~PlayPage()

{

  delete ui;

}

void PlayPage::mousePressEvent(QMouseEvent *event)

{

  QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

  // 检测鼠标左键单击时该位置是否在 head 中

  if (ui->playHead->geometry().contains(point))

  {

​    if (event->button() == Qt::LeftButton)

​    {

​      dragPos = event->globalPosition().toPoint() - geometry().topLeft(); // 保存相对位置

​      return;

​    }

  }

  QWidget::mousePressEvent(event);

}

void PlayPage::mouseMoveEvent(QMouseEvent *event)

{

  QPoint point = event->position().toPoint(); // 获取鼠标点击的位置

  // 检测鼠标左键移动时该位置是否在 head 中

  if (ui->playHead->geometry().contains(point))

  {

​    if (event->buttons() == Qt::LeftButton)

​    {

​      move(event->globalPosition().toPoint() - dragPos); // 把窗口移动到新的位置

​      return;

​    }

  }

}

void PlayPage::onVolumeBtnClicked()

{

  volume->show();

}



”

老师课上的讲话：“
音量调节窗口布局完成之后，接下来我们再把它的样式去处理一下，再重新设置样式之前，先将我们之前添加进去的测试颜色给它拿掉，好，我们先把这些背景颜色给它处理掉，玻璃完了没有在我们的背景上把它就是删除掉，删除掉我们重新它来进行设置。Ok还有我们的猫灵boss，颜色也给它拿掉，完了之后这个地方有咱们的应该对吧？应该的颜色我也给他拿掉，包括奥特赖的亚瑟王全部给它拿掉，那这样所有的背景颜色我就把它处理掉了，对吧？处理掉了之后，接下来我们先给他去设立一个背景，这个背景就把它改成井号这种方式，微波Lule对吧？笔记它的背景颜色background大家都渴望的刚发了Col这里面是号井号三、d3、d3、b然后给一个就是3b3D3、b3b完了之后给它完善的应用我们页面当中所希望看到的颜色对吧？颜色。完了之后我们再给他去设计成一个圆角半径bord芽孢的杠MACD卖出去对吧？把他的对应该是高的杠rbdxus你那只能是设置这个图片的，圆角半径的话，我就把它改成4个行不行？然后正好点击1个应用对吧？应用这个是怎么定的？要再往下走，完了就是毛领 Boss。毛宁boss吗？我们在内部上主要就是给我们到依赖奥特曼，比如说给这两个q福利，把两个半径去设置一下对吧？我们只能用它的类型选择项，在model box当中有类型选择器，气的时候就是他内部这些元素，如果类型和我所给的类型是一致的，他都可以享受在box当中所设置的类型选择器的样式，对吧？阿q鼓励 ffqframe福利，那么刚刚不是想让这个福利吗？让他也有一个圆角的半径对吧？等于包的被d盘us包的windows，把它的圆角半径变成两个相同点，来上一个应用，现在在我们这个页面当中我们是看不来，等到我们给他把背景颜色加上，大家就能看到对吧？接下来是我们给到依赖，今后1万很快，另外他的背景颜色1CK9我有一点到c完了对吧？大家都葛朗德真的是警号八八八第八把这个配套点一个应用，这个就是我们在涉及到并不错对吧？应带到可以看一下，现在它上面已经出现了一个圆乎的情况，圆乎的这种效果。好，完了之后还有我们的奥特莱奥特莱奥特就是警报包车走到街道情况出来，eackbback8和droud background的杠Col background的2，然后它的颜色是井号三e三e ce然后是fe三ecfe ok可以过来，完了之后点击一个页面确定我给你颜色的效果让它在里面也就出来了，对吧？像最后还有我们给到按钮的样式，井号内ol由m116 100010b间，好，猫零1000气囊在里面是小写的对吧？小写的。这个按钮的话，backdround它也有自己的背景颜色对吧？所以我按了然后颜色怎么样去填空？八八第八对基本上都对吧？Ok然后来上一个应用。我们看一下包流微波 M一包流感觉压床好像没有上去是吧？还是猫流明星 bug background babackgroundcolor background color情况，d8d8d8有没有什么问题？那么再把它的 B或d边框给它拿掉对吧？重新设置一下边框，它是一个像素点ppx然后还是solid这个边边框它那个线是一个实心的，线量在里面是97，另外然后可以过来这块，那么还得需要去设计下它的圆角半径，b b包的杠AD us包的瑞德斯把它的圆角半径给同5个3个点。第一，我们的矩形它刚好是伸出时的，所以说圆心把它的半圆角半径给成五了，将来圆的圆心它刚好就在矩形的正中央，对吧？确定，然后确定这样子的话，我们的按钮它就成了一个圆球球对吧？你可以点一下工具，然后底下有一个预览对吧？预览于我们看到的windows风格。来看到我们现在我们就看到刚刚我们所设置好的按钮，它就是我们现在所看到的这样一个叫对吧？效果其实让它活，我们的界面当中所给的这种效果肯定是一样的，能下来肯定是一样的，好完成了以后我们得需要让窗口给它显示出来，对吧？它显示出来了。我们看一下在国内配置，比如说在我们的播放页面里面来进行假设，可能因为将来是点击了那个页面的就是音量调节按钮之后才会对吧，让它显示出来。接下来我们必须要在普利亚地址当中给它添加上一个图标变 volume volume，就是保留的信号，我们给一个vivo按61毛进来，当然用到了我们就必须要包含它的软件音刻录的，然后这可能是 volume对吧？猫0.0什么包含进来了之后，然后在构造方法的内容，在这个位置vol我们可以他去拗上一个 volum6毛6对吧？用上一个毛6，然后像咱们刚才所给的 This就是把他的货发布在里面去设置一下，对吧？设置好了之后，将来你再点击了弹出窗口的时候才会需要的话，弹出来对吧？音量按钮的时候才需要让它弹出来，所以在这个位置我们就需要给他的窗口给他去添加一个槽函数，对吧？怎么说？第二类近似有的地方是 slogs高一档，它是我们的二类olumn o 6b7n它 Clsaked点击的时候，我们让它去弹出我们的音量调节窗口，按照out键加回车，在原文件里面就是完成了方法的定义，对吧？这个方法指的内容包流让他数数，就是让窗口给它显示出来对吧？好，完了之后别忘把它显示出来对吧？完了之后别忘记就是在我们的位置上来上一个可耐卡绑定信号头，UI那边有一个猫目b签这个包的冰箱，它将来会触发一个q工程师必签的方法，对吧？给我部署给钱，他又不是，并且完了之后，然后他会触发一个就是点击的信号，这个信号我让当前页面去处理，刚刚我们已经在怎么样配置当中把它的槽函数添加了，对吧？好你给我明天来。你在点击的时候让这个窗口让它弹出来，把它弹出来，好，完成了之后把我们的程序给它运行一下，他现在正在编译，稍等片刻运行。弹出我们的播放窗口，我们现在看到播放窗口它在也就说音量调节窗口在我们的播放窗口弹出来之后，它立马就显示出来了，对吧？我们现在看到的现象和现象就是不是播放窗口，就是音量调节窗口，它在播放窗口显示出来时对吧？已经在窗口的左上角，他们就和我们所期望的在里面不一样，还有我们在期望的是当用户点击音量调节按钮的时候，对吧？能够传输弹出就是音量调节窗口，当用户点击播放页面的其他位置的时候，我们的音量调节方法对吧？就这样消失，可能在里面消失，这一步的消失就是让他看不到对吧？看不到。好，也就是这个过程它应该是自动的，其实我们刚刚所描述的这一点就说明让我们的音量调节窗口应该是因为它有很多对吧？弹出窗口它是想去有这种效果，刚开始我们页面显示的时候它并不会显示，你需要让它显示的时候给它竖一下，你需要让它消失的时候，我们其在窗口的音量解决窗口外面的任意一个位置，你给它点击一下，音量调节窗口它就消失了，对吧了，这个是我们现在所看到的第一个问题。除了这个问题之外，我们还有二二第二个问题，也就是说因为音量调节窗口它的音量调节窗口的初始位置不准确，对吧？它初始位置不正确，我们将来所期望看到的它的主意是应该刚好能在音量调节按钮的正上方把它就是拿过来对吧？拿过来。也就是说音量调节按钮，音量调节窗口，狗的初始位置应该在音量给它设置音量调节按钮当中对吧？在正中方居中的位置，所以说它现在显示的这个位置的话肯定是不正确的，因此将来我们还得需要再去做两件事情，第一就是把音量调节窗口给它视为弹出窗口。第二个就是把它的初始显示位置让它去设置一下。”