package nchu.water_saver;

import android.util.Log;

public class srcAppLog {
    private static final String APP_TAG = "AudioRecorder";

    public static int logString(String message){
        return Log.i(APP_TAG,message);
    }
}
