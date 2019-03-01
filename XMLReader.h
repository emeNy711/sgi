
#ifndef XMLREADER
#define XMLREADER

#include <qtreewidget>
#include <qxmlstreamreader>
#include <Qpair>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>
#include <QDir>

class XMLReader : public QObject
{
	Q_OBJECT
public:
	XMLReader();
	void init( QString _filePath, QString _fileName);
	//bool read(/*QIODevice *device, QString filePath, QString fileName*/);
	QString errorString() const;
	~XMLReader();

public slots:
	bool read(/*QIODevice *device, QString filePath, QString fileName*/);

private:

	QString filePath;
	QString fileName;


	void readXML(QString baseName);
	void readSettings(QString baseName);
	void readService(QString baseName);
	void readServiceItem(QString baseName);
	void readNotice(QString baseName);
	void readNoticeItem(QString baseName);
	void readBillList(QString baseName);
	void readBill(QString baseName);
	void readCompanyInfo(QString billIndex);
	void readClientInfo(QString billIndex);
	void readAddress(QString billIndex);
	void readAddressDelivery(QString billIndex);
	void readQRcode(QString billIndex);
	void readStoredInfo(QString billIndex);
	void readAnimals(QString billIndex);
	void readAnimalsItem(QString billIndex);
	void readFee(QString billIndex);
	void readFeeService(QString billIndex);
	void readTariffsOdn(QString billIndex);
	void readTariffsOdnItem(QString billIndex);
	void readByCounter(QString billIndex);
	void readByCounterScale(QString billIndex, int byCounter);
	void readBeginCounter(QString byCounter, QString byCounterScale);
	void readFactCounter(QString byCounter, QString byCounterScale);
	void readEndCounter(QString byCounter, QString byCounterScale);
	void readTariffs(QString billIndex, QString byCounter, QString byCounterScale);
	void readTariffsItem(QString billIndex, QString byCounter, QString byCounterScale, int nTariffs);
	void readByNorma(QString billIndex);
	void readByNormaScale(QString billIndex);
	void readByNormaScaleTarriffs(QString billIndex);
	void readByNormaScaleTarriffsItem(QString billIndex);
	void readGroupCounter(QString billIndex);
	void readGroupCounterItem(QString billIndex);
	void readCntInfo(QString billIndex);
	void readCnt(QString billIndex);
	void readCounterValue(QString billIndex);
	void readCounterValueScale(QString billIndex);
	void readLastFactValue(QString billIndex);
	void readLastFactValueScale(QString billIndex);
	void readCntInfoItem(QString billIndex);
	void readServInfo(QString billIndex);
	void readServInfoItem(QString billIndex);
	void readPays(QString billIndex);
	void readLastPay(QString billIndex);
	void readTotal(QString billIndex);
	void readGraphPay(QString billIndex);
	void readPrivelInfo(QString billIndex);
	void readPrivelInfoItem(QString billIndex);
	void readNewPage(QString billIndex);
	bool fileExists(QString path);
	void queryUpdate(QString table, QStringList fieldList, QStringList valueList, QString WHERE, QString WHEREVALUE);
	void queryInsert(QString table, QStringList fieldList, QStringList valueList);


	QXmlStreamReader xml;
	QSqlDatabase db;
	QSqlQuery *query_ptr;
	int byCounter = 0;
	int byCounterScale = 0;
	QString billFileName;

	void setParsingError(QString msg);
	bool parsingError;	


signals:
	void indexSignal(QString msg);
	void sendErrMsgSignal(QString msg);
};
#endif