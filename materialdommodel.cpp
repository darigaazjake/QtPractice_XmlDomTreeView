#include "domitem.h"
#include "materialdommodel.h"

MaterialDomModel::MaterialDomModel(QDomDocument document, QObject *parent)
    :DomModel(document, parent)
{
    //DomModelのコンストラクタ呼ぶだけ
}

/**
 * @brief （オーバーライド）状態を返す
 * @param index
 * @return
 */
Qt::ItemFlags MaterialDomModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    //indexが指すノードを取り出す
    DomItem *item = static_cast<DomItem*>(index.internalPointer());
    QDomNode node = item->node();

    if (node.nodeName()=="#comment")
        return 0;

    return QAbstractItemModel::flags(index);
}

/**
 * @brief (オーバーライド)指定されたインデックスのデータを返す
 *  columnの値で分岐
 *   0:ノード名
 *   1:属性
 *   2:ノードのテキスト
 * @param インデックス
 * @param 返すデータの種類
 * @return データ
 */
QVariant MaterialDomModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    //DisplayRole以外のroleは無効
    if (role != Qt::DisplayRole)
        return QVariant();

    //indexが指すノードを取り出す
    DomItem *item = static_cast<DomItem*>(index.internalPointer());
    QDomNode node = item->node();

    //if (node.nodeName()=="#comment")
    //    return QVariant();

    QStringList attributes;
    QDomNamedNodeMap attributeMap = node.attributes();

    switch (index.column())
    {
        case 0:
            return node.nodeName();
        case 1:
            for (int i = 0; i < attributeMap.count(); ++i)
            {
                QDomNode attribute = attributeMap.item(i);
                attributes << attribute.nodeName() + "=\""
                              +attribute.nodeValue() + '"';
            }
            return attributes.join(' ');
        case 2:
            return node.nodeValue().split("\n").join(' ');
        default:
            return QVariant();
    }
}
