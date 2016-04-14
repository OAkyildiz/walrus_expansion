#ifndef RADAR_H
#define RADAR_H

#include <QFrame>
#include <QLabel>

#include "qnode.h"


#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/default_plugin/view_controllers/fixed_orientation_ortho_view_controller.h"

#include "rviz/display.h"

namespace rviz
{
class Display;
class RenderPanel;
class VisualizationManager;
class Config;
class YamlConfigReader;
class FixedOrientationOrthoViewController;
}

class Radar : public QFrame
{
public:
    explicit Radar(QWidget* parent = 0, qnode::QNode* qnode = 0);
    virtual ~Radar();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    qnode::QNode* qnode_;

    rviz::VisualizationManager* manager_;
    rviz::RenderPanel* render_panel_;
    rviz::FixedOrientationOrthoViewController* view_;
    QLabel* bound_;

    rviz::Display* grid_;
    rviz::Display* obstacles_;
    rviz::Display* robot_marker_;

};

#endif // RADAR_H
