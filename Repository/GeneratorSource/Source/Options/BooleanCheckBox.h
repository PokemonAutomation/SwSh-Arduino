/*  BooleanCheckBox
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_BooleanCheckBox_H
#define PokemonAutomation_BooleanCheckBox_H

#include "SingleStatementOption.h"

class BooleanCheckBox : public SingleStatementOption{
public:
    static const QString OPTION_TYPE;

public:
    BooleanCheckBox(const QJsonObject& obj);

    virtual const QString& type() const override{ return OPTION_TYPE; }
    virtual void restore_defaults() override;

    virtual QJsonObject to_json() const override;
    virtual std::string to_cpp() const override;

    virtual QWidget* make_ui(QWidget& parent) override;

private:
    friend class BooleanCheckBoxUI;
    bool m_default;
    bool m_current;
};



class BooleanCheckBoxUI : public QWidget{
    Q_OBJECT

public:
    BooleanCheckBoxUI(QWidget& parent, BooleanCheckBox& value, const QString& label);
    ~BooleanCheckBoxUI();
private:
    BooleanCheckBox& m_value;
};



#endif
