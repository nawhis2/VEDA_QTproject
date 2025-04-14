#include "Contact.h"

ContactModel::ContactModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    // 트리의 루트 노드 생성
    root = new Contact{QUuid::createUuid(), "ROOT", DataType::GROUP, "", {}, 0, "", "", "", nullptr};

    // 테스트용 자식 그룹/연락처 삽입
    Contact* group_Favorite = new Contact{QUuid::createUuid(), "Favorite", DataType::GROUP, "", {}, 0, "", "", "", root};
    Contact* group_Birth = new Contact{QUuid::createUuid(), "Birth Day", DataType::GROUP, "", {}, 0, "", "", "", root};
    Contact* mom = new Contact{QUuid::createUuid(), "엄마", DataType::CONTACT, "010-1234-5678", {},0, "", "", "", group_Favorite};
    Contact* dad = new Contact{QUuid::createUuid(), "아빠", DataType::CONTACT, "010-1111-2222", {},0, "", "", "", group_Favorite};

    group_Favorite->children.append(mom);
    group_Favorite->children.append(dad);
    root->children.append(group_Favorite);

    // 검색을 위한 전체 리스트에 포함
    allContacts << mom << dad;
}

// 자식 아이템 찾기
QModelIndex ContactModel::index(int row, int column, const QModelIndex& parent) const
{
    if (row < 0 || column < 0 || column >= columnCount(parent)) return QModelIndex();

    Contact* parentNode = parent.isValid() ? static_cast<Contact*>(parent.internalPointer()) : root;
    if (row >= parentNode->children.size()) return QModelIndex();

    Contact* child = parentNode->children.at(row);
    return createIndex(row, column, child);
}

// 부모 찾기
QModelIndex ContactModel::parent(const QModelIndex& index) const
{
    if (!index.isValid()) return QModelIndex();

    Contact* child = static_cast<Contact*>(index.internalPointer());
    Contact* parent = child->parent;
    if (!parent || parent == root) return QModelIndex();

    Contact* grand = parent->parent;
    int row = grand ? grand->children.indexOf(parent) : 0;
    return createIndex(row, 0, parent);
}

// 자식 수
int ContactModel::rowCount(const QModelIndex& parent) const {
    Contact* node = parent.isValid() ? static_cast<Contact*>(parent.internalPointer()) : root;
    return node ? node->children.size() : 0;
}


// 열 수 (보통 1~3)
int ContactModel::columnCount(const QModelIndex&) const
{
    return 2; // 이름, 전화번호
}


// 	표시할 데이터
QVariant ContactModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) return QVariant();

    Contact* node = static_cast<Contact*>(index.internalPointer());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) return node->name;
        if (index.column() == 1 && node->type == DataType::CONTACT) return node->phone;
    }

    if (role == Qt::DecorationRole && index.column() == 0) {
        if (node->type == DataType::GROUP)
            return QIcon(":/icons/folder.png");
        else
            return QIcon(":/icons/person.png");
    }

    return QVariant();
}

Qt::ItemFlags ContactModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0) return "이름";
        if (section == 1) return "전화번호";
    }
    return QVariant();
}

QList<Contact*>&  ContactModel::getList()
{
    return allContacts;
}

Contact* ContactModel::getRoot()
{
    return root;
}

void ContactModel::addContact(Contact* contact, Contact* parent)
{
    if (!parent) parent = root;

    int row = parent->children.size();
    beginInsertRows(createIndexForNode(parent), row, row);
    parent->children.append(contact);
    contact->parent = parent;
    allContacts.append(contact);
    endInsertRows();
}

// 선택된 노드 → QModelIndex 생성 (트리뷰 삽입 시 parentIndex 필요)
QModelIndex ContactModel::createIndexForNode(Contact* node) const {
    if (node == root) return QModelIndex(); // 루트는 invalid index
    Contact* parent = node->parent;
    int row = parent ? parent->children.indexOf(node) : 0;
    return createIndex(row, 0, node);
}
