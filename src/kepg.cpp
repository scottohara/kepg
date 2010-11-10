/*
 * kepg.cpp
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#include "kepg.h"
#include "kepgview.h"
#include "settings.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>
#include <QtGui/QPrinter>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>

#include <KDE/KLocale>

kepg::kepg()
    : KXmlGuiWindow(),
      m_view(new kepgView(this)),
      m_printer(0)
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // add a status bar
    statusBar()->show();

    // a call to KXmlGuiWindow::setupGUI() populates the GUI
    // with actions, using KXMLGUI.
    // It also applies the saved mainwindow settings, if any, and ask the
    // mainwindow to automatically save settings if changed: window size,
    // toolbar position, icon size, etc.
    setupGUI();
}

kepg::~kepg()
{
}

void kepg::setupActions()
{
    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());

    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // custom menu and menu item - the slot is in the class kepgView
    KAction *custom = new KAction(KIcon("colorize"), i18n("Swi&tch Colors"), this);
    actionCollection()->addAction( QLatin1String("switch_action"), custom );
    connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));
    
    KAction *dl = new KAction(KIcon("colorize"), i18n("&Get Data List"), this);
    actionCollection()->addAction( QLatin1String("get_data_list"), dl );
    connect(dl, SIGNAL(triggered(bool)), m_view, SLOT(getDataList()));    

    KAction *cl = new KAction(KIcon("colorize"), i18n("&Get Channel List"), this);
    actionCollection()->addAction( QLatin1String("get_channel_list"), cl );
    connect(cl, SIGNAL(triggered(bool)), m_view, SLOT(getChannelList()));      
}

void kepg::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // create a new window
    (new kepg)->show();
}

void kepg::optionsPreferences()
{
    // The preference dialog is derived from prefs_base.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    QWidget *generalSettingsDlg = new QWidget;
    ui_prefs_base.setupUi(generalSettingsDlg);
    dialog->addPage(generalSettingsDlg, i18n("General"), "package_setting");
    connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(settingsChanged()));
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

#include "kepg.moc"
