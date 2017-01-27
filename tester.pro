#-------------------------------------------------
#
# Project created by QtCreator 2017-01-27T14:49:55
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tester
TEMPLATE = app
CONFIG += warn_off

SOURCES +=\
        widget.cpp

HEADERS  += widget.h \
    includes.h

FORMS    += widget.ui

INCLUDEPATH +=C:\Qt\Qt5.5.1\5.5\msvc2013\\include
INCLUDEPATH +=C:\OpenSSL-Win32\include\openssl
INCLUDEPATH +=C:\Qt\scakeformlibs\dx
INCLUDEPATH +=C:\Qt\scakeformlibs\dx\Include
INCLUDEPATH +=C:\Qt\scakeformlibs\Include
INCLUDEPATH +=C:\Qt\scakeformlibs\Src
INCLUDEPATH +=C:\ProgramFiles(x86)\AwesomiumTechnologiesLLC\AwesomiumSDK\1.7.5.1\include
INCLUDEPATH +=C:\Qt\Qt5.5.1\5.5\msvc2013\include\assimp-3.2\include


LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\glut32.lib
LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\assimp-vc120-mt.lib
LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\DevIL.lib
LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\ILU.lib
LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\ILUT.lib
LIBS+=C:\Qt\Qt5.5.1\5.5\msvc2013\lib\awesomium.lib
LIBS+=C:\OpenSSL-Win32\lib\openssl.lib
LIBS+=C:\Qt\scakeformlibs\libAS3.lib
LIBS+=C:\Qt\scakeformlibs\libAS2.lib
LIBS+=C:\Qt\scakeformlibs\libgfx.lib
LIBS+=C:\Qt\scakeformlibs\libgfxrender_gl.lib
LIBS+=C:\Qt\scakeformlibs\Render_GL.lib
LIBS+=C:\Qt\scakeformlibs\libpng.lib
LIBS+=C:\Qt\scakeformlibs\zlib.lib
LIBS+=C:\Qt\scakeformlibs\libjpeg.lib

##
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3dx10.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3dx9.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\DxErr.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\dxguid.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3d9.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3d11.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3dcompiler.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\d3dx11.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\winmm.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\comctl32.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\DXUT.lib
LIBS+=C:\Qt\scakeformlibs\dx\Lib\x86\User32.lib
LIBS+="C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x86\Gdi32.lib"
