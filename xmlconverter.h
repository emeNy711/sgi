#ifndef XMLCONVERTER_H
#define XMLCONVERTER_H

#include "XMLReader.h"
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
public slots:
	void indexSlot(QString msg);
	void reciveErrMsgSlot(QString msg);
signals:
	//void openFileSignal();
};

#endif // XMLCONVERTER_H
