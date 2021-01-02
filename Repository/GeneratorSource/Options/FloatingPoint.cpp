/*  Floating Point
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QLineEdit>
#include "Tools/Tools.h"
#include "FloatingPoint.h"

const QString FloatingPoint::OPTION_TYPE = "FloatingPoint";
const QString FloatingPoint::JSON_MIN_VALUE = "03-MinValue";
const QString FloatingPoint::JSON_MAX_VALUE = "04-MaxValue";


int FloatingPoint_init = register_option(
    FloatingPoint::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new FloatingPoint(obj)
        );
    }
);

FloatingPoint::FloatingPoint(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_min_value(json_get_double(obj, JSON_MIN_VALUE))
    , m_max_value(json_get_double(obj, JSON_MAX_VALUE))
    , m_default(json_get_double(obj, JSON_DEFAULT))
    , m_current(json_get_double(obj, JSON_CURRENT))
{}
bool FloatingPoint::is_valid() const{
    return m_min_value <= m_current && m_current <= m_max_value;
}
void FloatingPoint::restore_defaults(){
    m_current = m_default;
}
QJsonObject FloatingPoint::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_MIN_VALUE, m_min_value);
    root.insert(JSON_MAX_VALUE, m_max_value);
    root.insert(JSON_DEFAULT, m_default);
    root.insert(JSON_CURRENT, m_current);
    return root;
}
std::string FloatingPoint::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = ";
    str += std::to_string(m_current);
    str += ";\r\n";
    return str;
}
QWidget* FloatingPoint::make_ui(QWidget& parent){
    return new FloatingPointUI(parent, *this, m_label);
}

FloatingPointUI::FloatingPointUI(QWidget& parent, FloatingPoint& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);
    QLineEdit* box = new QLineEdit(QString::number(m_value.m_current, 'f', 2), this);
//    box->setInputMask("999999999");
    QDoubleValidator* validator = new QDoubleValidator(value.m_min_value, value.m_max_value, 2, this);
    box->setValidator(validator);
    layout->addWidget(box, 1);
    connect(
        box, &QLineEdit::textChanged,
        this, [=](const QString& text){
            double read = text.toDouble();
            double fixed = read;
//            fixed = std::max(fixed, m_value.m_min_value);
            fixed = std::min(fixed, m_value.m_max_value);
            if (read != fixed){
                box->setText(QString::number(fixed, 'f', 2));
            }
            m_value.m_current = fixed;
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Text, m_value.is_valid() ? Qt::black : Qt::red);
            box->setPalette(*palette);
        }
    );
}
FloatingPointUI::~FloatingPointUI(){

}
