#Magnus e Doublebass agradeceram pelo esforço e disseram que ter um canal de backing track é muito importante.

# implementar MIDI
# listagem de VST está lenta no início, algum tipo de cache persistente
# mostrar plugins nativos
# trabalhar com VSTi - POrt midi
# duplo clique no controle de pan não reseta adequadamente
# quando clico para ouvir uma outra sala não está resetando o plot da sala que eu estava ouvindo
# Melhorar o visual do Delay, os LineEdit estão grandes demais
# Seria interessante possibilitar que os parâmetros do delay sejam alterados através dos lineEdit

#buga tudo se não tem conexão com a internet

# - Coisas legais para implementar: fazer um plugin de delay para iniciar a saga dos plugins nativos do Jamtaba
# - O stream do ninjamer.com não é mono como achei que era, mas está dando problema
# - Tenho que fazer resample do stream
# -
# - O DAW LMMS usa PortAudio, pode ser interessante roubar o código deles.



#BUGS relacionados com o diálogo de audioIO:
#1 - quando seleciono as entradas sPDIF da fast track a aplicação encerra
#2 - quando seleciono saídas que não são 1 e 2 dá um crash também.
#3 - Com a fast track quando seleciono as entradas e simplesmente volto para a tela de audio IO o valor do segundo combo está bugado.
#4 - preciso testar com a fonte da fast track para ver se os outros canais estão realmente funcionando



#-------------------------------------------------
#
# Project created by QtCreator 2015-01-13T11:05:00
#
#-------------------------------------------------

QT       +=  gui  network

QMAKE_CXXFLAGS += -std=c++11 #-Wno-unused-parameter

#MAC
macx:QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_MACOSX_DEPLOYMENT_TARGET=10.6

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Jamtaba2
TEMPLATE = app

MAIN = src/jamtaba/main.cpp
#MAIN = src/jamtaba/ninjam/main.cpp


HEADERS += \
    #nvwa/debug_new.h \
    #--------------------------------
    #minimp3/minimp3.h \
    #--------------------------------
    src/jamtaba/persistence/ConfigStore.h \
    #--------------------------------
    src/jamtaba/audio/core/AudioDriver.h \
    src/jamtaba/audio/core/AudioNode.h \
    src/jamtaba/audio/core/AudioMixer.h \
    src/jamtaba/audio/core/PortAudioDriver.h \
    #--------------------------------
    src/jamtaba/gui/widgets/PeakMeter.h \
    src/jamtaba/gui/widgets/WavePeakPanel.h \
    #--------------------------------
    src/jamtaba/loginserver/LoginService.h \
    src/jamtaba/loginserver/JamRoom.h \
    src/jamtaba/loginserver/JsonUtils.h \
    #--------------------------------
    src/jamtaba/MainController.h \
    src/jamtaba/JamtabaFactory.h \
    #--------------------------------
    src/jamtaba/ninjam/protocol/ServerMessageParser.h \
    src/jamtaba/ninjam/protocol/ServerMessages.h \
    src/jamtaba/ninjam/protocol/ClientMessages.h \
    src/jamtaba/ninjam/User.h \
    src/jamtaba/ninjam/Service.h \
    src/jamtaba/ninjam/Server.h \
    #--------------------------------
    src/jamtaba/loginserver/natmap.h \
    src/jamtaba/audio/RoomStreamerNode.h \
    src/jamtaba/audio/codec.h \
    src/jamtaba/gui/LocalTrackView.h \
    src/jamtaba/gui/AudioDialog.h \
    src/jamtaba/gui/JamRoomViewPanel.h \
    src/jamtaba/gui/MainFrame.h \
    src/jamtaba/gui/TrackView.h \
    src/jamtaba/gui/FxPanel.h \
    src/jamtaba/gui/FxPanelItem.h \
    src/jamtaba/audio/core/plugins.h \
    src/jamtaba/gui/plugins/guis.h \
    src/jamtaba/audio/vst/PluginFinder.h \
    src/jamtaba/audio/vst/VstPlugin.h \
    src/jamtaba/audio/vst/vsthost.h


