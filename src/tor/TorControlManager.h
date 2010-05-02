/* TorIM - http://gitorious.org/torim
 * Copyright (C) 2010, John Brooks <special@dereferenced.net>
 *
 * TorIM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TorIM. If not, see http://www.gnu.org/licenses/
 */

#ifndef TORCONTROLMANAGER_H
#define TORCONTROLMANAGER_H

#include <QObject>
#include <QHostAddress>

class QNetworkProxy;

namespace Tor
{

class HiddenService;

class TorControlManager : public QObject
{
	Q_OBJECT
	friend class ProtocolInfoCommand;

public:
	enum AuthMethod
	{
		AuthUnknown = 0,
		AuthNull = 0x1,
		AuthHashedPassword = 0x2,
		AuthCookie = 0x4
	};

	enum Status
	{
		Error = -1,
		NotConnected,
		Connecting,
		Authenticating,
		Connected
	};

    explicit TorControlManager(QObject *parent = 0);

	/* Information */
	Status status() const { return pStatus; }
	QString torVersion() const { return pTorVersion; }
	QString statusText() const;

	bool isSocksReady() const { return !pSocksAddress.isNull(); }
	QHostAddress socksAddress() const { return pSocksAddress; }
	quint16 socksPort() const { return pSocksPort; }
	QNetworkProxy connectionProxy();

	/* Authentication */
	QFlags<AuthMethod> authMethods() const { return pAuthMethods; }
	void setAuthPassword(const QByteArray &password);

	/* Connection */
	bool isConnected() const { return status() == Connected; }
	void connect(const QHostAddress &address, quint16 port);

	/* Hidden Services */
	const QList<HiddenService*> &hiddenServices() const { return pServices; }
	void addHiddenService(HiddenService *service);

signals:
	void statusChanged(int newStatus, int oldStatus);
	void connected();
	void disconnected();
	void socksReady();

private slots:
	void socketConnected();
	void socketDisconnected();
	void socketError();

	void commandFinished(class TorControlCommand *command);

	void getSocksInfoReply();

	void setError(const QString &message);

private:
	class TorControlSocket *socket;
	QString pErrorMessage;
	QString pTorVersion;
	QByteArray pAuthPassword;
	QHostAddress pSocksAddress;
	QList<HiddenService*> pServices;
	quint16 pSocksPort;
	QFlags<AuthMethod> pAuthMethods;
	Status pStatus;

	void setStatus(Status status);

	void authenticate();
	void getSocksInfo();
	void publishServices();
};

}

extern Tor::TorControlManager *torManager;

#endif // TORCONTROLMANAGER_H
