#include "LoRa_E220.h"
#include "E220_My_Settings.h"

ResponseStatus configureLoRa(LoRa_E220 &e220ttl, void (*printParameters)(struct Configuration configuration))
{
    ResponseStructContainer c;
    c = e220ttl.getConfiguration();
    Configuration configuration = *(Configuration *)c.data;

    printParameters(configuration); // Вивід параметрів

    ResponseStructContainer cMi;
    cMi = e220ttl.getModuleInformation();
    Serial.println(cMi.status.getResponseDescription());
    Serial.println(cMi.status.code);

    configuration.ADDL = 0x02;
    configuration.ADDH = 0x00;
    configuration.CHAN = 23;

    configuration.SPED.uartBaudRate = UART_BPS_9600;
    configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;
    configuration.SPED.uartParity = MODE_00_8N1;

    configuration.OPTION.subPacketSetting = SPS_200_00;
    configuration.OPTION.RSSIAmbientNoise = RSSI_AMBIENT_NOISE_DISABLED;
    configuration.OPTION.transmissionPower = POWER_13;

    configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;
    configuration.TRANSMISSION_MODE.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
    configuration.TRANSMISSION_MODE.enableLBT = LBT_DISABLED;
    configuration.TRANSMISSION_MODE.WORPeriod = WOR_2000_011;

    // application changes
    ResponseStatus rs = e220ttl.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
    Serial.println(rs.getResponseDescription());
    Serial.println(rs.code);

    c = e220ttl.getConfiguration();
    configuration = *(Configuration *)c.data;
    Serial.println(c.status.getResponseDescription());
    Serial.println(c.status.code);

    printParameters(configuration);
    c.close();
    // return status
    return rs;
}

void printParameters(struct Configuration configuration)
{
    Serial.println("----------------------------------------");

    Serial.print(F("HEAD : "));
    Serial.print(configuration.COMMAND, HEX);
    Serial.print(" ");
    Serial.print(configuration.STARTING_ADDRESS, HEX);
    Serial.print(" ");
    Serial.println(configuration.LENGHT, HEX);
    Serial.println(F(" "));
    Serial.print(F("AddH : "));
    Serial.println(configuration.ADDH, HEX);
    Serial.print(F("AddL : "));
    Serial.println(configuration.ADDL, HEX);
    Serial.println(F(" "));
    Serial.print(F("Chan : "));
    Serial.print(configuration.CHAN, DEC);
    Serial.print(" -> ");
    Serial.println(configuration.getChannelDescription());
    Serial.println(F(" "));
    Serial.print(F("SpeedParityBit     : "));
    Serial.print(configuration.SPED.uartParity, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getUARTParityDescription());
    Serial.print(F("SpeedUARTDatte     : "));
    Serial.print(configuration.SPED.uartBaudRate, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getUARTBaudRateDescription());
    Serial.print(F("SpeedAirDataRate   : "));
    Serial.print(configuration.SPED.airDataRate, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.SPED.getAirDataRateDescription());
    Serial.println(F(" "));
    Serial.print(F("OptionSubPacketSett: "));
    Serial.print(configuration.OPTION.subPacketSetting, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getSubPacketSetting());
    Serial.print(F("OptionTranPower    : "));
    Serial.print(configuration.OPTION.transmissionPower, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getTransmissionPowerDescription());
    Serial.print(F("OptionRSSIAmbientNo: "));
    Serial.print(configuration.OPTION.RSSIAmbientNoise, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.OPTION.getRSSIAmbientNoiseEnable());
    Serial.println(F(" "));
    Serial.print(F("TransModeWORPeriod : "));
    Serial.print(configuration.TRANSMISSION_MODE.WORPeriod, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.TRANSMISSION_MODE.getWORPeriodByParamsDescription());
    Serial.print(F("TransModeEnableLBT : "));
    Serial.print(configuration.TRANSMISSION_MODE.enableLBT, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.TRANSMISSION_MODE.getLBTEnableByteDescription());
    Serial.print(F("TransModeEnableRSSI: "));
    Serial.print(configuration.TRANSMISSION_MODE.enableRSSI, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.TRANSMISSION_MODE.getRSSIEnableByteDescription());
    Serial.print(F("TransModeFixedTrans: "));
    Serial.print(configuration.TRANSMISSION_MODE.fixedTransmission, BIN);
    Serial.print(" -> ");
    Serial.println(configuration.TRANSMISSION_MODE.getFixedTransmissionDescription());

    Serial.println("----------------------------------------");
}
void printModuleInformation(struct ModuleInformation moduleInformation)
{
    Serial.println("----------------------------------------");
    Serial.print(F("HEAD: "));
    Serial.print(moduleInformation.COMMAND, HEX);
    Serial.print(" ");
    Serial.print(moduleInformation.STARTING_ADDRESS, HEX);
    Serial.print(" ");
    Serial.println(moduleInformation.LENGHT, DEC);

    Serial.print(F("Model no.: "));
    Serial.println(moduleInformation.model, HEX);
    Serial.print(F("Version  : "));
    Serial.println(moduleInformation.version, HEX);
    Serial.print(F("Features : "));
    Serial.println(moduleInformation.features, HEX);
    Serial.println("----------------------------------------");
}
