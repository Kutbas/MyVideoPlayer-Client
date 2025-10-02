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

#### 音量调节窗口的位置调整

但是目前音量调节窗口的位置并不正确。它总是出现在播放窗口的左上角，和预期的“出现在音量调节按钮正上方居中”有偏差。问题的根源在于我们在创建这个窗口时，并没有把它放到播放窗口的布局器里，而是把它单独作为一个窗口来显示，因此 Qt 默认把它绘制在左上角。

为了解决这个问题，我们首先在 `volume.cpp` 中把音量调节窗口设置成弹出窗口。Qt 提供了 `Qt::Popup` 标记来定义这种行为：窗口在显示时会悬浮在界面之上，并且在用户点击其他区域时会自动关闭，非常符合我们对音量窗口的预期。

```c++
// volume.cpp增加新功能后的代码：

#include "volume.h"
#include "ui_volume.h"

Volume::Volume(QWidget *parent)
  : QWidget(parent), ui(new Ui::Volume)
{
  ui->setupUi(this);
  setWindowFlag(Qt::Popup); // 将音量调节窗口设置为弹出窗口
}

Volume::~Volume()
{
  delete ui;
}
```

不过，把窗口设置成 `Qt::Popup` 之后，还会遇到一个新问题：音量调节窗口会直接跑到电脑屏幕的左上角，而不是播放窗口的相对位置。这是因为在 Qt 中，弹出窗口被视为顶层窗口，它没有父窗口，因此默认显示位置是屏幕的 `(0,0)`。

要解决这个问题，就需要手动指定弹出窗口的位置。思路是先获取播放窗口的左上角坐标，并把它转换为全局坐标，然后再在此基础上加上偏移量，把音量窗口放到正确的位置。比如在这里，我们让窗口显示在播放页面的右下角区域，横向位置通过播放窗口的宽度减去音量窗口的宽度再减去 13 来对齐右边界，纵向则设置在 y = 533 的位置。

在 `playpage.cpp` 中新增了 `moveWindows` 方法，用来处理弹出窗口的位置调整：

```c++
// playpage.cpp修改的部分代码：

void PlayPage::onVolumeBtnClicked()
{
  // 获取播放窗口的左上角坐标，并将其转换为基于桌面的坐标
  moveWindows(mapToGlobal(QPoint(0, 0)));
  volume->show();
}

void PlayPage::moveWindows(const QPoint &point)
{
  // point 已经是基于屏幕的全局坐标
  QPoint newPoint = point + QPoint(this->width() - volume->width() - 13, 533);
  volume->move(newPoint);
}
```

这样处理之后，音量窗口就不再跑到屏幕左上角，而是准确地出现在播放页面的指定位置。点击音量按钮时，它能正常弹出；点击播放页面的其他地方时，它会自动消失。这种方式不仅满足了交互需求，也为将来可能新增的其他弹出窗口（比如“倍速调节”窗口）提供了可复用的定位方法。

#### 音量调节窗口的交互实现

在前面，我们已经让音量调节窗口能够作为弹出窗口出现，并且可以正确地定位在播放页面中。但光能弹出来还不够，用户需要能通过 **点击或拖拽滑杆来调整音量**。这个过程和我们之前实现播放进度条的思路很类似：核心就是要捕捉鼠标事件，根据鼠标的位置去更新音量条和按钮的位置。

Qt 里捕捉鼠标事件通常有两种方式：

1. 直接重写鼠标的 `mousePressEvent` / `mouseReleaseEvent` / `mouseMoveEvent`。
2. 安装 **事件过滤器 (Event Filter)**，统一拦截并处理鼠标事件。

这里我们选择了第二种方式，把事件过滤器安装到 `volumeBox` 这个控件上。这样一来，用户只要在音量调节的区域中点击或拖拽，我们就能统一拦截事件并更新音量。

修改后的完整代码如下：

```c++
// volume.cpp修改后的完整代码：

#include "volume.h"
#include "ui_volume.h"
#include "util.h"

Volume::Volume(QWidget *parent)
  : QWidget(parent), ui(new Ui::Volume)
{
  ui->setupUi(this);
  setWindowFlag(Qt::Popup); // 将音量调节窗口设置为弹出窗口
  ui->volumeBox->installEventFilter(this); // 在volumeBox上安装事件过滤器
}

Volume::~Volume()
{
  delete ui;
}

bool Volume::eventFilter(QObject *watched, QEvent *event)
{
  if (ui->volumeBox == watched)
  {
    if (event->type() == QEvent::MouseButtonPress)
    {
      calcVolume(); // 鼠标按下时计算音量
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
      // 释放暂时不做处理
    }
    else if (event->type() == QEvent::MouseMove)
    {
      calcVolume(); // 拖拽时实时更新音量
    }
    return true; // 已拦截并处理
  }
  return QObject::eventFilter(watched, event);
}

void Volume::calcVolume()
{
  // 获取鼠标点击时的Y坐标（基于屏幕的全局坐标）
  int y = ui->volumeBox->mapFromGlobal(QCursor().pos()).y();
  LOG() << y;

  // 限制Y坐标范围 [5, 150]
  y = y < 5 ? 5 : y;
  y = y > 150 ? 150 : y;

  // 更新 outLine 的高度
  ui->outLine->setGeometry(ui->outLine->x(), y, ui->outLine->width(), 150 - y);

  // 更新 volumeBtn 的位置
  int volumeBtnY = ui->outLine->y() - ui->volumeBtn->height() / 2;
  volumeBtnY = volumeBtnY > 140 ? 140 : volumeBtnY;
  ui->volumeBtn->move(ui->volumeBtn->x(), volumeBtnY);
}
```

这里的逻辑可以总结为三步：

1. **获取鼠标位置**
    通过 `QCursor().pos()` 拿到全局坐标，再用 `mapFromGlobal` 转换到 `volumeBox` 内部的相对坐标。我们只关心 `y` 值，因为音量条是竖直的。
2. **限制取值范围**
    为了避免越界，把 `y` 值限制在 `[5, 150]` 区间内。这对应音量条的有效范围，超出部分直接裁剪。
3. **更新控件位置**
    根据 `y` 值动态更新两个东西：
   - `outLine` 的高度：表示当前的音量大小。
   - `volumeBtn` 的位置：按钮需要跟随滑动，但要注意当按钮快到底部时，可能会“掉出去一半”，所以这里加了一个边界判断，把它限制在 140 以内。

运行效果是，当用户在音量区域点击或拖拽时，音量条高度和按钮位置会实时更新，看上去就像真正的音量滑杆一样。

不过目前，这个控件只是完成了 **UI 层面的交互**，它还没有真正和播放器的音量挂钩。换句话说，拖动按钮可以改变控件的显示效果，但还不会改变播放视频的音量。等到后续我们把播放模块实现完毕，就可以把 `calcVolume()` 的结果映射到实际的音量值上，实现真正的音量控制。

### 倍速播放窗口的设计与实现

在视频播放器里，倍速播放是一个非常常见的功能。相比音量调节，它的交互更简单：用户只需要点击一个按钮，弹出一个小面板，在里面选择 0.5 倍、1 倍、1.5 倍或 2 倍的播放速度即可。本节就来实现这样一个倍速选择窗口。

**1. 界面结构设计**

倍速窗口单独做成一个 `QWidget`，命名为 `PlaySpeed`，尺寸设置为 `80×134`。
 在窗口里放置一个背景容器 `playSpeedBg`，应用垂直布局（QVBoxLayout），边距和间距全部设置为 0。这样做的目的是让按钮在竖直方向上紧凑排列，方便用户点击。

接着，在布局中添加四个 `QPushButton`，分别命名为：

- `speed20`（显示文本 “x2”）
- `speed15`（显示文本 “x1.5”）
- `speed10`（显示文本 “x1”）
- `speed05`（显示文本 “x0.5”）

每个按钮的高度固定为 24px，布局的边距设置为 9，间距设置为 3。这样就能保证小窗口看起来不拥挤，同时按钮之间留有一定的呼吸感。

**2. 样式设计**

为了让这个窗口在视觉上与播放器整体风格统一，我们给它加上了深色半透明背景、圆角边框和悬停高亮效果。

```css
#playSpeedBg {
  background-color: #3D3b3b;
  border-radius: 10px;
}

QPushButton {
  border: none;
  border-radius: 4px;
  color: #FFFFFF;
  font-size: 12px;
  font-family: 微软雅黑;
}

QPushButton:hover {
  background-color: rgba(255,255,255,0.41);
}
```

这种样式的好处是：

1. 深色背景让按钮更突出；
2. 圆角让小窗口显得更柔和；
3. 悬停高亮能给用户即时的交互反馈。

整体效果与音量窗口保持一致，风格统一。

**3. PlaySpeed 类实现**

倍速窗口单独写成一个类 `PlaySpeed`，继承自 `QWidget`。它的特点是：

- 设置窗口类型为 `Qt::Popup | Qt::FramelessWindowHint`，保证弹出后不带边框，并且点击窗口外部时会自动关闭；
- 开启 `Qt::WA_TranslucentBackground`，让圆角效果自然呈现；
- 每个按钮点击时调用一个槽函数，后续会与播放器逻辑联动。

```c++
// playspeed.h
class PlaySpeed : public QWidget {
  Q_OBJECT

public:
  explicit PlaySpeed(QWidget *parent = nullptr);
  ~PlaySpeed();

private slots:
  void onPlay20SpeedClicked();
  void onPlay15SpeedClicked();
  void onPlay10SpeedClicked();
  void onPlay05SpeedClicked();

private:
  Ui::PlaySpeed *ui;
};
```

