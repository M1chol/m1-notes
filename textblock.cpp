#include "TextBlock.h"
#include <QVBoxLayout>
#include <QDebug>

TextBlock::TextBlock(const QPoint &pos, QWidget *parent)
    : QWidget(parent), document(nullptr), position(pos)
{
    move(pos);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    layout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(layout);

    CustomText *ct = createCustomText(1);
    layout->addWidget(ct);

    adjustSize();
    show();
}

TextBlock::~TextBlock() {}

CustomText* TextBlock::createCustomText(bool firstOne)
{

    CustomText *ct = new CustomText(!firstOne, this);

    // Set a size policy so the widget only takes the space it needs.
    ct->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    // Allow the widget to accept focus when clicked.
    ct->setFocusPolicy(Qt::ClickFocus);
    ct->setReadOnly(false);

    // Connect the enterPressed signal so this widget notifies TextBlock.
    connect(ct, &CustomText::enterPressed, this, &TextBlock::onCustomTextEnterPressed);

    connect(ct, &CustomText::backPressed, this, &TextBlock::onCustomTextBackPressed);

    customTexts.append(ct);
    qDebug() << "CustomText created; total count:" << customTexts.size();

    return ct;
}

void TextBlock::onCustomTextEnterPressed(CustomText *sender)
{
    // Get the full text entered by the user.
    QString senderText = sender->toPlainText();
    if (senderText.isEmpty())
        return;

    QStringList lines = senderText.split("\n", Qt::SkipEmptyParts);

    bool titleFound = false;


    QString lastLine = lines[lines.count()-1];
    if (lastLine.trimmed().startsWith("# ")) {
        CustomText *block = createCustomText();
        layout()->addWidget(block);
        if(lines.count() > 1)
        {
            block->setPlainText(lastLine);
            lines.pop_back();
            CustomText *block2 = createCustomText();
            layout()->addWidget(block2);
        }
        QString newText = lines.join("\n");
        sender->setPlainText(newText);

    }else
    {
        sender->append("");
    }
}

void TextBlock::onCustomTextBackPressed(CustomText *sender){
    if (sender->toPlainText().isEmpty()) {
        layout()->removeWidget(sender);
        customTexts.removeOne(sender);
        sender->deleteLater();
        adjustSize();
        CustomText *lastBox = customTexts[customTexts.count()-1];
        lastBox->setFocus();
        lastBox->moveCursor(QTextCursor::End);
        qDebug() << "CustomText widget deleted due to Backspace.";
    }
}
