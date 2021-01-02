/*  Time Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_TimeOption_H
#define PokemonAutomation_TimeOption_H

#include "SingleStatementOption.h"

class TimeExpression : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;
    static const QString JSON_MIN_VALUE;
    static const QString JSON_MAX_VALUE;

public:
    TimeExpression(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    bool is_valid() const override{ return m_error.isEmpty(); }
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

public:
    bool set_value(const QString& str);
    QString time_string() const;

private:
    bool update();

private:
    friend class ExpressionUI;
    int32_t m_min_value;
    int32_t m_max_value;
    QString m_default;
    QString m_current;

//    uint32_t m_limit;

    int32_t m_value;
    QString m_error;
};


class ExpressionUI : public QWidget{
    Q_OBJECT

public:
    ExpressionUI(QWidget& parent, TimeExpression& value, const QString& label);
    ~ExpressionUI();

private:
    TimeExpression& m_value;
};


#endif