在 `cpp` 文件中，完成 UI 初始化和信号连接：

```c++
PlaySpeed::PlaySpeed(QWidget *parent)
  : QWidget(parent), ui(new Ui::PlaySpeed) {
  ui->setupUi(this);
  setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
  setAttribute(Qt::WA_TranslucentBackground);

  connect(ui->speed20, &QPushButton::clicked, this, &PlaySpeed::onPlay20SpeedClicked);
  connect(ui->speed15, &QPushButton::clicked, this, &PlaySpeed::onPlay15SpeedClicked);
  connect(ui->speed10, &QPushButton::clicked, this, &PlaySpeed::onPlay10SpeedClicked);
  connect(ui->speed05, &QPushButton::clicked, this, &PlaySpeed::onPlay05SpeedClicked);
}

void PlaySpeed::onPlay20SpeedClicked() { LOG() << "2.0"; }
void PlaySpeed::onPlay15SpeedClicked() { LOG() << "1.5"; }
void PlaySpeed::onPlay10SpeedClicked() { LOG() << "1.0"; }
void PlaySpeed::onPlay05SpeedClicked() { LOG() << "0.5"; }
```

目前点击按钮时先打印日志，后续会与播放器的倍速控制绑定。

**4. 集成到播放页面**

最后一步是把 `PlaySpeed` 窗口集成到播放页 `PlayPage` 中。思路与音量窗口一致：

- 在 `PlayPage` 构造函数里初始化一个 `playSpeed` 实例；
- 在 `moveWindows` 函数里计算它的弹出位置，使其相对播放器底部按钮对齐；
- 在点击倍速按钮时弹出窗口。

```c++
playSpeed = new PlaySpeed(this);

void PlayPage::moveWindows(const QPoint &point) {
  QPoint newPoint = point + QPoint(this->width() - playSpeed->width() - 80, 536);
  playSpeed->move(newPoint);
}

void PlayPage::onSpeedBtnClicked() {
  moveWindows(mapToGlobal(QPoint(0, 0)));
  playSpeed->show();
}
```

这样，当用户点击“倍速按钮”时，就能看到一个带有圆角和悬停效果的小面板，里面列出了所有速度选项。

### 弹幕编辑框实现

在播放页面上，我们还缺少一个重要的元素——弹幕编辑框。它的功能就是让用户能够在观看视频时输入文字，点击右侧的发送按钮，就能把这条弹幕发到视频上。

从设计图可以看出，弹幕编辑框整体结构很简单，本质上是一个文本输入框，右侧多了一个“发送”按钮。Qt 自带的 `QLineEdit` 虽然提供了文本输入功能，但没法直接满足这种“编辑框 + 按钮”的需求，因此我们需要自定义一个类来实现。

这里我们新建一个类 `BarrageEdit`，继承自 `QLineEdit`，在其中手动添加一个按钮，并设置好样式。这部分内容不需要使用 Qt Designer 的 UI 界面，因为控件本身非常简单，用代码就能完成。

**1. 类的定义**

`barrageedit.h` 中定义了 `BarrageEdit`，在内部维护一个 `QPushButton` 作为发送按钮，并在点击时触发槽函数：

```c++
#ifndef BARRAGEEDIT_H
#define BARRAGEEDIT_H

#include <QLineEdit>
#include <QPushButton>

class BarrageEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit BarrageEdit(QWidget *parent = nullptr);

private slots:
    void onSendBsBtnClicked();

private:
    QPushButton *sendBsBtn;
};

#endif // BARRAGEEDIT_H
```

**2. 构造函数与样式设置**

在 `barrageedit.cpp` 中完成具体实现。首先是对编辑框本身进行设置：

- 固定大小：`1030x32`，与播放页面保持一致；
- 占位提示：`"这个视频在说什么？"`；
- 输入限制：最多支持 30 个字符；
- 内边距：`setTextMargins(12, 6, 0, 7)`，保证文字不会紧贴边框；
- 样式：深灰背景、白灰色文字、圆角矩形。

代码如下：

```c++
#include "barrageedit.h"
#include "util.h"

BarrageEdit::BarrageEdit(QWidget *parent)
  : QLineEdit{parent}
{
  // 设置编辑框属性
  setFixedSize(1030, 32);
  setPlaceholderText("这个视频在说什么？");
  setMaxLength(30);
  setTextMargins(12, 6, 0, 7);
  setStyleSheet(
    "font-family : 微软雅黑;"
    "font-size : 14px;"
    "background-color : #4D4D4D;"
    "color : #DEDEDE;"
    "border : none;"
    "border-radius : 4px;"
  );

  // 初始化发送按钮
  sendBsBtn = new QPushButton(this);
  sendBsBtn->setFixedSize(58, 28);
  sendBsBtn->setText("发送");
  sendBsBtn->setCursor(QCursor(Qt::ArrowCursor));
  sendBsBtn->setStyleSheet(
    "background-color : #3ECEFE;"
    "color : #FFFFFF;"
    "border-radius : 4px;"
    "font-family : 微软雅黑;"
    "font-size : 14px;"
  );

  // 调整按钮位置（靠右对齐，垂直居中）
  sendBsBtn->move(width() - sendBsBtn->width() - 2, 2);

  // 信号槽绑定
  connect(sendBsBtn, &QPushButton::clicked, this, &BarrageEdit::onSendBsBtnClicked);
}
```

**3. 槽函数：发送弹幕**

点击按钮后暂时先打印日志，后续会与前端显示、后端逻辑对接：

```c++
void BarrageEdit::onSendBsBtnClicked()
{
  LOG() << "发送弹幕：" << text();
}
```

这样，一个完整的弹幕编辑框控件就定义好了。

**4. 在播放页面中使用**

定义好 `BarrageEdit` 后，还需要把它放到播放页面里。方法是：

1. 在 Qt Designer 中选中原有的输入框；
2. 右键选择 **提升为** → 输入 `BarrageEdit`；
3. 应用后，原控件就会替换成我们自定义的类。

运行程序时，编辑框会显示提示文字，右侧带有一个蓝色圆角的“发送”按钮，点击后可以触发槽函数。

最终效果是这样的：

- 编辑框外观与整体界面保持一致；
- 输入上限 30 字符，避免过长的弹幕；
- 按钮样式和交互正常，点击能响应。

至此，弹幕编辑框的基本功能完成，后续只需要把 `onSendBsBtnClicked()` 和弹幕渲染逻辑对接，就可以真正把弹幕显示在视频播放中。

## 我的页面与关注页面的布局设计

在完成了播放页面的功能之后，下一个重点就是“我的页面”。当用户点击主页左侧的 **我的** 切换按钮时，就会进入到这一页面，这里展示的是当前登录用户的个人信息，以及他之前上传并且已经审核通过的视频。与此同时，设计图里还有一个“关注页面”，它的整体布局与“我的页面”几乎一致，只是在交互上有些区别。为了避免重复开发，我们需要对这两个页面进行抽象和整合。

**1. 页面整体布局**

无论是“我的页面”还是“关注页面”，整体结构都是上下分区布局：

- 顶部：基本信息区（用户头像、昵称、账号数据、退出或关注按钮等）
- 中间：辅助功能区（说明信息、上传视频按钮等）
- 底部：视频展示区（通过 `VideoBox` 组件复用来显示视频信息）

这样的结构层次清晰，也方便后续用 `QVBoxLayout` 来实现。

**2. 基本信息区**

最上方区域放置的是用户的头像和个人信息。头像并不只是一个静态图片，而是一个按钮：

- 在“我的页面”中，点击头像可以修改用户头像，头像是圆形的，并带有灰色的半透明遮罩层；
- 在“关注页面”中，头像只作为展示，不能点击修改。

头像右侧是用户昵称，类型是 `QLabel`，而旁边还会有一个修改昵称和密码的按钮。在“我的页面”里，这个按钮点击后弹出修改对话框，而在“关注页面”中则隐藏。

再往右侧是用户的数据信息，包括 **关注数、粉丝数、获赞数、播放数** 等。它们会放到一个类似二维表格的布局器中，整体排版整齐。

最右侧部分则是 **功能按钮**：

- 在“我的页面”中，这里是 **退出登录按钮**；
- 在“关注页面”中，这里会显示 **关注/取消关注按钮**。

**3. 辅助功能区**

这一部分内容在两个页面之间也有差异：

- 在“我的页面”中，会显示说明信息（例如“我的视频”），并且提供 **上传视频按钮**。点击按钮后会弹出文件选择对话框，用户选择本地视频后上传到服务器。上传成功后，还会弹出一个视频信息填写窗口，让用户补充标题、封面、简介、分类、标签等内容。这些信息会用于首页和搜索功能，也会在 `VideoBox` 中显示。
- 在“关注页面”中，没有上传视频的功能，说明文字会显示成“他的视频”。

**4. 视频展示区**

底部区域是用户上传的视频集合。这里的布局依旧使用 `QGridLayout`，所有的视频单元由 `VideoBox` 来承载。

需要注意的一点是，“我的页面”和“关注页面”在视频展示上的区别：

- 在“我的页面”中，`VideoBox` 不显示播放信息，而是显示 **删除按钮**。点击删除按钮并不会立刻删除视频，而是弹出一个菜单，让用户确认后，再将该视频信息从服务器删除。
- 在“关注页面”中，`VideoBox` 隐藏删除按钮，因为用户没有权限删除他人视频。

考虑到用户可能上传了大量视频，一个页面无法容纳所有内容，因此底部区域会被放进一个 `QScrollArea` 中。当视频数量超过一屏时，右侧会自动出现垂直滚动条，保证用户可以浏览所有视频。

