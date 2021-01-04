/*  UI List for all the Settings
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <vector>
#include "Dialogs/MainWindow.h"
#include "Programs/AllPrograms.h"
#include "SettingsDialog.h"


SettingsDialog::SettingsDialog(MainWindow& parent)
    : m_parent(parent)
{
    setMaximumWidth(300);
//    setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

    connect(this, &QListWidget::itemClicked, this, &SettingsDialog::row_selected);
    connect(this, &QListWidget::currentRowChanged, this, &SettingsDialog::row_changed);

    const auto& list = SETTINGS_LIST();
    if (list.empty()){
        setMaximumHeight(50);
        return;
    }

    for (const auto& item : list){
        addItem(item->name());
    }
//    updateGeometry();

    setMaximumHeight(4 + list.size() * (sizeHintForRow(0) + 2));
}

#include <iostream>
using std::cout;
using std::endl;

#if 0
QSize SettingsDialog::sizeHint() const{
    if (model()->rowCount() == 0) return QSize(width(), 0);
    int nToShow = model()->rowCount();
    cout << "asdf" << endl;
    return QSize(width(), nToShow * sizeHintForRow(0));
}
#endif

void SettingsDialog::row_selected(QListWidgetItem* item){
    auto iter = SETTINGS_MAP().find(item->text());
    if (iter == SETTINGS_MAP().end()){
//        std::cout << item->text().toUtf8().data() << std::endl;
        throw "Invalid program name: " + item->text();
    }

    m_parent.replace_active_program(*iter->second);
}
void SettingsDialog::row_changed(int row){
    row_selected(this->item(row));
}





