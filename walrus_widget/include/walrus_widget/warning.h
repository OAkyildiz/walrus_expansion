#ifndef WARNING_H
#define WARNING_H

#include <QLabel>
#include <QPropertyAnimation>
#include <QPixmap>

class Warning : public QLabel
{
    Q_OBJECT

public:
    explicit Warning(QWidget* parent, QString name, QString image );

    virtual ~Warning() {}
    void startFade();
    void stopFade();

protected:
    const QString name_;
    QPixmap* icon_;
    QPropertyAnimation* fader_;
    bool switch_;

    void resizeEvent(QResizeEvent * event);

private:
    void setFader();

};

#endif // WARNING_H
