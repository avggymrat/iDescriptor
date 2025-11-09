/*
 * iDescriptor: A free and open-source idevice management tool.
 *
 * Copyright (C) 2025 Uncore <https://github.com/uncor3>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "../../iDescriptor.h"
#include <QByteArray>
#include <QDebug>

QByteArray read_afc_file_to_byte_array(afc_client_t afcClient, const char *path)
{
    uint64_t fd_handle = 0;
    afc_error_t fd_err =
        afc_file_open(afcClient, path, AFC_FOPEN_RDONLY, &fd_handle);

    if (fd_err != AFC_E_SUCCESS) {
        qDebug() << "Could not open file" << path << "Error:" << fd_err;
        return QByteArray();
    }

    // TODO:Maybe use afc_get_file_info_plist instead?
    char **info = NULL;
    afc_get_file_info(afcClient, path, &info);
    uint64_t fileSize = 0;
    if (info) {
        for (int i = 0; info[i]; i += 2) {
            if (strcmp(info[i], "st_size") == 0) {
                fileSize = std::stoull(info[i + 1]);
                break;
            }
        }
        afc_dictionary_free(info);
    }

    if (fileSize == 0) {
        afc_file_close(afcClient, fd_handle);
        return QByteArray();
    }

    QByteArray buffer;
    buffer.resize(fileSize);

    uint64_t totalBytesRead = 0;
    const uint32_t CHUNK_SIZE = 1024 * 1024; // Read in 1MB chunks
    char *p = buffer.data();

    while (totalBytesRead < fileSize) {
        uint32_t bytesToRead =
            std::min((uint64_t)CHUNK_SIZE, fileSize - totalBytesRead);
        uint32_t bytesReadThisChunk = 0;
        afc_error_t read_err =
            afc_file_read(afcClient, fd_handle, p + totalBytesRead, bytesToRead,
                          &bytesReadThisChunk);

        if (read_err != AFC_E_SUCCESS) {
            qDebug() << "AFC Error: Read failed for file" << path
                     << "Error:" << read_err;
            afc_file_close(afcClient, fd_handle);
            return QByteArray();
        }

        if (bytesReadThisChunk == 0) {
            // Premature end of file
            break;
        }
        totalBytesRead += bytesReadThisChunk;
    }

    afc_file_close(afcClient, fd_handle);

    if (totalBytesRead != fileSize) {
        qDebug() << "AFC Error: Read mismatch for file" << path
                 << "Read:" << totalBytesRead << "Expected:" << fileSize;
        return QByteArray(); // Read failed
    }

    return buffer;
}