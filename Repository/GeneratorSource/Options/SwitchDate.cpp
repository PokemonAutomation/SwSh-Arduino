/*  Switch Date
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonArray>
#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QDateEdit>
#include "Tools/Tools.h"
#include "SwitchDate.h"

const QString SwitchDate::OPTION_TYPE = "SwitchDate";


int SwitchDate_init = register_option(
    SwitchDate::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new SwitchDate(obj)
        );
    }
);

SwitchDate::SwitchDate(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_default(json_get_date(obj, JSON_DEFAULT))
    , m_current(json_get_date(obj, JSON_CURRENT))
{}
bool SwitchDate::is_valid() const{
    return valid_switch_date(m_current);
}
void SwitchDate::restore_defaults(){
    m_current = m_default;
}
QJsonObject SwitchDate::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_DEFAULT, json_write_date(m_default));
    root.insert(JSON_CURRENT, json_write_date(m_current));
    return root;
}
std::string SwitchDate::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = {";
    str += std::to_string(m_current.year());
    str += ", ";
    str += std::to_string(m_current.month());
    str += ", ";
    str += std::to_string(m_current.day());
    str += "};\r\n";
    return str;
}
QWidget* SwitchDate::make_ui(QWidget& parent){
    return new SwitchDateUI(parent, *this, m_label);
}

SwitchDateUI::SwitchDateUI(QWidget& parent, SwitchDate& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);

    QDateEdit* date_edit = new QDateEdit(m_value.m_current);
    layout->addWidget(date_edit, 1);
    date_edit->setMinimumDate(QDate(2000, 1, 1));
    date_edit->setMaximumDate(QDate(2060, 12, 31));

    connect(
        date_edit, &QDateEdit::dateChanged,
        this, [=](const QDate& date){
            m_value.m_current = date;
        }
    );
}
SwitchDateUI::~SwitchDateUI(){

}







