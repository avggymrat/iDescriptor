#include "../../iDescriptor.h"
#include "plist/plist.h"
#include <QDebug>
#include <libimobiledevice/diagnostics_relay.h>
#include <string>

void get_battery_info(std::string productType, idevice_t idevice,
                      bool is_iphone, plist_t &diagnostics)
{
    diagnostics_relay_client_t diagnostics_client = nullptr;
    try {

        if (diagnostics_relay_client_start_service(idevice, &diagnostics_client,
                                                   nullptr) !=
            DIAGNOSTICS_RELAY_E_SUCCESS) {
            qDebug() << "Failed to start diagnostics relay service.";
            return;
        }

        bool newerThaniPhone8 =
            is_product_type_newer(productType, std::string("iPhone8,1"));

        const char *batteryQuery =
            is_iphone
                ? newerThaniPhone8 ? "AppleSmartBattery" : "AppleARMPMUCharger"
                : "AppleARMPMUCharger";

        if (diagnostics_relay_query_ioregistry_entry(
                diagnostics_client, nullptr, batteryQuery, &diagnostics) !=
                DIAGNOSTICS_RELAY_E_SUCCESS &&
            !diagnostics) {

            qDebug()
                << "Failed to query diagnostics relay for AppleARMPMUCharger.";
            if (diagnostics_client)
                diagnostics_relay_client_free(diagnostics_client);
        }
    } catch (const std::exception &e) {
        if (diagnostics_client)
            diagnostics_relay_client_free(diagnostics_client);
        qDebug() << "Exception in get_battery_info: " << e.what();
    }
}