#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_MainWindow.h"
#include "BusyDialog.h"
#include "chords/ChordsPanel.h"
#include "NinjamRoomWindow.h"
#include "MainController.h"
#include "JamRoomViewPanel.h"
#include "LocalTrackGroupView.h"
// #include "performance/PerformanceMonitor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller::MainController *mainController, QWidget *parent = 0);
    virtual ~MainWindow();

    virtual void initialize(); // this is overrided in inherited classes

    void closeEvent(QCloseEvent *) override;
    void changeEvent(QEvent *) override;
    void timerEvent(QTimerEvent *) override;
    void resizeEvent(QResizeEvent *) override;

    void detachMainController();

    virtual Persistence::LocalInputTrackSettings getInputsSettings() const;

    inline int getChannelGroupsCount() const
    {
        return localGroupChannels.size();
    }

    inline QString getChannelGroupName(int index) const
    {
        return localGroupChannels.at(index)->getGroupName();
    }

    void highlightChannelGroup(int index) const;

    virtual void addChannelsGroup(const QString &name);
    void removeChannelsGroup(int channelGroupIndex);

    void exitFromRoom(bool normalDisconnection, QString disconnectionMessage = "");

    inline bool isRunningInMiniMode() const
    {
        return !fullViewMode;
    }

    inline bool isRunningInFullViewMode() const
    {
        return fullViewMode;
    }

    virtual inline Controller::MainController *getMainController()
    {
        return mainController;
    }

    virtual void loadPresetToTrack(const Persistence::Preset &preset);
    void resetLocalChannels();

    bool isTransmiting(int channelID) const;
    void setTransmitingStatus(int channelID, bool xmitStatus);

    QStringList getChannelsNames() const;

public slots:
    void enterInRoom(const Login::RoomInfo &roomInfo);

protected:
    Controller::MainController *mainController;
    Ui::MainFrameClass ui;
    QList<LocalTrackGroupView *> localGroupChannels;

    void centerDialog(QWidget *dialog);

    virtual NinjamRoomWindow *createNinjamWindow(const Login::RoomInfo &, Controller::MainController *) = 0;

    virtual void setFullViewStatus(bool fullViewActivated);

    bool eventFilter(QObject *target, QEvent *event);

    LocalTrackGroupView *addLocalChannel(int channelGroupIndex, const QString &channelName,
                                         bool createFirstSubchannel);

    // this factory method is overrided in derived classes to create more specific views
    virtual LocalTrackGroupView *createLocalTrackGroupView(int channelGroupIndex);

    virtual void showPreferencesDialog(int initialTab) = 0;

    virtual void initializeLocalSubChannel(LocalTrackView *localTrackView, const Persistence::Subchannel &subChannel);

    void stopCurrentRoomStream();

    virtual void removeAllInputLocalTracks();

    template<class T>
    QList<T> getLocalChannels() const
    {
        QList<T> localChannels;
        foreach (LocalTrackGroupView * trackGroupView, localGroupChannels) {
            localChannels.append( dynamic_cast<T>(trackGroupView));
        }
        return localChannels;
    }

    void updatePublicRoomsListLayout();

    bool canUseTwoColumnLayout() const;

protected slots:
    void closeTab(int index);
    void changeTab(int index);

    // main menu
    void openPreferencesDialog(QAction *action);

    void showNinjamCommunityWebPage();
    void showNinjamOfficialWebPage();

    void showPrivateServerDialog();

    // view mode menu
    void changeViewMode(QAction *action);

    // ninjam controller
    void startTransmission();
    void prepareTransmission();

    // help menu
    void showJamtabaIssuesWebPage();
    void showJamtabaWikiWebPage();
    void showJamtabaUsersManual();

    // private server
    void connectInPrivateServer(const QString &server, int serverPort, const QString &password);

    // login service
    void showNewVersionAvailableMessage();
    void handleIncompatiblity();
    virtual void handleServerConnectionError(const QString &errorMsg);

    // +++++  ROOM FEATURES ++++++++
    void playPublicRoomStream(const Login::RoomInfo &roomInfo);
    void stopPublicRoomStream(const Login::RoomInfo &roomInfo);

    // collapse local controls
    void toggleLocalInputsCollapseStatus();

    // channel name changed
    void updateChannelsNames();

    // room streamer
    void handlePublicRoomStreamError(const QString &msg);

    // master fader
    void setMasterFaderPosition(int);

    // chords progression
    void showChordProgression(const ChordProgression &chordProgression);
    void sendCurrentChordProgressionToChat();

    void updateBpi(int bpi);
    void updateBpm(int bpm);
    void updateCurrentIntervalBeat(int beat);

    void tryEnterInRoom(const Login::RoomInfo &roomInfo, const QString &password = "");

private slots:

    void showJamtabaCurrentVersion();

    void updateLocalInputChannelsGeometry();

    void refreshPublicRoomsList(const QList<Login::RoomInfo> &publicRooms);

    void hideChordsPanel();
private:

    BusyDialog busyDialog;

    void showBusyDialog(const QString &message);
    void showBusyDialog();
    void hideBusyDialog();
    void centerBusyDialog();

    void showMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon);

    int timerID;

    QPointF computeLocation() const;

    QMap<long long, JamRoomViewPanel *> roomViewPanels;

    QScopedPointer<NinjamRoomWindow> ninjamWindow;

    QScopedPointer<Login::RoomInfo> roomToJump;// store the next room reference when jumping from on room to another
    QString passwordToJump;

    static bool jamRoomLessThan(const Login::RoomInfo &r1, const Login::RoomInfo &r2);

    void initializeLoginService();
    void initializeLocalInputChannels(const Persistence::LocalInputTrackSettings &localInputSettings);

    void initializeMainTabWidget();
    void initializeViewModeMenu();

    bool fullViewMode;// full view or mini view mode? This is not the FullScreen mode, full screen is available only in Standalone.

    void showPeakMetersOnlyInLocalControls(bool showPeakMetersOnly);

    void setInputTracksPreparingStatus(bool preparing);

    ChordsPanel *chordsPanel;

    ChordsPanel *createChordsPanel();

    JamRoomViewPanel* createJamRoomViewPanel(const Login::RoomInfo &roomInfo);

    void setupSignals();
    void setupWidgets();

    void restoreWindowPosition();

    // PerformanceMonitor performanceMonitor;//cpu and memmory usage
    // qint64 lastPerformanceMonitorUpdate;
    // static const int PERFORMANCE_MONITOR_REFRESH_TIME;

    static const QSize MINI_MODE_MIN_SIZE;
    static const QSize FULL_VIEW_MODE_MIN_SIZE;
};

#endif
