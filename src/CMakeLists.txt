set(kepg_SRCS channelswidget.cpp
   kepg.cpp
   main.cpp
   kepgview.cpp
   xmltvbase.cpp
   datalist.cpp 
   channellist.cpp
   stationday.cpp
 )

kde4_add_ui_files(kepg_SRCS kepgview_base.ui prefs_base.ui channel_prefs.ui)

kde4_add_kcfg_files(kepg_SRCS settings.kcfgc )

kde4_add_executable(kepg ${kepg_SRCS})

target_link_libraries(kepg ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} )

install(TARGETS kepg ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( FILES kepg.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES kepg.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES kepgui.rc  DESTINATION  ${DATA_INSTALL_DIR}/kepg )
