/**
 * @author Michael Quinlan
 *
 * This file was generated by Aldebaran Robotics ModuleGenerator
 */

#ifndef NAOINTERFACE_NAOINTERFACE_H
#define NAOINTERFACE_NAOINTERFACE_H

#include <alcore/alptr.h>
#include <alcommon/almodule.h>
#include <string>

#include <memory/Memory.h>
#include <memory/Lock.h>

#include <memory/FrameInfoBlock.h>
#include <memory/SensorBlock.h>
#include <memory/JointBlock.h>
#include <memory/JointCommandBlock.h>
#include <memory/LEDBlock.h>
#include <memory/WalkInfoBlock.h>
#include <memory/ALWalkParamBlock.h>
#include <memory/WalkRequestBlock.h>
#include <memory/SpeechBlock.h>

#include "dcmwrapper.h"
#include "almotionwrapper.h"

namespace AL
{
  class ALBroker;
  class ALMemoryFastAccess;
  class ALTextToSpeechProxy;
  class DCMProxy;
  class ALSonarProxy;
}

/**
 * DESCRIBE YOUR CLASS HERE
 */
class naointerface : public AL::ALModule
{
  public:
    /**
     * Default Constructor.
     */
     naointerface(AL::ALPtr<AL::ALBroker> broker, const std::string& name);

    /**
     * Destructor.
     */
    virtual ~naointerface();
    
    void start();
    void stop();
    
    double getSystemTime();

    void postProcess(); // called immediately after sensors arrives
    void preProcess(); // called before sending joint commands

    void initMemory();
    void initFastAccess();

    void populateSensors();

    void preProcessJoints();
    void postProcessJoints();
    
    void initSonar();

    // Used for fast memory access
    AL::ALPtr<AL::ALMemoryFastAccess> fast_sensor_access_;
    std::vector<std::string> sensor_keys_;
    std::vector<float> sensor_values_;

    // Class that handles most of the DCM calls
    DCMWrapper* dcmWrap_;
    ALMotionWrapper* al_motion_wrap_;

    AL::ALPtr<AL::ALSonarProxy> sonar_proxy_;
    AL::ALPtr<AL::ALTextToSpeechProxy> tts_proxy_;

    void initPositions();
    void setAllPositions(float positions[NUM_JOINTS]);
   
    // Used for postprocess sync with the DCM
    ProcessSignalConnection dcm_postprocess_connection_;
    ProcessSignalConnection dcm_preprocess_connection_;

    Memory *memory_;
    Lock *motion_lock_;

    FrameInfoBlock *frame_info_;
    SensorBlock* raw_sensors_;
    JointBlock* raw_joint_angles_;
    JointCommandBlock* raw_joint_commands_;
    JointBlock* processed_joint_angles_;
    JointCommandBlock* processed_joint_commands_;
    LEDBlock* led_commands_;
    WalkInfoBlock* walk_info_;
    ALWalkParamBlock* al_walk_param_;
    WalkRequestBlock* walk_request_;
    SpeechBlock *speech_;
};

#endif  // NAOINTERFACE_NAOINTERFACE_H

