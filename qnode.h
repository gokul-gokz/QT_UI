#ifndef QNODE_H
#define QNODE_H

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#include <std_msgs/String.h>
#endif
#include <sensor_msgs/Image.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <QImage>
#include <TestParams.h>
#include <Params.h>

class QNode : public QThread {
    Q_OBJECT

public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    void run();
    ros::Publisher pub;
    ros::Publisher control_flow_pub;
    ros::Publisher test_params_pub;

    // callback
    void topicCallback(const std_msgs::String::ConstPtr& msg);
    void imageCallback(const sensor_msgs::Image::ConstPtr &msg);

    // Variables:
    std::string sub_message = "";
    std::string pub_message = "";
    std::string control_message="";
    QImage img_message;

    // Signals
Q_SIGNALS:
    void msgSubscribed();
    void ImagemsgSubscribed();


private:
    int init_argc;
    char** init_argv;
    ros::Subscriber subs;
    ros::Subscriber sub_image;



};

#endif // QNODE_H
