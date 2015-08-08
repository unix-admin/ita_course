#ifndef PARSER_H
#define PARSER_H
#include <QMovie>
#include <QMap>
#include <QJsonDocument>
#include <QByteArray>
#include <QString>
#include <QVariant>
//#include <QList>
#include <QStringList>
#include <QObject>
#include "requests.h"
class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    QStringList parseSearchRequest(QByteArray *data);
    QString parseTweets(QByteArray *data);
    void parseSearchMetadata(QByteArray *data, QStringList *listData);
    QString maxTweetID;
    QString minTweetID;
    QStringList parseUserInfo(QByteArray *data);
signals:
    parseFinished();
public slots:
    void quit();
private :
    QString dateFormat(QVariant value);
};

#endif // PARSER_H
