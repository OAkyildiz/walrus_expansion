/**
 * @file /include/walrus_widget/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef walrus_widget_QNODE_HPP_
#define walrus_widget_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>

#include <QThread>
#include <QStringListModel>

#include "std_msgs/String.h"
#include "diagnostic_aggregator/aggregator.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qnode {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();

    //boost::shared_ptr<diagnostic_msgs::DiagnosticStatus> diagnosticReport;
    const std::vector<boost::shared_ptr<diagnostic_msgs::DiagnosticStatus> > diagnosticReport;

	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

    void updateBattery();
    void updateSignal();


    //updates here
private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
    ros::Subscriber diagnostics_sub;
    QStringListModel logging_model;

    //3 node handles (odom, rviz?, diag)
    void setupNode();
    void diagnosticsCallback(const diagnostic_msgs::DiagnosticArray::ConstPtr& diag_msg);
};

}  // namespace qnode

#endif /* walrus_widget_QNODE_HPP_ */
