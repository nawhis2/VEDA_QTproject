#include "Contact.h"

ContactModel::ContactModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    // 트리의 루트 노드 생성
    root = new Contact{DataType::GROUP,QUuid::createUuid().toString(), "ROOT",  "", {}, 0, "", "", "", nullptr};

    // 테스트용 자식 그룹/연락처 삽입
    Contact* group_Favorite = new Contact{DataType::GROUP,QUuid::createUuid().toString(), "Favorite",  "", {}, 0, "", "","", "", root};
    Contact* group_Birth = new Contact{DataType::GROUP,QUuid::createUuid().toString(), "Birth Day",  "", {}, 0, "", "","", "", root};
    Contact* mom = new Contact{DataType::CONTACT,QUuid::createUuid().toString(), "엄마",  "010-1234-5678", {},1, "", "","", "", group_Favorite};
    Contact* dad = new Contact{ DataType::CONTACT, QUuid::createUuid().toString(), "아빠","010-1111-2222", {},1, "", "","", "", group_Favorite};

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
    return 1; // 이름, 전화번호
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

void ContactModel::removeContact(Contact* contact)
{
    if (!contact || !contact->parent || contact->type == DataType::GROUP) return;

    Contact* parent = contact->parent;
    int row = parent->children.indexOf(contact);
    if (row < 0) return;

    QModelIndex parentIndex = createIndexForNode(parent);

    beginRemoveRows(parentIndex, row, row);
    parent->children.removeAt(row);
    allContacts.removeOne(contact);
    delete contact;
    endRemoveRows();
}

void ContactModel::clearAll()
{
    beginResetModel();
    deleteTree(root);

    root = new Contact{DataType::GROUP,QUuid::createUuid().toString(), "ROOT",  "", {}, 0, "", "", "", nullptr};
    Contact* group_Favorite = new Contact{DataType::GROUP,QUuid::createUuid().toString(), "Favorite",  "", {}, 0, "", "","", "", root};

    root->children.append(group_Favorite);

    allContacts.clear();
    endResetModel();
}

void ContactModel::deleteTree(Contact* node)
{
    if(!node) return;

    for (Contact* child : node->children)
        deleteTree(child);

    delete node;
}

// 선택된 노드 → QModelIndex 생성 (트리뷰 삽입 시 parentIndex 필요)
QModelIndex ContactModel::createIndexForNode(Contact* node) const
{
    if (node == root) return QModelIndex(); // 루트는 invalid index
    Contact* parent = node->parent;
    int row = parent ? parent->children.indexOf(node) : 0;
    return createIndex(row, 0, node);
}

// void ContactModel::updateFavoriteGroup(Contact* contact, bool isFavorite)
// {
//     Contact* favGroup = [&]() -> Contact*{
//         for (Contact* group : root->children)
//             if (group->name == "Favorite" && group->type == DataType::GROUP)
//                 return group;
//         return nullptr;
//     }();

//     if (!favGroup || !contact) return;
//     if (isFavorite)
//     {
//         if (!favGroup->children.contains(contact))
//         {
//             int insertRow = favGroup->children.size();
//             beginInsertRows(createIndexForNode(favGroup), insertRow, insertRow);
//             favGroup->children.append(contact);
//             contact->parent = favGroup;
//             endInsertRows();
//         }
//     }
//     else {
//         int row = favGroup->children.indexOf(contact);
//         if (row >= 0)
//         {
//             beginRemoveRows(createIndexForNode(favGroup), row, row);
//             favGroup->children.removeAt(row);
//             // ⚠️ parent 유지할지 지울지 정책에 따라 다르게
//             endRemoveRows();
//         }
//     }
// }