**5. 我的页面与关注页面的整合**

通过对比可以发现，这两个页面的绝大部分结构是一致的，只是在个别功能上有所差异：

- 我的页面：支持修改头像、修改昵称、上传视频、删除视频、退出登录
- 关注页面：不支持这些功能，只显示关注按钮和他人视频

因此在实现时，可以只写一个通用页面，然后根据不同场景选择性地隐藏或显示部分控件。这样既避免了重复劳动，也保证了界面风格的一致性。

### 我的页面布局实现

在完成了首页和播放页面的功能之后，下一个重点就是“我的页面”。当用户点击主页左侧的 **我的** 切换按钮时，就会进入到这一界面，这里展示的是当前登录用户的个人信息，以及他上传并审核通过的视频。设计上，“我的页面”其实分为三大部分：顶部的基本信息区，中间的标题栏区域，以及底部的视频展示区。为了让布局保持整齐和统一，我们在实现时充分利用了 `QVBoxLayout` 和 `QGridLayout`，并结合 `QScrollArea` 来支持滚动。

**1. 页面整体布局**

首先在项目中添加一个新的 Qt Designer 界面，命名为 **MyselfWidget**，并将其 `geometry` 调整为 **1341 × 784**。随后在这个界面中依次放置三个 QWidget：**baselnfoArea**、**titleBar** 和 **VideolnfoArea**，它们构成了页面的三个纵向分区。为了便于调试和区分位置，每个区域临时赋予了不同的背景颜色，同时设置 `minimumSize` 和 `maximumSize`，确保各自高度固定，避免布局混乱。

**2. 基本信息区**

最上方的 baselnfoArea 是用户的个人信息区，它由三个水平并排的子区域组成：**userInfoBox**、**videoNumBox** 和 **BtnBox**。
 在 userInfoBox 中，我们放置了一个头像按钮 **avatarBtn**（尺寸 60×60），右边是用户昵称标签 **nicknameLabel**（最小宽度 125），以及一个设置按钮 **settingBtn**，用于修改昵称或密码。控件之间的间距设为 7，并在末尾加上一个弹簧，让排版更自然。

videoNumBox 负责展示账号的数据信息，包括关注数、粉丝数、获赞数和播放数。这里采用二维表格形式的栅格布局，上下两行分别放置类别名称和对应的数值。为了保证美观，栅格的水平间距设置为 7，垂直间距为 14。

BtnBox 则位于最右侧，放置了两个功能按钮：一个是 **attentionBtn**（关注按钮），另一个是 **quitBtn**（退出登录按钮）。在“我的页面”中，默认显示退出登录；而在关注他人主页时，显示的则是关注或取消关注。它们通过 geometry 属性叠放在一起，后续只需在逻辑层切换显示状态即可。

**3. 标题栏区域**

标题栏 titleBar 的作用是提示用户当前的内容，并提供一个上传功能。在这里，我们放置了一个标签 **myVideoLabel**（文本为“我的视频”）和一个按钮 **uploadVideoBtn**。二者之间通过弹簧分隔，按钮被固定为 116×30 的尺寸。未来在逻辑层中，当用户点击上传按钮时，会弹出文件选择对话框并进入视频上传流程。

**4. 视频展示区**

最底部的 VideolnfoArea 是视频信息展示的主体区域。这里放置了一个 **QScrollArea**，里面包含一个 QWidget **container**，并对其设置 `QGridLayout`。这样每个上传的视频都会以 **VideoBox** 的形式展示在网格里，布局器自动管理它们的排版和间距。当视频数量过多时，QScrollArea 会自动出现滚动条，保证用户可以浏览完整内容。

在“我的页面”中，VideoBox 的特殊之处是会显示一个 **删除按钮**。点击删除不会立即生效，而是弹出一个菜单，用户确认之后才会向服务器发送删除请求。而在“关注页面”中，这个按钮则会被隐藏，因为用户没有权限删除他人上传的视频。

### 我的页面样式设置

在完成了“我的页面”的基本布局之后，本节对其中的控件样式进行了统一的设定。开始之前，需要先去掉之前用于调试的临时背景色，让界面保持干净整洁。这样可以更直观地看到新的样式效果。

**1. 基础区域样式**

首先是基础信息区域（`baseInfoArea`），背景色设置为浅灰色，便于和其他区域区分：

```css
#baseInfoArea{
    background-color:#F5F5F5;
}
```

**2. 头像与按钮**

头像按钮需要以圆形形式显示用户头像。为了达到这一效果，设置了透明背景、去掉边框，并通过圆角半径控制形状。图片通过 `border-image` 加载默认头像：

```css
#avatarBtn{
    background-color:transparent;
    border:none;
    border-radius:30px;
    border-image:url(":/images/myself/defaultAvatar.png");
}
```

修改按钮同样不显示边框，而是直接用图片作为背景：

```cs
#settingBtn{
    border:none;
    border-image:url(":/images/myself/xiugai.png");
}
```

**3. 用户数据标签**

关注数、粉丝数、点赞数和播放数这几项信息的样式保持一致，统一使用微软雅黑字体，字号 16px，颜色为浅灰：

```css
#attentionLabel,
#playLabel,
#fansLabel,
#likeLabel{
    font-family:微软雅黑;
    font-size:16px;
    color:#999999;
}
```

对应的数字则稍大一些，18px 字号，颜色加深为 #222222：

```css
#attentionCountLabel,
#fansCountLabel,
#likeCountLabel,
#playCountLabel{
    font-family:微软雅黑;
    font-size:18px;
    color:#222222;
}
```

**4. 功能按钮**

退出登录按钮需要有边框和圆角，字体相对小一些；而上传视频按钮则以图标作为背景：

```css
#quitBtn{
    border:1px solid #DDDDDD;
    border-radius:15px;
    font-family:微软雅黑;
    color:#999999;
    font-size:14px;
}

#uploadVideoBtn{
    border-radius:15px;
    border-image:url(":/images/myself/shangchuanshipin.png");
}
```

**5. 标题与滚动区域**

“我的视频”标题字体大小设置为 18px：

```css
#myVideoLabel{
    font-family:微软雅黑;
    font-size:18px;
}
```

视频展示区使用 `QScrollArea`，背景色设为白色，去掉边框，同时对滚动条进行美化：
 滑块为浅灰色并带圆角，上下箭头隐藏，只保留简洁的滚动条本体。

```css
#scrollArea{
    border:none;
    background-color:#FFFFFF;
}

QScrollBar::vertical{
    border:none;
    background-color:#FFFFFF;
    width:10px;
}

QScrollBar::handle::vertical{
    border:none;
    border-radius:5px;
    background-color:#E8E8E8;
    min-height:134px;
}

QScrollBar::up-arrow:vertical,
QScrollBar::down-arrow:vertical{
    border:none;
    width:0px;
    height:0px;
}

#scrollAreaWidgetContents{
    background-color:#FFFFFF;
}
```

#### MyselfWidget 测试与初始化

在完成了 `MyselfWidget` 的基本界面设计之后，需要先进行一次简单的测试，看看界面实际运行时的效果。这一步主要包括两个方面：隐藏不需要的控件，以及往视频显示区域批量添加一些 `VideoBox`，从而直观地观察界面布局是否符合预期。

这些逻辑被集中放在一个私有的 `initUI()` 方法中，并在构造函数里调用：

```c++
void MyselfWidget::initUI()
{
    ui->attentionBtn->hide();

#ifdef TEST_UI
    for (int i = 0; i < 16; i++)
    {
        VideoBox *videoBox = new VideoBox();
        ui->layout->addWidget(videoBox, i / 4, i % 4);
    }
#endif
}
```

运行后，视频区域会显示一个 **4×4** 的 `VideoBox` 网格，把界面撑开并出现滚动条，这样可以很直观地检验布局效果。为了避免这段测试代码干扰后续开发，还加了条件编译，只要在需要时定义 `TEST_UI` 宏即可启用。

### 自定义头像按钮 AvatarButton

在「我的页面」里，用户头像本质上是一个按钮。和普通按钮不同，这里需要一个小细节：当鼠标移到头像上时，按钮上方会出现一个半透明的遮罩层，并显示“修改图像”的提示文字；鼠标移开后遮罩层消失。用户点击按钮时，可以选择本地图片作为头像。

Qt 虽然提供了 `hover` 伪状态，但它无法区分“我的页面”和“关注页面”这两种场景。如果直接用 `hover`，两个页面上的头像按钮都会有遮罩层效果，但实际上在关注页面中是不允许修改头像的。为了更灵活地控制，就需要自定义一个按钮类 `AvatarButton`。

这个类继承自 `QPushButton`，内部叠加了一个 `QLabel` 作为遮罩层。遮罩层的样式设为圆形半透明，并在居中位置显示提示文字。通过重写 `enterEvent` 和 `leaveEvent`，可以在鼠标进入和离开时切换遮罩层的显示状态。同时，类中提供了一个布尔成员 `isShow` 来控制遮罩层是否启用，这样在关注页面就可以禁止显示。

核心代码如下：

