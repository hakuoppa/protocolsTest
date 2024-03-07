#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>

class ChatProtocol : public QObject
{
    Q_OBJECT
public:
    explicit ChatProtocol(QObject *parent = nullptr);

    enum MessageType {
        Text,
        IsTyping,
        SetName,
        NewClient,
        ClientDisconnected,
        ConnectionACK
    };

    QByteArray textMessage(QString message, QString receiver);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString name);

    void loadData(QByteArray data);

    const QString &myName() const;
    const QString &name() const;
    const QString &message() const;

    const QStringList &clientsName() const;
    const QString &clientName() const;
    QString receiver() const;

private:
    MessageType _type;
    QString _receiver;
    QString _message;
    QString _myName;
    QStringList _clientsName;
    QString _name;


    QByteArray getData(MessageType type, QString data);

};
#endif // CHATPROTOCOL_H
