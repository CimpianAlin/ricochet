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

#ifndef CONTACTSMANAGER_H
#define CONTACTSMANAGER_H

#include <QObject>
#include <QList>
#include "ContactUser.h"

class ContactsManager : public QObject
{
	Q_OBJECT
	Q_DISABLE_COPY(ContactsManager)

public:
    explicit ContactsManager();

	const QList<ContactUser*> &contacts() const { return pContacts; }
	ContactUser *lookupSecret(const QByteArray &secret) const;


public slots:
	void connectToAll();

private:
	QList<ContactUser*> pContacts;

	void loadFromSettings();
};

extern ContactsManager *contactsManager;

#endif // CONTACTSMANAGER_H
