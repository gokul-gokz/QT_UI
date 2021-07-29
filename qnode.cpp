#include "qnode.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <string>


QNode::QNode(int argc, char** argv):
    init_argc(argc),
    init_argv(argv)
    {}

QNode::~QNode(){
    if(ros::isStarted()){
        ros::shutdown(); //
    }
    wait();
}

bool QNode::init() {
    ros::init(init_argc, init_argv, "QtRosNode");
    if ( !ros::master::check()) {
        return false;
    }
    ros::start();
    ros::NodeHandle node;
    subs = node.subscribe("/Diagnostic_msgs", 5, &QNode::topicCallback, this);
    sub_image = node.subscribe("/image", 5, &QNode::imageCallback, this);
    pub = node.advertise<std_msgs::String>("/chatter", 5);
    control_flow_pub = node.advertise<std_msgs::String>("/control_flow", 5);
    test_params_pub = node.advertise<r2d2_params::TestParams>("/test_params",5);
    start();
    std::cout << "Successfully initialized node." << std::endl;
    return true;
}

void QNode::run() {
    // QThread function
    ros::Rate loop_rate(10); // too fast loop rate crashed the GUI
    std::cout << "Node is running." << std::endl;
    while (ros::ok()){
        ros::spinOnce();
        loop_rate.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    //Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}

void QNode::topicCallback(const std_msgs::String::ConstPtr &msg){
    this->sub_message = msg->data.c_str();
    Q_EMIT msgSubscribed();
}

void QNode::imageCallback(const sensor_msgs::Image::ConstPtr &msg){
    QImage source_image(&msg->data[0], msg->width, msg->height, QImage::Format_RGB888);
    this->img_message=source_image;
    Q_EMIT ImagemsgSubscribed();
}

