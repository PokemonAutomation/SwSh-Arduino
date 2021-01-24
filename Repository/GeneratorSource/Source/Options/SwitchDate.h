/*  Switch Date
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_SwitchDate_H
#define PokemonAutomation_SwitchDate_H

#include <QDate>
#include "SingleStatementOption.h"

class SwitchDate : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;

public:
    SwitchDate(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    virtual bool is_valid() const override;
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

private:
    friend class SwitchDateUI;
    QDate m_default;
    QDate m_current;
};

class SwitchDateUI : public QWidget{
    Q_OBJECT

public:
    SwitchDateUI(QWidget& parent, SwitchDate& value, const QString& label);
    ~SwitchDateUI();

private:
    SwitchDate& m_value;
};

#endif


