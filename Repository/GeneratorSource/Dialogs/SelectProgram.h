/*  UI List for all the Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_SelectProgram_H
#define PokemonAutomation_SelectProgram_H

#include <QListWidget>
#include <QVBoxLayout>
#include "Dialogs/McuList.h"
#include "Programs/AllPrograms.h"

class MainWindow;

class ProgramDialog : public QListWidget{
    Q_OBJECT

public:
    ProgramDialog(MainWindow& parent);

public slots:
    void currentRowChanged(int currentRow);

private:
    MainWindow& m_parent;
};


#endif