```c++
// avatarbutton.h
class AvatarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AvatarButton(QWidget *parent = nullptr);
    void changeMode(bool isShow);

protected:
    void enterEvent(QEnterEvent *event) override; // 鼠标进入
    void leaveEvent(QEvent *event) override;      // 鼠标离开

private:
    QLabel *mask; // 遮罩层
    bool isShow;  // 是否显示遮罩层
};
// avatarbutton.cpp
AvatarButton::AvatarButton(QWidget *parent)
    : QPushButton{parent}, isShow(true)
{
    mask = new QLabel(this);
    mask->setObjectName("maskLabel");
    mask->setGeometry(0, 0, 60, 60);
    mask->setStyleSheet("#maskLabel{"
                        "color:#FFFFFF;"
                        "background-color:rgba(0,0,0,0.5);"
                        "border-radius:30px;}");
    mask->setText("修改图像");
    mask->setAlignment(Qt::AlignCenter);
    mask->hide();
}

void AvatarButton::enterEvent(QEnterEvent *event)
{
    (void)event;
    if (isShow) mask->show();
}

void AvatarButton::leaveEvent(QEvent *event)
{
    (void)event;
    mask->hide();
}

void AvatarButton::changeMode(bool isShow)
{
    this->isShow = isShow;
}
```

在 `myselfwidget.ui` 中，将原有的 `avatarBtn` 提升为 `AvatarButton` 类型，就能直接看到效果：

- 我的页面：鼠标悬停时显示遮罩层，点击后可以选择头像。
- 关注页面：遮罩层不显示，头像不可更改。

这样，一个简单的自定义按钮就解决了遮罩层在不同页面的差异化需求。

#### 修改头像功能实现

在完成了自定义头像按钮 `AvatarButton` 的遮罩层效果后，接下来要解决的就是头像修改功能。当用户点击头像按钮时，应该弹出文件选择对话框，让用户能够从本地磁盘挑选一张图片，并将其设置为头像。

要实现这个功能，我们需要先在 `MyselfWidget::initUI()` 中为 `avatarBtn` 增加点击事件的绑定：

```c++
void MyselfWidget::initUI()
{
    ui->attentionBtn->hide();

#ifdef TEST_UI
    // 向视频显示区域添加 VideoBox，测试代码
    for (int i = 0; i < 16; i++)
    {
        VideoBox *videoBox = new VideoBox();
        ui->layout->addWidget(videoBox, i / 4, i % 4);
    }
#endif

    // 绑定头像按钮点击事件
    connect(ui->avatarBtn, &QPushButton::clicked, this, &MyselfWidget::onAvatarBtnClicked);
}
```

这样一来，点击头像按钮后就会触发 `onAvatarBtnClicked()` 槽函数。在槽函数中，我们需要依次完成三个步骤：**弹出文件对话框、读取图片数据、设置头像并上传**。

首先是文件选择对话框。Qt 提供了 `QFileDialog::getOpenFileName` 这个静态方法，它可以直接弹出系统的文件选择窗口，并返回用户所选文件的路径。其函数签名如下（板书内容）：

```c++
QString QFileDialog::getOpenFileName(QWidget *parent = nullptr,
                                     const QString &caption = QString(),
                                     const QString &dir = QString(),
                                     const QString &filter = QString(),
                                     QString *selectedFilter = nullptr,
                                     QFileDialog::Options options = Options())
```

这是一个便捷的静态函数，如果用户点击取消，它会返回空字符串。我们在代码中这样使用：

```c++
void MyselfWidget::onAvatarBtnClicked()
{
    // 弹出对话框，从本地磁盘选择图片
    QString fileName = QFileDialog::getOpenFileName(
        nullptr, "修改图像", "", tr("Images (*.png *.jpg)"));

    if (fileName.isEmpty())
    {
        LOG() << "选择头像取消";
        return;
    }

    LOG() << fileName;
    ...
}
```

当用户选择文件后，我们拿到的就是图片的路径。但仅仅有路径还不够，下一步要做的是读取文件内容，也就是把这张图片加载到内存里。为了让读写文件操作在其他地方也能复用，我们将其封装在 `util.h` 中：

```c++
// 读文件：读取所有二进制内容到 QByteArray
static inline QByteArray loadFileToByteArray(const QString &fileName)
{
    QFile file(fileName);
    bool ok = file.open(QFile::ReadOnly);
    if (!ok)
    {
        LOG() << "文件打开失败！";
        return QByteArray();
    }
    QByteArray content = file.readAll();
    file.close();
    return content;
}

// 写文件：将 QByteArray 内容写入文件
static inline void writeByteArrayToFile(const QString &fileName, const QByteArray &content)
{
    QFile file(fileName);
    bool ok = file.open(QFile::WriteOnly);
    if (!ok)
    {
        LOG() << "文件打开失败！";
        return;
    }
    file.write(content);
    file.flush();
    file.close();
}
```

`QFile` 的读写模式要注意区分，读文件用 `QFile::ReadOnly`，写文件用 `QFile::WriteOnly`。同时，记得在读取失败时要及时返回，避免后续逻辑出错。

有了文件内容之后，我们还需要将它转换为按钮可以显示的图标。这里用到 `QPixmap::loadFromData` 来加载图片数据，然后再生成 `QIcon`：

```c++
static inline QIcon makeIcon(const QByteArray &imageData)
{
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    QIcon icon(pixmap);
    return icon;
}
```

于是，完整的槽函数逻辑如下：

```c++
void MyselfWidget::onAvatarBtnClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr, "修改图像", "", tr("Images (*.png *.jpg)"));

    if (fileName.isEmpty())
    {
        LOG() << "选择头像取消";
        return;
    }

    LOG() << fileName;

    // 获取图片数据
    QByteArray fileData = loadFileToByteArray(fileName);
    if (fileData.isEmpty())
    {
        LOG() << "读取文件失败！";
        return;
    }

    // 将图片设置为按钮图标
    ui->avatarBtn->setIcon(makeIcon(fileData));

    // 后续：上传图片到服务器
}
```

运行程序后，点击头像按钮即可弹出文件对话框，选择一张本地图片后，按钮图标会立即更新为新头像。如果用户点击了取消，就要用 `isEmpty()` 判断并提前返回，否则后续会出现空文件处理的错误。

#### 在按钮中实现圆形用户头像

我们继续完善用户头像按钮的功能。最初的思路是：用户点击按钮，选择一张图片作为头像，然后将其设置到按钮的图标上。但是实际运行时，发现了一个问题：图像虽然加载了，但并没有填充满整个按钮区域。原因在于我们选择的头像图像本身尺寸很小，比如只有 `18×18` 像素，而按钮的大小是 `60×60` 像素，这就导致按钮中只显示了图像的一部分。

为了解决这个问题，需要将图像缩放到按钮大小（60×60），这样才能填充满整个按钮。Qt 提供了 `QPixmap::scaled()` 方法，可以方便地完成这一操作。缩放时，我们一般选择 `Qt::IgnoreAspectRatio` 来忽略宽高比，并且使用 `Qt::SmoothTransformation` 提升缩放后的图像质量。

不过，做到这里还不够。即便图像被放大填充了整个按钮，它仍然是一个矩形图像。而我们希望用户头像是一个**真正的圆形**。之前按钮之所以看起来是圆的，是因为给按钮设置了样式（`border-radius: 30px;`），但头像图像本身仍然是方的。为了实现真正的圆形头像，需要对图像进行裁剪。

在 Qt 中，我们可以借助 `QPainter` 和 `QPainterPath` 来实现。具体做法是：

1. 创建一个与目标大小一致的透明画布 `QPixmap output`。
2. 使用 `QPainter` 在这张画布上绘图，并设置抗锯齿。
3. 定义一个圆形的 `QPainterPath`，作为裁剪区域。
4. 将缩放后的图像绘制到画布上，并受圆形路径裁剪。
5. 最后将结果转换为 `QIcon`，返回给调用者。

对应的工具函数如下：

```c++
// util.h

static inline QIcon makeCircleIcon(const QByteArray &imageData, int radius)
{
  QPixmap pixmap;
  pixmap.loadFromData(imageData);
  if (pixmap.isNull())
    return QIcon();

  pixmap = pixmap.scaled(radius * 2, radius * 2,
                         Qt::IgnoreAspectRatio,
                         Qt::SmoothTransformation);

  // 将 pixmap 裁剪为圆形
  QPixmap output = QPixmap(pixmap.size());
  output.fill(Qt::transparent); // 背景透明

  QPainter painter(&output);
  painter.setRenderHint(QPainter::Antialiasing);

  // 创建圆形裁剪路径
  QPainterPath path;
  path.addEllipse(0, 0, radius * 2, radius * 2);

  // 设置裁剪路径
  painter.setClipPath(path);
  painter.drawPixmap(0, 0, pixmap);

  QIcon icon(output);
  return icon;
}
```

这样，我们就完成了一个可以直接生成圆形头像图标的方法。调用时只需要传入图像的字节数据和目标半径，就能得到一个裁剪好的圆形图标，再把它设置到按钮上即可。

运行效果是：当用户选择一张头像图片后，程序会将其缩放并裁剪成圆形，最终显示在头像按钮中。这就解决了图像过小、不完整显示，以及头像图形并非真正圆形的问题。

### 修改密码功能的设计与实现

在用户资料管理模块中，修改密码是一个常见的功能点。通常它需要单独的输入与验证逻辑，并且和修改昵称、头像等资料相对独立。因此在设计时，可以将修改密码作为一个独立的对话框进行处理，而不是直接混在主资料修改界面中。这样既能保持逻辑清晰，也方便后续扩展。

从界面交互的角度看，流程大致如下：用户进入个人资料页面，点击“修改密码”，弹出一个新的密码对话框。在这个对话框里，用户需要输入新密码并确认输入，如果格式正确且两次输入一致，就允许提交；否则在下方提示区域显示错误信息。提交完成后返回主页面，取消则直接关闭窗口。

界面结构上，新密码对话框通常包含以下几个部分：

