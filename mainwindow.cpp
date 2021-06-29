#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(int argc, char** argv, QWidget *parent) :
    QMainWindow(parent), qnode(argc, argv),
    ui(new Ui::MainWindow)
{
    qnode.init();
    ui->setupUi(this);
    mResourceDir = "../Images";
    QObject::connect(&qnode, SIGNAL(msgSubscribed()), this, SLOT(updateSubBox()));
    QObject::connect(&qnode, SIGNAL(ImagemsgSubscribed()), this, SLOT(updateGraphicsBox()));

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
