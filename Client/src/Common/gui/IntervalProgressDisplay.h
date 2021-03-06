#ifndef CIRCULAR_PROGRESS_DISPLAY
#define CIRCULAR_PROGRESS_DISPLAY

#include <QWidget>

class QResizeEvent;
class QPaintEvent;
class QPainter;
class QComboBox;

class IntervalProgressDisplay : public QWidget
{
    Q_OBJECT
public:
    enum PaintMode {
        CIRCULAR, ELLIPTICAL, LINEAR
    };
    explicit IntervalProgressDisplay(QWidget *parent);
    ~IntervalProgressDisplay();
    inline bool isShowingAccents() const
    {
        return showAccents;
    }

    void setShowAccents(bool showAccents);
    void setCurrentBeat(int interval);
    void setBeatsPerAccent(int beats);
    inline int getBeatsPerInterval() const
    {
        return beats;
    }

    inline int getBeatsPerAccent() const
    {
        return beatsPerAccent;
    }

    void setBeatsPerInterval(int beats);
    void setSliceNumberColor(const QColor &sliceNumberColor);
    inline QColor getSliceNumberColor() const
    {
        return sliceNumberColor;
    }

    void setPaintMode(PaintMode mode);

    QSize minimumSizeHint() const;

    void setPaintUsingLowContrastColors(bool state);

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;

private:

    static QColor PLAYED_BEATS_FIRST_COLOR;
    static QColor PLAYED_BEATS_SECOND_COLOR;
    static QColor PATH_COLOR;

    // linear painting
    static const int LINEAR_PAINT_MODE_OVAL_SIZE;
    static const QColor LINEAR_SLICE_NUMBER_COLOR;
    static const QColor LINEAR_BG_COLOR;
    static const QColor LINEAR_BG_SECOND_COLOR;
    static const QColor LINEAR_BORDER_COLOR;
    static const QColor LINEAR_TEXT_COLOR;
    static const QColor LINEAR_ACCENT_BORDER_COLOR;

    PaintMode paintMode;

    QColor highlightColor;

    // ellipse and circle painting
    void paintElliptical(QPainter &p, const QColor &textColor, int hRadius, int vRadius);
    void paintEllipticalPath(QPainter &p, int hRadius, int vRadius);
    void paintCircular(QPainter &p, const QColor &textColor);
    void drawBeatCircles(QPainter &p, int hRadius, int vRadius, int beatCircles, int startIterval);

    // linear painting
    void drawPoint(int x, int y, int size, QPainter *g, int value, const QBrush &bgPaint, const QColor &border,
                   bool small, bool drawText = false);
    void drawHorizontalPoints(QPainter *painter, int yPos, int startPoint, int totalPoinstToDraw);
    float getHorizontalSpace(int totalPoinstToDraw, int initialXPos) const;

    const QFont SMALL_FONT;
    const QFont BIG_FONT;

    void initialize();

    static const int MARGIN;
    static const int PREFERRED_OVAL_SIZE;
    int ovalSize;

    int currentBeat;
    int beats;

    int horizontalRadius;
    int verticalRadius;
    int centerX;
    int centerY;

    QColor sliceNumberColor;

    int beatsPerAccent;

    bool showAccents;

    bool usingLowContrastColors;//used to paint with low contrast when using chord progressions

    static const double PI;
};

#endif