- 标题栏与说明文字
- 新密码输入框与确认密码输入框（设置为密码模式，不显示明文）
- 提示区域（用于显示校验结果，例如格式错误或不一致）
- 底部操作按钮（提交 / 取消）

**1. 修改密码对话框**

在实现上，修改密码的功能通过一个单独的 `NewPasswordDialog` 类完成。它继承自 `QDialog`，主要代码如下：

```c++
#include "newpassworddialog.h"
#include "ui_newpassworddialog.h"

NewPasswordDialog::NewPasswordDialog(QWidget *parent)
  : QDialog(parent), ui(new Ui::NewPasswordDialog)
{
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  connect(ui->cancelBtn, &QPushButton::clicked, this, &QDialog::close);
}

NewPasswordDialog::~NewPasswordDialog()
{
  delete ui;
}
```

这里去掉了默认窗口边框，并为取消按钮绑定了关闭动作。UI 设计时，两个输入框都需要设置 `EchoMode` 为 `Password`，确保用户输入时不会显示明文。提示区域则可以通过修改 `QLabel` 的文字和样式动态反馈用户输入的合法性。

**2. 修改个人资料对话框**

在资料修改的主对话框 `ModifyMyselfDialog` 中，通过按钮触发密码对话框的显示。代码如下：

```c++
#include "modifymyselfdialog.h"
#include "ui_modifymyselfdialog.h"
#include "util.h"
#include "newpassworddialog.h"

ModifyMyselfDialog::ModifyMyselfDialog(QWidget *parent)
  : QDialog(parent), ui(new Ui::ModifyMyselfDialog)
{
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  ui->passwordWidget->hide();

  connect(ui->submitBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::onSubmitBtnClicked);
  connect(ui->cancelBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::onCancelBtnClicked);
  connect(ui->passwordBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::showPasswordDlg);
  connect(ui->changePasswordBtn, &QPushButton::clicked, this, &ModifyMyselfDialog::showPasswordDlg);
}

ModifyMyselfDialog::~ModifyMyselfDialog()
{
  delete ui;
}

void ModifyMyselfDialog::onSubmitBtnClicked()
{
  LOG() << "提交";
}

void ModifyMyselfDialog::onCancelBtnClicked()
{
  close();
}

void ModifyMyselfDialog::showPasswordDlg()
{
  NewPasswordDialog *dlg = new NewPasswordDialog();
  dlg->exec();
  delete dlg;
}
```

这里 `passwordWidget` 初始时隐藏，用户点击“修改密码”后才会调用 `showPasswordDlg()`，弹出 `NewPasswordDialog`。`exec()` 方式确保密码输入是模态对话框，用户必须完成操作后才能返回。

#### 密码校验功能实现

在用户信息修改中，密码是一个必须严格校验的输入项。为了保证安全性，我们对密码设定了如下限制条件：

1. 密码由 **数字、大写字母、小写字母、特殊字符** 组成。
2. 至少包含两类字符。
3. 长度在 **8–16 位** 之间。

当用户输入新密码时，需要对输入结果进行验证：既要检查是否满足规则，也要保证两次输入一致。

**1. 验证时机的选择**

对于验证的“**时机**”，一般有两种思路：

- **方式一：实时验证**
   用户每输入一个字符就进行判断。如果不是合法字符，立即拦截或提示。这样保证了输入框中始终只有合规字符，但实现上要捕获键盘事件，逻辑稍微复杂。
- **方式二：编辑完成后整体验证**
   等用户输入完成（触发 `editingFinished` 信号）时再统一检查。这种方式实现起来更简单，效率也更高。

我们在这里采用**第二种方式**。
 `QLineEdit` 提供了 `editingFinished` 信号：当用户按下回车或输入框失去焦点时，会触发该信号。因此我们在构造函数里，将两个密码输入框的 `editingFinished` 信号绑定到校验槽函数 `onEdittingFinished`，就能在用户完成输入时自动触发验证。

**2. 对话框代码结构**

修改密码对话框 `NewPasswordDialog` 的基本逻辑如下：

```c++
NewPasswordDialog::NewPasswordDialog(QWidget *parent)
  : QDialog(parent), ui(new Ui::NewPasswordDialog)
{
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  connect(ui->submitBtn, &QPushButton::clicked,
          this, &NewPasswordDialog::onSubmitBtnClicked);
  connect(ui->cancelBtn, &QPushButton::clicked,
          this, &QDialog::close);

  // 绑定两个输入框的编辑结束信号
  connect(ui->passwordEdit1, &QLineEdit::editingFinished,
          this, &NewPasswordDialog::onEdittingFinished);
  connect(ui->passwordEdit2, &QLineEdit::editingFinished,
          this, &NewPasswordDialog::onEdittingFinished);
}
```

用户在两个输入框中输入密码后，只要输入结束就会触发 `onEdittingFinished()`，而其中会调用 `checkPasswordEdit()` 来做具体验证。

**3. 密码验证的三步流程**

在 `checkPasswordEdit()` 中，主要有三个检查步骤：

1. **是否为空**
    如果任意一个输入框为空，直接提示“密码不能为空”。
2. **是否满足条件**
    使用辅助函数 `passwordValid()` 检测密码是否符合要求。这个函数会依次验证：
   - 长度是否在 8–16 位之间；
   - 每个字符是否为数字、大小写字母或特殊字符；
   - 是否至少包含两类字符。
3. **两次输入是否一致**
    如果两个输入框的内容不一致，则提示“两次输入的密码不一致”。

如果三步全部通过，则认为输入有效，清空提示信息。

**4. 密码条件验证实现**

关键函数 `passwordValid(const QString &password)` 的逻辑如下：

```c++
QString NewPasswordDialog::passwordValid(const QString &password)
{
  if (password.length() < 8)
    return "密码长度不能小于8位！";
  if (password.length() > 16)
    return "密码长度不能大于16位！";

  enum CharType { Upper, Lower, Digit, Punct };
  QMap<CharType, int> charTypeMap;

  for (int i = 0; i < password.length(); i++) {
    QChar ch = password[i];
    if (ch.isUpper()) charTypeMap[Upper] = 1;
    else if (ch.isLower()) charTypeMap[Lower] = 1;
    else if (ch.isDigit()) charTypeMap[Digit] = 1;
    else if (ch.isPunct()) charTypeMap[Punct] = 1;
    else
      return "密码中只能包含数字、字母及标点符号！";
  }

  int totalCount = 0;
  for (auto &e : charTypeMap) totalCount += e;

  if (totalCount < 2)
    return "密码中必须包含至少两类字符！";

  return "";
}
```

这里借助了 `QChar` 提供的几个方法：

- `isUpper()`：是否为大写字母
- `isLower()`：是否为小写字母
- `isDigit()`：是否为数字
- `isPunct()`：是否为标点符号

通过一次遍历，不仅可以判断字符是否合法，还能统计密码包含了多少种类别。如果类别数少于 2，就直接判定不合格。

**5. 提交逻辑**

当用户点击“提交”按钮时，会调用 `onSubmitBtnClicked()`：

```c++
void NewPasswordDialog::onSubmitBtnClicked()
{
  if (!checkPasswordEdit())
    return;   // 验证失败直接返回

  password = ui->passwordEdit1->text();  // 保存密码
  close();  // 关闭对话框
}
```

随后，外部调用 `getPassword()` 获取结果。如果用户点击了取消按钮，则返回的密码为空，这样可以区分两种操作。

**6. 整体流程总结**

1. 用户点击“修改密码”，弹出对话框。
2. 输入两次密码，完成后触发 `editingFinished` 信号。
3. 调用 `checkPasswordEdit()`，依次检查：
   - 是否为空；
   - 是否符合规则（长度、字符合法性、至少两类字符）；
   - 两次是否一致。
4. 验证通过，允许提交；否则在提示框显示错误信息。
5. 点击提交时再次调用验证，若成功则保存密码并关闭窗口。

### 上传视频页面分析与实现

在这一节课中，我们重点讲解了上传视频页面的整体结构与实现思路。上传功能不仅仅是把视频文件传到服务器，还需要配合一个上传信息对话框，让用户填写视频的标题、封面、简介、分类和标签等内容，从而便于平台后续展示和筛选。

**1. 上传视频的逻辑流程**

当用户在“我的页面”中点击“上传视频”按钮时，程序并不会直接弹出上传视频对话框，而是**先打开文件选择对话框**，让用户选择要上传的视频文件路径。

- 一旦拿到路径，系统会立即开始上传视频到服务器；
- 与此同时，会显示“上传视频对话框”，供用户填写视频的基本信息。

在上传过程中，对话框的顶部区域会显示上传进度：

- 上传中 → 显示“上传中”；
- 上传完成 → 显示“上传完成”，并在右侧出现一个完成标记图标。

视频的封面图有两种情况：

1. 默认封面为视频的首帧画面；
2. 用户可以点击“更改封面图”按钮，从本地磁盘选择喜欢的图片替换封面。

在封面和上传信息之下，还包括标题输入框（最多 80 个字）、简介输入框（最多 1000 个字）、视频分类选择（与首页分类保持一致）、视频标签（随分类动态变化）等。最后是“提交”按钮，点击后用户填写的信息会和视频一起上传到服务器。

由于上传页面控件较多，如果全部直接堆在一个固定大小的窗口里会显得非常拥挤，所以**整个页面都放在 `QScrollArea` 中**，当内容超过界面高度时，可以通过滚动条查看。

**2. 上传页面的布局实现**

我们在 Qt Designer 中新建了一个界面 `UploadVideoPage`，设置窗口大小为 `1350 * 792`，然后按如下步骤进行布局：

