
#include "../common/GeoVizClient.h"
#include <geoviz/camera/MousePanCameraManipulator.h>
#include <geoviz/camera/MouseZoomCameraManipulator.h>
#include <geoviz/camera/MouseRotateCameraManipulator.h>

#include <android_native_app_glue.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <NDKHelper.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <jni.h>
#include <mutex>
#include <deque>
#include <chrono>
#include <functional>
#include <cstdlib>

class GeoVizWidget : public GeoVizClient, public GeoVizClientListener
{
public:
    GeoVizWidget(android_app* app);
    ~GeoVizWidget() override;

    static GeoVizWidget* instance();

    int x() const;
    int y() const;
    int width() const;
    int height() const;

    bool isInitialized() const;
    void initialize();

    bool hasFocus() const;
    void setFocus(bool hasFocus);

    ANativeWindow* window() const;
    void setWindow(ANativeWindow* window);

    void onLayerSwitched(const std::string& name) override;
    void onLayerGroupSwitched(const std::string& name) override;
    void onViewHovered(int x, int y) override;
    void onViewClicked(int x, int y) override;

    void runOnRenderThread(const std::function<void()>& action);
    void processActions(size_t kMaxIntervalInMsecs = 5);

private:
    // application cmd callbacks
    void onAppCmd(uint32_t cmd);
    void onInputChanged();
    void onInitWindow();
    void onTermWindow();
    void onWindowResized();
    void onWindowRedrawNeeded();
    void onContentRectChanged();
    void onGainedFocus();
    void onLostFocus();
    void onConfigChanged();
    void onLowMemory();
    void onStart();
    void onResume();
    void onSaveState();
    void onPause();
    void onStop();
    void onDestroy();

    int32_t onInputEvent(AInputEvent* event);

private:
    void destroy();

    android_app* m_app;
    ANativeWindow* m_window{nullptr};
    bool m_initialized = false;
    bool m_hasFocus = false;

    std::recursive_mutex m_actionsMutex;
    std::deque<std::function<void()>> m_actions;
    ndk_helper::DragDetector m_dragDetector;
    ndk_helper::PinchDetector m_pinchDetector;
    ndk_helper::DoubletapDetector m_doubletapDetector;

    static GeoVizWidget* s_instance;
};

GeoVizWidget* GeoVizWidget::s_instance;

GeoVizWidget::GeoVizWidget(android_app* app)
    : GeoVizClient(this)
    , m_app(app)
{
    assert(!s_instance);
    s_instance = this;
    app->userData = this;

    app->onAppCmd = [](android_app* app, int32_t cmd)
    {
        GeoVizWidget* widget = static_cast<GeoVizWidget*>(app->userData);
        widget->onAppCmd(cmd);
    };

    app->onInputEvent = [](android_app* app, AInputEvent* event) -> int32_t
    {
        const auto eventType = AInputEvent_getType(event);
        if (eventType != AINPUT_EVENT_TYPE_MOTION)
            return 0;
        GeoVizWidget* widget = static_cast<GeoVizWidget*>(app->userData);
        return widget->onInputEvent(event);
    };
}

GeoVizWidget::~GeoVizWidget()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

GeoVizWidget* GeoVizWidget::instance()
{
    return s_instance;
}

void GeoVizWidget::onLayerSwitched(const std::string& name)
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onLayerGroupSwitched(const std::string& name)
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onViewHovered(int x, int y)
{
}

void GeoVizWidget::onViewClicked(int x, int y)
{
}

int GeoVizWidget::x() const
{
    return 0;
}

int GeoVizWidget::y() const
{
    return 0;
}

int GeoVizWidget::width() const
{
    return m_window ? ANativeWindow_getWidth(m_window) : 0;
}

int GeoVizWidget::height() const
{
    return m_window ? ANativeWindow_getHeight(m_window) : 0;
}

ANativeWindow* GeoVizWidget::window() const
{
    return m_window;
}

void GeoVizWidget::setWindow(ANativeWindow* window)
{
    m_window = window;
}

bool GeoVizWidget::isInitialized() const
{
    return m_initialized;
}

void GeoVizWidget::initialize()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    assert(!m_initialized);
    assert(m_app);
    assert(m_app->activity);
    assert(m_app->window);

    setWindow(m_app->window);

    GeoVizClient::GraphicsOptions options;
    options.jvm = m_app->activity->vm;
    options.activity = m_app->activity->clazz;
    options.window = m_app->window;
    options.resourcesPath = "/sdcard/data"; // ### fixme
    GeoVizClient::initialize(options);
    m_initialized = true;
}

void GeoVizWidget::destroy()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    m_view = geoviz::View();
    m_model = geoviz::Model();
}

bool GeoVizWidget::hasFocus() const
{
    return m_hasFocus;
}

void GeoVizWidget::setFocus(bool hasFocus)
{
    m_hasFocus = hasFocus;
}

void GeoVizWidget::onInputChanged()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onInitWindow()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    setWindow(m_app->window);
}

void GeoVizWidget::onTermWindow()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onWindowResized()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    setWindow(m_app->window);
}

void GeoVizWidget::onWindowRedrawNeeded()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onContentRectChanged()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onGainedFocus()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    setFocus(true);
}

