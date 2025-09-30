#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>

#define TEST_UI

// 从文件路径中提取文件名
inline QString getFileName(const QString &filePath)
{
    QFileInfo fileInfo(filePath);
    return fileInfo.fileName();
}

// 封装日志宏
#define TAG QString("[%1:%2]").arg(getFileName(__FILE__), QString::number(__LINE__))
#define LOG() qDebug().noquote() << TAG

// 读文件：从指定文件中，读取所有的二进制内容，将其保存到 QByteArray 中
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

// 写文件：从 QByteArray 中的内容，写入到指定文件中
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

static inline QIcon makeCircleIcon(const QByteArray &imageData, int radius)
{
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    if (pixmap.isNull())
        return QIcon();

    pixmap = pixmap.scaled(radius * 2, radius * 2, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // 将 pixmap 裁剪为圆形
    QPixmap output = QPixmap(pixmap.size());
    output.fill(Qt::transparent); // 将绘图背景设置成透明的
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing);

    // 创建圆形裁剪路径
    QPainterPath path;
    path.addEllipse(0, 0, radius * 2, radius * 2);
    // 设置裁剪的路径
    painter.setClipPath(path);

    painter.drawPixmap(0, 0, pixmap);
    QIcon icon(output);

    return icon;
}

#endif // UTIL_H
