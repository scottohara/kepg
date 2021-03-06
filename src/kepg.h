/*
 * kepg.h
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KEPG_H
#define KEPG_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"
#include "channelswidget.h"

class kepgView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for kepg.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class kepg : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    kepg();

    /**
     * Default Destructor
     */
    virtual ~kepg();

private slots:
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    ChannelsWidget ui_channel_prefs;
    kepgView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _KEPG_H_
