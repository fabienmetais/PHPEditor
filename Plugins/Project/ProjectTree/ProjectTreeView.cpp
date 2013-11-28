#include "ProjectTree/ProjectTreeView.h"
#include "ProjectTree/ProjectTreeModel.h"
#include "ProjectTree/ProjectTreeItem.h"

#include "ProjectManager.h"

#include "CodeEditor.h"
#include "Editor/EditorManager.h"
#include "Menu/Menu.h"
#include "Action/Manager.h"

#include <QHeaderView>
#include <QTreeWidget>
#include <QDebug>

namespace CE {
namespace Project {
ProjectTreeView::ProjectTreeView(ProjectManager *projectManager)
{
    mProjectTreeModel = new ProjectTreeModel(projectManager);
    //hide the tree header
    header()->close();
    setModel(mProjectTreeModel);
    setStyleSheet(QString("QTreeView::branch { border-image: none; }"));
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    setContextMenuPolicy(Qt::CustomContextMenu);

    createContextMenuActions();

    connect(this, SIGNAL(customContextMenuRequested(QPoint)), SLOT(onCustomContextMenuRequested(const QPoint&)));
    connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onDoubleClick(const QModelIndex&)));

    connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(onExpand(const QModelIndex&)));
    connect(this, SIGNAL(collapsed(QModelIndex)), this, SLOT(onCollapse(const QModelIndex&)));

}

/**
 * @brief ProjectTreeView::createContextMenuActions
 *
 * Create the action require by the context menu
 */
void ProjectTreeView::createContextMenuActions()
{

}

/**
 * @brief ProjectTreeView::onDoubleClick
 *
 * Slot call when double clik on an item of the project tree
 *
 * @param index
 */
void ProjectTreeView::onDoubleClick (const QModelIndex &index)
{
    if (index.isValid()) {
        ProjectTreeItem *item = static_cast<ProjectTreeItem*>(index.internalPointer());
        qDebug() << "Double click on item " + item->getPath();
        CodeEditor::getEditorManager()->openFile(item->getPath());
        qDebug() << "/Double click on item " + item->getPath();
    }
}

void ProjectTreeView::onExpand (const QModelIndex &index)
{
    if (index.isValid()) {
        ProjectTreeItem *item = static_cast<ProjectTreeItem*>(index.internalPointer());
        item->setIsExpand(true);
    }
}

void ProjectTreeView::onCollapse (const QModelIndex &index)
{
    if (index.isValid()) {
        ProjectTreeItem *item = static_cast<ProjectTreeItem*>(index.internalPointer());
        item->setIsExpand(false);
    }
}

/**
 * @brief ProjectTreeView::onCustomContextMenuRequested
 *
 * Slot call when the custom context menu is requested on the project tree
 *
 * Get the tree item clicked for show the context menu and show it
 *
 * @param QPoint pos
 */
void ProjectTreeView::onCustomContextMenuRequested(const QPoint& pos)
{
    QModelIndex index = indexAt(pos);
    ProjectTreeItem *item = static_cast<ProjectTreeItem*>(index.internalPointer());
    if (item) {
        // Note: We must map the point to global from the viewport to
        // account for the header.
        showContextMenu(item, viewport()->mapToGlobal(pos));
    }
}

/**
 * @brief ProjectTreeView::showContextMenu
 *
 * Generate the context menu of the project tree and show it
 *
 * @param item
 * @param globalPos
 */
void ProjectTreeView::showContextMenu(ProjectTreeItem *item, const QPoint& globalPos)
{
    Menu *contextMenu = new Menu;

    //Project type item
    if (item->getType() == ProjectTreeItem::ProjectItemType) {
        QMenu *newMenu = contextMenu->menu("new", tr("&New"));
        newMenu->addAction(CodeEditor::getActionManager()->getAction("new_file"));

        QMenu *newDirectory = contextMenu->menu("new/directory", tr("&Directory"));

        QMenu *search = contextMenu->menu("search", tr("&Search"));
        QMenu *deleteProject = contextMenu->menu("delete", tr("&Delete project"));
        QMenu *properties = contextMenu->menu("properties", tr("&Properties"));

    //Directory type item
    } else if (item->getType() == ProjectTreeItem::DirectoryItemType) {
        QMenu *newMenu = contextMenu->menu("new", tr("&New"));
        newMenu->addAction(CodeEditor::getActionManager()->getAction("new_file"));

        QMenu *newDirectory = contextMenu->menu("new/directory", tr("&Directory"));

        QMenu *copy = contextMenu->menu("copy", tr("&Copy"));
        QMenu *cut = contextMenu->menu("cut", tr("&Cut"));
        QMenu *paste = contextMenu->menu("paste", tr("&Paste"));

        QMenu *search = contextMenu->menu("search", tr("&Search"));
        QMenu *deleteDirectory = contextMenu->menu("delete", tr("&Delete"));
        QMenu *properties = contextMenu->menu("properties", tr("&Properties"));

    //File item type
    } else if (item->getType() == ProjectTreeItem::FileItemType) {
        QMenu *open = contextMenu->menu("open", tr("&Open"));

        QMenu *copy = contextMenu->menu("copy", tr("&Copy"));
        QMenu *cut = contextMenu->menu("cut", tr("&Cut"));

        QMenu *deleteFile = contextMenu->menu("delete", tr("&Delete"));
        QMenu *properties = contextMenu->menu("properties", tr("&Properties"));
    }


    emit createContextMenu(contextMenu, item);
    contextMenu->exec(globalPos);
}

void ProjectTreeView::addProject(QString name, QString location)
{
    mProjectTreeModel->addProject(name, location);
}
}
}
