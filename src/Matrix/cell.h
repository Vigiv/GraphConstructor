#pragma once
#include <QSpinBox>


class Cell : public QObject
{
    Q_OBJECT
public:
    enum class State
    {
        EMPTY, VERTEX, OCCUPY
    };

    explicit Cell(QObject *objParent = nullptr, QWidget *widgetParent = nullptr);

    void setState(State state);
    void setValue(int value);
    void setColor(const QColor &color);

    QSpinBox *getWidget() const;

signals:
    void cellChanged(QSpinBox *spinBox);

public slots:
    void changed(int);

private:
    QSpinBox *spinBox;
    State state{ State::EMPTY };
};
