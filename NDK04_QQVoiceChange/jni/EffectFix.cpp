#include "inc/fmod.hpp"
#include "org_fmod_example_EffectUtils.h"
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>

#include<android/log.h>
#include <android/log.h>
#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"wzwjni",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"wzwjni",FORMAT,##__VA_ARGS__);


#define MODE_NORMAL    0
#define MODE_LUOLI     1
#define MODE_DASHU     2
#define MODE_JINGSONG  3
#define MODE_GAOGUAI   4
#define MODE_KONGLING  5

using namespace FMOD;
using namespace std;

//static bool  isStop = false;

//void* stop_thread(void *arg){
//     Channel   *channel = (Channel*)arg;
//    //线程执行体
//    //每秒钟判断一下是否停止播放
//    while(!isStop){
//       //单位是微妙
//       usleep(1000 *1000);
//     }
//    //停止播放
//    channel->stop();
//   return 0;
//}


void releaseFmod(System *system, Sound *sound){
      //释放资源
      sound->release();
      system->close();
      system->release();
}

static Channel   *channel  = 0;

JNIEXPORT void JNICALL Java_org_fmod_example_EffectUtils_fix
  (JNIEnv *env, jclass jcls, jstring path_jstr, jint type){

    System    *system             = 0;
    Sound     *sound              = 0;
    DSP       *dsp                = 0;
//    Channel   *channel            = 0; //音频通道
    void      *extradriverdata    = 0; //额外的数据
    bool      isPlaying           = true;
    float     frequency           = 0;

    const char* path_cstr = env->GetStringUTFChars(path_jstr, JNI_FALSE);
    try {
         //初始化
          System_Create(&system);
          system->init(32, FMOD_INIT_NORMAL, extradriverdata);


          //创建声音
          system->createSound(path_cstr, FMOD_DEFAULT, 0, &sound);

          switch(type){
           //原生播放
           case MODE_NORMAL:
               isPlaying = true;
               system->playSound(sound, 0, false, &channel);
               LOGI("%s", path_cstr);
               break;
           //萝莉
           case MODE_LUOLI:
                isPlaying = true;
               //DSP_digital_progress
               //dsp -> 音效 创建fmod中预定义好的音效
               //FMOD_DSP_TYPE_PITCHSHIFT DSP 提升或降低音调 用的一种音效
              system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
               //设置音调的参数
               dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 2.2);
               //播放
               system->playSound(sound, 0, false, &channel);
               //添加到channel
               channel->addDSP(0, dsp);
               LOGI("%s", path_cstr);
               break;
           //大叔
           case MODE_DASHU:
              isPlaying = true;
              system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
              //设置音调的参数
              dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.7);
              //播放
              system->playSound(sound, 0, false, &channel);
              //添加到channel
              channel->addDSP(0, dsp);
              LOGI("%s", path_cstr);
              break;

           case MODE_JINGSONG:
            //紧张
             isPlaying = true;
             system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
             dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
             system->playSound(sound, 0, false, &channel);
             channel->addDSP(0, dsp);
             break;

           //搞怪
           case MODE_GAOGUAI:
             isPlaying = true;
              //播放
              system->playSound(sound, 0, false, &channel);
              //获得语速
              channel->getFrequency(&frequency);
              //加快语速
              frequency = frequency * 1.6;
              channel->setFrequency(frequency);

             break;
           //空灵
           case MODE_KONGLING:
             isPlaying = true;
              //回声
              system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
              //设置回声延时
              dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
              //设置回声次数
              dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
              system->playSound(sound, 0, false, &channel);
              channel->addDSP(0, dsp);
              break;
           default:
               break;
          }
    }catch (...) {
         LOGE("%s","发生异常");
         releaseFmod(system, sound);
     }

    system->update();
   // pthread_t pt;
    //pthread_create(&pt, NULL, &stop_thread, (void*)channel);


    //每秒钟判断一下是否在播放
    while(isPlaying){
      channel->isPlaying(&isPlaying);
      //单位是微妙
      usleep(1000 *1000);
    }

    //释放资源
    env->ReleaseStringUTFChars(path_jstr,path_cstr);

    releaseFmod(system, sound);
}


JNIEXPORT void JNICALL Java_org_fmod_example_EffectUtils_stopPaly
  (JNIEnv *env, jclass jcls){
     channel->stop();
}
