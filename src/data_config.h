#ifndef DATA_CONFIG_H
#define DATA_CONFIG_H
#include <EEPROM.h>

class DataConfig
{
private:
    String ssid;
    String password;
    int eepromSize = 512;
    DataConfig();

public:
    static DataConfig &getInstance()
    {
        static DataConfig instance;
        return instance;
    }

    void loadWifiConfig();
    void updateWifiConfig(String SSID, String PASS);
    String getSSID();
    String getPASSWORD();
};

#endif