#include "twitter.h"
#include <fstream>
#include <QDebug>
#include <QString>
#include <QUrlQuery>
#include <ctime>
#include <iostream>
#include <QByteArray>
#include <QJsonDocument>
#include <QVariant>
#include <QMap>
#include "database.h"
Twitter* Twitter::instance = 0;

Twitter::Twitter()
{
    key = "GgqXEJQD6rglvtLRnSGGPgB75"; // Key from Twitter
    secret = "hffrwdXOxsdOZ14JDPONP3VbhPGcYAuLkCAfSC6k1JJPMmjEpi"; // Secret from Twitter
    request_token_url = "https://api.twitter.com/oauth/request_token";
    request_token_query_args = "oauth_callback=oob";
    authorize_url = "https://api.twitter.com/oauth/authorize";
    access_token_url = "https://api.twitter.com/oauth/access_token";
    oauthSignature = "";
    oauthConsumer = new OAuth::Consumer(key,secret);
    oauthClient = new OAuth::Client(oauthConsumer);
    userTimeLineMap = new QMap<QString, QVariant>;
    userTimeLine = new QString;    
    twitterUserData.accessTokenKey = "";
    twitterUserData.accessTokenSecret = "";
    request_token = new OAuth::Token;
    QFile database("data.db3");
    if (database.exists())
    {
        twitterDB = QSqlDatabase::addDatabase("QSQLITE");
        twitterDB.setDatabaseName("data.db3");
        databaseStatus = true;
    }
    else
    {
        twitterDB = QSqlDatabase::addDatabase("QSQLITE");
        twitterDB.setDatabaseName("data.db3");
        databaseStatus = false;
    }

    networkStatus = false;
}

QUrl Twitter::getRequestToken()
{
    std::string base_request_token_url = request_token_url + (request_token_query_args.empty() ? std::string("") : (std::string("?")+request_token_query_args) );
    std::string oAuthQueryString = oauthClient->getURLQueryString( OAuth::Http::Get, base_request_token_url);
    std::string url = request_token_url + "?" + oAuthQueryString;
    QString temp =  QString::fromStdString(url).replace("#", "?");
    oauthSignature = QUrlQuery(temp).queryItemValue("oauth_signature").toStdString();    
    return QString::fromStdString(url);
}

void Twitter::setOauthToken(std::string response)
{
    *request_token = OAuth::Token::extract(response);
}

QUrl Twitter::getPIN()
{
    QUrl result;
    result = QString::fromStdString( authorize_url+"?oauth_token="+request_token->key());
    return result;
}

QUrl Twitter::accessToken()
{
    QUrl result;
    *oauthClient = OAuth::Client(oauthConsumer, request_token);
    result = QString::fromStdString(access_token_url + "?"+oauthClient->getURLQueryString( OAuth::Http::Get, access_token_url, std::string( "" ), true ));
    return result;
}

void Twitter::setPin(std::string PIN)
{
 request_token->setPin(PIN);

}

QUrl Twitter::generateQueryString(std::string url, std::string parameters)
{
    OAuth::Consumer consumer(key, secret);
    OAuth::Token token(twitterUserData.accessTokenKey.toStdString(), twitterUserData.accessTokenSecret.toStdString());
    OAuth::Client oauthClient(&consumer, &token);
    std::string oAuthQueryString = oauthClient.getURLQueryString(OAuth::Http::Get, url + "?" + parameters);
    return QUrl(QString::fromStdString(url+"?"+oAuthQueryString));
}

void Twitter::setUserData(userData data)
{
    twitterUserData = data;
}

void Twitter::setUserSettings(userSettings settings)
{
    twitterUserSettings = settings;
}

Twitter::userData *Twitter::getUserData()
{
    return &twitterUserData;
}

Twitter::userSettings *Twitter::getUserSettings()
{
    return &twitterUserSettings;
}

void Twitter::setLastSyncTime(QTime time)
{
    LastSync = time;
}

QStringList Twitter::getSyncedUsers()
{
    return syncedUsers;
}

QStringList Twitter::getSyncedTimelines()
{
    return syncedTimelines;
}

QTime Twitter::getLastSyncTime()
{
    return LastSync;
}

QSqlDatabase Twitter::getDatabase()
{
    return twitterDB;
}

void Twitter::setNetworkStatus(bool status)
{
    networkStatus = status;
}

bool Twitter::getNetworkStatus()
{
    return networkStatus;
}

bool Twitter::getDatabaseStatus()
{
    return databaseStatus;
}

void Twitter::setDatabaseStatus(bool status)
{
    databaseStatus = status;
}

void Twitter::setSyncedUsers(QStringList syncUsers)
{

    syncedUsers = syncUsers;
}

void Twitter::setSyncedTimelines(QStringList syncTimelines)
{
    syncedTimelines = syncTimelines;
}

void Twitter::fin()
{

}

QByteArray Twitter::nonce()
{
        static bool firstTime = true;
        if (firstTime) {
            firstTime = false;
            qsrand(QTime::currentTime().msec());
        }
        QString u = QString::number(QDateTime::currentDateTimeUtc().toTime_t());
        u.append(QString::number(qrand()));
        return u.toLatin1();
}



