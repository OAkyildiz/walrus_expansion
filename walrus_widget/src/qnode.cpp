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

#include "../include/walrus_widget/qnode.hpp"

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
                chatter_publisher.publish(msg);
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
    void QNode::setupNode(){
        ros::start(); // explicitly needed since our nodehandle is going out of scope.
        ros::NodeHandle diag_handle;
        log(Info,std::string("Master:")+ros::master::getURI()+std::string(",\n Host:")+ros::network::getHost());

        // Add your ros communications here.
        diagnostics_sub = diag_handle.subscribe("/diagnostics_agg", 1000, &QNode::diagnosticsCallback, this);
        chatter_publisher = diag_handle.advertise<std_msgs::String>("chatter", 1000);
        start();
    }

    void QNode::diagnosticsCallback(const diagnostic_msgs::DiagnosticArray::ConstPtr& diag_msg)
    {
        bool read = false;
//        for (unsigned int j = 0; j < diag_msg->status.size(); ++j)
//        {
//          analyzed = false;
//          diagnosticReport diagnostic_aggregator::item(new StatusItem(&diag_msg->status[j]));
            //diagnostic_msgs::DiagnosticStatus* stat= &diag_msg->status[j];
       log(Info,std::string("Diag received"));


//          if (analyzer_group_->match(item->getName()))
//            analyzed = analyzer_group_->analyze(item);

//          if (!analyzed)
//            other_analyzer_->analyze(item);
//        }
    }
}  // namespace qnode



