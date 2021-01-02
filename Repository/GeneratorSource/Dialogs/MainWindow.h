/*  Main Window UI
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_MainWindow_H
#define PokemonAutomation_MainWindow_H

#include <QVBoxLayout>
#include <QComboBox>
#include <QMainWindow>
#include "McuList.h"
#include "Programs/Program.h"

class ProgramDialog;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    void replace_active_program(Program& program);


private:
    QWidget* centralwidget;
    QMenuBar* menubar;
    QStatusBar* statusbar;

    McuList* m_mcu_list;
    ProgramDialog* m_program_list;

    QVBoxLayout* m_program_settings_parent_layout;
    QWidget* m_program_settings_widget;
};

#endif