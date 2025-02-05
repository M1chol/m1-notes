// customtext.cpp
#include "customtext.h"
#include <QStyle>
#include <QEvent>
#include <QMouseEvent>

CustomText::CustomText(bool canBeEmpty, QWidget *parent)
    : QTextEdit(parent),
    padding(25),
    canBeEmpty(canBeEmpty)//,
    //renderDoc(new QTextDocument(this))
{
    setFixedSize(100, 30); // Set initial size

    // Styling the text edit widget.
    setStyleSheet(
        "background-color: transparent;" // Transparent background
        "color: white;"                  // Set text color
        "border: 1px solid darkgrey;"
        "border-radius: 2px;"
        );
    show();
    setFocus();

    // Connect text changes to resizing.
    connect(this, &CustomText::textChanged, this, &CustomText::resizeText);
}


void CustomText::focusOutEvent(QFocusEvent *event)
{
    // Before calling base class focusOut,
    // try to commit the text to our document.
    if (onFocusLost()) {
        // Set the rendered text into our document.
        // This document can then be used elsewhere for rendering.
        // renderDoc->setPlainText(this->toPlainText());

        // Optionally, hide the editing widget once committed.
        setStyleSheet(
            "background-color: transparent;"
            "color: white;"
            "border: transparent;"
            "border-radius: 2px;"
            );

        QTextEdit::focusOutEvent(event);
    }
}

void CustomText::focusInEvent(QFocusEvent *event){
    setStyleSheet(
        "background-color: transparent;"
        "color: white;"
        "border: 1px solid darkgrey;"
        "border-radius: 2px;"
        );
    QTextEdit::focusInEvent(event);
}

bool CustomText::onFocusLost()
{
    if (toPlainText().isEmpty() && !canBeEmpty) {
        // Depending on the design, you might want
        // to simply clear or hide the widget. Here we delete.
        delete this;
        return false;
    }
    return true;
}

void CustomText::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return ||
        event->key() == Qt::Key_Enter) {
        // Emit a signal to notify that Enter was pressed.
        emit enterPressed(this);
        // Do not let the Enter add a new line.
        event->accept();
        return;
    }
    if (event->key() == Qt::Key_Backspace) {
        // Emit a signal to notify that Backspace was pressed.
        emit backPressed(this);
        event->accept();
    }
    QTextEdit::keyPressEvent(event);
}

void CustomText::resizeText()
{
    QString text = toPlainText();
    if (text.isNull() || text.isEmpty()) {
        setFixedWidth(100);
        setFixedHeight(30);
        return;
    }
    const QFontMetrics &font = fontMetrics();
    QSize textSize = font.size(Qt::TextShowMnemonic, text);
    int width = textSize.width() + padding;
    int height = textSize.height() + padding / 2;
    if (width < 100) {
        width = 100;
    }
    if (height < 30) {
        height = 30;
    }
    setFixedHeight(height);
    setFixedWidth(width);
}

CustomText::~CustomText()
{
    // The renderDoc is a child of this widget so it will be deleted automatically.
}
