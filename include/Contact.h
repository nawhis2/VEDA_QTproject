#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QAbstractItemModel>
#include <QList>
#include <QApplication>
#include <QStyle>

enum class DataType {
    GROUP,
    CONTACT
};

struct Contact {
    DataType        type;
    QString         name;

    QString         phone;
    QDate           birthday;
    bool            favorite;
    QString         email;
    QString         location;
    QString         SNS;
    QString         memo;

    Contact*        parent = nullptr;
    QList<Contact*> children;

    int             childIndex(Contact* child) const;
    void            removeChild(Contact* child);
    void            insertChild(int row, Contact* child);
    void            setParent(Contact* parent);
};

class ContactModel : public QAbstractItemModel
{
    Q_OBJECT

    QList<Contact*>     allContacts;
    Contact*            root;
    Contact*            group_Favorite;

private:
    void                setBasicGroup();

    QModelIndex         index(int row, int column, const QModelIndex& parent = QModelIndex())            const override;
    QModelIndex         parent(const QModelIndex& index)                                                 const override;
    int                 rowCount(const QModelIndex& parent = QModelIndex())                              const override;
    int                 columnCount(const QModelIndex& parent = QModelIndex())                           const override;
    QVariant            data(const QModelIndex& index, int role = Qt::DisplayRole)                       const override;
    Qt::ItemFlags       flags(const QModelIndex& index)                                                  const override;
    QVariant            headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public:
    explicit            ContactModel(QObject* parent = nullptr);

    QList<Contact*>&    getList();
    Contact*            getRoot();
    Contact*            getFavorite();

    void                addContact(Contact* contact, Contact* parent);
    void                removeContact(Contact* contact);
    void                clearAll();
    void                deleteTree(Contact*);

    void                toggleFavorite(Contact* contact);
    QModelIndex         indexForContact(Contact* contact) const;
};

#endif // CONTACT_H
