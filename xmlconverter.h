#ifndef XMLCONVERTER_H
#define XMLCONVERTER_H

#include "XMLReader.h"
#include "thread.h"
#include <QtWidgets/QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QLabel>
#include <QApplication>
#include <QTextEdit>
#include <QTextStream>
#include <QProgressBar>
#include <QTime>

class xmlconverter : public QMainWindow
{
	Q_OBJECT

public:
	xmlconverter(QWidget *parent = 0);
	~xmlconverter();
	QWidget *widg;
	QLineEdit *filePathEdit;
	QPushButton *openBtn;
	QPushButton *generateBtn;
	QHBoxLayout *HBoxLay;
	QVBoxLayout *VBoxLay;
	QLabel *label;
	QTextEdit *textEdit;
	QTextStream textStream;
	QProgressBar progressBar;
	

	QString filePath;
	void openFile();
	void generateFile();
	
	QTime t;
public slots:
	void indexSlot(QString msg);
	void reciveErrMsgSlot(QString msg);
signals:
	void readThreadSignal(QIODevice *device, QString filePath, QString fileName);
};

#endif // XMLCONVERTER_H
