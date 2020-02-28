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
	connect(generateBtn, &QPushButton::clicked, this, &xmlconverter::generateFile);
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
}

xmlconverter::~xmlconverter()
{
	delete filePathEdit;
	delete openBtn;
	delete generateBtn;
	delete HBoxLay;
	delete VBoxLay;
	//delete textEdit;
	//delete widg;
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
	t;
	t.start();

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
		
		if (!reader.read(&file, filePath, fileInfo.baseName())) 
			reciveErrMsgSlot("Ошибка разбора файла " + ss + ".xml");
		progressBar.setFormat(QString::number(++count) + "/" + QString::number(dirContent.size()));
		progressBar.setValue(progressBar.value() + 1);
		//count++;
	}
}

void xmlconverter::indexSlot(QString msg)
{
	label->setText(msg);

	if (msg == "Готово!")
	{
		//label->setText(QString::number(t.elapsed() / 1000));
	}

	QApplication::processEvents();
}

void xmlconverter::reciveErrMsgSlot(QString msg)
{
	textEdit->setText(textEdit->toPlainText() + msg);
	QApplication::processEvents();
}
