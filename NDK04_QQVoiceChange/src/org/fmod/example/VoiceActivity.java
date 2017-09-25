package org.fmod.example;

import java.io.File;

import org.fmod.FMOD;

import android.app.Activity;
import android.drm.DrmStore.Playback;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class VoiceActivity extends Activity implements OnClickListener, OnCheckedChangeListener {
   private  static final String TAG = "VoiceActivity";
   private TextView mNormalBtn;
   private TextView mLuoliBtn;
   private TextView mDashuBtn;
   private TextView mJingsongBtn;
   private TextView mGaoguaiBtn;
   private TextView mKonglingBtn;
   private TextView mStopBtn;
   private RadioGroup mRadioGroup;
   private String path = "file:///android_asset/xiaohuang.wav";

   public  boolean exitThread = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_voice);
        intiView();

        FMOD.init(this);
    }
    private void intiView(){
        mNormalBtn = (TextView)findViewById(R.id.voice_normal_tv);
        mLuoliBtn = (TextView)findViewById(R.id.voice_luoli_tv);
        mDashuBtn = (TextView)findViewById(R.id.voice_dashu_tv);
        mJingsongBtn = (TextView)findViewById(R.id.voice_jingsong_tv);
        mGaoguaiBtn = (TextView)findViewById(R.id.voice_gaoguai_tv);
        mKonglingBtn = (TextView)findViewById(R.id.voice_kongling_tv);
        mStopBtn = (TextView)findViewById(R.id.voice_stop_tv);
        mRadioGroup = (RadioGroup)findViewById(R.id.music_rg);


        mNormalBtn.setOnClickListener(this);
        mLuoliBtn.setOnClickListener(this);
        mDashuBtn.setOnClickListener(this);
        mJingsongBtn.setOnClickListener(this);
        mGaoguaiBtn.setOnClickListener(this);
        mKonglingBtn.setOnClickListener(this);
        mStopBtn.setOnClickListener(this);
        mRadioGroup.setOnCheckedChangeListener(this);

    }

    @Override
    protected void onDestroy(){
        FMOD.close();
     }


    @Override
    public void onClick(View v) {



      switch (v.getId()) {
          case R.id.voice_normal_tv:
              Toast.makeText(this, "原生", Toast.LENGTH_SHORT).show();
              EffectUtils.fix(path, EffectUtils.MODE_NORMAL);
              break;
          case R.id.voice_luoli_tv:
              Toast.makeText(this, "萝莉", Toast.LENGTH_SHORT).show();
              EffectUtils.fix(path, EffectUtils.MODE_LUOLI);
              break;
          case R.id.voice_dashu_tv:
              Toast.makeText(this, "大叔", Toast.LENGTH_SHORT).show();
              EffectUtils.fix(path, EffectUtils.MODE_DASHU);
              break;
          case R.id.voice_jingsong_tv:
              Toast.makeText(this, "惊悚", Toast.LENGTH_SHORT).show();

              //EffectUtils.fix(path, EffectUtils.MODE_JINGSONG);
              break;
          case R.id.voice_gaoguai_tv:
              Toast.makeText(this, "搞怪", Toast.LENGTH_SHORT).show();
              EffectUtils.fix(path, EffectUtils.MODE_GAOGUAI);
              break;
          case R.id.voice_kongling_tv:
              Toast.makeText(this, "空灵", Toast.LENGTH_SHORT).show();
              EffectUtils.fix(path, EffectUtils.MODE_KONGLING);
              break;
          case R.id.voice_stop_tv:
              //EffectUtils.stopPaly();
              break;
          default:
              break;
    }

    }
    @Override
    public void onCheckedChanged(RadioGroup group, int checkedId) {
         switch (group.getId()) {
        case R.id.music_rb1:
            path = "file:///android_asset/xiaohuang.wav";
            break;
       case R.id.music_rb2:
           path = "file:///android_asset/huanghun.mp3";
            break;
        default:
            path = "file:///android_asset/xiaohuang.wav";
            break;
        }
    }

}
