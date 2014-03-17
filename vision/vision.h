#ifndef VISION_H
#define VISION_H

#include <cmath>
#include <vector>

#include <Vision/BinaryImage.h>
#include <Vision/AxisCamera.h>
#include <networktables/NetworkTable.h>
#include <Task.h>
//#include <nivision.h>

class vision {
private:
    NetworkTable* table;
    Task vision_task;
public:
    vision();
    ~vision();
    
    bool continuousRunning;
    bool isContinuousRunning();
    
    void startContinuous();
    void stopContinuous();
    
    static int vision_entry(void*);
    
    static void processContinuous(int);
    int getHotGoal();
    
};

#endif

