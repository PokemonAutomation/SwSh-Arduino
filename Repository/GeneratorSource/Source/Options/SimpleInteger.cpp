/*  Simple Integer
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QIntValidator>
#include <QLineEdit>
#include "SharedCpp/QtJsonTools.h"
#include "Tools/Tools.h"
#include "SimpleInteger.h"

const QString SimpleInteger::OPTION_TYPE = "SimpleInteger";
const QString SimpleInteger::JSON_MIN_VALUE = "03-MinValue";
const QString SimpleInteger::JSON_MAX_VALUE = "04-MaxValue";


int SimpleInteger_init = register_option(
    SimpleInteger::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new SimpleInteger(obj)
        );
    }
);

SimpleInteger::SimpleInteger(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_min_value(json_get_int(obj, JSON_MIN_VALUE))
    , m_max_value(json_get_int(obj, JSON_MAX_VALUE))
    , m_default(json_get_int(obj, JSON_DEFAULT))
    , m_current(json_get_int(obj, JSON_CURRENT))
{}
bool SimpleInteger::is_valid() const{
    return m_min_value <= m_current && m_current <= m_max_value;
}
void SimpleInteger::restore_defaults(){
    m_current = m_default;
}
QJsonObject SimpleInteger::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_MIN_VALUE, m_min_value);
    root.insert(JSON_MAX_VALUE, m_max_value);
    root.insert(JSON_DEFAULT, m_default);
    root.insert(JSON_CURRENT, m_current);
    return root;
}
std::string SimpleInteger::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = ";
    str += std::to_string(m_current);
    str += ";\r\n";
    return str;
}
QWidget* SimpleInteger::make_ui(QWidget& parent){
    return new SimpleIntegerUI(parent, *this, m_label);
}

SimpleIntegerUI::SimpleIntegerUI(QWidget& parent, SimpleInteger& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);
    QLineEdit* box = new QLineEdit(QString::number(m_value.m_current), this);
//    box->setInputMask("999999999");
    QIntValidator* validator = new QIntValidator(value.m_min_value, value.m_max_value, box);
    box->setValidator(validator);
    layout->addWidget(box, 1);
    connect(
        box, &QLineEdit::textChanged,
        this, [=](const QString& text){
            int32_t read = text.toInt();
            int32_t fixed = read;
//            fixed = std::max(fixed, m_value.m_min_value);
            fixed = std::min(fixed, m_value.m_max_value);
            if (read != fixed){
                box->setText(QString::number(fixed));
            }
            m_value.m_current = fixed;
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Text, m_value.is_valid() ? Qt::black : Qt::red);
            box->setPalette(*palette);
        }
    );
}
SimpleIntegerUI::~SimpleIntegerUI(){

}
