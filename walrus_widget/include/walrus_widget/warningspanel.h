#ifndef WARNINGSPANEL_H
#define WARNINGSPANEL_H

#include <tr1/unordered_map>
// #include <unordered_map> //for c++11

#include <QFrame>
#include <QHBoxLayout>

#include "warning.h"
typedef std::tr1::unordered_map<std::string , Warning*> warnings_dict;
/*
template < class Key,                                    // unordered_map::key_type
           class T,                                      // unordered_map::mapped_type
           class Hash = std::tr1::hash<Key>,                       // unordered_map::hasher
           class Pred = std::equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = std::allocator< std::pair<const Key,T> >  // unordered_map::allocator_type
           > class unordered_map;

typedef unordered_map<const QString , Warning*> warnings_dict;
*/
class WarningsPanel : public QFrame
{
    Q_OBJECT

public:
    explicit WarningsPanel(QWidget *parent = 0);
    virtual ~WarningsPanel(){}
    void addWarning(std::string name, QString image);

public Q_SLOTS:
    void showWarning(std::string name);
    void hideWarning(std::string name);

protected:
   warnings_dict warnings_dict_;
   void resizeEvent(QResizeEvent *event);

private:
    QHBoxLayout* warnings_layout_;
    std::vector<std::string> warnings_keys_ ;

};

#endif // WARNINGSPANEL_H