1. **添加 QScrollArea**

   - 拖拽一个 `QScrollArea` 到页面中，命名为 `scrollArea`；
   - 对 `UploadVideoPage` 应用垂直布局；
   - 设置 `RightMargin=3`，`BottomMargin=10`，其余 Margin 设为 0，Spacing 设为 7；
   - 在 `scrollArea` 内添加一个 `QWidget`（命名为 `pageBg`），再对其应用垂直布局。
   - `pageBg` 的 `minimumSize` 高度设为 981，`maximumSize` 设为 `1350*981`，保证内容高度充足。

2. **添加主要结构控件**
    在 `pageBg` 中从上到下依次拖拽 7 个 `QWidget` 和 2 个 `QLabel`：

   - `uploadWidget`：上传进度显示区
   - `myVideo`（QLabel，文本“我的视频”）
   - `videoContent`：视频内容区域（封面等）
   - `titleContent`：标题输入区域
   - `briefIntroduce`：简介输入区域
   - `kindContent`：分类区域
   - `tagContent`：标签区域
   - `seperatorLine`（QLabel，用作分割线，高度设为 1，清空文本）
   - `btnWidget`：底部按钮区

   给 `pageBg` 应用垂直布局，设置 `LeftMargin=20`，`TopMargin=16`，`RightMargin=20`，`BottomMargin=0`，`Spacing=20`。

3. **设置各控件属性（调试时用背景色区分）**

   - `uploadWidget`：背景色 `rgb(170,170,0)`，高度固定 118；
   - `myVideo`：背景色 `rgb(170,255,127)`，高度固定 24，文本为“我的视频”；
   - `videoContent`：背景色 `rgb(170,255,255)`，高度固定 174；
   - `titleContent`：背景色 `rgb(255,170,127)`，高度固定 69；
   - `briefIntroduce`：背景色 `rgb(255,170,255)`，高度固定 180；
   - `kindContent`：背景色 `rgb(85,170,255)`，高度固定 69；
   - `tagContent`：背景色 `rgb(170,170,255)`，高度固定 69；
   - `seperatorLine`：高度 1，无文本；
   - `btnWidget`：背景色 `rgb(255,85,127)`，高度固定 48。

通过这种方式，上传视频页面的框架就搭建完成了，后续可以在这些区域内部再进行水平布局或控件细化，比如上传进度条、封面选择按钮、标题输入框、简介文本框、分类下拉框、标签动态按钮等。





帮我把下面本节课新写的代码和老师课上的讲话结合在一起整理成博客，要注意课上的讲话是通过语音转写成文字的，所以有些转写错误的地方需要对照一下笔记的内容，此外也要避免过多的分点陈述，做好上下文衔接，不要擅自修改板书中的代码，也不要反复强调老师说了什么：“

板书中的内容：“

主题：上传视频页面分析与实现

【上传对话框页面分析】
视频信息对话框中元素整体为上下结构，因为界面中元素较多，页面中显示不下，因此界面中所有元
素都处于QScrollArea中，界面结构大致如下：

先显示：选择视频文件的对话框--文件选择对话框
用户选择要上传的视频的路径，将路径拿到之后，视频就开始上传到服务器
在视频上传过程中，同时显示上传视频对话框-一—一目的：让用户对正在上传的视频进行描述
说明

视频在上传时，此处显示：上传中

视频上传完成后，此处显示：上传完成。并在右侧有一个图标

视频封面图：默认情况为视频首帧图②点击更改封面图按钮，用户可以从本地磁盘选择喜欢的图像作为视频的封面图

后序的这些控件是对视频基本信息进行描述

注意：该页面中控件比较多，所有控件全部在一个页面显示会非常拥挤，因此整个页面都处在QSCrollArea中

【上传页面的布局实现】
添加一个设计师界面，命名为UploadVideoPage，geometry的宽高设置为1350*792，然后按照以下
步骤布局：
①拖拽一个QScrollArea到UploadVideoPage中，objectName修改为scrollArea，然后选中
UploadVideoPage点击垂直布局，将UploadVideoPage的RightMargin设置为3，BottomMargin设置
为10,其余Margin全部设置为0，Spacing设置为7;拖拽一个QWidget到scrollArea中，objectName
修改为pageBg，然后选中scrollArea点击垂直布局，将scrollArea的scrollAreaWidgetContents的
Margin和Spacing全部设置为0，将pageBg的minimumSize的高度设置为981，将maximumSize的宽
高设置为1350*981
②拖拽七个QWidget和两个QLabel到pageBg中上下摆放，从上往下依次为QWidget、QLabel、
QWidget、QWidget、QWidget、QWidget、QWidget、QLabel、QWidget,objectName从上往下依
次修改为uploadWidget、myVideo、videoContent、titleContent、brieflntroduce、
kindContent、tagContent、seperatorLine、btnWidget，然后选择pageBg点击垂直布局，将
pageBg的LeftMargin设置为20，TopMargin设置为16，RightMargin设置为20，BottomMargin设置
为0，Spacing设置为20;将uploadWidget将的背景色设置为rgb(170,170,0)，minimumSize和
maximumSize的高设置为118;将myVideo将的背景色设置为rgb(170,255,127)，minimumSize和
maximumSize的高设置为24，文本设置为"我的视频"；将videoContent将的背景色设置为rgb(170,
255,255)，minimumSize和maximumSize的高设置为174;将titleContent将的背景色设置为
rgb(255,170,127)，minimumSize和maximumSize的高设置为69；将brieflntroduce将的背景色设

置为rgb(255,170,255)，minimumSize和maximumSize的高设置为180;将kindContent将的背景色
设置为rgb(85,170,255)，minimumSize和maximumSize的高设置为69；将tagContent将的背景色
设置为rgb(170,170,255)，minimumSize和maximumSize的高设置为69;将seperatorLine的
maximumSize的高设置为1，文本内容清除掉；将btnWidget将的背景色设置为rgb(255,85，127)，
minimumSize的高设置为48;

后续内容下节课继续

”

