#ifndef AFCEXPLORER_H
#define AFCEXPLORER_H

#include "iDescriptor-ui.h"
#include "iDescriptor.h"
#include <QAction>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QSplitter>
#include <QStack>
#include <QString>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <libimobiledevice/afc.h>

class AfcExplorerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AfcExplorerWidget(
        afc_client_t afcClient = nullptr,
        std::function<void()> onClientInvalidCb = nullptr,
        iDescriptorDevice *device = nullptr, QWidget *parent = nullptr);
signals:
    void fileSelected(const QString &filePath);

private slots:
    void goBack();
    void goForward();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onAddressBarReturnPressed();
    void onFileListContextMenu(const QPoint &pos);
    void onExportClicked();
    void onImportClicked();
    void onAddToFavoritesClicked();

private:
    QWidget *m_explorer;
    QWidget *m_navWidget;
    QPushButton *m_exportBtn;
    QPushButton *m_importBtn;
    QPushButton *m_addToFavoritesBtn;
    QListWidget *m_fileList;
    QStack<QString> m_history;
    QStack<QString> m_forwardHistory;
    int m_currentHistoryIndex;
    QLineEdit *m_addressBar;
    ClickableIconWidget *m_backButton;
    ClickableIconWidget *m_forwardButton;
    ClickableIconWidget *m_enterButton;
    iDescriptorDevice *m_device;

    // Current AFC mode
    afc_client_t m_currentAfcClient;

    void setupFileExplorer();
    void loadPath(const QString &path);
    void updateAddressBar(const QString &path);
    void updateNavigationButtons();
    void saveFavoritePlace(const QString &path, const QString &alias);

    void setupContextMenu();
    void exportSelectedFile(QListWidgetItem *item);
    void exportSelectedFile(QListWidgetItem *item, const QString &directory);
    int export_file_to_path(afc_client_t afc, const char *device_path,
                            const char *local_path);
    int import_file_to_device(afc_client_t afc, const char *device_path,
                              const char *local_path);
    void updateNavStyles();
};

#endif // AFCEXPLORER_H
