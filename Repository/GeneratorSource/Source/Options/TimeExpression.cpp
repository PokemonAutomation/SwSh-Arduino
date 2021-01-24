/*  Time Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "SharedCpp/PrettyPrint.h"
#include "SharedCpp/QtJsonTools.h"
#include "Tools/Tools.h"
#include "TimeExpression.h"


const QString TimeExpression::OPTION_TYPE = "TimeExpression";
const QString TimeExpression::JSON_MIN_VALUE = "03-MinValue";
const QString TimeExpression::JSON_MAX_VALUE = "04-MaxValue";


int TimeExpression_init = register_option(
    TimeExpression::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new TimeExpression(obj)
        );
    }
);


TimeExpression::TimeExpression(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_min_value(json_get_int(obj, JSON_MIN_VALUE))
    , m_max_value(json_get_int(obj, JSON_MAX_VALUE))
    , m_default(json_get_string(obj, JSON_DEFAULT))
    , m_current(json_get_string(obj, JSON_CURRENT))
{
    update();
}

void TimeExpression::restore_defaults(){
    m_current = m_default;
}
QJsonObject TimeExpression::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_MIN_VALUE, m_min_value);
    root.insert(JSON_MAX_VALUE, m_max_value);
    root.insert(JSON_DEFAULT, m_default);
    root.insert(JSON_CURRENT, m_current);
    return root;
}
std::string TimeExpression::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = ";
    str += std::to_string(m_value);
    str += ";\r\n";
    return str;
}
QWidget* TimeExpression::make_ui(QWidget& parent){
    return new ExpressionUI(parent, *this, m_label);
}
bool TimeExpression::update(){
    if (m_current.isEmpty() || m_current.isNull()){
        m_error = "Expression is empty.";
        return false;
    }
    try{
        m_value = parse_ticks_i32(m_current);
    }catch (const StringException& str){
        m_error = str.message;
        return false;
    }catch (...){
        m_error = "Unknown Error";
        return false;
    }

    if ((int64_t)m_value < (int64_t)m_min_value){
        m_error = "Overflow: Number is too small.";
        return false;
    }
    if ((int64_t)m_value > (int64_t)m_max_value){
        m_error = "Overflow: Number is too large.";
        return false;
    }
    m_error.clear();
    return true;
}
bool TimeExpression::set_value(const QString& str){
    m_current = str;
    return update();
}
QString TimeExpression::time_string() const{
    if (!m_error.isEmpty()){
        return "<font color=\"red\">" + m_error + "</font>";
    }
    return PokemonAutomation::ticks_to_time(m_value).c_str();
}

ExpressionUI::ExpressionUI(QWidget& parent, TimeExpression& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);
    QVBoxLayout* rows = new QVBoxLayout();
    layout->addLayout(rows, 1);

    QHBoxLayout* row0 = new QHBoxLayout();
    rows->addLayout(row0);
    QHBoxLayout* row1 = new QHBoxLayout();
    rows->addLayout(row1);

    QLineEdit* box = new QLineEdit(m_value.m_current, this);
    row0->addWidget(box);
    row0->addWidget(new QLabel("ticks", this));

    QLabel* seconds = new QLabel(m_value.time_string(), this);
    seconds->setAlignment(Qt::AlignHCenter);
    row1->addWidget(seconds);

    connect(
        box, &QLineEdit::textChanged,
        this, [=](const QString& text){
//            cout << text.toUtf8().data() << endl;
            m_value.set_value(text);
            seconds->setText(m_value.time_string());
        }
    );
}
ExpressionUI::~ExpressionUI(){

}


