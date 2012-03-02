#ifndef RULETREEMODEL_H
#define RULETREEMODEL_H

#include <QAbstractItemModel>

namespace Lvk
{

namespace BE
{
    class Rule;
}

namespace FE
{

class RuleTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    RuleTreeModel(const QString &data, QObject *parent = 0);
    ~RuleTreeModel();

    // QAbstractItemModel - read only models

    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex parent(const QModelIndex &index) const;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    // QAbstractItemModel - editable models

    virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                               int role = Qt::EditRole);

    virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

    virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

    // RuleTreeModel

    BE::Rule *invisibleRootItem();

    BE::Rule *itemFromIndex(const QModelIndex &index);

    QModelIndex index(int row, int column, BE::Rule *parentItem) const;

    QModelIndex indexFromItem(BE::Rule *item);

    bool appendItem(BE::Rule *item);

private:
    void setupModelData();

    // helpers
    int rowForItem(const BE::Rule *item) const;
    int columnCountForItem(const BE::Rule *item) const;
    QVariant dataForItem(const BE::Rule *item, int column, int role) const;
    bool setDataForItem(BE::Rule *item, const QVariant &value, int column, int role);

    BE::Rule *m_rootItem;
};

} // namespace FE

} // namespace Lvk

#endif // RULETREEMODEL_H