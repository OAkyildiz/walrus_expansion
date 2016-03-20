/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/network.h>
#include <sstream>
#include <typeinfo>

#include <QElapsedTimer>

#include "walrus_widget/qnode.h"

#include <sensor_msgs/image_encodings.h>

//#include <diagnostic_msgs/DiagnosticArray.h>
//#include <diagnostic_msgs/DiagnosticStatus.h>
//#include <diagnostic_msgs/KeyValue.h>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qnode {

/*****************************************************************************
** Implementation
*****************************************************************************/
//TO DO: parameterize NodeHandel nh for qnode, so it is reachable
//      -- This way ros::shutdown and start() can be changed to preferred methods.

    QNode::QNode(int argc, char** argv ) :
        init_argc(argc),
        init_argv(argv)
    {}

    QNode::~QNode() {
        if(ros::isStarted()) {
            ros::shutdown(); // explicitly needed since we use ros::start();
            ros::waitForShutdown();
        }
        wait();
    }

    bool QNode::init() {
        ros::init(init_argc,init_argv,"walrus_widget");
        if ( ! ros::master::check() ) {
            return false;
        }
        setupNode();
        return true;
    }

    bool QNode::init(const std::string &master_url, const std::string &host_url) {
        std::map<std::string,std::string> remappings;
        remappings["__master"] = master_url;
        remappings["__hostname"] = host_url;
        ros::init(remappings,"walrus_widget");
        if ( ! ros::master::check() ) {
            log(Info,std::string("Cannot communicate with the ROSMASTER!"));
            return false;
        }
        setupNode();
        return true;
    }

    void QNode::run() {
        ros::Rate loop_rate(1);
        int count = 0;
        while ( ros::ok() ) {

            if(false){
                std_msgs::String msg;
                std::stringstream ss;
                ss << "rosnode " << count;
                msg.data = ss.str();
                console_pub_.publish(msg);
                log(Info,std::string("I sent: ")+msg.data);
            }
            ros::spinOnce();
            loop_rate.sleep();
            ++count;
        }
        std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
        Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
    }


    void QNode::log( const LogLevel &level, const std::string &msg) {
        logging_model.insertRows(logging_model.rowCount(),1);
        std::stringstream logging_model_msg;
        switch ( level ) {
        case(Debug) : {
            ROS_DEBUG_STREAM(msg);
            logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
            break;
        }
        case(Info) : {
            ROS_INFO_STREAM(msg);
            logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
            break;
        }
        case(Warn) : {
            ROS_WARN_STREAM(msg);
            logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
            break;
        }
        case(Error) : {
            ROS_ERROR_STREAM(msg);
            logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
            break;
        }
        case(Fatal) : {
            ROS_FATAL_STREAM(msg);
            logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
            break;
        }
        }
        QVariant new_row(QString(logging_model_msg.str().c_str()));
        logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
        Q_EMIT loggingUpdated(); // used to readjust the scrollbar
    }

    // Main ros node logic goes here
    // seperating nodes is an option!!!
    void QNode::setupNode(){
        ros::start(); // explicitly needed since our nodehandle is going out of scope.
        ros::NodeHandle handle;
        log(Info,std::string("Master:")+ros::master::getURI()+std::string(",\n Host:")+ros::network::getHost());

        px_ = new QImage();
        image_transport::ImageTransport it_(handle);

        // Add your ros communications here.
        diagnostics_sub_ = handle.subscribe("/diagnostics_agg", 2000, &QNode::diagnosticsCallback, this);
        odom_sub_ = handle.subscribe("/base_epos/drive_controller/odom", 1000, &QNode::odomCallback, this);
        image_sub_ = it_.subscribe("/usb_cam/image_raw", 1, &QNode::cameraCallback, this
                                   );
        marker_pub_ = handle.advertise<visualization_msgs::Marker>("robot_marker", 1000);
        console_pub_ = handle.advertise<std_msgs::String>("chatter", 1000);

        initRobotMarker();
        start();

    }

    void QNode::diagnosticsCallback(const diagnostic_msgs::DiagnosticArray::ConstPtr& diag_msg)
    {
      // const std::vector<diagnostic_msgs::DiagnosticStatus_<std::allocator<void> >, std::allocator<diagnostic_msgs::DiagnosticStatus_<std::allocator<void> > > >*
        const std::vector<diagnostic_msgs::DiagnosticStatus>  *stats;


            for(int i=0;i<10;i++){
                const diagnostic_msgs::DiagnosticStatus* stat= &diag_msg->status[i];
                log(Info, stat->name + stat->hardware_id + stat->message);
            }
    }

    void QNode::odomCallback(const nav_msgs::Odometry::ConstPtr &odom_msg)
    {

        updateRobotMarker(&odom_msg->pose.pose);
        marker_pub_.publish(*robot_marker_);
    }

    void QNode::initRobotMarker()
    {
        robot_marker_ = new visualization_msgs::Marker();

        robot_marker_->header.frame_id = "walrus/base_footprint";
        robot_marker_->header.stamp = ros::Time::now();

        robot_marker_->ns = "radar";
        robot_marker_->id = 0;
        robot_marker_->type = visualization_msgs::Marker::TRIANGLE_LIST;
        robot_marker_->action = visualization_msgs::Marker::ADD;

        robot_marker_->pose = geometry_msgs::Pose();

        geometry_msgs::Point p1= geometry_msgs::Point();
        geometry_msgs::Point p2 = geometry_msgs::Point();
        geometry_msgs::Point p3 = geometry_msgs::Point();

        p1.x = 0.5;  p1.y = 0;      p1.z=0;
        p2.x = 0;    p2.y = 0.2;    p2.z=0;
        p3.x = 0;    p3.y = -0.2;   p3.z=0;

        robot_marker_->points.push_back(p1);
        robot_marker_->points.push_back(p2);
        robot_marker_->points.push_back(p3);

        robot_marker_->scale.x = 1;
        robot_marker_->scale.y = 1;
        robot_marker_->scale.z = 1;

        robot_marker_->color.a = 1.0; // Don't forget to set the alpha!
        robot_marker_->color.r = 0.9;
        robot_marker_->color.g = 0.05;
        robot_marker_->color.b = 0.05;
    }


    void QNode::updateRobotMarker(const geometry_msgs::Pose* pose)
    {

        robot_marker_->header.stamp = ros::Time::now();
        robot_marker_->pose = *pose;

        //rgba
    }

    //Camera stuff

    QImage QNode::cvtCvMat2QImage(const cv::Mat &image)
    {
        QImage qtemp;
        if(!image.empty() && image.depth() == CV_8U)
        {
            const unsigned char* data = image.data;
            qtemp = QImage(image.cols, image.rows, QImage::Format_RGB32);
            for(int y = 0; y < image.rows; ++y, data += image.cols*image.elemSize())
            {
                for(int x = 0; x < image.cols; ++x)
                {
                    QRgb* p = ((QRgb*)qtemp.scanLine (y)) + x;
                    *p = qRgb(data[x * image.channels()+2], data[x * image.channels()+1], data[x * image.channels()]);
                }
            }
        }
        else if(!image.empty() && image.depth() != CV_8U)
        {
            printf("Wrong image format, must be 8_bits\n");
        }

        //rgba
        return qtemp;
    }
    void QNode::cameraCallback(const sensor_msgs::ImageConstPtr& msg){

    //(const std_msgs::String::ConstPtr &msg) {
    //	ROS_INFO("I heard: [%s]", msg->data.c_str());
        cv_bridge::CvImagePtr cv_ptr;
          try
            {
              cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

            }
            catch (cv_bridge::Exception& e)
            {
              ROS_ERROR("cv_bridge exception: %s", e.what());
              return;
            }
        *px_ = cvtCvMat2QImage(cv_ptr->image);

        Q_EMIT Update_Image(px_);
    }



}  // namespace qnode



