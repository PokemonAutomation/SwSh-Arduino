QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += ../GeneratorSource/

#QMAKE_CFLAGS += -MT
#QMAKE_CFLAGS_RELEASE -= -MD
#QMAKE_CXXFLAGS += -MT
#QMAKE_CXXFLAGS_RELEASE -= -MD

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../GeneratorSource/Dialogs/MainWindow.cpp \
    ../GeneratorSource/Dialogs/McuList.cpp \
    ../GeneratorSource/Dialogs/ProgramDialog.cpp \
    ../GeneratorSource/Dialogs/SettingsDialog.cpp \
    ../GeneratorSource/Main.cpp \
    ../GeneratorSource/Options/BooleanCheckBox.cpp \
    ../GeneratorSource/Options/ConfigItem.cpp \
    ../GeneratorSource/Options/Divider.cpp \
    ../GeneratorSource/Options/EnumDropdown.cpp \
    ../GeneratorSource/Options/FixedCode.cpp \
    ../GeneratorSource/Options/FloatingPoint.cpp \
    ../GeneratorSource/Options/FossilTable.cpp \
    ../GeneratorSource/Options/MultiHostTable.cpp \
    ../GeneratorSource/Options/RandomCode.cpp \
    ../GeneratorSource/Options/SimpleInteger.cpp \
    ../GeneratorSource/Options/SingleStatementOption.cpp \
    ../GeneratorSource/Options/SwitchDate.cpp \
    ../GeneratorSource/Options/TimeExpression.cpp \
    ../GeneratorSource/Programs/AllPrograms.cpp \
    ../GeneratorSource/Programs/ConfigSet.cpp \
    ../GeneratorSource/Programs/JsonProgram.cpp \
    ../GeneratorSource/Programs/JsonSettings.cpp \
    ../GeneratorSource/Programs/Program.cpp \
    ../GeneratorSource/Tools/CommandRunner.cpp \
    ../GeneratorSource/Tools/ExpressionEvaluator.cpp \
    ../GeneratorSource/Tools/JsonHelpers.cpp \
    ../GeneratorSource/Tools/PersistentSettings.cpp

HEADERS += \
    ../GeneratorSource/Dialogs/MainWindow.h \
    ../GeneratorSource/Dialogs/McuList.h \
    ../GeneratorSource/Dialogs/ProgramDialog.h \
    ../GeneratorSource/Dialogs/SettingsDialog.h \
    ../GeneratorSource/Options/BooleanCheckBox.h \
    ../GeneratorSource/Options/ConfigItem.h \
    ../GeneratorSource/Options/Divider.h \
    ../GeneratorSource/Options/EnumDropdown.h \
    ../GeneratorSource/Options/FixedCode.h \
    ../GeneratorSource/Options/FloatingPoint.h \
    ../GeneratorSource/Options/FossilTable.h \
    ../GeneratorSource/Options/MultiHostTable.h \
    ../GeneratorSource/Options/RandomCode.h \
    ../GeneratorSource/Options/SimpleInteger.h \
    ../GeneratorSource/Options/SingleStatementOption.h \
    ../GeneratorSource/Options/SwitchDate.h \
    ../GeneratorSource/Options/TimeExpression.h \
    ../GeneratorSource/Programs/AllPrograms.h \
    ../GeneratorSource/Programs/ConfigSet.h \
    ../GeneratorSource/Programs/JsonProgram.h \
    ../GeneratorSource/Programs/JsonSettings.h \
    ../GeneratorSource/Programs/Program.h \
    ../GeneratorSource/Programs/RightPanel.h \
    ../GeneratorSource/Tools/PersistentSettings.h \
    ../GeneratorSource/Tools/Tools.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
