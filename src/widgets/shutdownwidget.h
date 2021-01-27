/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SHUTDOWNWIDGET
#define SHUTDOWNWIDGET

#include <QFrame>

#include <functional>

#include "src/global_util/util_updateui.h"
#include "rounditembutton.h"
#include "src/session-widgets/sessionbasemodel.h"
#include "src/session-widgets/framedatabind.h"
#include "src/global_util/dbus/dbuslogin1manager.h"
#include "switchos_interface.h"
#include "systemmonitor.h"

class ShutdownWidget: public QFrame
{
    Q_OBJECT
public:
    ShutdownWidget(QWidget* parent = nullptr);
    ~ShutdownWidget() override;
    void setModel(SessionBaseModel * const model);
    void onStatusChanged(SessionBaseModel::ModeStatus status);

public slots:
    void leftKeySwitch();
    void rightKeySwitch();
    void runSystemMonitor();
    void recoveryLayout();
    void onRequirePowerAction(SessionBaseModel::PowerAction powerAction);
    void setUserSwitchEnable(bool enable);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private:
    void initUI();
    void initConnect();
    void updateTr(RoundItemButton * widget, const QString &tr);
    void onOtherPageChanged(const QVariant &value);
    void hideToplevelWindow();
    void enterKeyPushed();
    void enableHibernateBtn(bool enable);
    void enableSleepBtn(bool enable);

private:
    int m_index;
    bool m_switchUserEnable= false;
    QList<RoundItemButton *> m_btnList;
    QList<std::pair<std::function<void (QString)>, QString>> m_trList;
    SessionBaseModel* m_model;
    FrameDataBind *m_frameDataBind;
    QFrame* m_shutdownFrame = nullptr;
    SystemMonitor* m_systemMonitor = nullptr;
    QFrame* m_actionFrame = nullptr;
    QStackedLayout* m_mainLayout;
    QHBoxLayout* m_shutdownLayout;
    QVBoxLayout* m_actionLayout;
    RoundItemButton* m_currentSelectedBtn = nullptr;
    RoundItemButton* m_requireShutdownButton;
    RoundItemButton* m_requireRestartButton;
    RoundItemButton* m_requireSuspendButton;
    RoundItemButton* m_requireHibernateButton;
    RoundItemButton* m_requireLockButton;
    RoundItemButton* m_requireLogoutButton;
    RoundItemButton* m_requireSwitchUserBtn;
    RoundItemButton* m_requireSwitchSystemBtn = nullptr;
    HuaWeiSwitchOSInterface* m_switchosInterface = nullptr;

};

#endif // SHUTDOWNWIDGET

