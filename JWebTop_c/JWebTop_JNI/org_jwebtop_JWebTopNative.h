/* DO NOT EDIT THIS FILE - it is machine generated */
#include "jni_jdk1_6_24\jni.h"
#include "jni_jdk1_6_24\jni_md.h"
#include "jni_jdk1_6_24\jawt_md.h"
/* Header for class org_jwebtop_JWebTopNative */

#ifndef _Included_org_jwebtop_JWebTopNative
#define _Included_org_jwebtop_JWebTopNative
#ifdef __cplusplus

extern "C" {
#endif

	// dll入口函数
	BOOL APIENTRY DllMain(HMODULE hModule, DWORD  dwReason, LPVOID lpReserved);
	/*
	 * 对应org.jwebtop.JWebTopNative类的nCreateJWebTop方法
	 * 该方法用于创建一个浏览器窗口
	 * processPath 待执行的JWebTop.exe的全路径。比如d:\c\JWebTop.exe，当然JWebTop可以命名为其他名字。
	 * configFile  此配置文件用于启动JWebTop进程（但，不立刻创建浏览器窗口，即使指定了url参数）
	 * parentWin   创建的浏览器的父窗口是哪个
	 */
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nCreateJWebTop
		(JNIEnv *, jclass, jstring processPath, jstring configFile);

	/*
	* 对应org.jwebtop.JWebTopNative类的nCreateBrowser方法
	* 该方法用于创建一个浏览器窗口
	* appFile    浏览器根据此配置文件进行初始化
	* parentWin  创建的浏览器的父窗口是哪个
	*
	* return 返回创建的浏览器窗口的句柄
	*/
	JNIEXPORT jlong JNICALL Java_org_jwebtop_JWebTopNative_nCreateBrowser
		(JNIEnv *, jclass, jstring appFile, jlong parentWin
		// 以下参数会替换appfile中的相应参数
		, jstring url       // 要打开的链接地址
		, jstring title     // 窗口名称
		, jstring icon      // 窗口图标
		, jint x, jint y    // 窗口左上角坐标,当值为-1时不启用此变量		 
		, jint w, jint h    // 窗口的宽、高，当值为-1时不启用此变量		
		);
   /*
	* 对应org.jwebtop.JWebTopNative类的nCloseBrowser方法
	* 该方法用于关闭一个浏览器窗口
	* browserHWnd  浏览器窗口句柄
	*/
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nCloseBrowser
		(JNIEnv * env, jclass, jlong browserHWnd);
	/*
	 * 下面四个方法用于执行浏览器脚本
	 */
	JNIEXPORT jstring JNICALL Java_org_jwebtop_JWebTopNative_nExecuteJSWait
		(JNIEnv *, jclass, jlong browserHWnd, jstring script);
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nExecuteJSNoWait
		(JNIEnv *, jclass, jlong browserHWnd, jstring script);
	JNIEXPORT jstring JNICALL Java_org_jwebtop_JWebTopNative_nExecuteJSONWait
		(JNIEnv *, jclass, jlong browserHWnd, jstring json);
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nExecuteJSONNoWait
		(JNIEnv *, jclass, jlong browserHWnd, jstring json);

	// jni方法：设置窗口大小
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetSize
		(JNIEnv *, jclass, jlong browserHWnd, jint w, jint h);

	// jni方法：设置窗口位置
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetLocation
		(JNIEnv *, jclass, jlong browserHWnd, jint x, jint y);

	// jni方法：设置窗口位置和大小
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nSetBound
		(JNIEnv *, jclass, jlong browserHWnd, jint x, jint y, int w, int h);

	// jni方法：退出JWebTop进程
	JNIEXPORT void JNICALL Java_org_jwebtop_JWebTopNative_nExit
		(JNIEnv *, jclass);

	JNIEXPORT jintArray Java_org_jwebtop_JWebTopNative_nGetWindowClient(JNIEnv *, jclass,jlong hWnd);
#ifdef __cplusplus
}
#endif
#endif
