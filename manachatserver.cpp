#include "manachatserver.h"
#include <QBuffer>
#include <QTcpSocket>

ManaChatServer::ManaChatServer(QObject* parent) : QTcpServer(parent)
{
	connect(this, SIGNAL(newConnection()), this, SLOT(addConnection()));
}

ManaChatServer::~ManaChatServer()
{
}

void ManaChatServer::addConnection()
{
    qDebug() <<"new connect";
	QTcpSocket* connection = nextPendingConnection();
	connections.append(connection);
	QBuffer* buffer = new QBuffer(this);
	buffer->open(QIODevice::ReadWrite);
	buffers.insert(connection, buffer);
	connect(connection, SIGNAL(disconnected()), SLOT(removeConnection()));
	connect(connection, SIGNAL(readyRead()),	SLOT(receiveMessage()));
}

void ManaChatServer::removeConnection()
{
    qDebug() <<"remove Connect";
	QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
	QBuffer* buffer = buffers.take(socket);
	buffer->close();
	buffer->deleteLater();
	connections.removeAll(socket);
	socket->deleteLater();
}

void ManaChatServer::receiveMessage()
{
    qDebug() <<"receive msg";
	QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
//	QBuffer* buffer = buffers.value(socket);
	
        qDebug()<< socket->readAll();
        /*
	qint64 bytes = buffer->write(socket->readAll());
	buffer->seek(buffer->pos() - bytes);
	while (buffer->canReadLine())
	{
		QByteArray line = buffer->readLine();
            	
		qDebug() << "msg:" <<line;

		foreach (QTcpSocket* connection, connections)
		{
			connection->write(line);

		}
	}*/
}

