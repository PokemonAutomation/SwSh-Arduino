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
#include "Panels/RightPanel.h"

class ProgramListUI;
class SettingsListUI;

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    const std::string& current_MCU() const;
    void change_panel(RightPanel& panel);

private:
    QWidget* m_centralwidget;
    QMenuBar* m_menubar;
//    QStatusBar* m_statusbar;

    McuList* m_mcu_list;
    ProgramListUI* m_program_list;
    SettingsListUI* m_settings_list;

    QVBoxLayout* m_right_panel_layout;
    QWidget* m_right_panel_widget;
};



#endif
