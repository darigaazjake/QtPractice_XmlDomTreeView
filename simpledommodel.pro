HEADERS     = domitem.h \
              dommodel.h \
              mainwindow.h \
    materialdommodel.h
SOURCES     = domitem.cpp \
              dommodel.cpp \
              main.cpp \
              mainwindow.cpp \
    materialdommodel.cpp
QT      += xml widgets
requires(qtConfig(filedialog))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/simpledommodel
INSTALLS += target

