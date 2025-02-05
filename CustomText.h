#ifndef CUSTOMTEXT_H
#define CUSTOMTEXT_H

#include <QTextEdit>
#include <QPoint>
#include <QPainter>

class CustomText : public QTextEdit
{
    Q_OBJECT

public:
    explicit CustomText(bool canBeEmpty = false, QWidget *parent = nullptr);
    ~CustomText();
    // QTextDocument* renderedDocument() const { return renderDoc; }

signals:
    void enterPressed(CustomText *sender);
    void backPressed(CustomText *sender);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    int padding;

public slots:
    bool onFocusLost();
    void resizeText();

private:
    QPoint position;
    bool canBeEmpty;
    // void setTitle(const QString text);
};

#endif // CUSTOMTEXT_H
