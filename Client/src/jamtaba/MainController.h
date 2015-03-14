#pragma once

#include <QApplication>
#include <QDebug>
#include <memory>
#include <QList>
#include "audio/core/plugins.h"

class MainFrame;

namespace Audio {
    class AudioDriver;
    class AudioDriverListener;
    class AbstractMp3Streamer;
    class Plugin;
    class AudioMixer;
}

namespace Login {
    class LoginService;
    class LoginServiceParser;
    class LoginServiceListener;
    class AbstractJamRoom;
}

namespace Vst {
    class VstHost;
}

class JamtabaFactory;

//+++++++++++++

namespace Controller {

class AudioListener;

struct Peaks{
    float left;
    float right;

    Peaks(float l, float r){
        left    = l;
        right   = r;
    }

    float max(){
        return std::max(std::abs(left), std::abs(right));
    }
};

//++++++++++++++++++++++++++++
class MainController : public QApplication
{
    Q_OBJECT

    friend class Controller::AudioListener;

public:
    MainController(JamtabaFactory *factory, int& argc, char** argv);
    ~MainController();

    void start();
    void stop();

    void process(Audio::SamplesBuffer& in, Audio::SamplesBuffer& out);

    void playRoomStream(Login::AbstractJamRoom *room);
    bool isPlayingRoomStream();
    Login::AbstractJamRoom* getCurrentStreamingRoom();
    void stopRoomStream();//stop currentRoom stream

    Audio::AudioDriver* getAudioDriver() const;
    Login::LoginService* getLoginService() const;



    Peaks getInputPeaks();
    Peaks getRoomStreamPeaks();

    std::vector<Audio::PluginDescriptor*> getPluginsDescriptors();

    Audio::Plugin* addPlugin(Audio::PluginDescriptor* descriptor);
    void removePlugin(Audio::Plugin* plugin);

    //tracks
    void setTrackMute(int trackID, bool muteStatus);
    bool trackIsMuted(int trackID) const;
    void setTrackSolo(int trackID, bool soloStatus);
    void setTrackLevel(int trackID, float level);
    void setTrackPan(int trackID, float pan);
private:
    Audio::Plugin* createPluginInstance(Audio::PluginDescriptor* descriptor);

    std::unique_ptr<Audio::AudioDriver> audioDriver;
    std::unique_ptr<Audio::AudioDriverListener> audioDriverListener;
    std::unique_ptr<Login::LoginService> loginService;

    std::unique_ptr<Audio::AudioMixer> audioMixer;

    std::unique_ptr<Audio::AbstractMp3Streamer> roomStreamer;
    Login::AbstractJamRoom* currentStreamRoom;

    std::map<int, Audio::AudioNode*> tracksNodes;

    Peaks inputPeaks;
    Peaks roomStreamerPeaks;
    //+++++++++++++++++++
    Vst::VstHost* vstHost;
    //+++++++++++++++++++++++++
    void configureStyleSheet();

private slots:
    void on_disconnectedFromServer();

};

}