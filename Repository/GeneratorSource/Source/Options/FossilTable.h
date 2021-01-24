/*  Fossil Table
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_FossilTable_H
#define PokemonAutomation_FossilTable_H

#include <vector>
#include <QTableWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "SingleStatementOption.h"

class FossilTable : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;
    static const QString JSON_GAME_SLOT;
    static const QString JSON_USER_SLOT;
    static const QString JSON_FOSSIL;
    static const QString JSON_REVIVES;

    enum Fossil{
        Dracozolt   =   0,
        Arctozolt   =   1,
        Dracovish   =   2,
        Arctovish   =   3,
    };
    struct GameSlot{
        int game_slot;
        int user_slot;
        Fossil fossil;
        int revives;
    };

public:
    FossilTable(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    virtual bool is_valid() const override;
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

private:
    friend class FossilTableUI;
    std::vector<GameSlot> m_default;
    std::vector<GameSlot> m_current;
};

class FossilTableUI : public QWidget{
    Q_OBJECT

public:
    FossilTableUI(QWidget& parent, FossilTable& value, const QString& label);
    ~FossilTableUI();

private:
    void add_row(int row, const FossilTable::GameSlot& game, int& index_ref);
    QComboBox* make_game_slot_box(QWidget& parent, int& row, int slot);
    QComboBox* make_user_slot_box(QWidget& parent, int& row, int slot);
    QComboBox* make_fossil_slot_box(QWidget& parent, int& row, FossilTable::Fossil fossil);
    QLineEdit* make_revives_slot_box(QWidget& parent, int& row, int revives);
    QPushButton* make_insert_button(QWidget& parent, int& row);
    QPushButton* make_remove_button(QWidget& parent, int& row);

private:
    FossilTable& m_value;
    QTableWidget* m_table;
    std::vector<std::unique_ptr<int>> m_index_table;
};


#endif
