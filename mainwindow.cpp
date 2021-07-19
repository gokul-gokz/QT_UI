#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_entry_dialog.h"
#include <QtWidgets>
#include <vector>
#include <fstream>
#include "TestParams.h"
MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent), qnode(argc, argv),
    ui(new Ui::MainWindow)
{
    qnode.init();
    ui->setupUi(this);
    mResourceDir = "../Images";
    QObject::connect(&qnode, SIGNAL(msgSubscribed()), this, SLOT(updateSubBox()));
    QObject::connect(&qnode, SIGNAL(ImagemsgSubscribed()), this, SLOT(updateGraphicsBox()));

//    //QTable values
//    std::vector<QString> barcode_numbers[30];
//    std::vector<int> TestTube_slots[30];
//    std::vector<int> TestStrip_slots[30];
//    std::vector<int> Test_Times[30];
//    std::vector<int> Comments[30];
}

MainWindow::~MainWindow()
{
    delete ui;
}

// convert to std::string to QString
QString MainWindow::toQString(std::string const &s)
{
    return QString::fromUtf8(s.c_str());
}
// convert from QString to std::string
std::string MainWindow::fromQString(QString const &s)
{
    return std::string(s.toUtf8().constData());
}

// updated subscribed data to subText text view box
void MainWindow::updateSubBox(){
    std::string subbed_msg = qnode.sub_message;
    QString outQString = toQString(subbed_msg);
    ui->subText->append(outQString);
}

// updated subscribed image data to the graphics view
void MainWindow::updateGraphicsBox(){

//      QGraphicsPixmapItem item(QPixmap::fromImage(qnode.img_message));

          if (! ui->graphicsView->scene()) {
      //        qDebug() << "No Scene!";

              QGraphicsScene *scene = new QGraphicsScene(this);
              ui->graphicsView->setScene(scene);
          }
          QPixmap originalImage = QPixmap::fromImage(qnode.img_message);
          QPixmap scaledImage = originalImage.scaledToHeight(ui->graphicsView->height(), Qt::SmoothTransformation);
          ui->graphicsView->scene()->addPixmap(scaledImage);

          QRectF bounds = ui->graphicsView->scene()->itemsBoundingRect();
  /*           bounds.setWidth(bounds.width()*0.9);         // to tighten-up margins
             bounds.setHeight(bounds.height()*0.9); */      // same as above
          ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);
//          ui->grahicsView->fitInView(gfxPixItem)
}

// publish text written on the input text box when button is pressed
void MainWindow::on_publishButton_clicked()
{
    std_msgs::String pub_msg;
    QString inputQString = ui->pubText->toPlainText();
    std::string inputString = fromQString(inputQString);
    qnode.pub_message = inputString;
    pub_msg.data = inputString;
    qnode.pub.publish(pub_msg);

//    QString filename = QFileDialog::getOpenFileName(this,
//                                                    tr("Load Image"),
//                                                    mResourceDir,
//                                                    tr("Images (*.png *.jpeg)"));

//    if (filename.isEmpty())  {
//        return;
//    }

//    QPixmap p(filename);


//    if (! ui->graphicsView->scene()) {
////        qDebug() << "No Scene!";

//        QGraphicsScene *scene = new QGraphicsScene(this);
//        ui->graphicsView->setScene(scene);
//    }
//    ui->graphicsView->scene()->addPixmap(p);


}

void MainWindow::on_startButton_clicked()
{
    std_msgs::String pub_msg;
    pub_msg.data = "1";
    qnode.control_flow_pub.publish(pub_msg);
}


void MainWindow::on_stopButton_clicked()
{
    std_msgs::String pub_msg;
    pub_msg.data = "0";
    qnode.control_flow_pub.publish(pub_msg);
}


void MainWindow::on_pauseButton_clicked()
{
    std_msgs::String pub_msg;
    pub_msg.data = "2";
    qnode.control_flow_pub.publish(pub_msg);
}


void MainWindow::on_Addentry_clicked()
{
    int res;
    int current_col=ui->tableWidget->columnCount()-1;
    add_entry_dialog ad(this);
    res=ad.exec();
    if (res==QDialog::Rejected)
        return;
    QString a = ad.barcode();

    barcode_numbers.push_back(ad.barcode());
    TestTube_slots.push_back(ad.testtube_slot_no());
    TestStrip_slots.push_back(ad.teststrip_slot_no());
    Test_Times.push_back(ad.test_time());
    Comments.push_back(ad.comments());

    ui->tableWidget->insertColumn(1);
    ui->tableWidget->setItem(BARCODE,current_col,new QTableWidgetItem(barcode_numbers.back()));
    ui->tableWidget->setItem(TESTTUBE,current_col,new QTableWidgetItem(QString::number(TestTube_slots.back())));
    ui->tableWidget->setItem(TESTSTRIP,current_col,new QTableWidgetItem(QString::number(TestStrip_slots.back())));
    ui->tableWidget->setItem(TIME,current_col,new QTableWidgetItem(QString::number(Test_Times.back())));
    ui->tableWidget->setItem(COMMENT,current_col,new QTableWidgetItem(Comments.back()));





}

void MainWindow::on_SaveTest_clicked()
{
    QString fpath= ui->filepath->toPlainText();
    std::string filepath = fromQString(fpath);
    printf("%s",filepath);
    if (filepath.size()==0)
        return;
//    filepath="/home/gokul/test.csv";
    std::ofstream TFile(filepath);
    TFile<<"Barcode_numbers"<<","<<"TestTube_Slots"<<","<<"TestStrip_slots"<<","<<"TestTime"<<","<<"Comments"<<"\n";
    for (int i=0;i<barcode_numbers.size();i++)
    {
        TFile<<fromQString(barcode_numbers[i])<<","<<TestTube_slots[i]<<","<<TestStrip_slots[i]<<","<<Test_Times[i]<<","<<fromQString(Comments[i])<<"\n";
    }
    TFile.close();
}

void MainWindow::on_Cleartest_clicked()
{
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->clearContents();
    barcode_numbers.clear();
    TestTube_slots.clear();
    TestStrip_slots.clear();
    Test_Times.clear();
    Comments.clear();
}

void MainWindow::on_LoadTest_clicked()
{
 return;
}



void MainWindow::on_Runtest_clicked()
{

}
