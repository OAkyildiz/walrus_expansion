#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include <QObject>

class RobotModel : public QObject
{
    Q_OBJECT
public:
    RobotModel();
    
    void construcDiagnostics();

protected:

//    boom_;
//    chassis_;
//    computer_;
//    drive_;
//    embedded_boards_;
//    environment_;
//    IMU_;
//    networking_;
//    pods_;
//    power_;
//    other_;
    
    int _diag_size;
    int _diag_names;
    
    int _battery_index[4];
    int _cpu_res_index;
    int _cpu_temp_index;
    int _env_index[4];

};

#endif // ROBOTMODEL_H
