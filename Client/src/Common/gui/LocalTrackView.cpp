#include "LocalTrackView.h"
#include "ui_BaseTrackView.h"
#include "MainController.h"

LocalTrackView::LocalTrackView(Controller::MainController *mainController, int channelIndex) :
    BaseTrackView(mainController, channelIndex),
    inputNode(nullptr)
{
    if (!mainController) {
        qCritical() << "LocalTrackView::init() mainController is null!";
        return;
    }

    // insert a input node in controller
    inputNode = new Audio::LocalInputAudioNode(channelIndex);
    trackID = mainController->addInputTrackNode(this->inputNode);
    bindThisViewWithTrackNodeSignals();// now is secure bind this LocalTrackView with the respective TrackNode model

    setInitialValues(1.0f, BaseTrackView::Boost::ZERO, 0.0f, false);

    setUnlightStatus(false);

    peakMetersOnly = false;
}

void LocalTrackView::setInitialValues(float initialGain, BaseTrackView::Boost boostValue,
                                      float initialPan, bool muted)
{
    inputNode->setGain(initialGain);
    inputNode->setPan(initialPan);
    initializeBoostButtons(boostValue);
    if (muted)
        inputNode->setMute(muted);
}

void LocalTrackView::detachMainController()
{
    this->mainController = nullptr;
}

void LocalTrackView::closeAllPlugins()
{
    inputNode->closeProcessorsWindows();// close vst editors
}

void LocalTrackView::mute(bool b)
{
    getInputNode()->setMute(b);// audio only
    ui->muteButton->setChecked(b);// gui only
}

void LocalTrackView::solo(bool b)
{
    getInputNode()->setSolo(b);// audio only
    ui->soloButton->setChecked(b);// gui only
}

void LocalTrackView::initializeBoostButtons(Boost boostValue)
{
    switch (boostValue) {
    case Boost::MINUS:
        ui->buttonBoostMinus12->click();
        break;
    case Boost::PLUS:
        ui->buttonBoostPlus12->click();
        break;
    default:
        ui->buttonBoostZero->click();
    }
}

QSize LocalTrackView::sizeHint() const
{
    if (peakMetersOnly) {
        int width = ui->mainWidget->sizeHint().width() + layout()->contentsMargins().left()
                    + layout()->contentsMargins().right();
        return QSize(width, height());
    }
    return BaseTrackView::sizeHint();
}

void LocalTrackView::setPeakMetersOnlyMode(bool peakMetersOnly, bool runningInMiniMode)
{
    if (this->peakMetersOnly != peakMetersOnly) {
        this->peakMetersOnly = peakMetersOnly;
        ui->boostPanel->setVisible(!this->peakMetersOnly);
        ui->levelSlider->setVisible(!this->peakMetersOnly);
        ui->panPanel->setVisible(!this->peakMetersOnly);

        QSizePolicy::Policy hPolicy = QSizePolicy::Minimum;
        QSizePolicy::Policy vPolicy = this->peakMetersOnly ? QSizePolicy::Ignored : QSizePolicy::Fixed;
        ui->panSpacer->changeSize(20, 20, hPolicy, vPolicy);

        QMargins margins = layout()->contentsMargins();
        margins.setLeft((peakMetersOnly || runningInMiniMode) ? 2 : 6);
        margins.setRight((peakMetersOnly || runningInMiniMode) ? 2 : 6);
        layout()->setContentsMargins(margins);

        ui->soloButton->setVisible(!peakMetersOnly);
        ui->muteButton->setVisible(!peakMetersOnly);
        ui->peaksDbLabel->setVisible(!peakMetersOnly);
        Qt::Alignment alignment = peakMetersOnly ? Qt::AlignRight : Qt::AlignHCenter;
        ui->levelSlider->parentWidget()->layout()->setAlignment(ui->levelSlider, alignment);

        this->drawDbValue = !peakMetersOnly;

        updateGeometry();

        setProperty("faderOnly", QVariant(peakMetersOnly));
        style()->unpolish(this);
        style()->polish(this);
    }
}

void LocalTrackView::togglePeakMetersOnlyMode(bool runninsInMiniMode)
{
    setPeakMetersOnlyMode(!peakMetersOnly, runninsInMiniMode);
}

void LocalTrackView::setUnlightStatus(bool unlighted)
{
    BaseTrackView::setUnlightStatus(unlighted);
    update();
}

Audio::LocalInputAudioNode *LocalTrackView::getInputNode() const
{
    return inputNode;
}

void LocalTrackView::reset()
{
    mainController->resetTrack(getTrackID());
}

LocalTrackView::~LocalTrackView()
{
    if (mainController)
        mainController->removeInputTrackNode(getTrackID());
}
