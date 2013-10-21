#include "CodeEditor.h"
#include "Setting/SettingManager.h"
#include "Theme/ThemeManager.h"
#include "MainWindow.h"
#include "Editor/EditorManager.h"
#include "Plugin/PluginManager.h"
#include "Workspace/Workspace.h"


#include <QDebug>

namespace CE {
SettingManager* CodeEditor::mSettingManager;
ThemeManager* CodeEditor::mThemeManager;
MainWindow* CodeEditor::mMainWindow;
PluginManager* CodeEditor::mPluginManager;
Workspace* CodeEditor::mWorkspace;
EditorManager* CodeEditor::mEditorManager;

/**
 * @brief CodeEditor::MonkeyCodeEditor::init
 *
 * Initialize all requier componement for CodeEditor
 * and show the main window
 */
void CodeEditor::init()
{
    qDebug() << "CodeEditor init";
    mSettingManager = new SettingManager;
    mThemeManager = new ThemeManager();
    mWorkspace = new Workspace;
    mMainWindow = new MainWindow;
    mEditorManager = new EditorManager;
    mPluginManager = new PluginManager;

    mMainWindow->show();
}

/**
 * @brief CodeEditor::getConfigManager
 *
 * Return the project manager instance
 *
 * @return ConfigManager*
 */
SettingManager* CodeEditor::getSettingManager()
{
    return mSettingManager;
}

ThemeManager* CodeEditor::getThemeManager()
{
    return mThemeManager;
}

/**
 * @brief CodeEditor::getMainWindow
 *
 * Return the main window instance
 *
 * @return MainWindow*
 */
MainWindow* CodeEditor::getMainWindow()
{
    return mMainWindow;
}

EditorManager* CodeEditor::getEditorManager()
{
    return mEditorManager;
}
/**
 * @brief CodeEditor::getPluginManager
 *
 * Return the plugin manager instance
 *
 * @return PluginManager*
 */
PluginManager* CodeEditor::getPluginManager()
{
    return mPluginManager;
}

/**
 * @brief CodeEditor::getWorkspace
 *
 * Return the workspace instance
 *
 * @return Workspace*
 */
Workspace* CodeEditor::getWorkspace()
{
    return mWorkspace;
}
}