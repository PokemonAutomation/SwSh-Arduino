/*  UI List for all the Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <vector>
#include "Dialogs/MainWindow.h"
#include "Programs/AllPrograms.h"
#include "SelectProgram.h"


ProgramDialog::ProgramDialog(MainWindow& parent)
    : m_parent(parent)
{
//    setSizeAdjustPolicy(SizeAdjustPolicy::AdjustToContents);
//    setMinimumWidth();
    setMaximumWidth(300);
//    sizeHintForRow(100);
//    sizeHintForColumn(100);

    connect(this, &QListWidget::currentRowChanged, this, &ProgramDialog::currentRowChanged);

    for (const auto& item : PROGRAM_LIST()){
        addItem(item->name());
    }

}

void ProgramDialog::currentRowChanged(int currentRow){
//    cout << item->text().toUtf8().constData() << endl;
    QListWidgetItem* item = this->item(currentRow);
    auto iter = PROGRAM_MAP().find(item->text());
    if (iter == PROGRAM_MAP().end()){
//        std::cout << item->text().toUtf8().data() << std::endl;
        throw "Invalid program name: " + item->text();
    }

    m_parent.replace_active_program(*iter->second);
}




