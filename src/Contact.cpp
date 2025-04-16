#include "Contact.h"

ContactModel::ContactModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    setBasicGroup();
}

void ContactModel::setBasicGroup()
{
    root = new Contact{DataType::GROUP, "ROOT",  "", {}, 0, "", "", "", nullptr};
    group_Favorite = new Contact{DataType::GROUP, "Favorite",  "", {}, 0, "", "","", "", root};
    root->children.append(group_Favorite);
}

QModelIndex ContactModel::index(int row, int column, const QModelIndex& parent) const
{
    if (row < 0 || column < 0 || column >= columnCount(parent)) return QModelIndex();

    Contact* parentNode = parent.isValid() ? static_cast<Contact*>(parent.internalPointer()) : root;
    if (row >= parentNode->children.size()) return QModelIndex();

    Contact* child = parentNode->children.at(row);
    return createIndex(row, column, child);
}

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

int ContactModel::rowCount(const QModelIndex& parent) const
{
    Contact* node = parent.isValid() ? static_cast<Contact*>(parent.internalPointer()) : root;
    return node ? node->children.size() : 0;
}

int ContactModel::columnCount(const QModelIndex&) const
{
    return 1;
}

QVariant ContactModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) return QVariant();

    Contact* node = static_cast<Contact*>(index.internalPointer());

    if (role == Qt::DisplayRole)
        if (index.column() == 0)
            return node->name;

    if (role == Qt::DecorationRole && index.column() == 0)
    {
        if (node->type == DataType::GROUP)
            return QIcon(":resources/file.png");
        else
            return QIcon(":resources/people.png");
    }

    return QVariant();
}

Qt::ItemFlags ContactModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant ContactModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        if (section == 0)
            return "연락처";
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

Contact* ContactModel::getFavorite()
{
    return group_Favorite;
}

void ContactModel::addContact(Contact* contact, Contact* parent)
{
    if (!parent) parent = root;

    int row = parent->children.size();
    beginInsertRows(indexForContact(parent), row, row);
    parent->children.append(contact);
    contact->parent = parent;
    allContacts.append(contact);
    endInsertRows();
}

void ContactModel::removeContact(Contact* contact)
{
    if (!contact            ||
        !contact->parent    ||
         contact->type == DataType::GROUP)
        return;

    Contact* parent = contact->parent;
    int row = parent->children.indexOf(contact);
    if (row < 0) return;

    QModelIndex parentIndex = indexForContact(parent);

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

    setBasicGroup();

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

void ContactModel::toggleFavorite(Contact* contact)
{
    Contact* oldParent = contact->parent;
    int oldRow = oldParent->childIndex(contact);
    QModelIndex oldParentIndex = indexForContact(oldParent);

    Contact* newParent = contact->favorite ? group_Favorite : root;
    int newRow = newParent->children.size();
    QModelIndex newParentIndex = indexForContact(newParent);

    beginMoveRows(oldParentIndex, oldRow, oldRow, newParentIndex, newRow);
    oldParent->removeChild(contact);
    newParent->insertChild(newRow, contact);
    endMoveRows();
}

QModelIndex ContactModel::indexForContact(Contact* contact) const
{
    if (contact == nullptr || contact == root)
        return QModelIndex();

    Contact* parent = contact->parent;
    int row = parent->childIndex(contact);

    return createIndex(row, 0, contact);
}

int Contact::childIndex(Contact* child) const
{
    return children.indexOf(child);
}


void Contact::removeChild(Contact* child)
{
    children.removeAll(child);
    child->setParent(nullptr);
}

void Contact::insertChild(int row, Contact* child)
{
    children.insert(row, child);
    child->setParent(this);
}

void Contact::setParent(Contact* parent)
{
    this->parent = parent;
}
