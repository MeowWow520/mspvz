#pragma once

#ifndef WAVE_H
#define WAVE_H
#include <vector>
#include "Enemy/EnemyType.h"



/** Wave.h 
 * 
 */
struct Wave {

    struct SpawnEvent { 
        double Interval{0.0};
        int SpawnPoint{0};
        EnemyType _EnemyType{EnemyType::Silme};
    };
    double Rawards{0.0};
    double Interval{0.0};
    std::vector<SpawnEvent> SpawnEventList;
    
};

#endif // !WAVE_H