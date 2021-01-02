/*  Persistent Settings
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QString>

class PersistentSettings{
public:
    void write() const;
    void read();

public:
    QString config_path = "GeneratorConfig";
    QString source_path = "DeviceSource";
    size_t mcu_index = 0;

};

extern PersistentSettings settings;
