/*
 * kepgview.h
 *
 * Copyright (C) 2007 %{AUTHOR} <%{EMAIL}>
 */
#ifndef KEPGVIEW_H
#define KEPGVIEW_H

#include <QtGui/QWidget>

#include "ui_kepgview_base.h"
#include "datalist.h"
#include "channellist.h"

class QPainter;
class KUrl;

/**
 * This is the main view class for kepg.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */

class kepgView : public QWidget, public Ui::kepgview_base
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    kepgView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~kepgView();

private:
    Ui::kepgview_base ui_kepgview_base;
    DataList::DataList *dl;
    ChannelList::ChannelList *cl;


signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);


private slots:
    void switchColors();
    void settingsChanged();
    void getDataList();
    void gotDataList();
    void getChannelList();
    void gotChannelList();
    void gotStationDay(XmlTvBase *xmltb);
};

#endif // kepgVIEW_H
