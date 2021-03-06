#ifndef USERDETAILS_H
#define USERDETAILS_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QJsonDocument>
#include <QVariant>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QPixmap>
#include "requests.h"
#include "parser.h"
#include "database.h"
#include "twitter.h"
namespace Ui {
class UserDetails;
}

class UserDetails : public QWidget
{
    Q_OBJECT

public:
    explicit UserDetails(QWidget *parent = 0);
    ~UserDetails();
    void prepareData(QString userid);

private:
    Ui::UserDetails *ui;
    Twitter *twitter;
    QString id;
    QPixmap photo;
    DataBase *db;
    Twitter::userData userData;
    Requests *twitterRequests;
    Parser *parser;
    QByteArray requestData;
    QString userTimeline;
    bool userInDatabase;
    int page;
    int currentPage;
    QTimer *syncTimer;
    QTime lastSynchronization;
    QString lastTweet;
private:
    void getUserinfoFromTwitter(std::string id);
    void getUserinfoFromDatabase(QString id);
    QString getTimeline(int left, int right, QString userLastTweet);
    void timeLineToDatabase();
    void showResults();
    bool databaseUser;
    void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;

signals:
    formClosed();
    finishedRequest();
private slots:
    void toDatabase();
    void appendTimeline();
    void updateData();
};

#endif // USERDETAILS_H
