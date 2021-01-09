/*  UI List for all the Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_ProgramDialog_H
#define PokemonAutomation_ProgramDialog_H

#include <QListWidget>
#include <QVBoxLayout>

class MainWindow;

class ProgramDialog : public QListWidget{
    Q_OBJECT

public:
    ProgramDialog(MainWindow& parent);
    int text_width() const{ return m_text_width; }

public slots:
    void row_selected(QListWidgetItem* item);
    void row_changed(int row);

private:
    MainWindow& m_parent;
    int m_text_width;
};


#endif
