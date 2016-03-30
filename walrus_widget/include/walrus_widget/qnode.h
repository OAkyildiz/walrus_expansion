/**
 * @file /include/walrus_widget/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/* Ifdefs */

#ifndef walrus_widget_QNODE_H
#define walrus_widget_QNODE_H

/*Includes */

#include <ros/ros.h>
#include <string>

#include <vector>
#include <set>
#include <boost/shared_ptr.hpp>

#include <QThread>
#include <QStringListModel>
#include <QImage>


#include "std_msgs/String.h"
#include "diagnostic_aggregator/aggregator.h"
#include "nav_msgs/Odometry.h"

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include "visualization_msgs/Marker.h"
/* Namespaces*/

//Q_DECLARE_METATYPE(std::string);

namespace qnode {

struct camera{

    QString title;
    std::string topic;

};


struct diagnostics{


    float t_CPU;
    int batteries[4];
    float cng_level;
    float co_level;
    float humidity;
    float h2_level;
    float lpg_level;
    float tenv;


    bool joystick;
};


const int camera_count = 5;

/* Class*/

class QNode : public QThread {
    Q_OBJECT
public:


    QNode(int argc, char** argv,bool verbose = true );
	virtual ~QNode();

    //boost::shared_ptr<diagnostic_msgs::DiagnosticStatus> diagnosticReport;
    const std::vector<boost::shared_ptr<diagnostic_msgs::DiagnosticStatus> > diagnosticReport;

	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

    /* Logging */
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);
    QImage* PixmapModel (){return px_;}

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

    void updateBattery();
    void updateSignal();
    void Update_Image(QImage* image);
    void Update_Video_Title(QString* title);
    void Update_Speed(double x, double y, double z);
    void Update_Pose(double x, double y, double z, double qx, double qy, double qz, double qw);

public Q_SLOTS:
    //mayhaps an inrementer instead of a selector int
    void cameraTopicChanged(int i);

    //updates here
private:
	int init_argc;
	char** init_argv;

    //generic flag for debug
    bool _first;
    //flag for printing diagnostic msgs
    bool _verbose;

    ros::Publisher console_pub_;
    ros::Publisher marker_pub_;

    ros::Subscriber diagnostics_sub_;
    ros::Subscriber odom_sub_;
    image_transport::Subscriber image_sub_;

    //cameras attr.
    camera cameras[camera_count];

    QImage* px_;
    image_transport::ImageTransport* it_;
    visualization_msgs::Marker* robot_marker_;

    const geometry_msgs::Vector3* vel_;
    QStringListModel logging_model;

//	void chatterCallback(const std_msgs::String::ConstPtr &msg);

    QImage cvtCvMat2QImage(const cv::Mat &image);


    //3 node handles (odom, rviz?, diag)
    void setupNode();
    void defineCameras();
    void diagnosticsCallback(const diagnostic_msgs::DiagnosticArray::ConstPtr& diag_msg);
    void odomCallback(const nav_msgs::Odometry::ConstPtr &odom_msg);
    void cameraCallback(const sensor_msgs::ImageConstPtr& msg);

    void initRobotMarker();
    void updateRobotMarker(const geometry_msgs::Pose* pose);


};

}  // namespace qnode

#endif /* walrus_widget_QNODE_H*/
