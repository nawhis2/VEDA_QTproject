#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>
#include <QDateEdit>
#include <QAbstractItemModel>
#include <QList>
#include <QUuid>

enum class DataType {
    GROUP,
    CONTACT
};


struct Contact {
    DataType    type;
    QString       id;
    QString     name;

    // 연락처 전용 필드 (그룹일 경우 무시됨)
    QString     phone;
    QDate       birthday;
    bool        favorite;
    QString     email;
    QString     location;
    QString     SNS;
    QString     memo;

    // 트리 구조용
    Contact* parent = nullptr;
    QList<Contact*> children;
};


class ContactModel : public QAbstractItemModel
{
    Q_OBJECT

    QList<Contact*>  allContacts;
    Contact*    root;

public:
    explicit ContactModel(QObject* parent = nullptr);

    // 필수 override
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // 데이터 제어 함수
    Contact* rootNode(); // 루트 노드 접근
    void setRoot(Contact* root); // 외부에서 루트 설정
    Contact* getNode(const QModelIndex& index) const; // QModelIndex → ContactNode*

    QList<Contact*>&  getList();
    Contact* getRoot();

    void addContact(Contact* contact, Contact* parent);
    void removeContact(Contact* contact);
    // void rebuildModelData();
    QModelIndex createIndexForNode(Contact* node) const;
  };


#endif // CONTACT_H
