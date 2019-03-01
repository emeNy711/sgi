#include "XMLReader.h"


XMLReader::XMLReader()
{
}

XMLReader::~XMLReader()
{
}


bool XMLReader::read(QIODevice *device, QString filePath, QString fileName)
{
	xml.setDevice(device);
	byCounter = 0;
	byCounterScale = 0;
	billFileName = fileName + ".xml";
	parsingError = false;

	db = QSqlDatabase::addDatabase("QODBC");
	QFileInfo fileinfo(filePath);
	QString baseName = fileinfo.baseName();		// рудимент
	
	QString path = filePath + "/" + fileName;
	QDir().mkdir(path);

	QDir dir;
	if(fileExists(path+"/SETTINGS.DBF"))
		if (!dir.remove(path + "/SETTINGS.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("SETTINGS.DBF занята другим процессом"));
	if (fileExists(path + "/SERVICE.DBF"))
		if (!dir.remove(path + "/SERVICE.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("SERVICE.DBF занята другим процессом"));
	if (fileExists(path + "/BILLLIST.DBF"))
		if(!dir.remove(path + "/BILLLIST.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("BILLLIST.DBF занята другим процессом"));
	if (fileExists(path + "/ANIMALS.DBF"))
		if (!dir.remove(path + "/ANIMALS.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("ANIMALS.DBF занята другим процессом"));
	if (fileExists(path + "/COUNTER.DBF"))
		if (!dir.remove(path + "/COUNTER.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("COUNTER.DBF занята другим процессом"));
	if (fileExists(path + "/CNTSCALE.DBF"))
		if (!dir.remove(path + "/CNTSCALE.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CNTSCALE.DBF занята другим процессом"));
	if (fileExists(path + "/CNTSCTRF.DBF"))
		if (!dir.remove(path + "/CNTSCTRF.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CNTSCTRF.DBF занята другим процессом"));
	if (fileExists(path + "/CNTSCTR2.DBF"))
		if (!dir.remove(path + "/CNTSCTR2.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CNTSCTR2.DBF занята другим процессом"));
	if (fileExists(path + "/NORSCTRF.DBF"))
		if (!dir.remove(path + "/NORSCTRF.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("NORSCTRF.DBF занята другим процессом"));
	if (fileExists(path + "/CICNTVSC.DBF"))
		if (!dir.remove(path + "/CICNTVSC.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CICNTVSC.DBF занята другим процессом"));
	if (fileExists(path + "/CICNTLSC.DBF"))
		if (!dir.remove(path + "/CICNTLSC.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CICNTLSC.DBF занята другим процессом"));
	if (fileExists(path + "/PIITEM.DBF"))
		if (!dir.remove(path + "/PIITEM.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("CICNTLSC.DBF занята другим процессом"));
	if (fileExists(path + "/ADDRESES.DBF"))
		if (!dir.remove(path + "/ADDRESES.DBF"))
			setParsingError("Ошибка в " + fileName + ". " + QString("ADDRESES.DBF занята другим процессом"));

	if (parsingError)
		return false;

	QString dsn = QString("Driver={Microsoft dBASE Driver (*.dbf)};DriverID=277;Dbq=%1").arg(path);//277
	db.setDatabaseName(dsn);
	if (!db.open()) 
	{  // is OK 
		QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
		return true;
	}
	
	QSqlQuery query(db);
	query_ptr = new QSqlQuery;
	query_ptr = &query;

	QString sql = QString::fromLocal8Bit("create table [SETTINGS] "
		"(path varchar(200), "
		"[currency] varchar(200), "
		"isCntryRus varchar(200), "
		"m_service varchar(200), "
		"lang varchar(200), "
		"internet varchar(200), "
		"isFioDsbld varchar(200), "
		"dblSdEnbld varchar(200), "
		"mnchrmMode varchar(200), "
		"isOnlElctr varchar(200), "
		"withPrivel varchar(200), "
		"withTrfNam varchar(200), "
		"withInptDt varchar(200), "
		"isCrmEnerg varchar(200), "
		"wBnkPrntPl varchar(200), "
		"adrStyle varchar(200), "
		"wthFnDetal varchar(200))");

	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	//qDebug() << query_ptr->lastQuery();

	sql = QString::fromLocal8Bit("create table [SERVICE] "
		"([codeservic] varchar(200), "
		"[name] varchar(200), "
		"[shortname] varchar(200), "
		"[edizm] varchar(200))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [BILLLIST] "
		"([number] varchar(15), "
		"[date] varchar(10), "
		"[time] varchar(8), "
		"[datepaybef] varchar(10), "
		"[summa] varchar(10), "
		"[index] varchar(5),"
		"[CIname] varchar(50),"
		"[CIen_name] varchar(50),"
		"[CIaddress] varchar(250),"
		"[CIphone] varchar(150),"
		"[CIaccount] varchar(20),"
		"[CImfo] varchar(10),"
		"[CIokpo] varchar(10),"
		"[CIcrrcount] varchar(20),"
		"[CIinn] varchar(10),"
		"[CIkpp] varchar(10),"
		"[CIbank] varchar(50),"
		"[CIpstindex] varchar(6),"
		"[CIwebsite] varchar(50),"
		"[Cabcode] varchar(25),"
		"[Cfio] varchar(45),"
		"[Caddress] varchar(250),"
		"[Cpostindex] varchar(10),"
		"[Cchecksum] varchar(10),"
		"[Csum_Osh] varchar(10),"
		"[CdlvrReg] varchar(6),"
		"[Qrdata] varchar(200),"
		"[vers] varchar(10),"
		"[peoplecnt] varchar(3),"
		"[watersqr] varchar(3),"
		"[allsquare] varchar(4),"
		"[roomcount] varchar(3),"
		"[eePrivLmt] varchar(20),"
		"[Fcdsrvc] varchar(5),"
		"[indvalue] varchar(10),"
		"[indsum] varchar(10),"
		"[prvelvalue] varchar(10),"
		"[privelsum] varchar(10),"
		"[recalcsum] varchar(10),"
		"[grpcntval] varchar(12),"
		"[grpcntsum] varchar(10),"
		"[totalsum] varchar(10),"
		"[odnfeeVal] varchar(12),"
		"[odntariff] varchar(12),"
		"[norma] varchar(40),"
		"[Nvalue] varchar(11),"
		"[Gcdservice] varchar(10),"
		"[readingbeg] varchar(10),"
		"[reading] varchar(50),"
		"[Gvalue] varchar(25),"
		"[feeall] varchar(50),"
		"[coef] varchar(40),"
		"[coefall] varchar(50),"
		"[coefunit] varchar(50),"
		"[fee] varchar(50),"
		"[feesum] varchar(12),"
		"[unit] varchar(50),"
		"[feeallstr] varchar(254),"
		"[indall] varchar(50),"
		"[Gncount] varchar(10),"
		"[old_delta] varchar(50),"
		"[dategosp] varchar(10),"
		"[Ccdservice] varchar(10),"
		"[topindex] varchar(20),"
		"[cntplace] varchar(40),"
		"[Cncount] varchar(15),"
		"[Cscale] varchar(6),"
		"[Cdate] varchar(10),"
		"[Ctype] varchar(5),"
		"[Ldate] varchar(10),"
		"[Ltype] varchar(5),"
		"[factval] varchar(20),"
		"[factdate] varchar(10),"
		"[Scdservice] varchar(5),"
		"[tarifname] varchar(250),"
		"[Starif] varchar(20),"
		"[feeprev] varchar(50),"
		"[feecur] varchar(50),"
		"[Sfeevalprv] varchar(50),"
		"[Sfeevalcur] varchar(50),"
		"[desc] varchar(254),"
		"[prevpays] varchar(12),"
		"[prevsubs] varchar(12),"
		"[curpays] varchar(12),"
		"[cursubs] varchar(12),"
		"[Lpsumma] varchar(10),"
		"[dateclient] varchar(10),"
		"[datebeg] varchar(10),"
		"[feemonth] varchar(20),"
		"[feemonthcr] varchar(20),"
		"[month2] varchar(20),"
		"[saldobeg] varchar(20),"
		"[feetotal] varchar(20),"
		"[pays] varchar(20),"
		"[Tsumma] varchar(20),"
		"[recReading] varchar(20),"
		"[recPeople] varchar(2),"
		"[recSrvoff] varchar(2),"
		"[recTmpnotl] varchar(2),"
		"[feecorr] varchar(20),"
		"[equipments] varchar(200),"
		"[grphpaysum] varchar(20),"
		"[ftotalcur] varchar(20),"
		"[feevalprev] varchar(20),"
		"[feevalcur] varchar(20),"
		"[feeyear] varchar(20),"
		"[feehlfyear] varchar(20),"
		"[Gsumma] varchar(10),"
		"[sumrest] varchar(20))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	qDebug() << query_ptr->lastQuery();

	sql = QString::fromLocal8Bit("create table [ADDRESES] "
		"([billnumber] varchar(15), "
		"[Acity] varchar(250),"
		"[Astreet] varchar(250),"
		"[Anhouse] varchar(3),"
		"[Acharhouse] varchar(10),"
		"[Anflat] varchar(3),"
		"[Acharflat] varchar(10),"
		"[Apostindex] varchar(50),"
		"[Aregion] varchar(250),"
		"[Aarea] varchar(250),"
		"[ADcity] varchar(250),"
		"[ADstreet] varchar(250),"
		"[ADnhouse] varchar(3),"
		"[ADchrhouse] varchar(10),"
		"[ADnflat] varchar(3),"
		"[ADcharflat] varchar(10),"
		"[ADpstindex] varchar(10),"
		"[ADregion] varchar(250),"
		"[ADarea] varchar(250))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [ANIMALS] "
		"([billnumber] varchar(15), "
		"[name] varchar(50), "
		"[count] varchar(10))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [COUNTER] "
		"([billnumber] varchar(15), "
		"[ncount] varchar(12), "
		"[transcoef] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [CNTSCALE] "
		"([billnumber] varchar(15), "
		"[counterInd] varchar(5), "
		"[cntscInd] varchar(12), "
		"[zonename] varchar(200), "
		"[value] varchar(20), "
		"[Bdate] varchar(20), "
		"[Btype] varchar(20), "
		"[Bvalue] varchar(20), "
		"[Fdate] varchar(20), "
		"[Ftype] varchar(20), "
		"[Fvalue] varchar(20), "
		"[Edate] varchar(20), "
		"[Etype] varchar(20), "
		"[Evalue] varchar(20))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());


	sql = QString::fromLocal8Bit("create table [CNTSCTRF] "
		"([billnumber] varchar(15), "
		"[counterInd] varchar(5), "
		"[cntscInd] varchar(12), "
		"[feeValue] varchar(12), "
		"[tariff] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	//qDebug() << query_ptr->lastQuery();

	sql = QString::fromLocal8Bit("create table [CNTSCTR2] "
		"([billnumber] varchar(15), "
		"[counterInd] varchar(5), "
		"[cntscInd] varchar(12), "
		"[feeValue1] varchar(12), "
		"[tariff1] varchar(12), "
		"[feeValue2] varchar(12), "
		"[tariff2] varchar(12), "
		"[feeValue3] varchar(12), "
		"[tariff3] varchar(12), "
		"[feeValue4] varchar(12), "
		"[tariff4] varchar(12), "
		"[feeValue5] varchar(12), "
		"[tariff5] varchar(12), "
		"[feeValue6] varchar(12), "
		"[tariff6] varchar(12))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	//qDebug() << query_ptr->lastQuery();

	sql = QString::fromLocal8Bit("create table [NORSCTRF] "
		"([billnumber] varchar(15), "
		"[feeValue] varchar(12), "
		"[tariff] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [CICNTVSC] "
		"([billnumber] varchar(15), "
		"[value] varchar(12), "
		"[zoneindex] varchar(12), "
		"[zonename] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [CICNTLSC] "
		"([billnumber] varchar(15), "
		"[value] varchar(12), "
		"[zoneindex] varchar(12), "
		"[zonename] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	sql = QString::fromLocal8Bit("create table [PIITEM] "
		"([billnumber] varchar(15), "
		"[PIname] varchar(100), "
		"[percent] varchar(12), "
		"[countlg] varchar(12), "
		"[limit] varchar(50))");
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());

	if (xml.readNextStartElement()) {
		if (xml.name() == "Root")// && xml.attributes().value("version") == "1.0")
			readXML(baseName);
		else
			xml.raiseError(QObject::tr("Ошибка! Xml файл не верен!"));
	}
	db.close();
	query_ptr = NULL;
	delete query_ptr;
	emit(indexSignal(QString("Готово!")));
	if (parsingError)
		emit sendErrMsgSignal("Закончил " + billFileName + " с ошибкой! \n");
	else
		emit sendErrMsgSignal("Закончил " + billFileName + ". \n");
	return !xml.error();
}

QString XMLReader::errorString() const
{
	return QObject::tr("%1\nLine %2, column %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}


void XMLReader::readXML(QString baseName)
{
	//Q_ASSERT(xml.isStartElement() && xml.name() == "Root");
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Root", "readXML(). Ожидается тег Root", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Settings")
			readSettings(baseName);
		else if (xml.name() == "Service")
			readService(baseName);
		else if	(xml.name() == "Notice")
			readNotice(baseName);
		else if (xml.name() == "BillList")
			readBillList(baseName);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readSettings(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Settings", "readXML(). Ожидается тег Settings", "нажмите \"Пропустить\" что бы продолжить");
	
	QString path = xml.attributes().value("path").toString();
	QString currency = xml.attributes().value("currency").toString();
	QString isCountryRussia = xml.attributes().value("isCountryRussia").toString();
	QString main_service = xml.attributes().value("main_service").toString();
	QString lang = xml.attributes().value("lang").toString();
	QString internet = xml.attributes().value("internet").toString();
	QString isFioDisabled = xml.attributes().value("isFioDisabled").toString();
	QString doubleSideEnabled = xml.attributes().value("doubleSideEnabled").toString();
	QString monochromeMode = xml.attributes().value("monochromeMode").toString();
	QString isOnlyElectro = xml.attributes().value("isOnlyElectro").toString();
	QString withPrivel = xml.attributes().value("withPrivel").toString();
	QString withTarifName = xml.attributes().value("withTarifName").toString();
	QString withInputDate = xml.attributes().value("withInputDate").toString();
	QString isCrymEnergo = xml.attributes().value("isCrymEnergo").toString();
	QString withBankPrintPlace = xml.attributes().value("withBankPrintPlace").toString();
	QString adrStyle = xml.attributes().value("adrStyle").toString();
	QString withFineDetail = xml.attributes().value("withFineDetail").toString();

	QString sql = QString::fromLocal8Bit("INSERT INTO [SETTINGS] (path, [currency], isCntryRus, m_service, lang, internet, isFioDsbld, dblSdEnbld "
		", mnchrmMode, isOnlElctr, withPrivel, withTrfNam, withInptDt, isCrmEnerg, wBnkPrntPl, adrStyle, wthFnDetal) VALUES('%2', '%3', '%4', '%5', '%6', '%7'"
	", '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18')").arg(baseName).arg(path).arg(currency).arg(isCountryRussia).arg(main_service).arg(lang).arg(internet)
		.arg(isFioDisabled).arg(doubleSideEnabled).arg(monochromeMode).arg(isOnlyElectro).arg(withPrivel).arg(withTarifName).arg(withInputDate).arg(isCrymEnergo).arg(withBankPrintPlace)
		.arg(adrStyle).arg(withFineDetail);

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
//	qDebug() << tmp;
	xml.readNextStartElement();
}


void XMLReader::readService(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Service", "readXML(). Ожидается тег Root", "нажмите \"Пропустить\" что бы продолжить");
	while (xml.readNextStartElement() && !parsingError)
	{
		if (xml.name() == "Item")
			readServiceItem(baseName);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readServiceItem(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (Service) Item", "нажмите \"Пропустить\" что бы продолжить");
	
	QString edizm = xml.attributes().value("edizm").toString();
	QString shortname = xml.attributes().value("shortname").toString();
	QString name = xml.attributes().value("name").toString();
	QString codeservice = xml.attributes().value("codeservice").toString();

	QString sql = QString::fromLocal8Bit("INSERT INTO [SERVICE] ([codeservic], [name], [shortname], [edizm]) VALUES('%1', '%2', '%3', '%4')")
		.arg(codeservice).arg(name).arg(shortname).arg(edizm);

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();

	xml.readNextStartElement();
}

void XMLReader::readNotice(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Notice", "readXML(). Ожидается тег Notice", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readNoticeItem(baseName);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readNoticeItem(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (Notice) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString index = xml.attributes().value("index").toString();
	QString text = xml.readElementText();
	//xml.readNextStartElement();
}

void XMLReader::readBillList(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "BillList", "readXML(). Ожидается тег BillList", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Bill")
			readBill(baseName);
		else if (xml.name() == "NewPage")
			readNewPage(baseName);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readBill(QString baseName)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Bill", "readXML(). Ожидается тег Bill", "нажмите \"Пропустить\" что бы продолжить");

	QString index = xml.attributes().value("index").toString();
	QString summa = xml.attributes().value("summa").toString();
	QString datepaybef = xml.attributes().value("datepaybef").toString();
	QString time = xml.attributes().value("time").toString();
	QString date = xml.attributes().value("date").toString();
	QString number = xml.attributes().value("number").toString();

	//qDebug() << number;
	emit(indexSignal(QString("BILL №: %1").arg(index)));

	QString sql = QString::fromLocal8Bit("INSERT INTO [BILLLIST] ([number], [date], [time], [datepaybef], [summa], [index]) VALUES('%1', '%2', '%3',"
		"'%4', '%5', '%6')").arg(number).arg(date).arg(time).arg(datepaybef).arg(summa).arg(index);

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "CompanyInfo")
			readCompanyInfo(number);
		else if (xml.name() == "ClientInfo")
			readClientInfo(number);
		else if (xml.name() == "StoredInfo")
			readStoredInfo(number);
		else if (xml.name() == "PrivelInfo")
			readPrivelInfo(number);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readCompanyInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "CompanyInfo", "readXML(). Ожидается тег CompanyInfo", "нажмите \"Пропустить\" что бы продолжить");

	QString name = xml.attributes().value("name").toString();
	QString account = xml.attributes().value("account").toString();
	QString postindex = xml.attributes().value("postindex").toString();
	QString bank = xml.attributes().value("bank").toString();
	QString kpp = xml.attributes().value("kpp").toString();
	QString inn = xml.attributes().value("inn").toString();
	QString corrcount = xml.attributes().value("corrcount").toString();
	QString okpo = xml.attributes().value("okpo").toString();
	QString mfo = xml.attributes().value("mfo").toString();
	QString website = xml.attributes().value("website").toString();
	QString phone = xml.attributes().value("phone").toString();
	QString address = xml.attributes().value("address").toString();
	QString en_name = xml.attributes().value("en_name").toString();

	QStringList fieldList;
	fieldList << "CIname" << "CIen_name" << "CIaddress" << "CIphone" << "CIaccount" << "CImfo" << "Ciokpo" << "CIcrrcount"
		<< "CIinn" << "CIkpp" << "CIbank" << "CIpstindex" << "CIwebsite";
	QStringList valueList;
	valueList << name << en_name << address << phone << account << mfo << okpo << corrcount
		<< inn << kpp << bank << postindex << website;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readClientInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "ClientInfo", "readXML(). Ожидается тег ClientInfo", "нажмите \"Пропустить\" что бы продолжить");

	QString postindex = xml.attributes().value("postindex").toString();
	QString address = xml.attributes().value("address").toString();
	QString deliveryRegion = xml.attributes().value("deliveryRegion").toString();
	QString checksum_Osh = xml.attributes().value("checksum_Osh").toString();
	QString checksum = xml.attributes().value("checksum").toString();
	QString fio = xml.attributes().value("fio").toString();
	QString abcode = xml.attributes().value("abcode").toString();

	QString sql = QString::fromLocal8Bit("UPDATE [BILLLIST] SET [Cabcode] = '%1', [Cfio] = '%2', [Caddress] = '%3', [Cpostindex] = '%4', [Cchecksum] = '%5' "
		", [Csum_Osh] = '%6', [CdlvrReg] = '%7'"
		" WHERE [number] = '%8'")
		.arg(abcode).arg(fio).arg(address).arg(postindex).arg(checksum).arg(checksum_Osh).arg(deliveryRegion).arg(billIndex);

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Address")
			readAddress(billIndex);
		else if (xml.name() == "AddressDelivery")
			readAddressDelivery(billIndex);
		else if (xml.name() == "QRcode")
			readQRcode(billIndex);
		else
			xml.skipCurrentElement();
	}

}

void XMLReader::readAddress(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Address", "readXML(). Ожидается тег Address", "нажмите \"Пропустить\" что бы продолжить");

	QString postindex = xml.attributes().value("postindex").toString();
	QString nflat = xml.attributes().value("nflat").toString();
	QString nhouse = xml.attributes().value("nhouse").toString();
	QString street = xml.attributes().value("street").toString();
	QString city = xml.attributes().value("city").toString();
	QString charhouse = xml.attributes().value("charhouse").toString();
	QString charflat = xml.attributes().value("charflat").toString();
	QString region = xml.attributes().value("region").toString();
	QString area = xml.attributes().value("area").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "Acity" << "Astreet" << "Anhouse" << "Acharhouse" << "Anflat" << "Acharflat" << "Apostindex" << "Aregion"
		<< "Aarea";
	QStringList valueList;
	valueList << billIndex << city << street << nhouse << charhouse << nflat << charflat << postindex << region
		<< area;

	queryInsert("ADDRESES", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readAddressDelivery(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "AddressDelivery", "readXML(). Ожидается тег AddressDelivery", "нажмите \"Пропустить\" что бы продолжить");

	QString postindex = xml.attributes().value("postindex").toString();
	QString nflat = xml.attributes().value("nflat").toString();
	QString nhouse = xml.attributes().value("nhouse").toString();
	QString street = xml.attributes().value("street").toString();
	QString city = xml.attributes().value("city").toString();
	QString charhouse = xml.attributes().value("charhouse").toString();
	QString charflat = xml.attributes().value("charflat").toString();
	QString region = xml.attributes().value("region").toString();
	QString area = xml.attributes().value("area").toString();

	QStringList fieldList;
	fieldList << "ADcity" << "ADstreet" << "ADnhouse" << "ADchrhouse" << "ADnflat" << "ADcharflat" << "ADpstindex" << "ADregion"
		<< "ADarea";
	QStringList valueList;
	valueList << city << street << nhouse << charhouse << nflat << charflat << postindex << region
		<< area;

	queryUpdate("ADDRESES", fieldList, valueList, "billnumber", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readQRcode(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "QRcode", "readXML(). Ожидается тег QRcode", "нажмите \"Пропустить\" что бы продолжить");

	QString data = xml.attributes().value("data").toString();

	QString sql = QString::fromLocal8Bit("UPDATE [BILLLIST] SET [Qrdata] = '%1'"
		" WHERE [number] = '%2'")
		.arg(data).arg(billIndex);
	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;

	xml.readNextStartElement();
}

void XMLReader::readStoredInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "StoredInfo", "readXML(). Ожидается тег StoredInfo", "нажмите \"Пропустить\" что бы продолжить");
	
	QString eePrivLimit = xml.attributes().value("eePrivLimit").toString();
	QString roomcount = xml.attributes().value("roomcount").toString();
	QString allsquare = xml.attributes().value("allsquare").toString();
	QString watersquare = xml.attributes().value("watersquare").toString();
	QString peoplecount = xml.attributes().value("peoplecount").toString();
	QString vers = xml.attributes().value("vers").toString();

	QString sql = QString::fromLocal8Bit("UPDATE [BILLLIST] SET [vers] = '%1', [peoplecnt] = '%2', [watersqr] = '%3', [allsquare] = '%4', [roomcount] = '%5' "
		", [eePrivLmt] = '%6'"
		" WHERE [number] = '%7'")
		.arg(vers).arg(peoplecount).arg(watersquare).arg(allsquare).arg(roomcount).arg(eePrivLimit).arg(billIndex);
	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Fee")
			readFee(billIndex);
		else if (xml.name() == "CntInfo")
			readCntInfo(billIndex);
		else if (xml.name() == "ServInfo")
			readServInfo(billIndex);
		else if (xml.name() == "LastPay")
			readLastPay(billIndex);
		else if (xml.name() == "Total")
			readTotal(billIndex);
		else if (xml.name() == "GraphPay")
			readGraphPay(billIndex);
		else if (xml.name() == "Animals")
			readAnimals(billIndex);
		else if (xml.name() == "GroupCounter")
			readGroupCounter(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readAnimals(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Animals", "readXML(). Ожидается тег Animals", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readAnimalsItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readAnimalsItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (Animals) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString name = xml.attributes().value("name").toString();
	QString count = xml.attributes().value("count").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "name" << "count";
	QStringList valueList;
	valueList << billIndex << name << count;

	queryInsert("ANIMALS", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readFee(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Fee", "readXML(). Ожидается тег Fee", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Service")
			readFeeService(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readFeeService(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Service", "readXML(). Ожидается тег (Fee) Service", "нажмите \"Пропустить\" что бы продолжить");

	QString codeservice = xml.attributes().value("codeservice").toString();
	QString totalsum = xml.attributes().value("totalsum").toString();
	QString indsum = xml.attributes().value("indsum").toString();
	QString indvalue = xml.attributes().value("indvalue").toString();
	QString privelvalue = xml.attributes().value("privelvalue").toString();
	if (privelvalue == "")
		privelvalue = "0";
	QString privelsum = xml.attributes().value("privelsum").toString();
	if (privelsum == "")
		privelsum = "0.00";
	QString recalcsum = xml.attributes().value("recalcsum").toString();
	QString groupcntvalue = xml.attributes().value("groupcntvalue").toString();
	QString groupcntsum = xml.attributes().value("groupcntsum").toString();
	//QString recalcsum = xml.attributes().value("recalcsum").toString(); // Дублируется в эксельке

	QStringList fieldList;
	fieldList << "Fcdsrvc" << "indvalue" << "indsum" << "prvelvalue" << "privelsum" << "recalcsum" << "grpcntval" << "grpcntsum"
		<< "totalsum";
	QStringList valueList;
	valueList << codeservice << indvalue << indsum << privelvalue << privelsum << recalcsum << groupcntvalue << groupcntsum
		<< totalsum;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "ByCounter")
			readByCounter(billIndex);
		else if (xml.name() == "TariffsOdn")
			readTariffsOdn(billIndex);
		else if (xml.name() == "ByNorma")
			readByNorma(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readTariffsOdn(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "TariffsOdn", "readXML(). Ожидается тег TariffsOdn", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readTariffsOdnItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}
void XMLReader::readTariffsOdnItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (TariffsOdn) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString feeValue = xml.attributes().value("feeValue").toString();
	QString tariff = xml.attributes().value("tariff").toString();

	QStringList fieldList;
	fieldList << "odnfeeVal" << "odntariff";
	QStringList valueList;
	valueList << feeValue << tariff;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readByCounter(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "ByCounter", "readXML(). Ожидается тег ByCounter", "нажмите \"Пропустить\" что бы продолжить");
	byCounter++;
	QString ncount = xml.attributes().value("ncount").toString();
	QString transcoef = xml.attributes().value("transcoef").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "ncount" << "transcoef";
	QStringList valueList;
	valueList << billIndex << ncount << transcoef;

	queryInsert("COUNTER", fieldList, valueList);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Scale")
			readByCounterScale(billIndex, byCounter);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readByCounterScale(QString billIndex, int byCounter)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Scale", "readXML(). Ожидается тег (ByCounter) Scale", "нажмите \"Пропустить\" что бы продолжить");
	byCounterScale++;
	QString zonename = xml.attributes().value("zonename").toString();
	QString value = xml.attributes().value("value").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "counterInd" << "cntscInd" << "zonename" << "value";
	QStringList valueList;
	valueList << billIndex << QString::number(byCounter) << QString::number(byCounterScale) << zonename << value;

	queryInsert("CNTSCALE", fieldList, valueList);


	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "BeginCounter")
			readBeginCounter(QString::number(byCounter), QString::number(byCounterScale));
		else if (xml.name() == "FactCounter")
			readFactCounter(QString::number(byCounter), QString::number(byCounterScale));
		else if (xml.name() == "EndCounter")
			readEndCounter(QString::number(byCounter), QString::number(byCounterScale));
		else if (xml.name() == "Tariffs")
			readTariffs(billIndex, QString::number(byCounter), QString::number(byCounterScale));
		else
			xml.skipCurrentElement();
	}

}

void XMLReader::readBeginCounter(QString byCounter, QString byCounterScale)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "BeginCounter", "readXML(). Ожидается тег BeginCounter", "нажмите \"Пропустить\" что бы продолжить");

	QString date = xml.attributes().value("date").toString();
	QString type = xml.attributes().value("type").toString();
	QString value = xml.attributes().value("value").toString();

	QStringList fieldList;
	fieldList << "Bdate" << "Btype" << "Bvalue";
	QStringList valueList;
	valueList << date << type << value;

	queryUpdate("CNTSCALE", fieldList, valueList, "cntscInd", byCounterScale);

	xml.readNextStartElement();
}

void XMLReader::readFactCounter(QString byCounter, QString byCounterScale)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "FactCounter", "readXML(). Ожидается тег FactCounter", "нажмите \"Пропустить\" что бы продолжить");

	QString date = xml.attributes().value("date").toString();
	QString type = xml.attributes().value("type").toString();
	QString value = xml.attributes().value("value").toString();

	QStringList fieldList;
	fieldList << "Fdate" << "Ftype" << "Fvalue";
	QStringList valueList;
	valueList << date << type << value;

	queryUpdate("CNTSCALE", fieldList, valueList, "cntscInd", byCounterScale);

	xml.readNextStartElement();
}

void XMLReader::readEndCounter(QString byCounter, QString byCounterScale)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "EndCounter", "readXML(). Ожидается тег EndCounter", "нажмите \"Пропустить\" что бы продолжить");

	QString date = xml.attributes().value("date").toString();
	QString type = xml.attributes().value("type").toString();
	QString value = xml.attributes().value("value").toString();

	QStringList fieldList;
	fieldList << "Edate" << "Etype" << "Evalue";
	QStringList valueList;
	valueList << date << type << value;

	queryUpdate("CNTSCALE", fieldList, valueList, "cntscInd", byCounterScale);

	xml.readNextStartElement();
}

void XMLReader::readTariffs(QString billIndex, QString byCounter, QString byCounterScale)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Tariffs", "readXML(). Ожидается тег Tariffs", "нажмите \"Пропустить\" что бы продолжить");
	int nTariffs = 0;
	while (xml.readNextStartElement() && !parsingError)
	{
		nTariffs++;
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readTariffsItem(billIndex, byCounter, byCounterScale, nTariffs);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readTariffsItem(QString billIndex, QString byCounter, QString byCounterScale, int nTariffs)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (Tariffs) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString tariff = xml.attributes().value("tariff").toString();
	QString feeValue = xml.attributes().value("feeValue").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "counterInd" << "cntscInd" << "tariff" << "feeValue";
	QStringList valueList;
	valueList << billIndex << byCounter << byCounterScale << tariff << feeValue;

	queryInsert("CNTSCTRF", fieldList, valueList);

	///////////////////////////////

	fieldList.clear();
	valueList.clear();

	if (nTariffs == 1)
	{
		fieldList << "billnumber" << "counterInd" << "cntscInd" << QString("tariff%1").arg(QString::number(nTariffs)) << QString("feeValue%1").arg(QString::number(nTariffs));
		valueList << billIndex << byCounter << byCounterScale << tariff << feeValue;
		queryInsert("CNTSCTR2", fieldList, valueList);
	}
	else
	{
		fieldList << QString("tariff%1").arg(QString::number(nTariffs)) << QString("feeValue%1").arg(QString::number(nTariffs));
		valueList << tariff << feeValue;
		queryUpdate("CNTSCTR2", fieldList, valueList, "BILLNUMBER", billIndex + QString("' AND [COUNTERIND] = '%1' AND [CNTSCIND] = '%2").arg(byCounter).arg(byCounterScale));
	}

	xml.readNextStartElement();
}

void XMLReader::readByNorma(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "ByNorma", "readXML(). Ожидается тег ByNorma", "нажмите \"Пропустить\" что бы продолжить");

	QString norma = xml.attributes().value("norma").toString();

	QString sql = QString::fromLocal8Bit("UPDATE [BILLLIST] SET [norma] = '%1'"
		" WHERE [number] = '%2'")
		.arg(norma).arg(billIndex);
	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Scale")
			readByNormaScale(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readByNormaScale(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Scale", "readXML(). Ожидается тег (ByNorma) Scale", "нажмите \"Пропустить\" что бы продолжить");

	QString value = xml.attributes().value("value").toString();

	QString sql = QString::fromLocal8Bit("UPDATE [BILLLIST] SET [Nvalue] = '%1'"
		" WHERE [number] = '%2'")
		.arg(value).arg(billIndex);
	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;


	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Tariffs")
			readByNormaScaleTarriffs(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readByNormaScaleTarriffs(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Tariffs", "readXML(). Ожидается тег (ByNormaScale) Tariffs", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readByNormaScaleTarriffsItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readByNormaScaleTarriffsItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (ByNormaScaleTarriffs) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString feeValue = xml.attributes().value("feeValue").toString();
	QString tariff = xml.attributes().value("tariff").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "feeValue" << "tariff";
	QStringList valueList;
	valueList << billIndex << feeValue << tariff;

	queryInsert("NORSCTRF", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readGroupCounter(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "GroupCounter", "readXML(). Ожидается тег GroupCounter", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readGroupCounterItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readGroupCounterItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (GroupCounter) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString codeservice = xml.attributes().value("codeservice").toString();
	QString readingbeg = xml.attributes().value("readingbeg").toString();
	QString reading = xml.attributes().value("reading").toString();
	QString value = xml.attributes().value("value").toString();
	QString feeall = xml.attributes().value("feeall").toString();
	QString coef = xml.attributes().value("coef").toString();
	QString coefall = xml.attributes().value("coefall").toString();
	QString coefunit = xml.attributes().value("coefunit").toString();
	QString fee = xml.attributes().value("fee").toString();
	QString feesum = xml.attributes().value("feesum").toString();
	QString unit = xml.attributes().value("unit").toString();
	QString feeallstr = xml.attributes().value("feeallstr").toString();
	QString indall = xml.attributes().value("indall").toString();
	QString ncount = xml.attributes().value("ncount").toString();
	QString old_delta_all = xml.attributes().value("old_delta_all").toString();

	QStringList fieldList;
	fieldList << "Gcdservice" << "readingbeg" << "reading" << "Gvalue" << "feeall" << "coef" << "coefall" << "coefunit"
		<< "fee" << "feesum" << "unit" << "feeallstr" << "indall" << "Gncount" << "old_delta";
	QStringList valueList;
	valueList << codeservice << readingbeg << reading << value << feeall << coef << coefall << coefunit << fee << feesum
		<< unit << feeallstr << indall << ncount << old_delta_all;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readCntInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "CntInfo", "readXML(). Ожидается тег CntInfo", "нажмите \"Пропустить\" что бы продолжить");

	QString dategosp = xml.attributes().value("dategosp").toString();

	QStringList fieldList;
	fieldList << "dategosp";
	QStringList valueList;
	valueList << dategosp;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Cnt")
			readCnt(billIndex);
		else if (xml.name() == "Item")
			readCntInfoItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readCnt(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Cnt", "readXML(). Ожидается тег Cnt", "нажмите \"Пропустить\" что бы продолжить");

	QString codeservice = xml.attributes().value("codeservice").toString();
	QString ncount = xml.attributes().value("ncount").toString();
	QString scale = xml.attributes().value("scale").toString();
	QString cntplace = xml.attributes().value("cntplace").toString();
	QString topindex = xml.attributes().value("topindex").toString();

	QStringList fieldList;
	fieldList << "Ccdservice" << "topindex" << "cntplace" << "Cncount" << "Cscale";
	QStringList valueList;
	valueList << codeservice << topindex << cntplace << ncount << scale;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "CounterValue")
			readCounterValue(billIndex);
		else if (xml.name() == "LastFactValue")
			readLastFactValue(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readCounterValue(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "CounterValue", "readXML(). Ожидается тег CounterValue", "нажмите \"Пропустить\" что бы продолжить");

	QString date = xml.attributes().value("date").toString();
	QString type = xml.attributes().value("type").toString();

	QStringList fieldList;
	fieldList << "Cdate" << "Ctype";
	QStringList valueList;
	valueList << date << type;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Scale")
			readCounterValueScale(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readCounterValueScale(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Scale", "readXML(). Ожидается тег (CounterValue) Scale", "нажмите \"Пропустить\" что бы продолжить");

	QString value = xml.attributes().value("value").toString();
	QString zoneindex = xml.attributes().value("zoneindex").toString();
	QString zonename = xml.attributes().value("zonename").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "value" << "zoneindex" << "zonename";
	QStringList valueList;
	valueList << billIndex << value << zoneindex << zonename;

	queryInsert("CICNTVSC", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readLastFactValue(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "LastFactValue", "readXML(). Ожидается тег LastFactValue", "нажмите \"Пропустить\" что бы продолжить");

	QString date = xml.attributes().value("date").toString();
	QString type = xml.attributes().value("type").toString();

	QStringList fieldList;
	fieldList << "Ldate" << "Ltype";
	QStringList valueList;
	valueList << date << type;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Scale")
			readLastFactValueScale(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readLastFactValueScale(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Scale", "readXML(). Ожидается тег (LastFactValue) Scale", "нажмите \"Пропустить\" что бы продолжить");

	QString value = xml.attributes().value("value").toString();
	QString zoneindex = xml.attributes().value("zoneindex").toString();
	QString zonename = xml.attributes().value("zonename").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "value" << "zoneindex" << "zonename";
	QStringList valueList;
	valueList << billIndex << value << zoneindex << zonename;

	queryInsert("CICNTLSC", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readCntInfoItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (CntInfo) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString factval = xml.attributes().value("factval").toString();
	QString factdate = xml.attributes().value("factdate").toString();

	QStringList fieldList;
	fieldList << "factval" << "factdate";
	QStringList valueList;
	valueList << factval << factdate;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);
	
	xml.readNextStartElement();
}

void XMLReader::readServInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "ServInfo", "readXML(). Ожидается тег ServInfo", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readServInfoItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readServInfoItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (ServInfo) Item", "нажмите \"Пропустить\" что бы продолжить");
	
	QString codeservice = xml.attributes().value("codeservice").toString();
	QString desc = xml.attributes().value("desc").toString();
	QString tarifname = xml.attributes().value("tarifname").toString();
	QString tarif = xml.attributes().value("tarif").toString();
	QString feeprev = xml.attributes().value("feeprev").toString();
	QString feecur = xml.attributes().value("feecur").toString();
	QString feevalprev = xml.attributes().value("feevalprev").toString();
	QString feevalcur = xml.attributes().value("feevalcur").toString();

	QStringList fieldList;
	fieldList << "Scdservice" << "tarifname" << "Starif" << "feeprev" << "feecur" << "Sfeevalprv" << "Sfeevalcur" << "desc";
	QStringList valueList;
	valueList << codeservice << tarifname << tarif << feeprev << feecur << feevalprev << feevalcur << desc;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readPays(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Pays", "readXML(). Ожидается тег Pays", "нажмите \"Пропустить\" что бы продолжить");

	QString prevpays = xml.attributes().value("prevpays").toString();
	QString prevsubs = xml.attributes().value("prevsubs").toString();
	QString curpays = xml.attributes().value("curpays").toString();
	QString cursubs = xml.attributes().value("cursubs").toString();

	QStringList fieldList;
	fieldList << "prevpays" << "prevsubs" << "curpays" << "cursubs";
	QStringList valueList;
	valueList << prevpays << prevsubs << curpays << cursubs;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readLastPay(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "LastPay", "readXML(). Ожидается тег LastPay", "нажмите \"Пропустить\" что бы продолжить");

	QString summa = xml.attributes().value("summa").toString();
	QString dateclient = xml.attributes().value("dateclient").toString();

	QStringList fieldList;
	fieldList << "Lpsumma" << "dateclient";
	QStringList valueList;
	valueList << summa << dateclient;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readTotal(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Total", "readXML(). Ожидается тег Total", "нажмите \"Пропустить\" что бы продолжить");

	QString datebeg = xml.attributes().value("datebeg").toString();
	QString feemonth = xml.attributes().value("feemonth").toString();
	QString feemonthcur = xml.attributes().value("feemonthcur").toString();
	QString month2 = xml.attributes().value("month2").toString();
	QString saldobeg = xml.attributes().value("saldobeg").toString();
	QString feetotal = xml.attributes().value("feetotal").toString();
	QString pays = xml.attributes().value("pays").toString();
	QString summa = xml.attributes().value("summa").toString();
	QString recalcReading = xml.attributes().value("recalcReading").toString();
	QString feecorr = xml.attributes().value("feecorr").toString();
	QString equipments = xml.attributes().value("equipments").toString();
	QString graphpaysum = xml.attributes().value("graphpaysum").toString();
	QString feetotalcur = xml.attributes().value("feetotalcur").toString();
	QString feevalprev = xml.attributes().value("feevalprev").toString();
	QString feevalcur = xml.attributes().value("feevalcur").toString();
	QString feeyear = xml.attributes().value("feeyear").toString();
	QString feehalfyear = xml.attributes().value("feehalfyear").toString();
	QString recalcPeople = xml.attributes().value("recalcPeople").toString();
	QString recalcServiceoff = xml.attributes().value("recalcServiceoff").toString();
	QString recalcTmpnotlive = xml.attributes().value("recalcTmpnotlive").toString();

	QStringList fieldList;
	fieldList << "datebeg" << "feemonth" << "feemonthcr" << "month2" << "saldobeg" << "feetotal" << "pays" << "Tsumma" << "recReading" 
		<< "feecorr" << "equipments" << "grphpaysum" << "ftotalcur" << "feevalprev" << "feevalcur" << "feeyear" << "feehlfyear"
		<< "recPeople" << "recSrvoff" << "recTmpnotl";
	QStringList valueList;
	valueList << datebeg << feemonth << feemonthcur << month2 << saldobeg << feetotal << pays << summa << recalcReading
		<< feecorr << equipments << graphpaysum << feetotalcur << feevalprev << feevalcur << feeyear << feehalfyear 
		<< recalcPeople << recalcServiceoff << recalcTmpnotlive;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readGraphPay(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "GraphPay", "readXML(). Ожидается тег GraphPay", "нажмите \"Пропустить\" что бы продолжить");

	QString summa = xml.attributes().value("summa").toString();
	QString sumrest = xml.attributes().value("sumrest").toString();

	QStringList fieldList;
	fieldList << "Gsumma" << "sumrest";
	QStringList valueList;
	valueList << summa << sumrest;

	queryUpdate("BILLLIST", fieldList, valueList, "number", billIndex);

	xml.readNextStartElement();
}

void XMLReader::readPrivelInfo(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "PrivelInfo", "readXML(). Ожидается тег PrivelInfo", "нажмите \"Пропустить\" что бы продолжить");

	while (xml.readNextStartElement() && !parsingError)
	{
		QString debug = xml.name().toString();
		if (xml.name() == "Item")
			readPrivelInfoItem(billIndex);
		else
			xml.skipCurrentElement();
	}
}

void XMLReader::readPrivelInfoItem(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "Item", "readXML(). Ожидается тег (PrivelInfo) Item", "нажмите \"Пропустить\" что бы продолжить");

	QString name = xml.attributes().value("name").toString();
	QString percent = xml.attributes().value("percent").toString();
	QString countlg = xml.attributes().value("countlg").toString();
	QString limit = xml.attributes().value("limit").toString();

	QStringList fieldList;
	fieldList << "billnumber" << "PIname" << "percent" << "countlg" << "limit";
	QStringList valueList;
	valueList << billIndex << name << percent << countlg << limit;

	queryInsert("PIITEM", fieldList, valueList);

	xml.readNextStartElement();
}

void XMLReader::readNewPage(QString billIndex)
{
	Q_ASSERT_X(xml.isStartElement() && xml.name() == "NewPage", "readXML(). Ожидается тег NewPage", "нажмите \"Пропустить\" что бы продолжить");

	xml.readNextStartElement();
}

bool XMLReader::fileExists(QString path)
{
	QFileInfo check_file(path);
	if (check_file.exists() && check_file.isFile()) 
		return true;
	else
		return false;
}

void XMLReader::queryUpdate(QString table, QStringList fieldList, QStringList valueList, QString WHERE, QString WHEREVALUE)
{
	Q_ASSERT_X(fieldList.count() == valueList.count(), "queryUpdate(). Количество полей и значений различаются!", "нажмите \"Пропустить\" что бы продолжить");

	QString sql = QString("UPDATE [%1] SET ").arg(table);

	for (int i = 0; i < fieldList.count(); i++)
	{
		if (i == 0)
			sql += QString("[%1] = '%2'").arg(fieldList.at(i)).arg(valueList.at(i));
		else
			sql += QString(", [%1] = '%2'").arg(fieldList.at(i)).arg(valueList.at(i));
	}

	sql += QString(" WHERE [%1] = '%2'").arg(WHERE).arg(WHEREVALUE);

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;
}

void XMLReader::queryInsert(QString table, QStringList fieldList, QStringList valueList)
{

	Q_ASSERT_X(fieldList.count() == valueList.count(), "queryInsert(). Количество полей и значений различаются!", "нажмите \"Пропустить\" что бы продолжить");

	QString sql = QString("INSERT INTO [%1] (").arg(table);

	for (int i = 0; i < fieldList.count(); i++)
	{
		if (i == 0)
			sql += QString("[%1]").arg(fieldList.at(i));
		else
			sql += QString(", [%1]").arg(fieldList.at(i));
	}
	sql += ") VALUES(";

	for (int i = 0; i < valueList.count(); i++)
	{
		if (i == 0)
			sql += QString("'%1'").arg(valueList.at(i));
		else
			sql += QString(", '%1'").arg(valueList.at(i));
	}
	sql += ")";

	query_ptr->clear();
	if (!query_ptr->exec(sql))
		setParsingError("Ошибка в " + billFileName + ". " + query_ptr->lastError().text());
	QString tmp = query_ptr->lastQuery();
	//qDebug() << tmp;
}


void XMLReader::setParsingError(QString msg)
{
	parsingError = true;
	msg += " \n";
	emit sendErrMsgSignal(msg);
}
