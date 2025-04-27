#include "LoRa_E220.h"

ResponseStatus configureLoRa(LoRa_E220 &e220ttl, void (*printParameters)(struct Configuration configuration));
void printParameters(struct Configuration configuration);
void printModuleInformation(struct ModuleInformation moduleInformation);