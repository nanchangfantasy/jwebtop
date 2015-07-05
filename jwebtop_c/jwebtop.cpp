// dllmain.cpp : 定义 DLL 应用程序的入口点。
// #include "stdafx.h"
#include "jni_jdk1_6_24\jni.h"
#include <iostream>
#include "org_jwebtop_JWebTopNative.h"
#include "jwebtop_brige.h"
#include "javautils.h"
#include "transparent_wnd.h"

typedef jboolean(JNICALL *GETAWT)(JNIEnv*, JAWT*);
typedef BOOL(WINAPI *lpfnSetLayeredWindowAttributes)(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);

using namespace std;

//extern TransparentWnd* pTransparentBrowser1;
HINSTANCE g_hIntance;

JavaVM* g_jvm;// 保存全局的虚拟机环境
jclass g_nativeClass;// 记录全局的本地类变量：com.toone.util.natives.NativeMethods
jmethodID g_invokeByJS;// 监视设备时的回调方法
long g_parentWin;// 全局父窗口

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved){
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
// 用于回调java程序的方法（定义于jwebtop_brige.h）
CefString invokeJavaMethod(CefString json){
	JNIEnv *env;
	if (g_jvm->AttachCurrentThread((void **)&env, NULL) < 0) return CefString();
	jstring sss = env->NewStringUTF(json.ToString().c_str());
	jstring str = (jstring)env->CallStaticObjectMethod(g_nativeClass, g_invokeByJS,sss);
	env->DeleteLocalRef(sss);
	// char * tmp = jstringToWindows(env, str);	
	CefString result = CefString(env->GetStringUTFChars(str, false));
	env->DeleteLocalRef(str);
	// delete tmp;
	return result;
}

// jni方法：创建浏览器
JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nCreateJWebTop
(JNIEnv * env, jclass nativeClass, jstring appfile, jlong parentWin){
	CefString result = CefString(env->GetStringUTFChars(appfile, false));
	g_parentWin = parentWin;
	if (g_invokeByJS == NULL){// 第一次被java端调用
		env->GetJavaVM(&g_jvm);// 获取当前的虚拟机环境并保存下来
		g_nativeClass = (jclass)(env->NewGlobalRef(nativeClass));// 将一个对象设置为全局对象，此处将nativeClasss设置为全局对象
		g_invokeByJS = env->GetStaticMethodID(g_nativeClass, "invokeByJS", "(Ljava/lang/String;)Ljava/lang/String;");// 取出要调用的方法
		wWinMain(NULL, 0, LPTSTR(result.ToWString().c_str()), 1);// 创建浏览器(创建过程中需要回调java，以便传递创建后的浏览器句柄到java端
	}
	else{
		// 这样再次创建浏览器窗口不行，难道是在不同线程的原因？？用js执行RunApp反而可以
		//TransparentWnd* win = new TransparentWnd();
		//CefString appName("D:\\study\\git\\repository\\webtop_new\\Release\\demo\\music\\index.app");
		//win->RunAppIn(appName, "", pTransparentBrowser1->GetUrl());
	}
//	delete buffer;
}

// jni方法：执行脚本
JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nExecuteJs
(JNIEnv * env, jclass, jlong browserHWnd, jstring json){
	string js;
	// js.clear();	// 可以考虑讲js作为一个全局变量，每次使用前/后都clear一下，这样效率是否更高？
	js = "invokeByJava(";
	const char * tmp = env->GetStringUTFChars(json, false);
	js += tmp;
	env->ReleaseStringUTFChars(json, tmp);
	js += ")";
	TransparentWnd* winHandler = (TransparentWnd*)static_cast<long>(browserHWnd);
	winHandler->ExecJS(js);
}


// jni方法：设置窗口大小
JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetSize
(JNIEnv * env, jclass, jlong browserHWnd, jint w, jint h){
	TransparentWnd* winHandler = (TransparentWnd*)static_cast<long>(browserHWnd);
	if (winHandler->width == w&&winHandler->height == h)return;
	winHandler->SetSize(w, h);
}

// jni方法：设置窗口位置
JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetLocation
(JNIEnv * env, jclass, jlong browserHWnd, jint x, jint y){
	TransparentWnd* winHandler = (TransparentWnd*)static_cast<long>(browserHWnd);
	if (winHandler->x == x&&winHandler->y == y)return;
	winHandler->Move(x, y);
}

// jni方法：设置窗口位置和大小
JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetBound
(JNIEnv *, jclass, jlong browserHWnd, jint x, jint y, int w, int h){
	TransparentWnd* winHandler = (TransparentWnd*)static_cast<long>(browserHWnd);
	if (winHandler->x == x&&winHandler->y == y)return;
	winHandler->SetBound(x, y, w, h);
}