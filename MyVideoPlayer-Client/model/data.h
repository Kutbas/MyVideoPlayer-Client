#ifndef DATA_H
#define DATA_H

#include <QList>
#include <QString>
#include <QHash>

// 该文件定义了程序中各种数据对应的数据结构
namespace model
{
    // 分类和标签
    class KindAndTag
    {
    public:
        KindAndTag();

        const QList<QString> getAllKinds() const;                           // 获取所有的分类
        const QHash<QString, int> getTagsByKind(const QString &kind) const; // 获取某个分类下所有的标签
        int getKindId(const QString &kind) const;                           // 获取 kind 对应的 id
        int getTagId(const QString &kind, const QString &tag) const;        // 获取 tag 对应的 id

    private:
        QHash<QString, int> kindIds;
        // 分类-标签
        QHash<QString, QHash<QString, int>> tagIds;
        static int id;
    };

} // end model

#endif // DATA_H
