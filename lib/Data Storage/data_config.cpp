#include "data_config.h"
DataConfig::DataConfig()
{
    EEPROM.begin(eepromSize);
    loadWifiConfig();
}
void DataConfig::updateWifiConfig(String SSID, String PASS)
{
    ssid = SSID;
    password = PASS;
    EEPROM.begin(eepromSize);

    // erase
    for (int i = 0; i < eepromSize; ++i)
    {
        EEPROM.write(i, 0xFF);
    }

    int ssidLength = ssid.length();
    int passLength = password.length();

    // Save ssid length
    EEPROM.write(0, ssidLength);

    // Save ssid
    for (int i = 0; i < ssidLength; i++)
    {
        EEPROM.write(i + 1, ssid[i]);
    }

    // Save password length
    EEPROM.write(ssidLength + 1, passLength);

    // Save password
    for (int i = 0; i < passLength; i++)
    {
        EEPROM.write(ssidLength + 2 + i, password[i]);
    }

    EEPROM.commit();
    EEPROM.end();
}

void DataConfig::loadWifiConfig()
{
    EEPROM.begin(eepromSize);

    // Read ssid length
    int ssidLength = EEPROM.read(0);

    // Read ssid
    char ssidBuffer[ssidLength + 1];
    for (int i = 0; i < ssidLength; i++)
    {
        ssidBuffer[i] = EEPROM.read(i + 1);
    }
    ssidBuffer[ssidLength] = '\0';
    ssid = String(ssidBuffer);

    // Read password length
    int passLength = EEPROM.read(ssidLength + 1);

    // Read password
    char passBuffer[passLength + 1];
    for (int i = 0; i < passLength; i++)
    {
        passBuffer[i] = EEPROM.read(ssidLength + 2 + i);
    }
    passBuffer[passLength] = '\0';
    password = String(passBuffer);

    EEPROM.end();
}

String DataConfig ::getSSID()
{
    return this->ssid;
}
String DataConfig ::getPASSWORD()
{
    return this->password;
}