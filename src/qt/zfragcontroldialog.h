// Copyright (c) 2017-2020 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZFRAGCONTROLDIALOG_H
#define ZFRAGCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zfrag/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZCrctControlDialog;
}

class CZCrctControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZCrctControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZCrctControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZCrctControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZCrctControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCrctControlDialog(QWidget *parent);
    ~ZCrctControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZCrctControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZCrctControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZFRAGCONTROLDIALOG_H
