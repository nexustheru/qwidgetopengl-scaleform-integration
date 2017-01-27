#ifndef WIDGET_H
#define WIDGET_H

#include <includes.h>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void moving();
    bool event(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void glend();
    void saveGLState();
    void restoreGLState();
    //scaleform
    void setupgfx(const char* pfilename);
    void AdvanceRenderGfx();
    Ptr<Movie> returnmovies();
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer time;
    //scaleform
    Ptr<MovieDef>           pMovieDef;
    Ptr<Movie>              pMovie;
    Ptr<Render::GL::HAL>    pRenderHAL;
    Ptr<Render::Renderer2D> pRenderer;
    MovieDisplayHandle      hMovieDisplay;
    UInt32                  MovieLastTime;
};

using namespace std;

class OurFSCommandHandler : public FSCommandHandler
{
public:
    virtual void Callback(Movie* pmovie,const char* pcommand, const char* parg)
    {

        printf("FSCommand: %s, Args: %s", pcommand, parg);
    }
};

class OurExternalInterfaceHandler : public ExternalInterface
{
public:
    virtual void Callback(Movie* pmovieView,const char* methodName,const Value* args,unsigned argCount)
    {
        printf("ExternalInterface: %s, %d args: ",  methodName, argCount);
        for(unsigned i = 0; i < argCount; i++)
        {
            switch(args[i].GetType())
            {
            case Value::VT_Null:
                printf("NULL");
                break;
            case Value::VT_Boolean:
                printf("%s", args[i].GetBool() ? "true" : "false");
                break;
            case Value::VT_Number:
                printf("%3.3f", args[i].GetNumber());
                break;
            case Value::VT_String:
                printf("%s", args[i].GetString());
                break;
            default:
                printf("unknown");
                break;
            }
            printf("%s", (i == argCount - 1) ? "" : ", ");
        }
        printf("\n");
        //recives from flash
        if(strcmp(methodName, "foo") == 0 && argCount == 1 && args[0].GetType() == Value::VT_String)
                {
                    const char *sent = args[0].GetString();
                    qDebug() << sent;
                }
    }
};

class GFxPlayerLog : public GFx::Log
{
public:
    // We override this function in order to do custom logging.
    virtual void    LogMessageVarg(LogMessageType messageType, const char* pfmt, va_list argList)
    {
        // Output log to console
        qDebug() << (const char*)argList;
        vprintf(pfmt, argList);
    }
};

#endif // WIDGET_H
