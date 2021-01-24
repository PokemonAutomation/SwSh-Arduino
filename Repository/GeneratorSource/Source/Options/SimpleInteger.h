/*  Simple Integer
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_SimpleInteger_H
#define PokemonAutomation_SimpleInteger_H

#include "SingleStatementOption.h"

class SimpleInteger : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;
    static const QString JSON_MIN_VALUE;
    static const QString JSON_MAX_VALUE;

public:
    SimpleInteger(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    virtual bool is_valid() const override;
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

private:
    friend class SimpleIntegerUI;
    int32_t m_min_value;
    int32_t m_max_value;
    int32_t m_default;
    int32_t m_current;
};

class SimpleIntegerUI : public QWidget{
    Q_OBJECT

public:
    SimpleIntegerUI(QWidget& parent, SimpleInteger& value, const QString& label);
    ~SimpleIntegerUI();

private:
    SimpleInteger& m_value;
};

#endif


