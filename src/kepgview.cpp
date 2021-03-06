/*
 * kepgview.cpp
 *
 * Copyright (C) 2008 %{AUTHOR} <%{EMAIL}>
 */
#include "kepgview.h"
#include "settings.h"
#include "datalist.h"
#include "channellist.h"

#include <klocale.h>
#include <QtGui/QLabel>

kepgView::kepgView(QWidget *)
{
    ui_kepgview_base.setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
    dl = new DataList::DataList();
    connect(dl, SIGNAL(fetched(XmlTvBase *)), this, SLOT(gotDataList()));

    cl = new ChannelList::ChannelList();
    connect(cl, SIGNAL(fetched(XmlTvBase *)), this, SLOT(gotChannelList()));
    
}

kepgView::~kepgView()
{
    delete dl;
    delete cl;
}

void kepgView::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

void kepgView::settingsChanged()
{
  /*
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::col_background());
    pal.setColor( QPalette::WindowText, Settings::col_foreground());
    ui_kepgview_base.kcfg_sillyLabel->setPalette( pal );
*/
    // i18n : internationalization
    //ui_kepgview_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
    emit signalChangeStatusbar( i18n("Settings changed") );
}

void kepgView::getDataList()
{
    dl->fetch();
}

void kepgView::gotDataList()
{
    QList<StationDay*> stationDays;
    dl->getStationDays(&stationDays);
    
    QList<StationDay*>::iterator sd;
    for (sd = stationDays.begin(); sd != stationDays.end(); ++sd) {
      connect((*sd), SIGNAL(fetched(XmlTvBase *)), this, SLOT(gotStationDay(XmlTvBase *)));
      (*sd)->fetch();
    }
}

void kepgView::getChannelList()
{
    cl->fetch();
}

void kepgView::gotChannelList()
{
    QList<QStringList> channelsList;
    cl->getChannelsList(&channelsList);
    
    QList<QStringList>::iterator chan;
    for (chan = channelsList.begin(); chan != channelsList.end(); ++chan) {
      ui_kepgview_base.plainTextEdit->appendPlainText((*chan).join(" - "));
    }
}

void kepgView::gotStationDay(XmlTvBase *xmltb)
{
    ui_kepgview_base.plainTextEdit->appendPlainText("Fetched " + xmltb->configGroup() + " " + xmltb->configPrefix());
}


#include "kepgview.moc"
