#include "thread.h"

Thread::Thread(QObject* parent/*, QString _device, QString _filePath, QString _fileName*/)
{
	//device = _device;
	//QFile file(fileInfo.absoluteFilePath());
	/*device.setFileName(_device);
	device.open(QFile::ReadOnly | QFile::Text);
	filePath = _filePath;
	fileName = _fileName;*/
}

void Thread::init(QString _filePath, QString _fileName)
{
	filePath = _filePath;
	fileName = _fileName;
}

void Thread::run(/*QString _device, QString _filePath, QString _fileName*/)
{/*
	QFile device(_device);
	device.open(QFile::ReadOnly | QFile::Text);
	QString filePath = _filePath;
	QString fileName = _fileName;
	//QMutexLocker mutexLocker(&mutex);*/
	XMLReader *reader = new XMLReader;
	reader->init(filePath, fileName);
	reader->read(/*&device, filePath, fileName*/);
	
	//exec();
}

void Thread::thr_read_slot(QIODevice *device, QString filePath, QString fileName)
{
	XMLReader reader;
	//reader.read(device, filePath, fileName);
}