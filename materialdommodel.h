#ifndef MATERIALDOMMODEL_H
#define MATERIALDOMMODEL_H

#include "dommodel.h"

class MaterialDomModel : public DomModel
{
public slots:
    void clickedItem(const QModelIndex&);

public:
    MaterialDomModel(QDomDocument document, QObject *parent=0);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // MATERIALDOMMODEL_H
