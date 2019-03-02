#ifndef THREAD_H
#define THREAD_H

#include <qthread.h>
#include <QThread>
#include <qmutex.h>
#include <QEventLoop>
#include <QIODevice>
#include "XMLReader.h"
#include <QMutexLocker>

class Thread : public QThread
{
	Q_OBJECT
public:

	Thread(QObject* parent = 0/*, QString _device, QString _filePath, QString _fileName*/);
	void init(QString _filePath, QString _fileName);
	QMutex mutex;
	 QFile device;
	 QString filePath; 
	 QString fileName;
protected:
	/// -- Основная функция потока;
	void run(/*QString _device, QString _filePath, QString _fileName*/);

public slots:
	void thr_read_slot(QIODevice *device, QString filePath, QString fileName);


};


#endif //THREAD_H