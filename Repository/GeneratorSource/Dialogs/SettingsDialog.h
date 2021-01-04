/*  UI List for all the Settings
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_SettingsDialog_H
#define PokemonAutomation_SettingsDialog_H

#include <QListWidget>
#include <QVBoxLayout>

class MainWindow;

class SettingsDialog : public QListWidget{
    Q_OBJECT

public:
    SettingsDialog(MainWindow& parent);

//    virtual QSize sizeHint() const override;

public slots:
    void row_selected(QListWidgetItem* item);
    void row_changed(int row);

private:
    MainWindow& m_parent;
};


#endif
