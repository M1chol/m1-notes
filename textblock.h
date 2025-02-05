#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include <QWidget>
#include <QTextDocument>
#include <QVector>
#include "CustomText.h"
#include <QBoxLayout>

class TextBlock : public QWidget
{
    Q_OBJECT
public:
    explicit TextBlock(const QPoint &pos, QWidget *parent = nullptr);
    ~TextBlock();

private slots:
    void onCustomTextEnterPressed(CustomText *sender);
    void onCustomTextBackPressed(CustomText *sender);

private:
    QTextDocument* document;
    QVector<CustomText*> customTexts;

    // Helper to create a new CustomText widget at a calculated position.
    CustomText* createCustomText(bool firstOne = false);
    QPoint position;
};

#endif // TEXTBLOCK_H