void GeoVizWidget::onLostFocus()
{
    NT_LOG_INFO("%s", __FUNCTION__);
    setFocus(false);
}

void GeoVizWidget::onConfigChanged()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onLowMemory()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onStart()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onResume()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onSaveState()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onPause()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onStop()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onDestroy()
{
    NT_LOG_INFO("%s", __FUNCTION__);
}

void GeoVizWidget::onAppCmd(uint32_t cmd)
{
    //NT_LOG_INFO("%s", __FUNCTION__);
    switch (cmd)
    {
    case APP_CMD_INPUT_CHANGED:
        onInputChanged();
        break;
    case APP_CMD_INIT_WINDOW:
        onInitWindow();
        break;
    case APP_CMD_TERM_WINDOW:
        onTermWindow();
        break;
    case APP_CMD_WINDOW_RESIZED:
        onWindowResized();
        break;
    case APP_CMD_WINDOW_REDRAW_NEEDED:
        onWindowRedrawNeeded();
        break;
    case APP_CMD_CONTENT_RECT_CHANGED:
        onContentRectChanged();
        break;
    case APP_CMD_GAINED_FOCUS:
        onGainedFocus();
        break;
    case APP_CMD_LOST_FOCUS:
        onLostFocus();
        break;
    case APP_CMD_CONFIG_CHANGED:
        onConfigChanged();
        break;
    case APP_CMD_LOW_MEMORY:
        onLowMemory();
        break;
    case APP_CMD_START:
        onStart();
        break;
    case APP_CMD_RESUME:
        onResume();
        break;
    case APP_CMD_SAVE_STATE:
        onSaveState();
        break;
    case APP_CMD_PAUSE:
        onPause();
        break;
    case APP_CMD_STOP:
        onStop();
        break;
    case APP_CMD_DESTROY:
        onDestroy();
        break;
    }
}

void GeoVizWidget::runOnRenderThread(const std::function<void()>& action)
{
    m_actionsMutex.lock();
    m_actions.push_back(action);
    m_actionsMutex.unlock();
}

void GeoVizWidget::processActions(size_t kMaxIntervalInMsecs)
{
    using namespace std::chrono;
    auto start = steady_clock::now();
    m_actionsMutex.lock();
    while(!m_actions.empty()) {
        auto event = m_actions.front();
        m_actions.pop_front();
        m_actionsMutex.unlock();
        event();
        m_actionsMutex.lock();
        duration<double> delta = steady_clock::now() - start;
        auto elapsed = duration_cast<milliseconds>(delta);
        if (elapsed.count() > kMaxIntervalInMsecs)
            break;
    }
    m_actionsMutex.unlock();
}

int32_t GeoVizWidget::onInputEvent(AInputEvent* event)
{
    if (AInputEvent_getType(event) != AINPUT_EVENT_TYPE_MOTION)
        return 0;

    ndk_helper::GESTURE_STATE dragState = m_dragDetector.Detect(event);

    if (dragState & ndk_helper::GESTURE_STATE_START)
    {
        ndk_helper::Vec2 v;
        m_dragDetector.GetPointer(v);
        float x, y;
        v.Value(x, y);
        mousePress(geoviz::Vector2f(x, y), MouseButton::Left);
    }
    else if (dragState & ndk_helper::GESTURE_STATE_MOVE)
    {
        ndk_helper::Vec2 v;
        m_dragDetector.GetPointer(v);
        float x, y;
        v.Value(x, y);
        mouseMove(geoviz::Vector2f(x, y), MouseButton::Left);
    }
    else if (dragState & ndk_helper::GESTURE_STATE_END)
    {
        ndk_helper::Vec2 v;
        m_dragDetector.GetPointer(v);
        float x, y;
        v.Value(x, y);
        mouseRelease(geoviz::Vector2f(x, y), MouseButton::Left);
    }

    return 1;
}

extern "C" {
JNIEXPORT void JNICALL Java_com_here_geoviz_GeoVizView_nativeInit(JNIEnv* env, jobject clazz,
                                                                  jobject activity, jobject surface)
{
    auto widget = GeoVizWidget::instance();
    assert(widget);
    widget->initialize();
}

JNIEXPORT void JNICALL Java_com_here_geoviz_GeoVizView_nativeResize(JNIEnv* env, jobject obj,
                                                                    jint width, jint height)
{
    // ### TODO
}

JNIEXPORT void JNICALL Java_com_here_geoviz_GeoVizView_nativeStep(JNIEnv* env, jobject obj)
{
    auto widget = GeoVizWidget::instance();
    assert(widget);

    if (widget->isInitialized() /*&& widget->hasFocus()*/)
    {
        widget->processActions();
        widget->updateCamera(widget->x(), widget->y(), widget->width(), widget->height());
        widget->draw();
    }
}

void android_main(android_app* app) // ### TODO: remove
{
    app_dummy();

    GeoVizWidget widget(app);
    while (true)
    {
        int id, events;
        android_poll_source* source;
        while ((id = ALooper_pollAll(widget.hasFocus() ? 0 : -1, nullptr, &events, (void**)&source) >= 0))
        {
            if (source)
                source->process(app, source);

            if (app->destroyRequested)
            {
                // widget.destroy();
                return;
            }
        }
    }
}

} // extern "C"
