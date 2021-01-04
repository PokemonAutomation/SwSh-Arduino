/*  BooleanCheckBox
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include "Tools/Tools.h"
#include "BooleanCheckBox.h"

const QString BooleanCheckBox::OPTION_TYPE = "BooleanCheckBox";

int BooleanCheckBox_init = register_option(
    BooleanCheckBox::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new BooleanCheckBox(obj)
        );
    }
);


BooleanCheckBox::BooleanCheckBox(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_default(json_get_bool(obj, JSON_DEFAULT))
    , m_current(json_get_bool(obj, JSON_CURRENT))
{}
void BooleanCheckBox::restore_defaults(){
    m_current = m_default;
}
QJsonObject BooleanCheckBox::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_DEFAULT, m_default);
    root.insert(JSON_CURRENT, m_current);
    return root;
}
std::string BooleanCheckBox::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = ";
    str += m_current ? "true" : "false";
    str += ";\r\n";
    return str;
}
QWidget* BooleanCheckBox::make_ui(QWidget& parent){
    return new BooleanCheckBoxUI(parent, *this, m_label);
}


BooleanCheckBoxUI::BooleanCheckBoxUI(QWidget& parent, BooleanCheckBox& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text, 3);
    text->setWordWrap(true);
    QCheckBox* box = new QCheckBox(this);
    box->setChecked(m_value.m_current);
    layout->addWidget(box, 1);
    connect(
        box, &QCheckBox::stateChanged,
        this, [=](int){ m_value.m_current = box->isChecked(); }
    );
}
BooleanCheckBoxUI::~BooleanCheckBoxUI(){

}
