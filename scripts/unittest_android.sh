timestamp="$(date +"%Y-%m-%d_%H-%M-%S")"
cd ~/structures_android_build/tests/unittests/bin

adb shell am force-stop com.structures.unittests

adb install -r unittests-debug.apk
#adb shell am instrument -w com.structures.unittests/.TestRunner
adb logcat -c
adb shell am start -n com.structures.unittests/.RunUnittests
#sleep 5
APP_IS_RUNNING=$(adb shell ps | grep unittests)
adb shell screencap -p /data/local/tmp/screen.png
adb pull /data/local/tmp/screen.png /home/mudryy/tmp/structures_screenshot_$timestamp.png

adb logcat -v time -d > /home/mudryy/tmp/structures_log_${timestamp}.txt

echo "Log file is written to /home/mudryy/tmp/structures_log_${timestamp}.txt"
adb pull /data/user/10/com.structures.unittests/files/example.txt /home/mudryy/tmp/out.xml
adb shell am force-stop com.structures.unittests.RunUnittests
adb shell pm uninstall com.structures.unittests

echo $APP_IS_RUNNING
if [ -z "$APP_IS_RUNNING" ]; then
    echo "unittest is crashed"
    exit -1
else
	echo "unittest app smoke test successfully passed"
fi
gedit /home/mudryy/tmp/structures_log_${timestamp}.txt