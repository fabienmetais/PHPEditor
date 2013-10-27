#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include "Export.h"

#include <QObject>

#include <map>

using namespace std;

namespace CE {
class Editor;
class CE_EXPORT EditorManager : public QObject
{
    Q_OBJECT
public:
    EditorManager();
    ~EditorManager();
    void openFile(QString path);
    void addEditor(Editor *editor);
    Editor* getEditorByExtension(QString extension);
    Editor* getEditorById(QString id);
    map<QString, Editor*> getEditors();

public slots:


private:

    map<QString, Editor*> mEditors;
};
}

#endif // PLUGINMANAGER_H