老师课上的讲话：“
接下来我们看一下上传视频页面的布局事项。Ok当用户点击我的页面当中上传视频按钮时，首先它会弹出一个文件选择的对话框，让用户去选择要上传的视频，ok这一块大家把逻辑上简单梳理一下。好，上传视频的按钮，这个按钮点击了之后，它不是立马给我们弹出上传视频对话框，而是先显示一个文件，或者说打开文件，或者说选择视频文件的对话框，对吧？就是我们的文件选择笔画稿，这个文件选择对话方式咱们之前已经用过了，我们在设立用户头像的时候，一点点完之后给我们弹出一个就是对话方式，让我们去选择具体图像的位置，对吧？好，上传视频它也是一样的，先弹出个对话框让用户去选择要上传的视频，要传到上传的视频，将来对话框关闭了之后，我们就能拿到视频的路径对吧？对吧？而且显示视频对话框，用户选择要上传的视频的路径对吧？视频的路径将这个路径拿到之后，将路径拿到之后，我们的视频它就开始上传到的途径，上传到服务器对吧？上传到服务器在视频上传的过程中，在视频上传过程中，那么同时显示视频信息上传视频的对吧？我们就需要将上传设置的对话框给人家显示出来，对吧？显示出来对话框的目的，让用户对方正在上传的上传的视频进行一些描述说明对吧？你上传的视频，它的标题、封面图、视频的简介、视频的分类、视频的标签等等，这些是我们要对上述的事情进行说明了，这样子说明了之后将来在首页当中显示的什么用户，其他的用户就可以根据分类和说明，分类和标签对吧？或者说你的标题等等对视频上进行一定的筛选。接下来我们看一下上短视频页面它长的是什么样子。好，当用户点击上传视频按钮之后，先弹出打开文件对话框，让用户去选择要上传的视频位置，拿到了视频的路径之后，一边上传视频，同时给我们显示上传视频的对话框。好，这个是上传视频的页面。接下来我先给大家说明一下这个页面当中的每一个控件它大概是什么意思，完了之后我们再把控件的页面的结构给大家分析一下，来粘贴管。好，首先就是在最上面的上面这部分它显示的是上传视频的相关信息，ok。也就是这个位置它那部分是上传视频的进度信息或者说视频的老师视频上传的进度信息，也就说在最底下这个位置，大家可以注意看用仓它现在出现的是上传中，现在这部分的信息是上传中，那就说明我们的视频正正在上传对吧？你比如说视频在上传时，此处显示上传中对吧？上传中如果视频上传完重复，为此处就显示事情上传完成或者说显示上传完成对吧？上传完成利用在右侧有一个图标，它的蕴藏就是有一个图标来进行标注，视频它现在已经上传完成了。Ok在我们的页面底下他还给了一个说明对吧？这个是这样子的，把它拿过来，你可以在里面简单的对比一下，对吧？对比一下，把他们反过来。我们看一下上传完成了之后显示上传完成，并且可能显示一个图标对吧？图标。Ok，这个页面当中的几个控件，你看左侧这个位置它显示了一个就是文件夹，这样子的一个图片，然后上面这个位置显示的是他说了这里是文件名，直接取源文件的名称即可，对吧？源文件的名称即可。所以说这个页面当中的几个控件它都是挺有利宝，就完了a比完了大家都是有力保在上方，最终它也是挺利宝对吧？我们给的文件夹三也是有利宝，包括了的显示，图像的位置上它也是有利的，当然都是有利的。好，再往下来走，等一下这个位置。底下再往下来走，比如说整体它实际上是对视频的信息进行描述的，好，我还是放这个整体后续的这些部件是用来对视频的基本信息进行好处的对吧？后续的这些业务当中内容，首先我们看到的中间的这部分，这一块它是视频的封面图，视频封面图对吧？这个视频封面图它有两种显示的效果，第一种第一种也就是默认情况，默认默认情况为默认情况为就是术前的首帧图对吧？这表示首帧是术前的首帧，也就是说它的你事先添加成功了之后，它的5000的秒对吧？就是的数据形成的一个画面给它拿出来了，也就是它的首帧图，ok再往下来走，还有另外的一种方式，因为有些情况下用户他可能对于首帧图片不是非常的满意，不是非常的满意，我们可以点击更改封面的更改封面图的按钮，对吧？点击这个按钮，然后用户可以从本地磁盘选择喜欢的封面，喜欢的头像对吧？头像作为知识频道封面图，这个封面图将来也会在我们的首页当中对吧？来进行显示。好，在这个页面当中我们所看到的右侧给到默认系统默认选择视频的第一帧作为封面，它实际上就是一个有力保说明符号对吧？然后我们在左侧这个位置它有一个红色的对方有一个心，对吧？然后还有一个封面，这两个统一都是这个地方好，他们两个都是手机不只不过一个里面放的心，一个里面放的是封面对吧？封面闹钟给到图像显示的时候，它其实也是一个福利的，再往下走底下它是一个对吧？封面图注意这个位置，它实际上是实际有一个按钮，好吧，实际上它这里面是一个按钮对吧？点击出来了之后，我们才可以选择本地磁盘里面的某一张图片作为视频的封面。好，再往下来走，就是我们给到视频的标题对吧？好，这个视频的标题同样我们给到底下这个位置就是带红色的点，然后还有标题，他们两个也都是QQ，也都是q点，然后像红点了表明无色或者说红色心。我们给到红色的拼音，它这里面的表明了就是我们的b选项b强了，你在里面你必须聊天，你上传那个视频，你不能布置视频的标题了，对吧？不能布置视频的封面了，像底下的简介，我们所给的简介，然后还有分类对吧？还有我们所给的标签可选，可填可付，那就根据你用户自己的想法来，你想填你花钱了对吧？你不想填也可以，当然一般情况下建议最好的还是花钱了，这样子的话用户将来就可以在首页当中根据视频的标签分类对吧？包括了标题和简介来进行视频的筛选问题。好，然后右侧这个位置它是视频的标题对吧？它怎么就是一个q目的，它的话就是一个q拉ID对吧？就是个q拉的，好再往下来走，这个位置它是一个流顺，它还有一个点给大家说明，像视频的标题发最多最多8080个字，最多它的里面是80个字，并且这个位置在输入时右侧有已输入字数和字数和总字数的形式，对吧？你可以看一下在它右侧它这个位置上是有一个有一个9 80，也就说最多你输入80个字符，现在输入了几个，这是视频的描述，信息刚好是9个字，那么再输入一个它这个就变成1080，所以说这个位置上它还有一个空间对吧？还有个空间，这个空间实际上它也是一个提供力量，就是个枢纽对吧？所以说将来对于q拉埃及和它内部的这些输入的内容变化的时候，我们也得需要突破这个信号。好，再往下走底下的这个位置，它是视频的是简介，这么一个视频简介，同理这个视频简介1000最多1000字，对吧？在用户输入时，我们右右下角会有已输入字数和总字数的汽车，也就是这个位置对吧？好了同时也要趴在里面，身上也是一个就LED也是一个q6，包括我们内部的简介，他也是q利宝，然后中间的空间10001000个文字的话，你一行肯定显示不下了，它实际上是一个多行的文本，也就是我的界面当中的这个就是普兰泰斯的案例不会有分配对吧？普兰泰斯的案子。再往下来走就是视频的分类和标签，这个是我们所给的视频分类，视频的分类对吧？此处的分类和首页中的分类是完全相同的，首页当中你有哪些分类，然后把首页当中的这些分类拿过来，直接填充在这个的分类内就可以了，对吧？就可以。好，然后再往下走，底下还有我们所给的标签的信息，这个是我们的标签信息，视频标签这个位置大家要注意我们的视频标签，视频标签刚开始是对吧？没有显示出来的，然后用户选择了分类之后，才会显示该分类下的所有标签。用户他就可以根据显示出来的这一些标签来给视频打标签了，对吧？那就视频打标签，因为刚开始为什么没有显示，因为用户他没有选择这个视频的分类，我们也不知道他到底有哪些标签，所以这几个的暗示动态进行进来的。标签按钮，标签按钮是动态对吧？Ok最后就是我们的提交按钮对吧？提交按钮就不用说了，当用户将视频的描述信息组织完成之后，当用户将视频的描述信息对吧，信息是抢险完成之后，对吧？二点击提交那事情的描述信息就会上传到服务器，那么就会把这个信息把它上传到服务器上去。然后上传完成之后，我们在这个就是切换回对页面能看到吗？这个就是页上传视频页面它整个的一个内部的一些控件的一个简单的说明，整个说明通过我们刚才的简单说明了，其实这一块大家也能够看到咱们给的页面它的布局了，对吧？它的布局它总体上实际上是一个上下布局的方式，我可以把这个画面稍微再给它来大一点。第二层它总体上是一个上下布局，上下布局来注意看，也就是说刚开始刚开始的话肯定是我们视频的上传信息对吧？然后再往下走是我的视频的封面的信息，封面信息我们把我的视频也给它当成一个单独的对吧？再往下走就是视频的封面信息，然后再往下走就是我们所给的标题的这一页对吧？这一页然后再往下走就是视频的简介，再往下走是视频的分类，然后再往下是视频的标签对吧？标签这个位置它是含有有一个显示的，类似于一个分割线一样，最后一个位置就是我们给到当前页面当中的按钮对吧？按钮总体上它是一个上下的布局的方式，然后在内部的话，在这个视频内部的话，我们就可以以左右布局的这种方式来进行处理了，对吧？从上往下，比如说我们刚刚所罗列出来的这一些这些这些它实际上都是 qw ID的一切都是q外地卡，你把它拖进来，拖进来了之后，然后点击一个垂直布局，把每个外地层的高度给它调整一下，我们页面框架就出来了，对吧？页面框架出来了之后，然后我们再往那边去拖 Q就是外地淘q阿里淘或者说去做一个什么TV宝等等，把这个视频就是每一个区域的内部性元素体现出好就可以了。对吧？你比方说我们给到中间这个位置，实际上它的里面就是一个水平布局了，对吧？在里面就是一个水平布局，我给你包上三个外立体，右侧方可以给它放上一个弹簧把它冲过去，这个位置实际上也是一样的，就是一个水平布局，对吧？水平不足，他实际上也是一样的，水平不足补过来就可以了。Ok这个是我们再来给到上传视频页面的分析。刚才有个点忘记给大家说了，上传视频页面当中的元素它比较多，一个页面显示不下，所以说这个页面它整体上都处在一个QC二当中对吧？要注意不要干页面多，或者说我们的控件比较多，所有控件全部在一个页面显示会非常拥挤，因此我们的整个页面都处在QS crorarea对吧？这样子的话，如果内部的这些控件它整体的高超过了界面的高度的时候，在右侧的位置它会显示一个就是垂直滚动条，对吧？我们可以通过拖拽垂直滚动条来查看当前页面当中比较靠下的一些空间。好，这个页面当中的实现步骤，同样我已经把它提前罗列好，放到我们的项目文档当中了。大家下来之后，按照我们项目文档当中所罗列的这些步骤，一步一步的往下去进行操作，就可以把咱们页面文化实现出来，对吧？所以这地方其实也没有什么，我的这些步骤，也是参考着 Ui可能提供好的页面对吧？每一个控件往哪个位置去摆，然后每一个控件它该有什么样的一些样式，实际上在这个表格当中，在设计图当中已经有了，对吧？有了之后我们直接把ux我们提供的一张图转化为qt的一个代码就可以了。Ok来回到我们到项目文档当中，同样我把设计步骤让它截下来，放到板书当中下来，我们就按照它里面所罗列的步骤，一步步往下去走就可以了。Ok先把它翻过来，这个页面稍微有点大，你的一页面一复杂了，它步骤也就比较多了，对吧？刚才我们是截取到它的第三个步骤，截取完了第三个步骤，然后再往下来走，还有他的456456也拿过来摆上去，456再往下走，我们看一下还有它的789摆过来。好，放上来之后，我们接下来就按照它里面给的这些步骤，一步一步一步来走一步一步来走，首先他说让我们添加一个设计师界面，把类的名字把它更改为阿普路德v6配置对吧？然后在 Gl出来它修改为1350792。好，那么现在回到qt格式当中，完了之后点击编辑就回到了我们写代码的页面，选中bit plan，然后右键单击选择添加新文件，我们这层添加的是 Q7的一个UI界面带雷的对吧？点击选择，然后下一步ok把它的名字修改一下，人家给的是upload的upload，录的就是上传vido上传视频的页面对吧？我们再对比一下 uploaduplod不要问题，upload the video page，完了之后点击下一步完成，这样子的话，我们的整个UI界面就把它添加好，添加好了之后，下一步我们就得需要修改一下它的宽和高1350792，ok把页面给它选中，然后是右侧的属性，位置的滚动条往上滑，指的是13521350792，1350，高度在认为792对吧？高度要改成792。好，再往下走，我们第一个步骤他说拖拽一个q4PRO2楼，为什么拖q42楼？刚才的上面已经说明了，对吧？拖进来之后把它的o站它的内容修改为4不用2楼，ok我们先给他拖拽一个。好， Q4q2那就是这个图像对吧？拖进来都进来了之后，他的up拆分内把它修改为4个r他现在就是4个人对吧？点完了之后，然后点击 node video配置，选择垂直布局，然后将它的right market修改为三Dota，market给它修改为10，其余market全部修改成0。好，我们先把它选中了之后来上一个垂直布局，对吧？它就撑开了之后，然后选中阿波罗的v6配置，将属性调了往下滑，找到拉顶对吧？他说将right数等于3包，它不能修改为10，right，3修改为3，都把它修改为10，其余的一些拉丁给它全部修改成0，这个也是0，只修改的是u和包袱， Right？到此。好，完成了之后将 space修改为7，我们给到间距，原子火元素质量间距把它给成一个7对吧？7。然后完了之后我们再拖出来一个平稳的特征，到死光热当中不摘，从内部修改为偏移值b级，也就是说他将来想用这个外力图作为背景对吧？这个 ok我们就好拖拽一个进来，内容修改为配置ID配置bjbj好，完成了之后选中4个肉肉，然后给他来上1个就是垂直布局对吧？来上1个垂直布局。Ok我们刚刚所添加的 App真的给它添加上背景色了，backjround到Col然后把它的背景颜色随便的给他选择一个背景颜色，选择好了之后分号加上，然后点单击确定，这样子的话我们的背景就把它涂在上面了。拖拽上来了之后点击垂直布局，将是不是安卓到内的控件对吧？把它的market和space全部设置为0，ok选中了之后往下滑，将market和space全部给它设置为0对吧？这样子的话我们刚刚所添加的配置BD，它就将整个的思路按照给它填充满了对吧？好再往下走了，他说将配置BD的高度对吧？高度这个是最小的高度，设置为981981，然后将它的宽高这个高度，然后宽高了给它设置为最大的宽高设置为1350980，好，我们就按照他给的来吧，说的是我们的性质DJ对吧？最小的高度设置为981，最小的高度这个高度最小的高度设置为981对吧？981，然后把他的最大的高度和宽度设置为1350981，最大的宽度是1350高度，然后把它改成一个就是981对吧？981完成了之后再让他往下来走，同志们注意看，这是第一步可能处理完了。第二个他让我们拖拽7个外力和两个KO label到配置比例当中，对吧？上下摆放。来，你注意摆放的位置，它从上往下依次是KO的外立堂、KO李波，这个是外地考，然后最后地方它的倒数第二个对吧？这是第二个，总共是7个奉献，要不就后来脱了老婆，这个是第一个对吧？一个然后再让它往下来走，然后把它往窄的来一点。第二个它是一个qe是一个QQ宝，然后再往下来走，我们的我把它删掉对吧？删掉，那么还是给它把颜色加上一CK，这样都有稳定让cos发了，添加上一个背景颜色，比方说就变成颜色了，分好了给它加上点击应用ok，把它拿掉来，完了不知道它往下面走，那我就做了1个了，2个现在3个空间了，4个5个6个对吧？6个7个，他第六个好像也是一个独立的1234567来看一下， Q外立场q力保12345充其量是55个，你好，再见。和谁？一个两个。好，12345，然后 qdbqyd最底下是一个q李博对吧？ Qq，然后底下给一个q里头，这样子的话我们就把这些控件了给他吐完了对吧？吐完了之后他说将 Update内容从上往下依次修改为阿普路德外立体，我们一个个来从上往下把它修改成阿普路德外立体，阿普路德w ID这一切阿普路德外地图。Ok再往下来走到第二的话就是我们所谓的QQ对吧？这个模式哪里有把他们给投哪里有。好再往下来走，就是我的三第三个问题，我把它修改成微丢考证，就这个对吧？Vrd有video，CD n Coontevedo他探讨好再往下走，下一个在这个是开通他探讨 tittle他们怎么去探索对吧？Tfttletscontet标题抬头问题好了，再往下走是我们的简介，对吧？再见。 Brief brief introduce bries brief includes ingro d 9cintrotoce我看一下， introtoc没错，再往下走了，我们的看到淘汰点是。好，这个是看得到问题。比如说参量的Conte减二的问题，对吧？再往下走，这个是我们在里面给的。我们看一下他们都讨论，然后是泰国团队就是标签和标签，然后全国因为这泰尔的contet第二个可能然后再往下来走，是我们给的qd宝对吧？土地宝它是separate和就是一个分隔线，seperatr separate和刚才这个没有设置吗？设置了，也就是设置对的，塞普瑞和s一p一r at和site和那就是分割线seperhr sepiq最后一个是我们的btn外地图，这个是我们的btn外地图。Ok带过来BT nw ID这一切把它改正确对吧？改正确。这样子的话我们顺便把内部颜色给它都去换一下，颜色不一样，我们就知道哪个空间在哪个位置，对吧？有没有确定，然后把这个颜色也给它去换一下，直接选中，然后你给他去添加自己，你想把它设计成颜色，什么颜色就给他什么颜色，直接点就可以了，对吧？你给他去画起来，添加颜色给人一种反应，出色的话，所以好完了之后把它的颜色也换过来，选中添加颜色，然后给成堆成来自这个颜色这里最后还有一个把它的颜色也给过来，颜色感觉都没得选了。好确定好，那完了之后还有我们的两个pod宝对吧？两个pod宝，把两条内部的背景颜色也给他定出来，一CK我有ID到cos，当然等到他了，然后把你的房间讨论一下，这个颜色我们就把它变成这种绿色分号，加上确定最底下方是我们给的分割线对吧？没有考虑到一CK也大家都忘了到CEO的话背景颜色，然后把它改成这种。你走起立。分号加上来，然后确定对吧？确定好，那么把这几个控件给他添加好了之后，然后再往下谈，他说对吧？配置BD点击垂直布局将配置BD的life20Top16设置为16，我们先一步往下来走，先选中我们的配置BD，然后来看看垂直布局对吧？好，然后把它选中往下拖，他说将 Left是不是20，然后将 Top Top二设置为十六，right？也设置为20Top10×16，right？将配置笔记的net设置为I10，Top16设置为16，我们先一步往下来走，先选中我们的配置BD，然后来上个垂直布局对吧？好，然后把它选中往下拖，他说将 Let是20，然后将 Top Top二设置为16，right？也设置为20Top10×16，外层也是朝暗示包头在这个设置的是0，包头设置的是0，然后将 CD的间隔把它改成20等于间距变成20了，对吧？间距改成20了。好，完了之后再往下走，底下这个位置就是修改它的每一个空间的背景颜色了，对吧？ Ok我们先当然他还要去修改它的最大的一个高度，首先他说将阿普路德外力图把它的高度最小和最大高度修改成118阿普路德外力图，选中阿普路德外力图，阿普路德外力图就最上面这个位置，把它的最大和最小的高度修改成118，这个是我们的最小高度，118最大高度我们也把它修改成就是118对吧？最小和最大的高度改成118。好完了之后将满为主的一辈子颜色修改，把它的最小和最大的高度设置成24，我的本事是从我的视频，ok我们到马路它对吧？往上走最小和最大的高度是24，然后它的最大高度也是24对吧？24把内部的文本修改为我的视频，对我的视频完了之后我们再往下来走，注意看下一个，他说叫video亢奋，好你就舍不得那个封面图了，不一定可能他最小和最大的高度设置成174174，这个位置唯一丢卡特点最小和最大的高度的高度174。好，最大的高度也给174最大水管，再往下来走就是我们开通可能把它的最小和最大的高度设置为69，v六抬头看一下，我的抬头等设置为69，高度给成69，然后最大的高度也设置为69。好，再往下来走，就到达我们的视频简介了，对吧？视频简介的高度给它设置成1180。视频简介，对布瑞夫64，ok把它的最小高度给出180，然后将最大的高度也设置为180最大180。点完了之后再往下走的是我们的碳的就是分类的标签，最大的高度给它设置成69，往下走，这个是我们给它分类，这一步要把它给成一个69对吧？69。最小的高度给成69，最大的高度也把它给成一个69给过来。你看我们的高度现在页面当中已经放不下了，那就可以拖它右侧滚动条了，对吧？滚动条。Ok，刚才我们设置的是看到设置完了之后，还有没有看过标签？分类的标签的位置，它的高度设置的也是69，来高度给成6969最大高度最小包装都变成69对吧？69。Ok69，完了之后，完了之后还有我们的分割线把它的高度给的是48，分割线的话就等于我们的分割线正好。分割线在这个位置把它的高度改成4848，我看一下最小高度设置成48，最大的高度也给它设置成48，对吧？48。你怎么把18好宽高度？错了，他说这个位置将我们的第一天y里头的高度48设置的是48，刚刚我们设置的是4分割线对吧？他来上一个扛着贼，扛着贼撤销一下，将它的高度设置成4048，然后最大的高度也给成4048，看起来它的分隔线梁确实看起来有一点点的宽，分割线有点宽的话没关系，到时候我们再来通过样式的话去进行控制，对吧？控制在这个位置看错了。他说将分割线的高度设置的，一是就说分割线怎么给它开宽了，分割线的高度在里面设置的是一，然后将文本内容给它清除掉，一个长一小时，最大的高度设置的是一选中，然后把它的max高度设置的是一，这样子的话它就成了一条线对吧？然后把它内部的文本先撤销一下，把它内部文本先清除掉对吧？把它清除，清除掉了之后，然后把它的最大高度在这个位置把它设置成一对是不是最大的高度和高度，我看一下他说谁这个选择错了，最大的高度上设置成一就是我们的分隔线能看到不？那这样子的话，我们就把这个页面总体的数据给他处理完了。”