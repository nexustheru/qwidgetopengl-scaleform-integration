#include "widget.h"
#include "ui_widget.h"

float Dist;
float m_distance;
float mx=NULL;
float my=NULL;
int lastX;
int lastY;
int xRot;
int yRot;
int lastzoom;
int xmove;
int ymove;
int lastmovex;
int lastmovey;
float keyx=0.0f;
float keyy=0.0f;
float keyz=0.0f;
UInt32  utime ;
float delta;
int len;

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    setAttribute( Qt::WA_OpaquePaintEvent, true);
    setAttribute( Qt::WA_PaintOnScreen, true);
    setMouseTracking(true);
    ui->setupUi(this);
}


void Widget::glend()
{
    connect(&time,SIGNAL(timeout()),this,SLOT(updateGL()));
    time.start(10);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_SPECULAR);
    glEnable(GL_AMBIENT);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DIFFUSE);
    glEnable(GL_SHININESS);
    glEnable(GL_COLOR);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClearColor(0,0,0,1);

}

void Widget::initializeGL()
{
   glend();
   setupgfx("C://Users//tess//Desktop//Ny mapp//jjj.swf");
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    moving();
    glutSolidTeapot(10.0);
    glPushAttrib(GL_DEPTH_BUFFER_BIT);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        AdvanceRenderGfx();
        glPopAttrib();
    time.start();
}

void Widget::resizeGL(int w, int h)
{
           glViewport(0,0,w,h);
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluPerspective(80.0f,(float)w/h,0.01,1000.0f);
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
           gluLookAt(0,0,5,0,0,0,0,1,0);
}

void Widget::moving()
{
           glTranslatef(0.0f, -6.0f, -50.0f);	// Move 40 Units And Into The Screen
           glTranslatef(0, 0, -m_distance);
           time.stop();
           glTranslatef(xmove/100,ymove/100,0);
           time.stop();
           glRotatef(xRot, 1, 0, 0);
           time.stop();
           glRotatef(yRot, 0, 1, 0);
           time.stop();
}

bool Widget::event(QMouseEvent *ev)
{
   return QGLWidget::event(ev);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
        int mxh = event->x();
        int myh = event->y();
        Ptr<Movie> clickedmovie=returnmovies();
        MouseEvent mevent(GFx::Event::MouseUp, 0, mxh, myh);
        clickedmovie->HandleEvent(mevent);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastX;
          int dy = event->y() - lastY;

          if (event->buttons() & Qt::LeftButton)
          {
              xRot += 3 * dy;
              yRot += 3 * dx;
          }
          else if (event->buttons() & Qt::RightButton)
          {
              xRot += 3 * dy;
              yRot += 3 * dx;
          }
          else if (event->buttons() & Qt::MiddleButton)
          {
              xmove += 3 * dx;
              ymove -= 3 * dy;

          }

          lastX = event->pos().x();
          lastY = event->pos().y();
          lastmovex = event->pos().x();
          lastmovey = event->pos().y();

          int mxh = event->x();
          int myh = event->y();
          Ptr<Movie> clickedmovie=returnmovies();
          MouseEvent mevent(GFx::Event::MouseMove, 0, mxh, myh);
          clickedmovie->HandleEvent(mevent);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
        lastX = event->pos().x();
        lastY = event->pos().y();
        lastmovex=event->pos().x();
        lastmovey=event->pos().y();

        int mxh = event->x();
        int myh = event->y();
        Ptr<Movie> clickedmovie=returnmovies();
        MouseEvent mevent(GFx::Event::MouseDown, 0, mxh, myh);
        clickedmovie->HandleEvent(mevent);
        //sends to flash
        bool bInvoked = pMovie->Invoke("setText", "");
}

void Widget::wheelEvent(QWheelEvent *event)
{
      m_distance += (event->delta()/120);
}

void Widget::saveGLState()
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
}

void Widget::restoreGLState()
{
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();
}

//mains
int main(int argc, char *argv[])
{
    ilInit();
    iluInit();
    ilutInit();
    SF::SysAllocMalloc am;
    GFx::System gfxInit(&am);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

Widget::~Widget()
{
    delete ui;
}

//scaleform
void Widget::setupgfx(const char *pfilename)
{

        len = strlen(pfilename);
        if(len <=0)
        {
            qDebug("theres no flash file input to render");
        }
        else
        {
            Loader gfxLoader;
            gfxLoader.SetLog(Ptr<GFx::Log>(*new GFxPlayerLog()));

            Ptr<FSCommandHandler> pcommandHandler = *new OurFSCommandHandler;
            gfxLoader.SetFSCommandHandler(pcommandHandler);

            Ptr<ExternalInterface> pEIHandler = *new OurExternalInterfaceHandler;
            gfxLoader.SetExternalInterface(pEIHandler );

            Ptr<FileOpener> pfileOpener = *new FileOpener;
            gfxLoader.SetFileOpener(pfileOpener);

            Ptr<FontProviderWin32> fontProvider = *new FontProviderWin32(::GetDC(0));
            gfxLoader.SetFontProvider(fontProvider);

            Ptr<ASSupport> pASSupport = *new GFx::AS3Support();
             gfxLoader.SetAS3Support(pASSupport);
                Ptr<ASSupport> pAS2Support = *new GFx::AS2Support();
             gfxLoader.SetAS2Support(pAS2Support);


            if(!(pMovieDef = *gfxLoader.CreateMovie(pfilename, Loader::LoadWaitFrame1)))
                qDebug() << "error no instance";

            pMovie = *pMovieDef->CreateInstance(true, 0);
            pMovie->SetMouseCursorCount(1);
            hMovieDisplay = pMovie->GetDisplayHandle();

            pRenderHAL = *new Render::GL::HAL();
            if (!(pRenderer = *new Render::Renderer2D(pRenderHAL.GetPtr())))
                qDebug() << "error no render";

            pRenderHAL->SetDependentVideoMode();

            pMovie->SetViewport(this->width(), this->height(), 0,0, this->width(), this->height());
            MovieLastTime = timeGetTime();
            pMovie->SetBackgroundAlpha(0.0f);
            pMovie->Advance(0.0f, 0, true);
        }


}

void Widget::AdvanceRenderGfx()
{
    // Set Wireframe
           glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

           utime   = timeGetTime();
           delta   = ((float)(utime - MovieLastTime)) / 1000.0f;
           MovieLastTime = utime;
           pMovie->Advance(delta);
           pRenderer->BeginFrame();

           if (hMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
           {

               pRenderer->Display(hMovieDisplay);
           }

           pRenderer->EndFrame();
}

Ptr<Movie> Widget::returnmovies()
{
    if(pMovie)
            {
                 return pMovie;
        }
}


