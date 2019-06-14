#include "UI.h"

#define GetCurrentDir _getcwd

UI::UI(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	QPixmap pix("Logo.jpg");
    ui.imm->setPixmap(pix);

	RealTimeAction realTimeAction;
	connect(ui.button1, SIGNAL(clicked()), this, SLOT(realTimeAction.action()));

	RegisterAction registerAction;
	connect(ui.button2, SIGNAL(clicked()), this, SLOT(registerAction.action()));

	connect(ui.button3, SIGNAL(clicked()), this, SLOT(carica_analizza()));
}

UI::~UI() {}

void mostra(cv::Mat original, cv::Mat risultati);
void mostra2(cv::Mat original,cv::Mat risultati,cv::String percentuale11,cv::String percentuale22,cv::String percentuale33,cv::String percentuale44,cv::String percentuale55,cv::String percentuale66,cv::String percentuale77,cv::String percentuale88,cv::String percentuale99,cv::String percentuale1010,cv::String percentuale00,float perc_entusiasmo,float perc_interesse,float perc_sorpresa,float perc_curiosita,float perc_concentrazione,float perc_attenzione,float perc_delusione,float perc_noia,float perc_perplessita,float perc_fastidio,float perc_frustrazione);


std::string UI::apriFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Carica Video"), QDir::currentPath(), tr("AVI (*.avi*)"));
	std::string risultato = filename.toStdString();
	return risultato;
}

std::string UI::salvaFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Salva Video"), QDir::currentPath(), tr("AVI (*.avi)"));
	std::string risultato = filename.toStdString();
	return risultato;
}

std::string UI::salvaRisultati()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Salva Risultati"), QDir::currentPath(), tr("TXT (*.txt)"));
	std::string risultato = filename.toStdString();
	return risultato;
}

