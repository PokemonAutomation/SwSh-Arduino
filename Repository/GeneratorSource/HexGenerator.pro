QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ../
INCLUDEPATH += Source/

#QMAKE_CFLAGS += -MT
#QMAKE_CFLAGS_RELEASE -= -MD
#QMAKE_CXXFLAGS += -MT
#QMAKE_CXXFLAGS_RELEASE -= -MD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../SharedCpp/PrettyPrint.cpp \
    ../SharedCpp/QtJsonTools.cpp \
    ../SharedCpp/Unicode.cpp \
    Source/Main.cpp \
    Source/Options/BooleanCheckBox.cpp \
    Source/Options/ConfigItem.cpp \
    Source/Options/Divider.cpp \
    Source/Options/EnumDropdown.cpp \
    Source/Options/FixedCode.cpp \
    Source/Options/FloatingPoint.cpp \
    Source/Options/FossilTable.cpp \
    Source/Options/MultiHostTable.cpp \
    Source/Options/RandomCode.cpp \
    Source/Options/SimpleInteger.cpp \
    Source/Options/SingleStatementOption.cpp \
    Source/Options/SwitchDate.cpp \
    Source/Options/TimeExpression.cpp \
    Source/Panels/ConfigSet.cpp \
    Source/Panels/JsonProgram.cpp \
    Source/Panels/JsonSettings.cpp \
    Source/Panels/PanelList.cpp \
    Source/Panels/Program.cpp \
    Source/Tools/CommandRunner.cpp \
    Source/Tools/ExpressionEvaluator.cpp \
    Source/Tools/MiscTools.cpp \
    Source/Tools/PersistentSettings.cpp \
    Source/UI/MainWindow.cpp \
    Source/UI/McuList.cpp \
    Source/UI/ProgramListUI.cpp \
    Source/UI/SettingsListUI.cpp

HEADERS += \
    ../SharedCpp/PrettyPrint.h \
    ../SharedCpp/QtJsonTools.h \
    ../SharedCpp/Unicode.h \
    Source/Options/BooleanCheckBox.h \
    Source/Options/ConfigItem.h \
    Source/Options/Divider.h \
    Source/Options/EnumDropdown.h \
    Source/Options/FixedCode.h \
    Source/Options/FloatingPoint.h \
    Source/Options/FossilTable.h \
    Source/Options/MultiHostTable.h \
    Source/Options/RandomCode.h \
    Source/Options/SimpleInteger.h \
    Source/Options/SingleStatementOption.h \
    Source/Options/SwitchDate.h \
    Source/Options/TimeExpression.h \
    Source/Panels/ConfigSet.h \
    Source/Panels/JsonProgram.h \
    Source/Panels/JsonSettings.h \
    Source/Panels/PanelList.h \
    Source/Panels/Program.h \
    Source/Panels/RightPanel.h \
    Source/Tools/PersistentSettings.h \
    Source/Tools/Tools.h \
    Source/UI/MainWindow.h \
    Source/UI/McuList.h \
    Source/UI/ProgramListUI.h \
    Source/UI/SettingsListUI.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
