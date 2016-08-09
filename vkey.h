
#ifndef VKEY_H
#define VKEY_H

#include <QDialog>
#include <QLineEdit>
#include "button.h"
#include <QtGui>

class VKey : public QDialog
{
    Q_OBJECT

public:
    VKey(QWidget *parent = 0);
    ~VKey();

    void lettersFun(char capital);
    QGridLayout *mainLayout;

    bool capFlag;
signals:
    void setvalue(const QString &);

private slots:
    void digitClicked();
    void letClicked();
    void enterClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void closeClicked();
    void shiftClicked();
    void spaceClicked();
    void addClicked();
    void reduClicked();
    void equClicked();
    void whyClicked();

private:
    bool waitingForOperand;
    Button *createButton(const QString &text, const char *member);

    QLineEdit *display;

    enum { NumDigitButtons = 10 };
    enum { LettersButton =26 };

    Button *digitButtons[NumDigitButtons];
    Button *LetButton[LettersButton];
};
#endif