win32:HEADERS += portaudio/include/pa_asio.h

SOURCES += \
    $$MAIN \
#    nvwa/debug_new.cpp \
#--------------------------------
    #minimp3/minimp3.c \
#-----------------------------------------
    src/jamtaba/persistence/ConfigStore.cpp \
#------------------------------------------------
    src/jamtaba/audio/core/AudioDriver.cpp \
    src/jamtaba/audio/core/AudioNode.cpp \
    src/jamtaba/audio/core/AudioMixer.cpp \
    src/jamtaba/audio/core/PortAudioDriver.cpp \
    src/jamtaba/audio/RoomStreamerNode.cpp \
#------------------------------------------------
    src/jamtaba/gui/widgets/PeakMeter.cpp \
    src/jamtaba/gui/widgets/WavePeakPanel.cpp \
#------------------------------------------------
    src/jamtaba/JamtabaFactory.cpp \
    src/jamtaba/MainController.cpp \
#------------------------------------------------
    src/jamtaba/loginserver/LoginService.cpp \
    src/jamtaba/loginserver/JsonUtils.cpp \
    src/jamtaba/loginserver/JamRoom.cpp \
#------------------------------------------------
    src/jamtaba/ninjam/protocol/ServerMessages.cpp \
    src/jamtaba/ninjam/protocol/ClientMessages.cpp \
    src/jamtaba/ninjam/protocol/ServerMessageParser.cpp \
    src/jamtaba/ninjam/Server.cpp \
    src/jamtaba/ninjam/Service.cpp \
    src/jamtaba/ninjam/User.cpp \
    src/jamtaba/gui/LocalTrackView.cpp \
    src/jamtaba/gui/FxPanel.cpp \
    src/jamtaba/gui/FxPanelItem.cpp \
    src/jamtaba/audio/core/plugins.cpp \
    src/jamtaba/audio/codec.cpp \
    src/jamtaba/gui/plugins/guis.cpp \
    src/jamtaba/gui/JamRoomViewPanel.cpp \
    src/jamtaba/gui/AudioIODialog.cpp \
    src/jamtaba/gui/MainFrame.cpp \
    src/jamtaba/gui/TrackView.cpp \
    src/jamtaba/audio/vst/PluginFinder.cpp \
    src/jamtaba/audio/vst/VstPlugin.cpp \
    src/jamtaba/audio/vst/vsthost.cpp

FORMS += src/jamtaba/gui/mainframe.ui \
    src/jamtaba/gui/audioiodialog.ui \
    src/jamtaba/gui/trackview.ui \
    src/jamtaba/gui/jamroomviewpanel.ui \


#macx: LIBPATH += /Users/Eliesr/Qt5.4.0/5.4/clang_64/lib \
win32:LIBPATH += C:/Qt/Qt5.4.0/Tools/mingw491_32/i686-w64-mingw32/lib/ \


LIBS += -L$$PWD/minimp3/lib/ -lminimp3 \
        -L$$PWD/portaudio/lib/ -lportaudio \

win32:LIBS += -lwinmm \
              -lole32 \


win32:PRE_TARGETDEPS += $$PWD/portaudio/lib/libportaudio.a

VST_SDK_PATH = "D:/Documents/Estudos/ComputacaoMusical/Jamtaba2/VST3 SDK/pluginterfaces/vst2.x/"

INCLUDEPATH += $$PWD/portaudio/include \
               $$PWD/minimp3/include \
               src/jamtaba/gui \
               src/jamtaba/gui/widgets \
               $$VST_SDK_PATH

DEPENDPATH += $$PWD/portaudio/include \
              $$PWD/minimp3/include

RESOURCES += src/jamtaba/resources/jamtaba.qrc