#include "chatprotocol.h"

ChatProtocol::ChatProtocol(QObject *parent)
    : QObject{parent}
{}

QByteArray ChatProtocol::textMessage(QString message, QString receiver)
{
    QJsonObject jsonMessage;
    jsonMessage["type"] = "text";
    jsonMessage["receiver"] = receiver;
    jsonMessage["message"] = message;

    return QJsonDocument(jsonMessage).toJson();
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping, "");
}

QByteArray ChatProtocol::setNameMessage(QString name)
{
    QJsonObject jsonMessage;
    jsonMessage["type"] = "set_name";
    jsonMessage["name"] = name;

    return QJsonDocument(jsonMessage).toJson();
}

const QString &ChatProtocol::message() const
{
    return _message;
}

void ChatProtocol::loadData(QByteArray data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = doc.object();

    _type = static_cast<MessageType>(jsonObj["type"].toInt());

    switch (_type) {
    case Text:
        _receiver = jsonObj["receiver"].toString();
        _message = jsonObj["message"].toString();
        break;
    case SetName:
        _name = jsonObj["name"].toString();
        break;
    case NewClient:
        break;
    case ClientDisconnected:
        // No additional data to load
        break;
    case ConnectionACK:
        _myName = jsonObj["myName"].toString();
        _clientsName = jsonObj["clientsName"].toString().split(",");
        break;
    default:
        qWarning() << "Unknown message type: " << _type;
        break;
    }
}

QByteArray ChatProtocol::getData(MessageType type, QString data)
{
    QJsonObject jsonMessage;
    jsonMessage["type"] = type;
    jsonMessage["data"] = data;

    return QJsonDocument(jsonMessage).toJson();
}

