#ifndef S21WINDOW_H
#define S21WINDOW_H

#include <QMainWindow>

class S21Window : public QMainWindow
{
    Q_OBJECT

public:
    S21Window(QWidget *parent = nullptr);
    ~S21Window();
};
#endif // S21WINDOW_H
