/*  Main Window UI
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "Tools/Tools.h"
#include "SettingsDialog.h"
#include "ProgramDialog.h"
#include "MainWindow.h"

const QString VERSION = "v0.2.8";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_program_settings_widget(nullptr)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(800, 600);
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    setCentralWidget(centralwidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    setStatusBar(statusbar);

    setWindowTitle(STRING_POKEMON + " Automation .hex Generator (" + VERSION + ")");

    QMetaObject::connectSlotsByName(this);

    QHBoxLayout* hbox = new QHBoxLayout(centralwidget);

    QVBoxLayout* left = new QVBoxLayout();
    hbox->addLayout(left, 2);
    left->setAlignment(Qt::AlignTop);
    left->addWidget(new QLabel("<b><font size=5>Device and Program:</font></b>", this));


    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Device/MCU Type:", this));
    left->addWidget(m_mcu_list = new McuList(*this));

    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Select a Program:", this));
    m_program_list = new ProgramDialog(*this);
    left->addWidget(m_program_list);

    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Global Settings:", this));
    m_settings_list = new SettingsDialog(*this);
    left->addWidget(m_settings_list);


    QHBoxLayout* support = new QHBoxLayout();
    left->addLayout(support);
//    support->setMargin(0);

    QVBoxLayout* links = new QVBoxLayout();
    support->addLayout(links);

    QLabel* discord = new QLabel(this);
    links->addWidget(discord);
    discord->setText("<a href=\"https://discord.gg/cQ4gWxN\">Discord Server</a>");
    discord->setTextFormat(Qt::RichText);
    discord->setTextInteractionFlags(Qt::TextBrowserInteraction);
    discord->setOpenExternalLinks(true);

    QLabel* github = new QLabel(this);
    links->addWidget(github);
    github->setText("<a href=\"https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts\">GitHub Repository</a>");
    github->setTextFormat(Qt::RichText);
    github->setTextInteractionFlags(Qt::TextBrowserInteraction);
    github->setOpenExternalLinks(true);


    QPushButton* about = new QPushButton("About", this);
    support->addWidget(about);
    connect(
        about, &QPushButton::clicked,
        this, [&](bool){
            QMessageBox box;
            box.information(
                nullptr,
                "About",
                STRING_POKEMON + " Automation .hex Generator (" + VERSION + ")<br>" +
                "Copyright: 2020 - 2021<br>" +
                "<br>"
                "Made by the " + STRING_POKEMON + " Automation Discord Server.<br>"
                "<br>"
                "This program uses Qt and dynamically links to unmodified Qt libraries under LGPL.<br>"
            );
        }
    );


    hbox->addSpacerItem(new QSpacerItem(10, 10));

    QVBoxLayout* right = new QVBoxLayout();
    m_program_settings_parent_layout = right;
    hbox->addLayout(right, 4);
    right->setAlignment(Qt::AlignTop);
    right->addWidget(new QLabel("<b><font size=5>Program Settings:</font></b>", this));

}

const std::string& MainWindow::current_MCU() const{
    return m_mcu_list->get_MCU();
}
void MainWindow::replace_active_program(RightPanel& panel){
    if (m_program_settings_widget != nullptr){
        m_program_settings_parent_layout->removeWidget(m_program_settings_widget);
        delete m_program_settings_widget;
        m_program_settings_widget = nullptr;
    }
    m_program_settings_widget = panel.make_ui(*this);
    m_program_settings_parent_layout->addWidget(m_program_settings_widget);
}






