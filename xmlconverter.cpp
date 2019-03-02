#include "xmlconverter.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>

#include <qmessagebox>
#include <qfiledialog>

//#include "XMLReader.h"


xmlconverter::xmlconverter(QWidget *parent)
	: QMainWindow(parent)
{
	widg = new QWidget(this);
	setCentralWidget(widg);
	filePathEdit = new QLineEdit();
	filePathEdit->setMinimumWidth(400);
	filePathEdit->setReadOnly(true);
	openBtn = new QPushButton("Открыть");
	connect(openBtn, &QPushButton::clicked, this, &xmlconverter::openFile);
	generateBtn = new QPushButton("Сгенерировать");
	//connect(generateBtn, &QPushButton::clicked, this, &xmlconverter::generateFile);
	connect(generateBtn, &QPushButton::clicked, this, &xmlconverter::generateFileThread);
	textEdit = new QTextEdit();
	textEdit->setReadOnly(true);
	VBoxLay = new QVBoxLayout(widg);
	HBoxLay = new QHBoxLayout(widg);
	HBoxLay->addWidget(filePathEdit);
	HBoxLay->addWidget(openBtn);
	HBoxLay->addWidget(generateBtn);

	label = new QLabel;
	label->setText("");
	VBoxLay->addLayout(HBoxLay);
	VBoxLay->addWidget(textEdit);
	VBoxLay->addWidget(&progressBar);
	VBoxLay->addWidget(label);
	thr = new Thread();
	thr2 = new Thread();
	thr3 = new QThread;
	thr4 = new QThread;
	thr5 = new QThread;
	thr6 = new QThread;
	thr7 = new QThread;
	thr8 = new QThread;
}

xmlconverter::~xmlconverter()
{
	delete filePathEdit;
	delete openBtn;
	delete generateBtn;
	delete HBoxLay;
	delete VBoxLay;
	delete textEdit;
	delete widg;
}

void xmlconverter::openFile()
{
	//filePath = QFileDialog::getOpenFileName(this,
	//	tr("Открыть файл XML"), "", tr("Xml Files (*.xml)"));

	filePath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "",
		QFileDialog::DontUseNativeDialog | QFileDialog::DontResolveSymlinks);

	filePathEdit->setText(filePath);
}

void xmlconverter::generateFile()
{
	textEdit->clear();
	progressBar.reset();

	QDir dir(filePath);
	QFileInfoList dirContent = dir.entryInfoList(QStringList()
		<< "*.xml",
		QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

	progressBar.setMinimum(0);
	progressBar.setMaximum(dirContent.size());
	progressBar.setValue(0);

	XMLReader reader;
	connect(&reader, &XMLReader::indexSignal, this, &xmlconverter::indexSlot);
	connect(&reader, &XMLReader::sendErrMsgSignal, this, &xmlconverter::reciveErrMsgSlot);
	int count = 0;
	progressBar.setFormat(QString::number(count) + "/" + QString::number(dirContent.size()));
	for (const auto &fileInfo : dirContent)
	{
		QString ss = fileInfo.baseName();

		reciveErrMsgSlot("Начал " + ss + ".xml \n");
		QFile file(fileInfo.absoluteFilePath());
		if (!file.open(QFile::ReadOnly | QFile::Text)) 
		{
			reciveErrMsgSlot("Не могу открыть файл " + ss + ".xml");
			continue;
		}
		
		//if (!reader.read(&file, filePath, fileInfo.baseName())) 
			//reciveErrMsgSlot("Ошибка разбора файла " + ss + ".xml");
		progressBar.setFormat(QString::number(++count) + "/" + QString::number(dirContent.size()));
		progressBar.setValue(progressBar.value() + 1);
		//count++;
	}
}

void xmlconverter::generateFileThread()
{
	/*
	Thread thr;
	Thread thr2;

	connect(this, &xmlconverter::readThreadSignal, &thr, &Thread::thr_read_slot, Qt::DirectConnection);
	connect(this, &xmlconverter::readThreadSignal, &thr2, &Thread::thr_read_slot, Qt::DirectConnection);
	thr.start();
	thr2.start();
	*/
	/*##################################################################################*/

	start = QDateTime::currentDateTime();

	t;
	t.start();

	QDir dir(filePath);
	QFileInfoList dirContent = dir.entryInfoList(QStringList()
		<< "*.xml",
		QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);


	
	
	/**/
	int count = 0;
	for (const auto &fileInfo : dirContent)
	{
		QString ss = fileInfo.baseName();

		//reciveErrMsgSlot("Начал " + ss + ".xml \n");
		
		//emit readThreadSignal(&file, filePath, fileInfo.baseName());
		if (count == 0)
		{
			//thr->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			connect(reader_thr3, &XMLReader::indexSignal, this, &xmlconverter::indexSlot);
			reader_thr3->moveToThread(thr3);
			connect(thr3, &QThread::started, reader_thr3, &XMLReader::read);
			thr3->start();
			

			//QtConcurrent::run(reader_thr3, &XMLReader::read);

		}
		if (count == 2)
		{
			//thr2->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr2->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			reader_thr3->moveToThread(thr4);
			connect(thr4, &QThread::started, reader_thr4, &XMLReader::read);
			thr4->start();

			//QtConcurrent::run(reader_thr3, &XMLReader::read);
		}
		if (count == 2)
		{
			//thr2->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr2->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			reader_thr3->moveToThread(thr4);
			//connect(thr4, &QThread::started, reader_thr4, &XMLReader::read);
			//thr4->start();

			QtConcurrent::run(reader_thr3, &XMLReader::read);
		}
		if (count == 3)
		{
			//thr2->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr2->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			reader_thr3->moveToThread(thr4);
			//connect(thr4, &QThread::started, reader_thr4, &XMLReader::read);
			//thr4->start();

			QtConcurrent::run(reader_thr3, &XMLReader::read);
		}
		if (count == 4)
		{
			//thr2->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr2->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			reader_thr3->moveToThread(thr4);
			//connect(thr4, &QThread::started, reader_thr4, &XMLReader::read);
			//thr4->start();

			QtConcurrent::run(reader_thr3, &XMLReader::read);
		}
		if (count == 5)
		{
			//thr2->init(fileInfo.absoluteFilePath(), filePath, fileInfo.baseName());
			//thr2->start(/*&file, fileInfo.absoluteFilePath(), fileInfo.baseName()*/);

			reader_thr3 = new XMLReader;
			reader_thr3->init(filePath, fileInfo.baseName());
			reader_thr3->moveToThread(thr4);
			//connect(thr4, &QThread::started, reader_thr4, &XMLReader::read);
			//thr4->start();

			QtConcurrent::run(reader_thr3, &XMLReader::read);
		}
		++count;
	}
	
}

void xmlconverter::indexSlot(QString msg)
{
	label->setText(msg);

	if (msg == "Готово!")
	{
		finish = QDateTime::currentDateTime();
		int secs = finish.secsTo(start);
		start.addSecs(secs);
		int msecs = finish.time().msecsTo(start.time());

		int msecs_duration = secs * 1000 + msecs;
		//t.elapsed();

		label->setText(QString::number(t.elapsed() / 1000));

	}

	QApplication::processEvents();
}

void xmlconverter::reciveErrMsgSlot(QString msg)
{
	textEdit->setText(textEdit->toPlainText() + msg);
	QApplication::processEvents();
}
