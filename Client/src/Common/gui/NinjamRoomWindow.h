#ifndef NINJAMROOMWINDOW_H
#define NINJAMROOMWINDOW_H

#include <QWidget>
#include "ninjam/UserChannel.h"
#include "ninjam/User.h"
#include "ninjam/Server.h"
#include "loginserver/LoginService.h"
#include "ChatPanel.h"
#include <QMessageBox>
#include "NinjamPanel.h"

class MainWindow;
class NinjamTrackGroupView;
class NinjamTrackView;

namespace Ui {
class NinjamRoomWindow;
}

namespace Controller {
class NinjamController;
class MainController;
}

class NinjamRoomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NinjamRoomWindow(MainWindow *parent, const Login::RoomInfo &roomInfo,
                              Controller::MainController *mainController);
    ~NinjamRoomWindow();
    void updatePeaks();
    void updateGeoLocations();

    // these two components are exposed to be showed in main window
    inline ChatPanel *getChatPanel() const
    {
        return chatPanel;
    }

    inline NinjamPanel *getNinjamPanel() const
    {
        return ninjamPanel;
    }

    void setFullViewStatus(bool fullView);

protected:
    Ui::NinjamRoomWindow *ui;
    Controller::MainController *mainController;
    NinjamPanel *ninjamPanel;// panel to show interval progress, ninjam BPM/BPI controls, metronome controls, etc
private:

    QMap<QString, NinjamTrackGroupView *> trackGroups;
    ChatPanel *chatPanel;

    void adjustTracksWidth();

    bool fullViewMode;

    void handleVoteMessage(const Ninjam::User &user, const QString &message);
    void handleChordProgressionMessage(const Ninjam::User &user, const QString &message);

    NinjamPanel *createNinjamPanel();

    void setupSignals(Controller::NinjamController *ninjamController);
    void disconnectFromNinjamControllerSignals(Controller::NinjamController *ninjamController);

    NinjamTrackView *getTrackViewByID(long trackID);

private slots:

    // ninjam panel controls
    void setNewBpi(const QString &);
    void setNewBpm(const QString &);
    void setNewBeatsPerAccent(int);

    // metronome events
    void setMetronomePanSliderPosition(int value);
    void setMetronomeFaderPosition(int value);
    void toggleMetronomeMuteStatus();
    void toggleMetronomeSoloStatus();

    // ninjam controller events
    void addChannel(const Ninjam::User &user, const Ninjam::UserChannel &channel, long channelID);
    void removeChannel(const Ninjam::User &user, const Ninjam::UserChannel &channel, long channelID);
    void changeChannelName(const Ninjam::User &user, const Ninjam::UserChannel &channel, long channelID);
    void setChannelXmitStatus(long channelID, bool transmiting);
    void updateIntervalDownloadingProgressBar(long trackID);
    void hideIntervalDownloadingProgressBar(long trackID);
    void addChatMessage(const Ninjam::User &, const QString &message);
    void handleUserLeaving(const QString &userName);
    void handleUserEntering(const QString &userName);

    void sendNewChatMessage(const QString &msg);

    void showServerLicence();

    // chat panel
    void voteToChangeBpi(int newBpi);
    void voteToChangeBpm(int newBpm);
};

#endif // NINJAMROOMWINDOW_H
