#include <QDebug>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/libimobiledevice.h>

afc_error_t safe_afc_read_directory(afc_client_t afcClient, idevice_t device,
                                    const char *path, char ***dirs)
{
    try {
        if (!afcClient || !device) {
            qDebug() << "AFC client is null in safe_afc_read_directory";
            return AFC_E_INVALID_ARG;
        }

        afc_error_t result = afc_read_directory(afcClient, path, dirs);

        return result;
    } catch (const std::exception &e) {
        qDebug() << "Exception in safe_afc_read_directory:" << e.what();
        return AFC_E_UNKNOWN_ERROR;
    }
}