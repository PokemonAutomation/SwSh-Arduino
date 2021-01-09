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
    int text_width() const{ return m_text_width; }

//    virtual QSize sizeHint() const override;

public slots:
    void row_selected(QListWidgetItem* item);
    void row_changed(int row);

private:
    MainWindow& m_parent;
    int m_text_width;
};


#endif
