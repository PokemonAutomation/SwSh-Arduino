/*  Multi-Host Table
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_MultiHostTable_H
#define PokemonAutomation_MultiHostTable_H

#include <vector>
#include <QTableWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include "SingleStatementOption.h"

class MultiHostTable : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;
    static const QString JSON_GAME_SLOT;
    static const QString JSON_USER_SLOT;
    static const QString JSON_SKIPS;
    static const QString JSON_BACKUP_SAVE;
    static const QString JSON_ALWAYS_CATCHABLE;
    static const QString JSON_ACCEPT_FRS;
    static const QString JSON_MOVE_SLOT;
    static const QString JSON_DYNAMAX;
    static const QString JSON_POST_RAID_DELAY;

    struct GameSlot{
        int game_slot;
        int user_slot;
        int skips;
        bool backup_save;
        bool always_catchable;
        bool accept_FRs;
        int move_slot;
        bool dynamax;
        QString post_raid_delay;
    };

public:
    MultiHostTable(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    virtual bool is_valid() const override;
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

private:
    friend class MultiHostTableUI;
    std::vector<GameSlot> m_default;
    std::vector<GameSlot> m_current;
};


class MultiHostTableUI : public QWidget{
    Q_OBJECT

public:
    MultiHostTableUI(QWidget& parent, MultiHostTable& value, const QString& label);
    ~MultiHostTableUI();

private:
    void add_row(int row, const MultiHostTable::GameSlot& game, int& index_ref);
    QComboBox* make_game_slot_box(QWidget& parent, int& row, int slot);
    QComboBox* make_user_slot_box(QWidget& parent, int& row, int slot);
    QLineEdit* make_skips_box(QWidget& parent, int& row, int skips);
    QWidget* make_backup_save_box(QWidget& parent, int& row, bool backup_save);
    QWidget* make_catchable_box(QWidget& parent, int& row, bool always_catchable);
    QWidget* make_accept_FRs_box(QWidget& parent, int& row, bool accept_FRs);
    QComboBox* make_move_slot_box(QWidget& parent, int& row, int move_slot);
    QWidget* make_dynamax_box(QWidget& parent, int& row, bool dynamax);
    QLineEdit* make_delay_box(QWidget& parent, int& row, const QString& post_raid_delay);
    QPushButton* make_insert_button(QWidget& parent, int& row);
    QPushButton* make_remove_button(QWidget& parent, int& row);

    void update_table_height();

private:
    MultiHostTable& m_value;
    QTableWidget* m_table;
    std::vector<std::unique_ptr<int>> m_index_table;
};


#endif
