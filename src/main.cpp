#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QStyleFactory>
#include <QtGlobal>
#include <stdlib.h> // For getenv

#ifdef WIN32
#include "platform/windows/check_deps.h"
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef WIN32
    // This setup MUST be done before the QApplication object is created.
    QString appPath = QCoreApplication::applicationDirPath();
    QString gstPluginPath =
        QDir::toNativeSeparators(appPath + "/gstreamer-1.0");
    QString gstPluginScannerPath =
        QDir::toNativeSeparators(appPath + "/gstreamer-1.0/gst-plugin-scanner");

    // Add the application's directory to the PATH so GStreamer plugins can find
    // their dependencies (e.g., FFmpeg DLLs).
    const char *oldPath = getenv("PATH");
    QString newPath = appPath + ";" + QString(oldPath);
    qputenv("PATH", newPath.toUtf8());

    qputenv("GST_PLUGIN_PATH", gstPluginPath.toUtf8());
    qDebug() << "GST_PLUGIN_PATH=" << gstPluginPath;
    printf("GST_PLUGIN_PATH=%s\n", gstPluginPath.toUtf8().data());
    qputenv("GST_REGISTRY_REUSE_PLUGIN_SCANNER", "yes");
    qDebug() << "GST_REGISTRY_REUSE_PLUGIN_SCANNER=yes";
    printf("GST_REGISTRY_REUSE_PLUGIN_SCANNER=yes\n");
    qputenv("GST_PLUGIN_SYSTEM_PATH", gstPluginPath.toUtf8());
    qDebug() << "GST_PLUGIN_SYSTEM_PATH=" << gstPluginPath;
    printf("GST_PLUGIN_SYSTEM_PATH=%s\n", gstPluginPath.toUtf8().data());
    qputenv("GST_DEBUG", "GST_PLUGIN_LOADING:5");
    qDebug() << "GST_DEBUG=GST_PLUGIN_LOADING:5";
    printf("GST_DEBUG=GST_PLUGIN_LOADING:5\n");
    qputenv("GST_PLUGIN_SCANNER_1_0", gstPluginScannerPath.toUtf8());
    qDebug() << "GST_PLUGIN_SCANNER_1_0=" << gstPluginScannerPath;
    printf("GST_PLUGIN_SCANNER_1_0=%s\n", gstPluginScannerPath.toUtf8().data());
#endif
    QCoreApplication::setOrganizationName("iDescriptor");
    // QCoreApplication::setOrganizationDomain("iDescriptor.com");
    QCoreApplication::setApplicationName("iDescriptor");
    // QCoreApplication::setApplicationVersion(IDESCRIPTOR_VERSION);
    // QApplication::setStyle(QStyleFactory::create("Windows"));
#ifndef __APPLE__
    QApplication::setStyle(QStyleFactory::create("Fusion"));
#endif

    MainWindow *w = MainWindow::sharedInstance();
    w->show();
    return a.exec();
}
