/*  Multi-Host Table
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonArray>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QComboBox>
#include <QLineEdit>
#include <QScrollBar>
#include "Tools/Tools.h"
#include "MultiHostTable.h"

#include <iostream>
using namespace std;

const QString MultiHostTable::OPTION_TYPE           = "MultiHostTable";
const QString MultiHostTable::JSON_GAME_SLOT        = "game_slot";
const QString MultiHostTable::JSON_USER_SLOT        = "user_slot";
const QString MultiHostTable::JSON_SKIPS            = "skips";
const QString MultiHostTable::JSON_BACKUP_SAVE      = "backup_save";
const QString MultiHostTable::JSON_ALWAYS_CATCHABLE = "always_catchable";
const QString MultiHostTable::JSON_ACCEPT_FRS       = "accept_FRs";
const QString MultiHostTable::JSON_MOVE_SLOT        = "move_slot";
const QString MultiHostTable::JSON_DYNAMAX          = "dynamax";
const QString MultiHostTable::JSON_POST_RAID_DELAY  = "post_raid_delay";


int MultiHostTable_init = register_option(
    MultiHostTable::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new MultiHostTable(obj)
        );
    }
);

std::vector<MultiHostTable::GameSlot> parse_game_slot(const QJsonObject& obj, const QString& key){
    std::vector<MultiHostTable::GameSlot> list;
    for (const auto& item : json_get_array(obj, key)){
        QJsonObject line = json_cast_object(item);
        MultiHostTable::GameSlot slot;

        slot.game_slot = json_get_int(line, MultiHostTable::JSON_GAME_SLOT);
        if (slot.game_slot < 1 || slot.game_slot > 2){
            throw "Config Error - Game slot is out of range.";
        }

        slot.user_slot = json_get_int(line, MultiHostTable::JSON_USER_SLOT);
        if (slot.user_slot < 1 || slot.user_slot > 8){
            throw "Config Error - User slot is out of range.";
        }

        slot.skips = json_get_int(line, MultiHostTable::JSON_SKIPS);
        if (slot.skips < 0 || slot.skips > 7){
            throw "Config Error - Skips is out of range.";
        }

        slot.backup_save = json_get_bool(line, MultiHostTable::JSON_BACKUP_SAVE);
        slot.always_catchable = json_get_bool(line, MultiHostTable::JSON_ALWAYS_CATCHABLE);
        slot.accept_FRs = json_get_bool(line, MultiHostTable::JSON_ACCEPT_FRS);

        slot.move_slot = json_get_int(line, MultiHostTable::JSON_MOVE_SLOT);
        if (slot.move_slot < 0 || slot.move_slot > 4){
            throw "Config Error - Skips is out of range.";
        }

        slot.dynamax = json_get_bool(line, MultiHostTable::JSON_DYNAMAX);

        slot.post_raid_delay = json_get_string(line, MultiHostTable::JSON_POST_RAID_DELAY);
        if (slot.post_raid_delay < 0 || slot.post_raid_delay > 65535){
            throw "Config Error - Skips is out of range.";
        }

        list.emplace_back(std::move(slot));
    }
    return list;
}
QJsonArray write_game_slot(const std::vector<MultiHostTable::GameSlot>& list){
    QJsonArray ret;
    for (const auto& item : list){
        QJsonObject obj;
        obj.insert(MultiHostTable::JSON_GAME_SLOT, item.game_slot);
        obj.insert(MultiHostTable::JSON_USER_SLOT, item.user_slot);
        obj.insert(MultiHostTable::JSON_SKIPS, item.skips);
        obj.insert(MultiHostTable::JSON_BACKUP_SAVE, item.backup_save);
        obj.insert(MultiHostTable::JSON_ALWAYS_CATCHABLE, item.always_catchable);
        obj.insert(MultiHostTable::JSON_ACCEPT_FRS, item.accept_FRs);
        obj.insert(MultiHostTable::JSON_MOVE_SLOT, item.move_slot);
        obj.insert(MultiHostTable::JSON_DYNAMAX, item.dynamax);
        obj.insert(MultiHostTable::JSON_POST_RAID_DELAY, item.post_raid_delay);
        ret += std::move(obj);
    }
    return ret;
}

MultiHostTable::MultiHostTable(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_default(parse_game_slot(obj, JSON_DEFAULT))
    , m_current(parse_game_slot(obj, JSON_CURRENT))
{}
bool MultiHostTable::is_valid() const{
    if (m_current.empty()){
        return false;
    }
    for (const auto& item : m_current){
        if (item.game_slot < 1 || item.game_slot > 2){
            return false;
        }
        if (item.user_slot < 1 || item.user_slot > 8){
            return false;
        }
        if (item.skips < 0 || item.skips > 7){
            return false;
        }
        if (item.move_slot < 0 || item.move_slot > 4){
            return false;
        }
        int ticks;
        try{
            ticks = parse_ticks_i32(item.post_raid_delay);
        }catch (...){
            return false;
        }
        if (ticks < 0 || ticks > 65535){
            return false;
        }
    }
    return true;
}
void MultiHostTable::restore_defaults(){
    m_current = m_default;
}
QJsonObject MultiHostTable::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_DEFAULT, write_game_slot(m_default));
    root.insert(JSON_CURRENT, write_game_slot(m_current));
    return root;
}
std::string MultiHostTable::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = {\r\n";
    for (const auto& item : m_current){
        str += "    {\r\n";
        str += std::string("        .game_slot        = ") + std::to_string(item.game_slot) + ",\r\n";
        str += std::string("        .user_slot        = ") + std::to_string(item.user_slot) + ",\r\n";
        str += std::string("        .skips            = ") + std::to_string(item.skips) + ",\r\n";
        str += std::string("        .backup_save      = ") + (item.backup_save ? "true" : "false") + ",\r\n";
        str += std::string("        .always_catchable = ") + (item.always_catchable ? "true" : "false") + ",\r\n";
        str += std::string("        .accept_FRs       = ") + (item.accept_FRs ? "true" : "false") + ",\r\n";
        str += std::string("        .move_slot        = ") + std::to_string(item.move_slot) + ",\r\n";
        str += std::string("        .dynamax          = ") + (item.dynamax ? "true" : "false") + ",\r\n";
        str += std::string("        .post_raid_delay  = ") + item.post_raid_delay.toUtf8().data() + ",\r\n";
        str += "    },\r\n";
    }
    str += "};\r\n";
    return str;
}
QWidget* MultiHostTable::make_ui(QWidget& parent){
    return new MultiHostTableUI(parent, *this, m_label);
}

void MultiHostTableUI::add_row(int row, const MultiHostTable::GameSlot& game, int& index_ref){
    index_ref = row;
    m_table->setCellWidget(row,  0, make_game_slot_box(*m_table, index_ref, game.game_slot - 1));
    m_table->setCellWidget(row,  1, make_user_slot_box(*m_table, index_ref, game.user_slot - 1));
    m_table->setCellWidget(row,  2, make_skips_box(*m_table, index_ref, game.skips));
    m_table->setCellWidget(row,  3, make_backup_save_box(*m_table, index_ref, game.backup_save));
    m_table->setCellWidget(row,  4, make_catchable_box(*m_table, index_ref, game.always_catchable));
    m_table->setCellWidget(row,  5, make_accept_FRs_box(*m_table, index_ref, game.accept_FRs));
    m_table->setCellWidget(row,  6, make_move_slot_box(*m_table, index_ref, game.move_slot));
    m_table->setCellWidget(row,  7, make_dynamax_box(*m_table, index_ref, game.dynamax));
    m_table->setCellWidget(row,  8, make_delay_box(*m_table, index_ref, game.post_raid_delay));
    m_table->setCellWidget(row,  9, make_insert_button(*m_table, index_ref));
    m_table->setCellWidget(row, 10, make_remove_button(*m_table, index_ref));
}
QComboBox* MultiHostTableUI::make_game_slot_box(QWidget& parent, int& row, int slot){
    QComboBox* box = new QComboBox(&parent);
    box->addItem("Slot 1");
    box->addItem("Slot 2");
    box->setCurrentIndex(slot);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].game_slot = index + 1;
        }
    );
    return box;
}
QComboBox* MultiHostTableUI::make_user_slot_box(QWidget& parent, int& row, int slot){
    QComboBox* box = new QComboBox(&parent);
    box->addItem("User 1");
    box->addItem("User 2");
    box->addItem("User 3");
    box->addItem("User 4");
    box->addItem("User 5");
    box->addItem("User 6");
    box->addItem("User 7");
    box->addItem("User 8");
    box->setCurrentIndex(slot);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].user_slot = index + 1;
        }
    );
    return box;
}
QLineEdit* MultiHostTableUI::make_skips_box(QWidget& parent, int& row, int skips){
    QLineEdit* box = new QLineEdit(&parent);
    QIntValidator* validator = new QIntValidator(0, 965, box);
    box->setValidator(validator);
    box->setText(QString::number(skips));
    box->setMaxLength(3);
    box->setMaximumWidth(50);
    box->setAlignment(Qt::AlignHCenter);
    connect(
        box, &QLineEdit::textChanged,
        this, [&, box](const QString& text){
            int revives = text.toInt();
            int fixed = revives;
            fixed = std::max(fixed, 0);
            fixed = std::min(fixed, 7);
            if (revives != fixed){
                box->setText(QString::number(fixed));
            }
            m_value.m_current[row].skips = fixed;
        }
    );
    return box;
}
QWidget* MultiHostTableUI::make_backup_save_box(QWidget& parent, int& row, bool backup_save){
    QWidget* widget = new QWidget(&parent);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setMargin(0);
    QCheckBox* box = new QCheckBox(&parent);
    layout->addWidget(box);
    box->setChecked(backup_save);
    connect(
        box, &QCheckBox::stateChanged,
        this, [&, box](int){
            m_value.m_current[row].backup_save = box->isChecked();
        }
    );
    return widget;
}
QWidget* MultiHostTableUI::make_catchable_box(QWidget& parent, int& row, bool always_catchable){
    QWidget* widget = new QWidget(&parent);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setMargin(0);
    QCheckBox* box = new QCheckBox(&parent);
    layout->addWidget(box);
    box->setChecked(always_catchable);
    connect(
        box, &QCheckBox::stateChanged,
        this, [&, box](int){
            m_value.m_current[row].always_catchable = box->isChecked();
        }
    );
    return widget;
}
QWidget* MultiHostTableUI::make_accept_FRs_box(QWidget& parent, int& row, bool accept_FRs){
    QWidget* widget = new QWidget(&parent);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setMargin(0);
    QCheckBox* box = new QCheckBox(&parent);
    layout->addWidget(box);
    box->setChecked(accept_FRs);
    connect(
        box, &QCheckBox::stateChanged,
        this, [&, box](int){
            m_value.m_current[row].accept_FRs = box->isChecked();
        }
    );
    return widget;
}
QComboBox* MultiHostTableUI::make_move_slot_box(QWidget& parent, int& row, int move_slot){
    QComboBox* box = new QComboBox(&parent);
    box->addItem("None");
    box->addItem("Slot 1");
    box->addItem("Slot 2");
    box->addItem("Slot 3");
    box->addItem("Slot 4");
    box->setCurrentIndex(move_slot);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].move_slot = index + 1;
        }
    );
    return box;
}
QWidget* MultiHostTableUI::make_dynamax_box(QWidget& parent, int& row, bool dynamax){
    QWidget* widget = new QWidget(&parent);
    QHBoxLayout* layout = new QHBoxLayout(widget);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setMargin(0);
    QCheckBox* box = new QCheckBox(&parent);
    layout->addWidget(box);
    box->setChecked(dynamax);
    connect(
        box, &QCheckBox::stateChanged,
        this, [&, box](int){
            m_value.m_current[row].dynamax = box->isChecked();
        }
    );
    return widget;
}
QLineEdit* MultiHostTableUI::make_delay_box(QWidget& parent, int& row, const QString& post_raid_delay){
    QLineEdit* box = new QLineEdit(&parent);
    box->setText(post_raid_delay);
//    box->setMaxLength(3);
//    box->setMaximumWidth(50);
    box->setAlignment(Qt::AlignHCenter);
//    box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(
        box, &QLineEdit::textChanged,
        this, [&](const QString& text){
            m_value.m_current[row].post_raid_delay = text;
//            QSize size = box->document()->size().toSize();
//            box->setFixedWidth(size);
        }
    );
    return box;
}
QPushButton* MultiHostTableUI::make_insert_button(QWidget& parent, int& row){
    QPushButton* button = new QPushButton(&parent);
    QFont font;
    font.setBold(true);
    button->setFont(font);
    button->setText("Insert");
//    QSizePolicy policy;
//    policy.setHorizontalPolicy(QSizePolicy::Minimum);
//    policy.setHorizontalStretch(0);
//    button->setSizePolicy(policy);
    button->setMaximumWidth(60);
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = row;
            MultiHostTable::GameSlot item{
                1, 1,
                3, false, true,
                true,
                0, true,
                "0 * TICKS_PER_SECOND"
            };

            //  Update data vector.
            m_value.m_current.insert(m_value.m_current.begin() + index, item);

            //  Update index vector.
            m_index_table.insert(m_index_table.begin() + index, std::unique_ptr<int>(new int(index)));
            int& new_row = *m_index_table[index];
            for (size_t c = 0; c < m_index_table.size(); c++){
                *m_index_table[c] = (int)c;
            }

            //  Update UI.
            m_table->insertRow(index);
            add_row(index, item, new_row);
            update_table_height();
        }
    );
    return button;
}
QPushButton* MultiHostTableUI::make_remove_button(QWidget& parent, int& row){
    QPushButton* button = new QPushButton(&parent);
    QFont font;
    font.setBold(true);
    button->setFont(font);
    button->setText("Delete");
    button->setMaximumWidth(60);
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = row;

            //  Update data vector.
            m_index_table.erase(m_index_table.begin() + index);

            //  Update index vector.
            for (size_t c = 0; c < m_index_table.size(); c++){
                *m_index_table[c] = (int)c;
            }
            m_value.m_current.erase(m_value.m_current.begin() + index);

            //  Update UI.
            m_table->removeRow(index);
            update_table_height();
        }
    );
    return button;
}

void MultiHostTableUI::update_table_height(){
    int rows = m_table->rowCount();
    int total_height = 5;
    total_height += m_table->horizontalHeader()->height();
    total_height += m_table->horizontalScrollBar()->height();
    for (int c = 0; c < rows; c++) {
        total_height += m_table->verticalHeader()->sectionSize(c);
    }
//    cout << total_height << endl;
    m_table->setMinimumHeight(total_height);
    m_table->setMaximumHeight(total_height);
//    this->adjustSize();
//    this->parentWidget()->adjustSize();
//    this->parentWidget()->parentWidget()->adjustSize();
}



MultiHostTableUI::MultiHostTableUI(QWidget& parent, MultiHostTable& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text);
//    text->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_table = new QTableWidget(this);
    layout->addWidget(m_table, 0, Qt::AlignTop);
    m_table->setColumnCount(11);

    QStringList header;
    header << "Game" << "User" << "Skips" << "Backup Save" << "Always Catchable" << "Accept FRs" << "1st Move" << "Dynamax" << "Post Raid Delay" << "" << "";
    m_table->setHorizontalHeaderLabels(header);
    QFont font;
    font.setBold(true);
    m_table->horizontalHeader()->setFont(font);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    m_table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
//    m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    size_t rows = m_value.m_current.size();
    m_table->setRowCount(m_value.m_current.size() + 1);
    for (size_t c = 0; c < rows; c++){
        const auto& item = m_value.m_current[c];
        m_index_table.emplace_back(new int);
        add_row(c, item, *m_index_table.back());
    }

    QPushButton* button = new QPushButton(m_table);
    button->setText("Add Row");
    m_table->setCellWidget(m_value.m_current.size(), 0, button);
    update_table_height();
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = m_index_table.size();

            //  Update data vector.
            m_value.m_current.emplace_back(
                MultiHostTable::GameSlot{
                    1, 1,
                    3, false, true,
                    true,
                    0, true,
                    "0 * TICKS_PER_SECOND"
                }
            );
            const auto& item = m_value.m_current.back();

            //  Update index vector.
            m_index_table.emplace_back(new int);

            //  Update UI.
            m_table->insertRow(index);
            add_row(index, item, *m_index_table.back());
            update_table_height();
        }
    );




}
MultiHostTableUI::~MultiHostTableUI(){

}





